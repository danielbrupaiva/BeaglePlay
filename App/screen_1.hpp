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
//        ImVec2(1089, 720)/
        if (ImGui::ImageButton("LOGO", Global::GL_Textures["logo"]->ID(), ImVec2(1280,720) , ImVec2(0, 0), ImVec2(1, 1), m_bg_color))
        {
            Global::current_state = Global::eSystemState::SCREEN2;
        }
    }
};
