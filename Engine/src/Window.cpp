// Created by const on 10/17/2025.
//

#include <Window.h>

#include <utility>

namespace VXForge {

    //TODO: Revoir un peu ce que std::move est et quand mettre std::string& ou std::string

    VXForgeWindow::VXForgeWindow(const int width, const int height, std::string name) : width{width}, height{height}, windowName{std::move(name)} {
        initWindow();
    }

    VXForgeWindow::~VXForgeWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }


    void VXForgeWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // NO_API = disable openGL
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // Disable auto resizable windows

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr); // monitor = fullscreen, share : openGl(null)
    }


}