#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen4 : public IScreen{
public:
    Screen4(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : IScreen{name, size, bg_color}
    {}

    void render(App::UI& app)
    {
        if (ImGui::Button("SCREEN4"))
        {
            app.close();
        }
    }
};
