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
        m_control_size = ImGui::GetContentRegionAvail();

        ImVec2 panel_size{ 540.0f, 650.0f };
        ImVec2 position{ 100, (m_window_size.y - panel_size.y) * 0.5f };
        ImGui::SetCursorPos(position);
        ImGui::GetWindowDrawList()->AddRectFilled( position,
                                                   ImVec2(position.x + panel_size.x,
                                                          position.y + panel_size.y),
                                                   IM_COL32(0xC4,0xC4,0xC4,0xFF), 12.0f);
        ImVec2 profile_icon_size{48.0f, 48.0f};
        position = ImVec2((position.x + panel_size.x + profile_icon_size.x) * 0.5, position.y + 30 );
        ImGui::SetCursorPos(position);
        ImGui::Image(Global::GL_Textures["profile"]->ID(), profile_icon_size);


        position = ImVec2(position.x, position.y + 48);
        ImGui::SetCursorPos(position);
        //aumentar a fonte
        ImGui::SetWindowFontScale(2.0);
        //mudar a cor
        ImGui::TextColored(ImVec4(0.109f, 0.109f, 0.109f, 1.0f), "WELCOME");



        ImGui::PushID(1);
        {
            ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0.173f, 0.173f, 0.173f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   ImVec4(0.271f, 0.271f, 0.271f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0.271f, 0.271f, 0.271f, 0.0f));

            static ImVec2 img_size{Global::GL_Textures["logo"]->ratio() * m_control_size.y * 0.6f, m_control_size.y * 0.6f };
            set_position(m_window_size, m_control_size, img_size, ImVec2(1.0f, 0.5f));
            if(ImGui::ImageButton(Global::GL_Textures["logo"]->ID(), img_size)){ Global::current_state = Global::eSystemState::SCREEN1;}

            ImGui::PopStyleColor(3);
        }ImGui::PopID();

    }
};