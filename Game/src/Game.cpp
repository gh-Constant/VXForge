//
// Created by const on 10/17/2025.
//

#include <Application.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>


int main() {
    try {
        VXForgeDemo::Application Application{};
        Application.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}