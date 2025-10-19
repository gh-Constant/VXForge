//
// Created by const on 10/17/2025.
//

#ifndef VXFORGE_GAMEWINDOW_H
#define VXFORGE_GAMEWINDOW_H

#include <string>

#include "GraphicsPipeline.h"
#include "SwapChain.h"
#include "Window.h"
#include <memory>
#include <vector>

#include "Model.h"

namespace VXForgeDemo {
    class Application {
    public:
        static constexpr int WINDOW_WIDTH = 800;
        static constexpr int WINDOW_HEIGHT = 800;

        inline static auto WINDOW_NAME = "VXForge Demo";
        inline static auto SHADER_NAME = "simple_shader";

        Application();
        ~Application();

        Application(const Application &) = delete;
        Application &operator=(const Application &) = delete;

        void run();

    private:
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);

        VXForge::VXForgeWindow gameWindow{WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME};
        VXForge::VXForgeDevice gameDevice{gameWindow};
        std::shared_ptr<VXForge::VXForgeSwapChain> gameSwapChain;
        std::unique_ptr<VXForge::VXForgeGraphicsPipeline> gamePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<VXForge::VXForgeModel> gameModel;
    };
}

#endif //VXFORGE_GAMEWINDOW_H
