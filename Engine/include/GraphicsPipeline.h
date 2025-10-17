//
// Created by const on 10/17/2025.
//
#pragma once

#ifndef VXFORGE_GRAPHICSPIPELINE_H
#define VXFORGE_GRAPHICSPIPELINE_H
#include <string>
#include <vector>

namespace VXForge {
    class VXForgeGraphicsPipeline {
    public:
        VXForgeGraphicsPipeline(const std::string& shaderName);

    private:
        static std::vector<char> readFile(const std::string &filepath);

        void createGraphicsPipeline(const std::string& shaderName);
    };
}


#endif //VXFORGE_GRAPHICSPIPELINE_H