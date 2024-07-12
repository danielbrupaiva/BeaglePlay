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

            static bool login_window = false;

            if(ImGui::Button("##", m_control_size)) {

                if (Global::system_user.get_is_logged()) {
                    Global::current_state = Global::eSystemState::SCREEN2;
                }
                else {
                    ImGui::OpenPopup("LoginWindow");
                }
            }

            if (ImGui::BeginPopupModal("LoginWindow", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove))
            {
                {
                    ImVec2 size{48.0f, 48.0f};
                    ImVec2 position = center_position(ImGui::GetWindowSize(), ImGui::GetContentRegionAvail(), size, ImVec2(0.5f, 0.0f));
                    ImGui::SetCursorPosX(position.x);
                    ImGui::Image(Global::GL_Textures["profile"]->ID(), size);
                }
                {
                    std::string text = "WELCOME";
                    ImVec2 size = ImGui::CalcTextSize(text.c_str());
                    ImVec2 position = center_position(ImGui::GetWindowSize(), ImGui::GetContentRegionAvail(), size, ImVec2(0.5f, 0.0f));
                    ImGui::SetCursorPosX(position.x);
                    ImGui::Text("%s", text.c_str());
                }
                {
                    std::string text = Global::system_user.get_name();
                    ImVec2 size = ImGui::CalcTextSize(text.c_str());
                    ImVec2 position = center_position(ImGui::GetWindowSize(), ImGui::GetContentRegionAvail(), size, ImVec2(0.5f, 0.0f));
                    ImGui::SetCursorPosX(position.x);
                    ImGui::Text("%s", text.c_str());
                }
                {
                    /** Username InputText field **/
                    ImGui::Text("Username");
                    static std::string username;
                    ImGui::InputTextWithHint("##username", "Enter username", username.data(), sizeof(username.data()),
                                             ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_CharsNoBlank);
                }
                {/** Password InputText field **/
                    ImGui::Text("Password");
                    static std::string password;
                    static bool isViewPass = false;
                    ImGui::InputTextWithHint("##password:", "Enter password", password.data(), sizeof(password.data()),
                                             isViewPass ? ImGuiInputTextFlags_None : ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_Password);
                    ImGui::SameLine();
                    ImGui::Checkbox("View", &isViewPass);
                }
                {/** Login | Logout button **/
                    if(ImGui::Button(Global::system_user.get_is_logged() ? "Logout" : "Login")){ }
                }
                {
                    std::string text = "Close";
                    ImVec2 size = ImGui::CalcTextSize(text.c_str());
                    ImVec2 position = center_position(ImGui::GetWindowSize(), ImGui::GetContentRegionAvail(), size, ImVec2(0.5f, 0.0f));
                    ImGui::SetCursorPosX(position.x);
                    if (ImGui::Button(text.c_str())) { ImGui::CloseCurrentPopup(); }
                }

                ImGui::EndPopup();
            }

            ImGui::PopStyleColor(3);
        }ImGui::PopID();

        static ImVec2 img_size{Global::GL_Textures["logo"]->resize(m_control_size)};
        set_position(m_window_size, m_control_size, img_size, ImVec2(0.5f, 0.0f));
        ImGui::Image(Global::GL_Textures["logo"]->ID(), img_size);
    }
};
