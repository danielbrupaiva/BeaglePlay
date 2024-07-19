#pragma once

#include <iostream>
#include <algorithm>
#include <vector>

#include "ui.hpp"
#include "IScreen.hpp"

class Screen2 : public IScreen{
    std::vector<Button> buttons ;
public:
    Screen2(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : IScreen{name, window_size, bg_color}
    {
        buttons = {
            /**Operation buttons **/
            {1, "BUTTON#1", false, &button_1_callback},
            {2, "BUTTON#2", false, &button_2_callback},
            {3, "BUTTON#3", false, &button_3_callback},
            {4, "BUTTON#4", false, &button_4_callback},
            {5, "BUTTON#5", false, &button_5_callback},
            {6, "BUTTON#6", false, &button_6_callback}
        };
    }

    void render(App::UI& app) override
    {
        {/**Operation buttons **/
            static ImVec2 size{ (ImGui::GetWindowWidth() - 2 * ImGui::GetStyle().FramePadding.x - (float)(buttons.size() - 1) * ImGui::GetStyle().ItemSpacing.x ) / (float)buttons.size(),
                                ImGui::GetWindowHeight() * 0.12f};
            ImGui::SetCursorPosY(ImGui::GetWindowHeight() - size.y - ImGui::GetStyle().FramePadding.y);

            std::for_each(buttons.begin(), buttons.end(), [&](auto& button){
                if(ImGui::Button(button.label.c_str(), size)) {
                    TOGGLE(button.state);
                    button.callback();
                }
                if(button.state)
                {   // Calculate position for the line and text
                    ImVec2 pos = ImGui::GetItemRectMin();
                    static float lineThickness = 8.0f;
                    ImVec2 lineStart = ImVec2(pos.x + 2 * ImGui::GetStyle().FramePadding.x, pos.y + 2 * ImGui::GetStyle().FramePadding.y);
                    ImVec2 lineEnd = ImVec2(pos.x + size.x - 2 * ImGui::GetStyle().FramePadding.x, pos.y + 2 * ImGui::GetStyle().FramePadding.y);
                    ImGui::GetWindowDrawList()->AddLine(lineStart, lineEnd, IM_COL32(0, 204, 0, 255), lineThickness);
                }
                if(button.id != buttons.end()->id){
                    ImGui::SameLine();
                }
            });
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