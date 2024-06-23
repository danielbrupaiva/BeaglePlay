#include <iostream>
#include <thread>

#include "globals.hpp"
#include "ui.hpp"

static const std::string TAG = "Main";

int main(int argc, char* argv[])
{
    logger.info(TAG,"APP start");

    ImGui::Spec spec = {
        .title = (char*)"IMGUI APP OpenGL3 / GLFW3",
        .window_size = ImVec2(1280,720),
        .bg_color = ImVec4(0.15f, 0.15f, 0.15f, 0.0f),
        .enable_vsync = 1
    };

    App::UI app{spec, App::eBackend::OPENGLES, "ES 3.0"};
    // Load GL textures resources
    Global::GL_textures_resources.insert({"logo", App::Image::LoadTextureFromFile("./resources/logo.png")});

    while(!app.is_close())
    {
        app.Run([]() {
            Global::StateMachine[static_cast<int>(Global::current_state)].pfHandler();
            ImGui::Begin("OpenGL Texture", NULL, ImGuiWindowFlags_NoDecoration );
            ImGui::Image((void*)(intptr_t)Global::GL_textures_resources["logo"], ImVec2(1089,720));
            ImGui::End();
        });

       std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    return 0;
}