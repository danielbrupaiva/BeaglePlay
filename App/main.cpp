#include "app.hpp"

int main(int argc, char* argv[])
{
    const static std::string TAG = "Main";
    logger.info(TAG,"APP start");
    Application::UI app{ImVec2(1280, 720), "ImGUI APP", Application::UI::BACKEND::SDL3};

    // Start backend
    bool show_demo_window = true;
    logger.info(TAG,"Do-While");
    do
    { // IMGUI code
        app.begin();
        {
            Global::StateMachine[static_cast<int>(Global::current_state)].pfHandler(app);
            //ImGui::ShowDemoWindow(&show_demo_window);
        }
        app.render();

    } while (!app.get_is_app_done());

    logger.info(TAG,"APP stop");


    return 0;
}
