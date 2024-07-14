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

        static ImVec2 login_panel_size = ImVec2(0,480);
        ImGui::SetNextWindowSize(login_panel_size);

        if (ImGui::BeginPopupModal("LoginWindow", NULL, ImGuiWindowFlags_NoTitleBar
                                                        | ImGuiWindowFlags_NoMove
                                                        | ImGuiWindowFlags_AlwaysAutoResize
                                                        | ImGuiWindowFlags_NoScrollbar))
        {
            {/** User icon **/
                static ImVec2 size{48.0f, 48.0f};
                ImGui::SetCursorPos({ (ImGui::GetWindowWidth() - size.x) * 0.5f, ImGui::GetStyle().FramePadding.y * 5});
                ImGui::Image(Global::GL_Textures["profile"]->ID(), size);
            }
            {/** Welcome textview **/
                static std::string text = Global::system_user.get_name().empty() ? "WELCOME" : Global::system_user.get_name();
                static ImVec2 size = ImGui::CalcTextSize(text.c_str());
                ImGui::SetCursorPosX((ImGui::GetWindowWidth() - size.x) * 0.5f);
                ImGui::Text("%s", text.c_str());
            }
            {/** Username textview **/
                static std::string text = Global::system_user.get_name();
                ImGui::Text("%s", text.c_str());
            }
            {/** Username InputText field **/
                ImGui::Text("Username");
                static std::string username;
                username.reserve(64);
                ImGui::InputTextWithHint("##username", "Enter your username", username.data(), username.capacity() + 1,
                                         ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank);
            }
            {/** Password InputText field **/
                ImGui::Text("Password");
                static std::string password;
                password.reserve(64);
                static bool isViewPass = false;
                ImGui::InputTextWithHint("##password:", "Enter your password", password.data(), password.capacity() + 1,
                                         isViewPass ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_Password);
                ImGui::SameLine();
                if(ImGui::ImageButton( isViewPass ? Global::GL_Textures["hidden_black_password"]->ID() : Global::GL_Textures["view_black_password"]->ID(), {24.0f, 24.0f})) { isViewPass = !isViewPass; }

            }
            {/** Login | Logout button **/
                if(ImGui::Button(Global::system_user.get_is_logged() ? "LOGOUT" : "LOGIN", {-1.0f, 0}))
                {
                    Global::system_user.set_is_logged(true);
                    ImGui::CloseCurrentPopup();
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
