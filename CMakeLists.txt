cmake_minimum_required(VERSION 3.20)

project(VXForge)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

if(APPLE)
    set(MOLTENVK_PATH "/opt/homebrew/lib/libMoltenVK.dylib")
    if(EXISTS ${MOLTENVK_PATH})
        message(STATUS "Using MoltenVK for Vulkan on macOS")
    endif()
endif()

# Add engine as a library
add_library(Engine
        Engine/src/Engine.cpp
        Engine/src/Window.cpp
        Engine/include/GraphicsPipeline.h
        Engine/src/GraphicsPipeline.cpp
        Engine/src/Device.cpp
        Engine/include/SwapChain.h
        Engine/src/SwapChain.cpp
)

target_include_directories(Engine SYSTEM PUBLIC Engine/include Game/include) #TODO: learn what is SYSTEM (constant)
target_link_libraries(Engine PUBLIC Vulkan::Vulkan glfw)


# Add game executable
add_executable(Game
        Game/src/Application.cpp
        Game/src/Game.cpp
        Game/include/Application.h
)

target_include_directories(Game SYSTEM PUBLIC Game/include Engine/include)

# Link engine to game
target_link_libraries(Game PRIVATE Engine)
