#include "ui.hpp"

int8_t App::UI::init(){

    if(!m_api)
        return throw std::runtime_error("No API avaiable! Could not initialize IMGUI");;

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

void App::UI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
};

void App::UI::set_style()
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

int8_t App::UI::setup_render_backend()
{
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL( m_api->get_window(), true );
    ImGui_ImplOpenGL3_Init( m_spec.glsl_version.c_str() );
    return EXIT_SUCCESS;
};

App::UI::~UI()
{
    shutdown();
};

App::UI::UI(App::Spec &spec) : m_spec{spec}, m_api{std::make_unique<App::GLFW>(m_spec)}
{
    init();
}
