#pragma once

#include "memory"

#include "glfw.hpp"
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace App{

class UI{
    App::Spec &m_spec;
    std::unique_ptr<App::GraphicApi> m_api;
public:
    ~UI();
    explicit UI(App::Spec &spec);
    // Prevent copying
    UI(const UI &) = delete;
    UI &operator=(const UI &) = delete;
    // Render method
    template<typename Func>
    void Run(Func&& Render);
    /*Getter and Setters*/
    inline bool is_close() const{ return m_api->is_close(); }

private:
    int8_t init();
    void shutdown();
    void set_style();
    int8_t setup_render_backend();
};

template<typename Func>
void UI::Run(Func&& Render) {
    glfwPollEvents();
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Render();
    // Rendering
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_api->get_window(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(m_spec.bg_color.x * m_spec.bg_color.w,
                 m_spec.bg_color.y * m_spec.bg_color.w,
                 m_spec.bg_color.z * m_spec.bg_color.w,
                 m_spec.bg_color.w);

    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers( m_api->get_window() );
};

}
