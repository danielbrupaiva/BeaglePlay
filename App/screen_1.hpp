//
// Created by daniel on 6/23/24.
//

#pragma once

#include "IScreen.hpp"

class Screen1 : public IScreen
{

public:
    Screen1(const std::string_view &name, const ImVec2 &size, const ImVec4 &bg_color)
        : IScreen(name, size, bg_color)
    {}
    void render() override;
};

