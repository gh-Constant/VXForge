#include <Application.h>
#include <array>
#include <functional>
#include <cassert>
#include <Window.h>
#include <stdexcept>

namespace VXForgeDemo {
    Application::Application() {
        loadModels();
        createPipelineLayout();
        recreateSwapChain();
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
        vkDeviceWaitIdle(gameDevice.device());
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
            gameSwapChain->width(),
            gameSwapChain->height()
        );

        pipeline_config.renderPass = gameSwapChain->getRenderPass();
        pipeline_config.pipelineLayout = pipelineLayout;
        gamePipeline = std::make_unique<VXForge::VXForgeGraphicsPipeline>(
            gameDevice,
            SHADER_NAME,
            pipeline_config
        );
    }

    void Application::recreateSwapChain() {
        auto extent = gameWindow.getExtent();
        while (extent.width == 0 || extent.height == 0) {
            extent = gameWindow.getExtent();
            glfwWaitEvents();
        }

        vkDeviceWaitIdle(gameDevice.device());

        if (gameSwapChain == nullptr) {
            gameSwapChain = std::make_shared<VXForge::VXForgeSwapChain>(gameDevice, extent);
        } else {
            std::shared_ptr<VXForge::VXForgeSwapChain> oldSwapChain = std::move(gameSwapChain);
            gameSwapChain = std::make_shared<VXForge::VXForgeSwapChain>(gameDevice, extent, oldSwapChain);

            if (!oldSwapChain->compareSwapFormats(*gameSwapChain.get())) {
                throw std::runtime_error("Swap chain image(or depth) format has changed!");
            }
        }

        createPipeline();
    }


    void Application::createCommandBuffers() {
        commandBuffers.resize(gameSwapChain->imageCount());

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
    }

    void Application::recordCommandBuffer(int imageIndex) {
        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[imageIndex], &begin_info) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = gameSwapChain->getRenderPass();
        render_pass_info.framebuffer = gameSwapChain->getFrameBuffer(imageIndex);

        render_pass_info.renderArea.offset = {0, 0};
        render_pass_info.renderArea.extent = gameSwapChain->getSwapChainExtent();

        std::array<VkClearValue, 2> clear_values{};
        clear_values[0].color = {{0.01f, 0.01f, 0.01f, 1.0f}};
        clear_values[1].depthStencil = {1.0f, 0};
        render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
        render_pass_info.pClearValues = clear_values.data();

        vkCmdBeginRenderPass(commandBuffers[imageIndex], &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        gamePipeline->bind(commandBuffers[imageIndex]);
        gameModel->bind(commandBuffers[imageIndex]);
        gameModel->draw(commandBuffers[imageIndex]);

        vkCmdEndRenderPass(commandBuffers[imageIndex]);
        if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }
    }


    void Application::drawFrame() {
        uint32_t image_index;
        auto result = gameSwapChain->acquireNextImage(&image_index);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        recordCommandBuffer(image_index);

        result = gameSwapChain->submitCommandBuffers(&commandBuffers[image_index], &image_index);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || gameWindow.wasWindowResized()) {
            gameWindow.resetWindowResizedFlag();
            recreateSwapChain();
            return;
        }

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }
    }

    void Application::loadModels() {
        std::vector<VXForge::VXForgeModel::Vertex> vertices;
        std::function<void(int, glm::vec2, glm::vec2, glm::vec2)> sierpinski =
            [&](int depth, glm::vec2 top, glm::vec2 left, glm::vec2 right) {
            if (depth <= 0) {
                vertices.push_back({top, {1.0f, 0.0f, 0.0f}});
                vertices.push_back({left, {0.0f, 1.0f, 0.0f}});
                vertices.push_back({right, {0.0f, 0.0f, 1.0f}});
                return;
            }
            auto left_mid = (top + left) / 2.0f;
            auto right_mid = (top + right) / 2.0f;
            auto bottom_mid = (left + right) / 2.0f;
            sierpinski(depth - 1, top, left_mid, right_mid);
            sierpinski(depth - 1, left_mid, left, bottom_mid);
            sierpinski(depth - 1, right_mid, bottom_mid, right);
        };

        sierpinski(3, {0.0f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f});
        gameModel = std::make_unique<VXForge::VXForgeModel>(gameDevice, vertices);
    }

}
