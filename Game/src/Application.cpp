#include <Application.h>
#include <array>
#include <Window.h>
#include <stdexcept>

namespace VXForgeDemo {
    Application::Application() {
        createPipelineLayout();
        createPipeline();
        createCommandBuffers();
    }

    Application::~Application() {
        vkDestroyPipelineLayout(
            gameDevice.device(),
            pipelineLayout,
            nullptr
        );
    }


    void Application::run() {
        while (!gameWindow.shouldClose()) {
            glfwPollEvents();
            drawFrame();
        }
    }

    void Application::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipeline_layout_create_info{};
        pipeline_layout_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipeline_layout_create_info.setLayoutCount = 0;
        pipeline_layout_create_info.pSetLayouts = nullptr;
        pipeline_layout_create_info.pushConstantRangeCount = 0;
        pipeline_layout_create_info.pPushConstantRanges = nullptr;

        if (vkCreatePipelineLayout(gameDevice.device(), &pipeline_layout_create_info, nullptr, &pipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    };

    void Application::createPipeline() {
        auto pipeline_config = VXForge::VXForgeGraphicsPipeline::defaultPipelineConfigInfo(
            gameSwapChain.width(),
            gameSwapChain.height()
        );

        pipeline_config.renderPass = gameSwapChain.getRenderPass();
        pipeline_config.pipelineLayout = pipelineLayout;
        gamePipeline = std::make_unique<VXForge::VXForgeGraphicsPipeline>(
            gameDevice,
            SHADER_NAME,
            pipeline_config
        );
    }

    void Application::createCommandBuffers() {
        commandBuffers.resize(gameSwapChain.imageCount());

        VkCommandBufferAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = gameDevice.getCommandPool();
        alloc_info.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

        if (vkAllocateCommandBuffers(
                gameDevice.device(),
                &alloc_info,
                commandBuffers.data()
            ) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate command buffers!");
            }

        for (int i = 0; i < commandBuffers.size(); i++) {
            VkCommandBufferBeginInfo begin_info{};
            begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

            if (vkBeginCommandBuffer(commandBuffers[i], &begin_info) != VK_SUCCESS) {
                throw std::runtime_error("failed to begin recording command buffer!");
            }

            VkRenderPassBeginInfo render_pass_info{};
            render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            render_pass_info.renderPass = gameSwapChain.getRenderPass();
            render_pass_info.framebuffer = gameSwapChain.getFrameBuffer(i);

            render_pass_info.renderArea.offset = {0, 0};
            render_pass_info.renderArea.extent = gameSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clear_values{};
            clear_values[0].color = {{0.01f, 0.01f, 0.01f, 1.0f}};
            clear_values[1].depthStencil = {1.0f, 0};
            render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
            render_pass_info.pClearValues = clear_values.data();

            vkCmdBeginRenderPass(commandBuffers[i], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

            gamePipeline->bind(commandBuffers[i]);
            vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

            vkCmdEndRenderPass(commandBuffers[i]);
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to record command buffer!");
            }
        };
    }

    void Application::drawFrame() {
        uint32_t image_index;
        auto result = gameSwapChain.acquireNextImage(&image_index);
        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = gameSwapChain.submitCommandBuffers(&commandBuffers[image_index], &image_index);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }
}
