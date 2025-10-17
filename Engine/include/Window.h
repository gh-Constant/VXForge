#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace VXForge {

    class VXForgeWindow {

    public:
        VXForgeWindow(int width, int height, std::string name);
        ~VXForgeWindow();

        bool shouldClose() const { return glfwWindowShouldClose(window);}

    private:
        void initWindow();

        const int width; // taille en abscisse
        const int height; // taille en ordonné

        std::string windowName;
        GLFWwindow *window{};
    };
}