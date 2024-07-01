#pragma once

#include <iostream>
#include "imgui.h"

using namespace std;

class IScreen{
private:
    ImVec2 m_size;
    ImVec4 m_bg_color;
    string m_name;
public:
    IScreen(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : m_name{name}, m_size{size}, m_bg_color{bg_color}
    {}
};