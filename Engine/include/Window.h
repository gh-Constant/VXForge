#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace VXForge {

    class VXForgeWindow {

    public:
        VXForgeWindow(int width, int height, std::string name);
        ~VXForgeWindow();

        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

        VXForgeWindow(const VXForgeWindow &) = delete;
        VXForgeWindow &operator=(const VXForgeWindow &) = delete;

        bool shouldClose() const { return glfwWindowShouldClose(window);}
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

    private:
        void initWindow();

        const int width; // taille en abscisse
        const int height; // taille en ordonné

        std::string windowName;
        GLFWwindow *window{};
    };
}