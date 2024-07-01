#pragma once

#include <iostream>
#include "ui.hpp"

class IScreen{
protected:
    ImVec2 m_size;
    ImVec4 m_bg_color;
    std::string m_name;
public:
    explicit IScreen(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : m_name{name}, m_size{size}, m_bg_color{bg_color}
    {}
    virtual void render(App::UI& app) = 0;
};