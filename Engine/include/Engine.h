#pragma once

class VulkanRenderer;

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize();
    void Update(float deltaTime);
    void Render();
    void Shutdown();
    void Run();

private:
    VulkanRenderer* renderer;
};
