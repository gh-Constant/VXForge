//
// Created by const on 10/17/2025.
//
#pragma once

#ifndef VXFORGE_GRAPHICSPIPELINE_H
#define VXFORGE_GRAPHICSPIPELINE_H
#include <string>
#include <vector>

#include "Device.h"

namespace VXForge {

    struct PipelineConfigInfo {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class VXForgeGraphicsPipeline {
    public:
        VXForgeGraphicsPipeline(VXForgeDevice& device, const std::string& shaderName, const PipelineConfigInfo& configInfo);
        ~VXForgeGraphicsPipeline();

        VXForgeGraphicsPipeline(const VXForgeGraphicsPipeline&) = delete;
        VXForgeGraphicsPipeline& operator=(const VXForgeGraphicsPipeline&) = delete;

        void bind(VkCommandBuffer commandBuffer) const;

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char> readFile(const std::string &filepath);

        void createGraphicsPipeline(const std::string& shaderName, const PipelineConfigInfo& config);

        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

        VXForgeDevice& vxforgeDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
}


#endif //VXFORGE_GRAPHICSPIPELINE_H