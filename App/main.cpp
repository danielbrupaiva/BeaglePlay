#include "logger.hpp"
#include "ui.hpp"

static const std::string TAG = "Main";

int main(int argc, char* argv[])
{
    logger.info(TAG,"APP start");

    App::Spec spec = {
        .title = "IMGUI APP OpenGL3 / GLFW3",
        .window_size = ImVec2(1280,720),
        .bg_color = ImVec4(0.15f, 0.15f, 0.15f, 0.0f),
        .backend = App::eBACKEND::OPENGL3,
        .api = App::eGRAPHIC_API::GLFW3,
        .glsl_version = "#version 130",
        .enable_vsync = 1
    };

    App::UI app{spec};
    while(!app.is_close())
    {
        app.Run([]() {
            ImGui::ShowDemoWindow();
        });
    }
    return EXIT_SUCCESS;
}