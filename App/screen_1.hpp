#pragma once

#include "IScreen.hpp"

class Screen1 : public IScreen
{
public:
    Screen1(const std::string_view &name, const ImVec2 &size, const ImVec4 &bgColor)
        : IScreen(name, size, bgColor)
    {};
    static void render(App::UI& app);
};
