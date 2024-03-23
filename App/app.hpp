#pragma once

#include <iostream>
#include <cstdio>
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
struct GLFWwindowDeleter {
    void operator()(GLFWwindow* window) const {
        glfwDestroyWindow(window);
    }
};

class IGraphicApi{
    virtual error_t shutdown() = 0;
    virtual error_t init(App::Spec& spec) = 0;
    virtual std::unique_ptr<GLFWwindow,GLFWwindowDeleter> &window() = 0;
};

//TODO: Create interfaces to extend backend api classes
class GLFW : IGraphicApi {
    App::Spec& m_spec;
    static std::unique_ptr<GLFWwindow,GLFWwindowDeleter> m_window;
    //TODO: Add Error handler from GLFWPP lib
    static void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }
    //TODO: Remove version hard coded
    //TODO: Add WindowHint from GLFWPP lib
    static void set_version(App::Spec& spec)
    {
        // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
        // GL ES 2.0 + GLSL 100
        spec.glsl_version = "#version 100";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
        // GL 3.0 + GLSL 130
        spec.glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif
    };

    static std::unique_ptr<GLFWwindow,GLFWwindowDeleter> create_window(App::Spec& spec){
        return std::unique_ptr<GLFWwindow,GLFWwindowDeleter>( glfwCreateWindow(spec.window_size.x, spec.window_size.y, spec.title.c_str(), nullptr, nullptr) ,GLFWwindowDeleter() );
    };

    error_t shutdown() override {
        if(m_window) { glfwDestroyWindow( m_window.get() ); }
        glfwTerminate();
        return EXIT_SUCCESS;
    };

public:
    ~GLFW() { assert( shutdown() ); }
    explicit GLFW(App::Spec& spec) : m_spec{spec} {};
    // Prevent copying
    GLFW(const GLFW &) = delete;
    GLFW &operator=(const GLFW &) = delete;

    error_t init(App::Spec& spec) override
    {

        glfwSetErrorCallback(glfw_error_callback);

        assert( glfwInit() );

        set_version( spec );

        m_window = create_window( spec );

        glfwMakeContextCurrent( m_window.get() );

        glfwSwapInterval( spec.enable_vsync ); // Enable vsync

        return EXIT_SUCCESS;
    };

    inline std::unique_ptr<GLFWwindow,GLFWwindowDeleter> &window() override { return m_window; }
    inline void set_spec(App::Spec& spec){ m_spec = spec;};
};

class IMGUI{
    App::Spec& m_spec;
    std::unique_ptr<GLFW> m_api;

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

    error_t setup_render_backend()
    {
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL( m_api->window().get(), true );
        ImGui_ImplOpenGL3_Init( m_spec.glsl_version.c_str() );
        return EXIT_SUCCESS;
    }

    error_t init()
    {
        m_api = std::make_unique<GLFW>(m_spec);
        m_api->init( m_spec );

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

    static void shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };

public:
    ~IMGUI() { shutdown(); };
    explicit IMGUI(App::Spec& spec) : m_spec{spec}{
        assert( init() );
    };
    // Prevent copying
    IMGUI(const IMGUI &) = delete;
    IMGUI &operator=(const IMGUI &) = delete;

    template<typename Func>
    void render(Func&& Render)
    {
        glfwPollEvents();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Render();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_api->window().get(), &display_w, &display_h);
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

        glfwSwapBuffers( m_api->window().get() );
    };
    /*Getter and Setters*/
    [[nodiscard]] inline bool is_close() const { return glfwWindowShouldClose( m_api->window().get() ); }
};

} // namespace App

