//
// Created by daniel on 6/23/24.
//

#pragma once

#include <iostream>
#include "imgui.h"

struct IScreen{
private:
    std::string m_name;
    ImVec2 m_size;
    ImVec4 m_bg_color;
public:
    IScreen(const std::string_view mName, const ImVec2 &mSize, const ImVec4 &mBgColor)
        : m_name(mName), m_size(mSize), m_bg_color(mBgColor)
    {}
    virtual void render() = 0;
};
