#pragma once

#include <iostream>
#include "GLFW/glfw3.h"
#include "imgui.h"

namespace App{

enum class eBACKEND{OPENGL3, VULKAN};
enum class eGRAPHIC_API{GLFW3};
// Application specifications
struct Spec{
    std::string title;
    ImVec2 window_size;
    ImVec4 bg_color;
    eBACKEND backend;
    eGRAPHIC_API api;
    std::string glsl_version;
    uint8_t enable_vsync;
};

// Interface for graphics api
class GraphicApi{
public:
    virtual void shutdown() = 0;
    virtual int8_t init() = 0;
    virtual GLFWwindow * get_window() = 0;
    virtual bool is_close() = 0;
};

// Custom deleter for Window
struct WindowDeleter{
    void operator()(GLFWwindow *window) const {
        glfwDestroyWindow(window);
    };
};

} // namespace App

