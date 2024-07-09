#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen3 : public IScreen{
public:
    Screen3(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : IScreen{name, window_size, bg_color}
    {}

    void render(App::UI& app)
    {
//        ImVec2 control_size = ImGui::GetContentRegionAvail();
//
//        const uint8_t numbers_buttons = 6;
//
//        ImVec2 item_spacing {0.0f, 0.0f};
//        ImVec2 item_inner_spacing {0.0f, 0.0f};
//        ImVec2 frame_padding {0.0f, 0.0f};
//        float frame_rounding {6.0f};
//        float frame_border_size {0.0f};
//
//        ImVec2 button_size{(control_size.x - 2 * item_spacing.x) / numbers_buttons, (control_size.y - 2 * item_spacing.y) / 10};
//        //ImGui::SetCursorPos(ImVec2(0.0f, control_size.y - button_size.y - item_spacing.y));
//
//        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, item_spacing);
//        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, item_inner_spacing);
//        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, frame_padding);
//        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, frame_rounding);
//        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, frame_border_size);
//
//        if(ImGui::Button("BUTTON #1", button_size)){} ImGui::SameLine();
//        if(ImGui::Button("BUTTON #2", button_size)){} ImGui::SameLine();
//        if(ImGui::Button("BUTTON #3", button_size)){} ImGui::SameLine();
//        if(ImGui::Button("BUTTON #4", button_size)){} ImGui::SameLine();
//        if(ImGui::Button("BUTTON #5", button_size)){} ImGui::SameLine();
//        if(ImGui::Button("BUTTON #6", button_size)){} ImGui::SameLine();
//
//        ImGui::PopStyleVar(5);
    }
};
