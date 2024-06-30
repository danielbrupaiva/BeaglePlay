//
// Created by daniel on 6/23/24.
//

#pragma once

#include "IScreen.hpp"

class Screen1 : public IScreen
{
public:
    Screen1(App::UI &app, const std::string_view &name, const ImVec2 &size, const ImVec4 &bgColor)
        : IScreen(app, name, size, bgColor)
    {};
    void render(App::UI& app) override;
};

