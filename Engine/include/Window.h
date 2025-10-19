#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>

namespace VXForge {

    class VXForgeWindow {

    public:
        VXForgeWindow(int width, int height, std::string name);
        ~VXForgeWindow();

        VXForgeWindow(const VXForgeWindow &) = delete;
        VXForgeWindow &operator=(const VXForgeWindow &) = delete;

        bool shouldClose() const { return glfwWindowShouldClose(window);}
        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

        bool wasWindowResized() const { return framebufferResized; }
        void resetWindowResizedFlag() { framebufferResized = false; }

        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

    private:

        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

        void initWindow();

        int width; // taille en abscisse
        int height; // taille en ordonné
        bool framebufferResized = false;

        std::string windowName;
        GLFWwindow *window{};
    };
}