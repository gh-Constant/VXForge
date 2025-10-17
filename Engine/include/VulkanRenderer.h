//
// Created by Constant Suchet on 17/10/2025.
//

#ifndef UNTITLED_VULKANRENDERER_H
#define UNTITLED_VULKANRENDERER_H

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>
#include <array>

const int MAX_FRAMES_IN_FLIGHT = 2;

struct Vertex {
    float x, y, z;
    float r, g, b;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, x);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, r);

        return attributeDescriptions;
    }
};

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class VulkanRenderer {
public:
    VulkanRenderer();
    ~VulkanRenderer();

    bool Initialize();
    void Cleanup();
    void CreateWindow(int width, int height, const char* title);
    void Run();
    void DrawFrame();

private:
    bool CreateInstance();
    bool CreateSurface();
    bool PickPhysicalDevice();
    bool CreateLogicalDevice();
    bool CreateSwapchain();
    bool CreateImageViews();
    bool CreateRenderPass();
    bool CreateGraphicsPipeline();
    bool CreateFramebuffers();
    bool CreateCommandPool();
    bool CreateVertexBuffer();
    bool CreateIndexBuffer();
    bool CreateCommandBuffers();
    bool CreateSyncObjects();

    bool CheckValidationLayerSupport();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkShaderModule CreateShaderModule(const std::vector<char>& code);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void RecreateSwapchain();
    void CleanupSwapchain();
    std::vector<char> ReadFile(const std::string& filename);
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSwapchainKHR swapchain;
    std::vector<VkImage> swapchainImages;
    VkFormat swapchainImageFormat;
    VkExtent2D swapchainExtent;
    std::vector<VkImageView> swapchainImageViews;
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    std::vector<VkFramebuffer> swapchainFramebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    GLFWwindow* window;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
};


#endif //UNTITLED_VULKANRENDERER_H