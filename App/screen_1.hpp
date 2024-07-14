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

        ImGui::PushStyleColor(ImGuiCol_Button,          ImVec4(0.173f, 0.173f, 0.173f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,   ImVec4(0.271f, 0.271f, 0.271f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,    ImVec4(0.271f, 0.271f, 0.271f, 0.0f));

        static bool login_window = false;

        if(ImGui::Button("##", m_control_size)) {

            if (Global::system_user.get_is_logged()) {
                Global::current_state = Global::eSystemState::SCREEN2;
            }
            else {
                ImGui::OpenPopup("LoginWindow");
            }
        }
        ImGui::PopStyleColor(3);

        if (ImGui::BeginPopupModal("LoginWindow", NULL, ImGuiWindowFlags_NoTitleBar
                                                        | ImGuiWindowFlags_NoMove
                                                        | ImGuiWindowFlags_AlwaysAutoResize
                                                        | ImGuiWindowFlags_NoScrollbar))
        {
            {/** User icon **/
                static ImVec2 size{96.0f, 96.0f};
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - size.x) * 0.5f);
                ImGui::Image( Global::GL_Textures["profile"]->ID(), size);
            }
            {/** Close / Exit button **/
                static ImVec2 size{24.0f, 24.0f};
                ImGui::SameLine();
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 2 * size.x));
                if(ImGui::ImageButton( Global::GL_Textures["close_reject"]->ID(), size)) { ImGui::CloseCurrentPopup(); }
            }
            {/** Username InputText field **/
                ImGui::Text("Username");
                /** Username compobox **/
                static char* usernames[] = {"ADMIN", "SUPERVISOR", "USER#1", "USER#2", "USER#3"};
                static int32_t selected_user = -1;
                static ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;
                ImGui::Combo("##", &selected_user, usernames, IM_ARRAYSIZE(usernames));
            }
            {/** Password InputText field **/
                ImGui::Text("Password");
                static std::string password;
                static bool isViewPass = false;
                ImGui::InputTextWithHint("##password:", "Enter your password", &password,
                                         isViewPass ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_Password);
                ImGui::SameLine();
                if(ImGui::ImageButton( isViewPass ? Global::GL_Textures["hidden_password"]->ID() : Global::GL_Textures["view_password"]->ID(), {24.0f, 24.0f})) { isViewPass = !isViewPass; }

            }
            {/** Users states **/
                static ImVec2 size{60.0f, 60.0f};
                if(ImGui::ImageButton( Global::GL_Textures["maintenance_person"]->ID() , size)) { }
                ImGui::SameLine();
                if(ImGui::ImageButton( Global::GL_Textures["restricted_person"]->ID() , size)) { }
                ImGui::SameLine();
                if(ImGui::ImageButton( Global::GL_Textures["add_person"]->ID() , size)) { }
                ImGui::SameLine();
                if(ImGui::ImageButton( Global::GL_Textures["delete_person"]->ID() , size)) { }
                ImGui::SameLine();
                static bool user_is_logger = Global::system_user.get_is_logged();
                if(ImGui::ImageButton( user_is_logger ? Global::GL_Textures["logout"]->ID() : Global::GL_Textures["login"]->ID(), size))
                {
                    user_is_logger = !user_is_logger;
                    Global::system_user.set_is_logged(user_is_logger);
                }
            }

            ImGui::EndPopup();
        }

        static ImVec2 img_size{Global::GL_Textures["logo"]->resize(m_window_size)};
        static ImVec2 position {(ImGui::GetContentRegionAvail().x - img_size.x) * 0.5f,
                                (ImGui::GetContentRegionAvail().y - img_size.y) * 0.0f};
        ImGui::SetCursorPos(position);
        ImGui::Image(Global::GL_Textures["logo"]->ID(), img_size);

    }
};
