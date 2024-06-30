//
// Created by daniel on 6/23/24.
//

#pragma once

#include <iostream>
#include "imgui.h"
#include "ui.hpp"

struct IScreen{
private:
    App::UI& m_app;
    std::string m_name;
    ImVec2 m_size;
    ImVec4 m_bg_color;
public:
    IScreen(App::UI& app, const std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : m_app{app}, m_name{name}, m_size{size}, m_bg_color{bg_color}
    {}
    virtual void render(App::UI& app) = 0;
};
