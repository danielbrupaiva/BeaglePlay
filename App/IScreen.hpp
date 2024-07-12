#pragma once

#include <iostream>
#include "ui.hpp"

class IScreen{
protected:
    ImVec2 m_window_size;
    ImVec4 m_bg_color;
    std::string m_name;
    ImVec2 m_control_size;
public:
    explicit IScreen(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : m_name{name}, m_window_size{window_size}, m_bg_color{bg_color}
    {}
    virtual void render(App::UI& app) = 0;

    static void set_position(ImVec2 window_size, ImVec2 control_size, ImVec2 size, ImVec2 offset = {0.5f, 0.5f}, ImVec2 factor = {0.0f, 0.0f})
    {
        ImGui::SetCursorPos(center_position(window_size, control_size, size, offset, factor));
    }

    static ImVec2 center_position(ImVec2 window_size, ImVec2 control_size, ImVec2 size, ImVec2 offset = {0.5f, 0.5f}, ImVec2 factor = {0.0f, 0.0f})
    {
        ImVec2 position{(window_size.x - control_size.x) * factor.x + (window_size.x - size.x) * offset.x,
                        (window_size.y - control_size.y) * factor.y + (window_size.y - size.y) * offset.y};
        return position;
    }
};