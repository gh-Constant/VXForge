#include <Application.h>
#include <Engine.h>
#include <Window.h>

namespace VXForgeDemo {
    void Application::run() {
        while (!gameWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}
