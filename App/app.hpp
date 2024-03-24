#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "logger.hpp"

namespace App{

enum class eBACKEND{OPENGL3, VULKAN};
enum class eGRAPHIC_API{GLFW3, SDL3};
// Application specifications
struct Spec{
    std::string title;
    ImVec2 window_size;
    ImVec4 bg_color;
    eBACKEND backend;
    eGRAPHIC_API api;
    std::string glsl_version;
    uint8_t enable_vsync;
};

// Custom deleter for GLFWwindow
struct WindowDeleter {
    void operator()(GLFWwindow* window) const {
        glfwDestroyWindow(window);
    };
};

class GraphicApi{
public:
    virtual void shutdown() = 0;
    virtual int8_t init() = 0;
    virtual GLFWwindow * get_window() = 0;
    virtual bool is_close() = 0;
};

class GLFW : public GraphicApi {

    App::Spec& m_spec;
    std::unique_ptr<GLFWwindow,WindowDeleter> m_window;

    int8_t init() override {

        glfwSetErrorCallback(glfw_error_callback);

        if ( !glfwInit() ) { return EXIT_FAILURE; }

        set_opengl_version();

        m_window = std::unique_ptr<GLFWwindow,WindowDeleter>(glfwCreateWindow((int32_t) m_spec.window_size.x, (int32_t) m_spec.window_size.y, m_spec.title.c_str(), nullptr, nullptr), WindowDeleter());
        if( nullptr == m_window ){ return EXIT_FAILURE; }

        glfwMakeContextCurrent( m_window.get() );

        glfwSwapInterval( m_spec.enable_vsync ); // Enable vsync

        return EXIT_SUCCESS;
    };

    void shutdown() override {
        if(m_window) { glfwDestroyWindow( m_window.get() ); }
        glfwTerminate();
    };

    //TODO: Remove version hard coded
    //TODO: Add WindowHint from GLFWPP lib
    void set_opengl_version() {
        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        m_spec.glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
        // GL 3.0 + GLSL 130
        m_spec.glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
    };

    //TODO: Add Error handler from GLFWPP lib
    static void glfw_error_callback(int error, const char* description){

        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    };


public:
    ~GLFW(){ shutdown();}
    explicit GLFW(App::Spec& spec) : m_spec{spec}, m_window{nullptr} { init(); };
    // Prevent copying
    GLFW(const GLFW &) = delete;
    GLFW &operator=(const GLFW &) = delete;

    GLFWwindow* get_window() override { return m_window.get(); }
    bool is_close() override{ return glfwWindowShouldClose( m_window.get() );};
};

class IMGUI{

    App::Spec& m_spec;
    std::unique_ptr<App::GraphicApi> m_api;

public:
    ~IMGUI() { shutdown(); };
    explicit IMGUI(App::Spec& spec) : m_spec{spec}, m_api{std::make_unique<App::GLFW>(m_spec)} { PRINT(std::to_string(init())); };
    // Prevent copying
    IMGUI(const IMGUI &) = delete;
    IMGUI &operator=(const IMGUI &) = delete;
    // Render method
    template<typename Func>
    void render(Func&& Render) {
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
    /*Getter and Setters*/
    inline bool is_close() const { return m_api->is_close(); }

private:
    int8_t init()
    {
        if(!m_api)
            return EXIT_FAILURE;

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        set_style();

        setup_render_backend();

        return EXIT_SUCCESS;
    };

    void shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };
    void set_style()
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
        ImGui_ImplGlfw_InitForOpenGL( m_api->get_window(), true );
        ImGui_ImplOpenGL3_Init( m_spec.glsl_version.c_str() );
        return EXIT_SUCCESS;
    }
};
} // namespace App

