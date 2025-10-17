//
// Created by const on 10/17/2025.
//

#ifndef VXFORGE_GAMEWINDOW_H
#define VXFORGE_GAMEWINDOW_H

#include <string>

#include "GraphicsPipeline.h"
#include "Window.h"

namespace VXForgeDemo {
    class Application {
    public:
        static constexpr int WINDOW_WIDTH = 800;
        static constexpr int WINDOW_HEIGHT = 800;

        inline static auto WINDOW_NAME = "VXForge Demo";
        inline static auto SHADER_NAME = "simple_shader";

        void run();

    private:
        VXForge::VXForgeWindow gameWindow{WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME};
        VXForge::VXForgeGraphicsPipeline gameGraphicsPipeline{SHADER_NAME};
    };
}

#endif //VXFORGE_GAMEWINDOW_H
