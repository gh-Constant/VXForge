#include "Engine.h"
#include "VulkanRenderer.h"
#include <iostream>

Engine::Engine() : renderer(nullptr) {}

Engine::~Engine() {
    delete renderer;
}

bool Engine::Initialize() {
    std::cout << "Engine initialized!\n";

    renderer = new VulkanRenderer();
    if (!renderer->Initialize()) {
        std::cerr << "Failed to initialize Vulkan renderer!" << std::endl;
        return false;
    }

    renderer->CreateWindow(800, 600, "VXForge");

    return true;
}

void Engine::Update(float deltaTime) {
    // Game loop logic will call this
}

void Engine::Render() {
    // Vulkan rendering goes here
    std::cout << "Rendering frame...\n";
}

void Engine::Run() {
    if (renderer) {
        renderer->Run();
    }
}

void Engine::Shutdown() {
    if (renderer) {
        renderer->Cleanup();
    }
    std::cout << "Engine shutdown!\n";
}
