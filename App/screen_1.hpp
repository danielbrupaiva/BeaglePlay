#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen1 : public IScreen{
public:
    Screen1(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : IScreen{name, size, bg_color}
    {}

    void render(App::UI& app)
    {
        ImVec2 position = ImVec2(0.0f, 0.0f);
        ImVec2 control_size = ImGui::GetContentRegionAvail();

        ImVec2 size = Global::GL_Textures["logo"]->resize();
        float x_offset = (control_size.x - size.x) * 0.5f;
        float y_offset = (control_size.y - size.y) * 0.5f;

        ImGui::SetCursorPos(ImVec2(position.x + x_offset, position.y + y_offset));
        if(ImGui::ImageButton("LOGO", Global::GL_Textures["logo"]->ID(), Global::GL_Textures["logo"]->resize())) {
            Global::current_state = Global::eSystemState::SCREEN2;
        }
    }
};
