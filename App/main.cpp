#include <iostream>
#include <thread>

#include "globals.hpp"
#include "ui.hpp"
#include "screen_1.hpp"

static const std::string TAG = "Main";
static void debug_screen(App::UI& app);

int main(int argc, char* argv[])
{
    logger.info(TAG,"APP start");

    App::Spec spec = {
        .title = (char*)"IMGUI APP OpenGL3 / GLFW3",
        .window_size = ImVec2(1280,720),
        .bg_color = ImVec4(0.15f, 0.15f, 0.15f, 0.0f),
        .enable_vsync = 1
    };

    static App::UI app{spec, App::eBackend::OPENGLES, "ES 3.0"};
    static std::unique_ptr<IScreen> screen1 = std::make_unique<Screen1>(app, "Screen1", ImVec2(1024,720), ImVec4(0,0,0,0));
    // Load GL textures resources
    Global::GL_textures_resources.insert({"logo", App::Image::LoadTextureFromFile("./resources/logo.png")});

    while(!app.is_close())
    {
        app.Run([&]() {
            Global::FSM[static_cast<int>(Global::current_state)].pfHandler(app);
            debug_screen(app);
        });
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return EXIT_SUCCESS;
}

void debug_screen(App::UI& app){

    static bool show_demo_window = false;
    if(show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    ImGui::Begin("OpenGL Texture", NULL, ImGuiWindowFlags_NoDecoration);
    ImGui::Image((void *) (intptr_t) Global::GL_textures_resources["logo"], ImVec2(1089, 720));
    ImGui::End();


    ImGui::Begin("Debug");
    {
        if(ImGui::Button("IMGUI"))
        {
            show_demo_window = !show_demo_window;
        }
        if(ImGui::Button("SCREEN1"))
        {
            Global::current_state = Global::eSystemState::SCREEN1;
        }ImGui::SameLine();
        if(ImGui::Button("SCREEN2"))
        {
            Global::current_state = Global::eSystemState::SCREEN2;
        }ImGui::SameLine();
        if(ImGui::Button("SCREEN3"))
        {
            Global::current_state = Global::eSystemState::SCREEN3;
        }ImGui::SameLine();
        if(ImGui::Button("SCREEN4"))
        {
            Global::current_state = Global::eSystemState::SCREEN4;
        }ImGui::SameLine();
        if(ImGui::Button("SCREEN5"))
        {
            Global::current_state = Global::eSystemState::SCREEN5;
        };
        if(ImGui::Button("EXIT"))
        {
            app.close();
        }

    }ImGui::End();
}