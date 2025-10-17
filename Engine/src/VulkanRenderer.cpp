//
// Created by Constant Suchet on 17/10/2025.
//

#include "VulkanRenderer.h"
#include <iostream>
#include <stdexcept>

VulkanRenderer::VulkanRenderer() : instance(VK_NULL_HANDLE), window(nullptr) {}

VulkanRenderer::~VulkanRenderer() {
    Cleanup();
}

bool VulkanRenderer::Initialize() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VXForge";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "VXForge Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    const char* extensions[] = {
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME
    };

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = 1;
    createInfo.ppEnabledExtensionNames = extensions;
    createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        std::cerr << "Failed to create Vulkan instance!" << std::endl;
        return false;
    }

    std::cout << "Vulkan instance created successfully!" << std::endl;
    return true;
}

void VulkanRenderer::CreateWindow(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        throw std::runtime_error("Failed to create GLFW window!");
    }

    std::cout << "Window created successfully!" << std::endl;
}

void VulkanRenderer::Run() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void VulkanRenderer::Cleanup() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    if (instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
        instance = VK_NULL_HANDLE;
    }

    glfwTerminate();
}