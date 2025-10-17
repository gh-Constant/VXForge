//
// Created by const on 10/17/2025.
//

#include <GameWindow.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>


int main() {
    try {
        VXForgeDemo::GameWindow gameWindow{};
        gameWindow.start();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}