//
// Created by const on 10/19/2025.
//
#pragma once
#ifndef VXFORGE_MODEL_H
#define VXFORGE_MODEL_H
#include <Device.h>

#define GLM_FORCE_RADIANS
#define GLM_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace VXForge {
    class VXForgeModel {
    public:
        struct Vertex {
            glm::vec2 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        VXForgeModel(VXForgeDevice &device, std::vector<Vertex> &vertices);
        ~VXForgeModel();

        VXForgeModel(const VXForgeModel &) = delete;
        VXForgeModel &operator=(const VXForgeModel &) = delete;

        void bind(VkCommandBuffer commandBuffer);
        void draw(VkCommandBuffer commandBuffer);

    private:

        void createVertexBuffers(const std::vector<Vertex> &vertices);

        VXForgeDevice& device;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}


#endif //VXFORGE_MODEL_H