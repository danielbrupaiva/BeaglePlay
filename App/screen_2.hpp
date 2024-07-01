#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

using namespace std;

class Screen2 : private IScreen{
public:
    Screen2(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : IScreen{name, size, bg_color}
    {}

    static void render(App::UI& app)
    {
        if (ImGui::Button("SCREEN2"))
        {
            app.close();
        }
    }
};
