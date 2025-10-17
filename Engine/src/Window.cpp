//
// Created by const on 10/17/2025.
//
#include "Window.h"

namespace VXForge {

    VXForgeWindow::VXForgeWindow(int width, int height, std::string name) : width{width}, height{height}, windowName{name} {
        initWindow();
    }

}