#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen5 : public IScreen{
public:
    Screen5(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : IScreen{name, size, bg_color}
    {}

    void render(App::UI& app)
    {
        if (ImGui::Button("SCREEN5"))
        {
            app.close();
        }
    }
};
