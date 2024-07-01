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
        if (ImGui::Button("SCREEN1"))
        {
            app.close();
        }
    }
};
