//
// Created by const on 10/17/2025.
//

#include "GraphicsPipeline.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

namespace VXForge {

    VXForgeGraphicsPipeline::VXForgeGraphicsPipeline(const std::string& shaderName) {
        createGraphicsPipeline(shaderName);
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

    void VXForgeGraphicsPipeline::createGraphicsPipeline(const std::string& shaderName) {
        const std::string vertFilepath = "../Engine/shaders/" + shaderName + ".vert.spv";
        const std::string fragFilepath = "../Engine/shaders/" + shaderName + ".frag.spv";

        std::cout << "Attempting to load vertex shader from: " << vertFilepath << '\n';
        std::cout << "Attempting to load fragment shader from: " << fragFilepath << '\n';

        const auto vertCode = readFile(vertFilepath);
        const auto fragCode = readFile(fragFilepath);

        std::cout << "Vertex Shader Code Size " << vertCode.size() << '\n';
        std::cout << "Fragment Shader Code Size " << fragCode.size() << '\n';
    }



}
