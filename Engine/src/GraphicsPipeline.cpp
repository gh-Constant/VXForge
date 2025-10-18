//
// Created by const on 10/17/2025.
//

#include "GraphicsPipeline.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace VXForge {

    VXForgeGraphicsPipeline::VXForgeGraphicsPipeline(
        VXForgeDevice& device,
        const std::string& shaderName,
        const PipelineConfigInfo& configInfo) : vxforgeDevice{device}, graphicsPipeline(VK_NULL_HANDLE), vertShaderModule(VK_NULL_HANDLE), fragShaderModule(VK_NULL_HANDLE) {
        createGraphicsPipeline(shaderName, configInfo);
    }

    VXForgeGraphicsPipeline::~VXForgeGraphicsPipeline() {
        vkDestroyPipeline(vxforgeDevice.device(), graphicsPipeline, nullptr);
        vkDestroyShaderModule(vxforgeDevice.device(), fragShaderModule, nullptr);
        vkDestroyShaderModule(vxforgeDevice.device(), vertShaderModule, nullptr);
    }

    std::vector<char> VXForgeGraphicsPipeline::readFile(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file " + filepath);
        }

        const size_t fileSize = file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), static_cast<std::streamsize>(fileSize));

        file.close();
        return buffer;
    }

    void VXForgeGraphicsPipeline::createGraphicsPipeline(const std::string& shaderName, const PipelineConfigInfo& configInfo) {
        const std::string vertFilepath = "../Engine/shaders/" + shaderName + ".vert.spv";
        const std::string fragFilepath = "../Engine/shaders/" + shaderName + ".frag.spv";

        std::cout << "Attempting to load vertex shader from: " << vertFilepath << '\n';
        std::cout << "Attempting to load fragment shader from: " << fragFilepath << '\n';

        const auto vertCode = readFile(vertFilepath);
        const auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex Shader Code Size " << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size " << fragCode.size() << '\n';
    }

    void VXForgeGraphicsPipeline::createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t *>(code.data());

        if (vkCreateShaderModule(vxforgeDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module!");
        }
    }

    PipelineConfigInfo VXForgeGraphicsPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};

        return configInfo;
    }





}
