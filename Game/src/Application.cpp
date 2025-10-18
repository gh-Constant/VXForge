#include <Application.h>
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

    };

    void drawFrame() {

    }

}
