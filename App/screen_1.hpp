#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen1 : public IScreen{
public:
    Screen1(std::string_view name, const ImVec2 &size, const ImVec4 &bg_color)
        : IScreen{name, size, bg_color}
    {}

    void render(App::UI& app)
    {
        ImVec2 control_size = ImGui::GetContentRegionAvail();
        ImGui::PushID(1);
        {
            ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0.173f, 0.173f, 0.173f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   ImVec4(0.271f, 0.271f, 0.271f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0.271f, 0.271f, 0.271f, 0.0f));

            if(ImGui::Button("##", control_size))
            {
                Global::current_state = Global::eSystemState::SCREEN2;
            }

            ImGui::PopStyleColor(3);
        }ImGui::PopID();

        ImVec2 image_size = Global::GL_Textures["logo"]->resize(control_size);
        ImVec2 position{0.0f, 0.0f};
        ImVec2 factor{0.5f, 0.5f};
        ImVec2 offset = ImVec2( (control_size.x - image_size.x) * factor.x, (control_size.y - image_size.y) * factor.y);
        ImGui::SetCursorPos(ImVec2(position.x + offset.x, position.y +offset.y));
        ImGui::Image(Global::GL_Textures["logo"]->ID(), image_size);
    }
};
