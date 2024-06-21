#pragma once

#include <memory>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "backend.hpp"

namespace App{

class UI{
    ImGui::Spec& m_spec;
    std::unique_ptr<GLFW> m_api;
    std::unique_ptr<Backend> m_backend;

public:
    ~UI(){
        shutdown();
    };
    explicit UI(ImGui::Spec &spec, const eBackend backend, const std::string& shader_version) :
        m_spec{spec},
        m_api{std::make_unique<GLFW>(m_spec)},
        m_backend{std::make_unique<Backend>(backend, shader_version)}
    {
        init();
    };
    // Prevent copying
    UI(const UI &) = delete;
    UI &operator=(const UI &) = delete;
    // Render method
    template<typename Func>
    void Run(Func&& Render);
    /*Getter and Setters*/
    [[nodiscard]] inline bool is_close() const{ return m_api->is_close(); }

private:
    int8_t init()
    {
        if(!m_api)
        {
            throw std::runtime_error("No API avaiable! Could not initialize IMGUI");;
            return EXIT_FAILURE;
        }

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
//    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
//    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        set_style();

        setup_render_backend();

        return EXIT_SUCCESS;
    };

    static void shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };

    static void set_style()
    {
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
    };
    int8_t setup_render_backend()
    {
        // Setup Platform/Renderer backends

        ImGui_ImplGlfw_InitForOpenGL( get_glfw_window_from_api(), true );
        ImGui_ImplOpenGL3_Init( m_backend->get_version().c_str() );

        return EXIT_SUCCESS;
    };
    [[nodiscard]] inline GLFWwindow * get_glfw_window_from_api() const { return m_api->get_window();}
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
    glfwGetFramebufferSize( get_glfw_window_from_api(), &display_w, &display_h);
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

    glfwSwapBuffers( get_glfw_window_from_api() );
};

}
