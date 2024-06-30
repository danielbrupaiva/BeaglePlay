#include "screen_1.hpp"

void Screen1::render(App::UI& app)
{
    ImGui::Begin("SCREEN1", NULL, ImGuiWindowFlags_NoDecoration );
//    ImGui::Image((void *) (intptr_t) Global::GL_textures_resources["logo"], ImVec2(1089, 720));

    if(ImGui::Button("EXIT"))
    {
        app.close();
    }

    ImGui::End();
}