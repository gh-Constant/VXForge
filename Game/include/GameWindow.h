//
// Created by const on 10/17/2025.
//

#ifndef VXFORGE_GAMEWINDOW_H
#define VXFORGE_GAMEWINDOW_H

#include <string>

#include "Window.h"

namespace VXForgeDemo {
    class GameWindow {
    public:
        GameWindow() : gameWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME) {}

        void start() const;

    private:
        static constexpr int WINDOW_WIDTH = 800;
        static constexpr int WINDOW_HEIGHT = 800;
        static constexpr std::string WINDOW_NAME = "VXForge Demo";

        VXForge::VXForgeWindow gameWindow;
    };
}

#endif //VXFORGE_GAMEWINDOW_H