#pragma once

#include <iostream>
#include "ui.hpp"
#include "IScreen.hpp"

class Screen1 : public IScreen{
public:
    Screen1(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : IScreen{name, window_size, bg_color}
    {}

    void render(App::UI& app) override
    {
        m_control_size = ImGui::GetContentRegionAvail();
        ImGui::PushID(1);
        {
            ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0.173f, 0.173f, 0.173f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   ImVec4(0.271f, 0.271f, 0.271f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0.271f, 0.271f, 0.271f, 0.0f));

            if(ImGui::Button("##", m_control_size)) { Global::current_state = Global::eSystemState::SCREEN2; }

            ImGui::PopStyleColor(3);
        }ImGui::PopID();

        static ImVec2 img_size{Global::GL_Textures["logo"]->resize(m_control_size)};
        set_position(m_window_size, m_control_size, img_size, ImVec2(0.5f, 0.0f));
        ImGui::Image(Global::GL_Textures["logo"]->ID(), img_size);
    }
};
