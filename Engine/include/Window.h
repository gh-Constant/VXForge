#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

namespace VXForge {

    class VXForgeWindow {

    public:
        VXForgeWindow(int width, int height, string name);
        ~VXForgeWindow();

    private:
        void initWindow();

        const int width; // taille en abscisse
        const int height; // taille en ordonné

        string windowName;
        GLFWwindow *window;
    };
}