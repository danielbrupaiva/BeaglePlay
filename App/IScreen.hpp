#pragma once

#include <iostream>
#include "ui.hpp"

class IScreen{
protected:
    struct Button{
        uint32_t id;
        std::string label;
        bool state = false;
        std::function<void()> callback = nullptr;
        ImVec2 size{0,0};
        ImVec2 position{0,0};
        Image* image = nullptr;
    };
    ImVec2 m_window_size;
    ImVec4 m_bg_color;
    std::string m_name;
    ImVec2 m_control_size;
public:
    explicit IScreen(std::string_view name, const ImVec2 &window_size, const ImVec4 &bg_color)
        : m_name{name}, m_window_size{window_size}, m_bg_color{bg_color}
    {}
    virtual void render(App::UI& app) = 0;

    static void drawCircularGauge(const ImVec2& position, const float &radius, const float &thickness, const float &value, const float value_max, float start_angle, float final_angle, const int num_segments, const ImVec4& color)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
        {
            return;
        }

        final_angle = ImClamp<float>( final_angle, 0.0f, 2.0f * IM_PI);
        // Background
        window->DrawList->PathArcTo(position, radius, start_angle, final_angle, num_segments );
        window->DrawList->PathStroke(ImGui::GetColorU32(ImGuiCol_FrameBg), false, thickness);
        // Calculate start and end points of the arc
        ImVec2 p0(position.x + radius * cosf(start_angle), position.y + radius * sinf(start_angle));
        ImVec2 p1(position.x + radius * cosf(final_angle), position.y + radius * sinf(final_angle));
        // Draw rounded ends
        window->DrawList->AddCircleFilled(p0, thickness * 0.5f, ImGui::GetColorU32(ImGuiCol_FrameBg));
        window->DrawList->AddCircleFilled(p1, thickness * 0.5f, ImGui::GetColorU32(ImGuiCol_FrameBg));
        // Gauge arc
        float calc_angle = start_angle + (value / value_max ) * (final_angle - start_angle);
        calc_angle = ImClamp<float>(calc_angle, 0, value_max);
        // Calculate start and end points of the arc
        ImVec2 p2(position.x + radius * cosf(start_angle) , position.y + radius * sinf(start_angle));
        ImVec2 p3(position.x + radius * cosf(calc_angle) , position.y + radius * sinf(calc_angle));
        // Draw rounded ends
        window->DrawList->AddCircleFilled(p2, thickness * 0.5f, ImGui::GetColorU32(color));
        window->DrawList->AddCircleFilled(p3, thickness * 0.5f, ImGui::GetColorU32(color));
        //
        window->DrawList->PathClear();
        window->DrawList->PathArcTo(position, radius, start_angle, calc_angle, num_segments);
        window->DrawList->PathStroke(ImGui::GetColorU32(color), false, thickness);
        //
        std::string str_value = fmt::format("{:.0f}", value);
        ImVec2 text_size = ImGui::CalcTextSize(str_value.c_str());
        ImGui::SetCursorPos({ position.x - text_size.x * 0.5f, position.y - text_size.y * 0.5f });
        ImGui::Text("%s", str_value.c_str());
    }

    static void invDrawCircularGauge(const ImVec2& position, const float &radius, const float &thickness, const float &value, const float value_max, float start_angle, float final_angle, const int num_segments, const ImVec4& color)
    {
        ImGuiWindow* window = ImGui::GetCurrentWindow();
        if (window->SkipItems)
        {
            return;
        }
        // Background
        window->DrawList->PathArcTo(position, radius, start_angle, final_angle, num_segments );
        window->DrawList->PathStroke(ImGui::GetColorU32(ImGuiCol_FrameBg), false, thickness);
        // Calculate start and end points of the arc
        ImVec2 p0(position.x + radius * cosf(start_angle), position.y + radius * sinf(start_angle));
        ImVec2 p1(position.x + radius * cosf(final_angle), position.y + radius * sinf(final_angle));
        // Draw rounded ends
        window->DrawList->AddCircleFilled(p0, thickness * 0.5f, ImGui::GetColorU32(ImGuiCol_FrameBg));
        window->DrawList->AddCircleFilled(p1, thickness * 0.5f, ImGui::GetColorU32(ImGuiCol_FrameBg));
        // Gauge arc
        float calc_angle = start_angle + (value / value_max ) * (final_angle - start_angle);
        calc_angle = ImClamp<float>(calc_angle, 0, value_max);
        // Calculate start and end points of the arc
        ImVec2 p2(position.x + radius * cosf(start_angle) , position.y + radius * sinf(start_angle));
        ImVec2 p3(position.x + radius * cosf(calc_angle) , position.y + radius * sinf(calc_angle));
        // Draw rounded ends
        window->DrawList->AddCircleFilled(p2, thickness * 0.5f, ImGui::GetColorU32(color));
        window->DrawList->AddCircleFilled(p3, thickness * 0.5f, ImGui::GetColorU32(color));
        //
        window->DrawList->PathClear();
        window->DrawList->PathArcTo(position, radius, start_angle, calc_angle, num_segments);
        window->DrawList->PathStroke(ImGui::GetColorU32(color), false, thickness);
        //
        std::string str_value = fmt::format("{:.0f}", value);
        ImVec2 text_size = ImGui::CalcTextSize(str_value.c_str());
        ImGui::SetCursorPos({ position.x - text_size.x * 0.5f, position.y - text_size.y * 0.5f });
        ImGui::Text("%s", str_value.c_str());
    }
};