#pragma once

#include <iostream>
#include "imgui.h"
#include "ui.hpp"

struct IScreen{
private:
    std::string m_name;
    ImVec2 m_size;
    ImVec4 m_bg_color;
public:
    IScreen(const std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : m_name{name}, m_size{size}, m_bg_color{bg_color}
    {}
    void render(App::UI& app);
};
