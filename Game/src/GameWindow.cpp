#include <GameWindow.h>
#include <Engine.h>
#include <Window.h>

namespace VXForgeDemo {
    void GameWindow::start() const {
        while (!gameWindow.shouldClose()) {
            glfwPollEvents();
        }
    }
}
