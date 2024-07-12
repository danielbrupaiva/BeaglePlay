#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen2 : public IScreen{
public:
    Screen2(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : IScreen{name, window_size, bg_color}
    {}

    void render(App::UI& app) override
    {

    }
};