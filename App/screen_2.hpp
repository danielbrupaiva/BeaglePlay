#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "ui.hpp"
#include "IScreen.hpp"

class Screen2 : public IScreen{

    std::vector<Button> buttons = {
        {1, "BUTTON#1", false, &button_1_callback},
        {2, "BUTTON#2", false, &button_2_callback},
        {3, "BUTTON#3", false, &button_3_callback},
        {4, "BUTTON#4", false, &button_4_callback},
        {5, "BUTTON#5", false, &button_5_callback},
        {6, "BUTTON#6", false, &button_6_callback}
    };

public:
    Screen2(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : IScreen{name, window_size, bg_color}
    {}

    void render(App::UI& app) override
    {
        {/**Operation buttons **/
            static const uint32_t NUM_BUTTONS = 6;
            static ImVec2 size{ (ImGui::GetWindowWidth() - 2 * ImGui::GetStyle().FramePadding.x - (NUM_BUTTONS - 1 ) * ImGui::GetStyle().ItemSpacing.x ) / (float) NUM_BUTTONS,
                                ImGui::GetWindowHeight() * 0.12f};

            ImGui::SetCursorPosY(ImGui::GetWindowHeight() - size.y - ImGui::GetStyle().FramePadding.y);
            /**Button 1**/
            static bool is_btn1_active = false;
            if(ImGui::Button("BUTTON #1", size)) {
                is_btn1_active = !is_btn1_active;
                button_1_callback();
            }
            if(is_btn1_active)
            {// Calculate position for the line and text
                static ImVec2 pos = ImGui::GetItemRectMin();
                static float lineThickness = 8.0f;
                ImVec2 lineStart = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImVec2 lineEnd = ImVec2(pos.x + size.x - ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
            }
            ImGui::SameLine();
            /**Button 2**/
            static bool is_btn2_active = false;
            if(ImGui::Button("BUTTON #2", size)) {
                is_btn2_active = !is_btn2_active;
                button_2_callback();
            }
            if(is_btn2_active)
            {// Calculate position for the line and text
                static ImVec2 pos = ImGui::GetItemRectMin();
                static float lineThickness = 8.0f;
                ImVec2 lineStart = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImVec2 lineEnd = ImVec2(pos.x + size.x - ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
            }
            ImGui::SameLine();
            /**Button 3**/
            static bool is_btn3_active = false;
            if(ImGui::Button("BUTTON #3", size)) {
                is_btn3_active = !is_btn3_active;
                button_3_callback();
            }
            if(is_btn3_active)
            {// Calculate position for the line and text
                static ImVec2 pos = ImGui::GetItemRectMin();
                static float lineThickness = 8.0f;
                ImVec2 lineStart = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImVec2 lineEnd = ImVec2(pos.x + size.x - ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
            }
            ImGui::SameLine();
            /**Button 4**/
            static bool is_btn4_active = false;
            if(ImGui::Button("BUTTON #4", size)) {
                is_btn4_active = !is_btn4_active;
                button_4_callback();
            }
            if(is_btn4_active)
            {// Calculate position for the line and text
                static ImVec2 pos = ImGui::GetItemRectMin();
                static float lineThickness = 8.0f;
                ImVec2 lineStart = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImVec2 lineEnd = ImVec2(pos.x + size.x - ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
            }
            ImGui::SameLine();
            /**Button 5**/
            static bool is_btn5_active = false;
            if(ImGui::Button("BUTTON #5", size)) {
                is_btn5_active = !is_btn5_active;
                button_5_callback();
            }
            if(is_btn5_active)
            {// Calculate position for the line and text
                static ImVec2 pos = ImGui::GetItemRectMin();
                static float lineThickness = 8.0f;
                ImVec2 lineStart = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImVec2 lineEnd = ImVec2(pos.x + size.x - ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
            }
            ImGui::SameLine();
            /**Button 6**/
            static bool is_btn6_active = false;
            if(ImGui::Button("BUTTON #6", size)) {
                is_btn6_active = !is_btn6_active;
                button_6_callback();
            }
            if(is_btn6_active)
            {// Calculate position for the line and text
                static ImVec2 pos = ImGui::GetItemRectMin();
                static float lineThickness = 8.0f;
                ImVec2 lineStart = ImVec2(pos.x + ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImVec2 lineEnd = ImVec2(pos.x + size.x - ImGui::GetStyle().FramePadding.x, pos.y + ImGui::GetStyle().FramePadding.y);
                ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
            }
        }
    }
private:
    static void button_1_callback(){ logger.debug("Button #1 callback");}
    static void button_2_callback(){ logger.debug("Button #2 callback");}
    static void button_3_callback(){ logger.debug("Button #3 callback");}
    static void button_4_callback(){ logger.debug("Button #4 callback");}
    static void button_5_callback(){ logger.debug("Button #5 callback");}
    static void button_6_callback(){ logger.debug("Button #6 callback");}
};