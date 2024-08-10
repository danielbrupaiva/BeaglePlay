#include <iostream>
#include <thread>

#include "globals.hpp"

#include "screen_1.hpp"
#include "screen_2.hpp"
#include "screen_3.hpp"
#include "screen_4.hpp"
#include "screen_5.hpp"

static const std::string TAG = "Main";
static void debug_screen(App::UI& app);

static void load_gl_textures_resources(std::map< std::string, std::unique_ptr<Image> >& GL_Textures) {
    //https://www.flaticon.com/br/packs/functional-ui
    GL_Textures.insert({"logo", std::make_unique<Image>("./resources/logo.png")});
    GL_Textures.insert({"profile", std::make_unique<Image>("./resources/profile.png")});
    GL_Textures.insert({"maintenance_person", std::make_unique<Image>("./resources/maintenance_person.png")});
    GL_Textures.insert({"restricted_person", std::make_unique<Image>("./resources/restricted_person.png")});
    GL_Textures.insert({"verify_person", std::make_unique<Image>("./resources/verify_person.png")});
    GL_Textures.insert({"add_person", std::make_unique<Image>("./resources/add_person.png")});
    GL_Textures.insert({"delete_person", std::make_unique<Image>("./resources/delete_person.png")});
    GL_Textures.insert({"view_password", std::make_unique<Image>("./resources/view.png")});
    GL_Textures.insert({"hidden_password", std::make_unique<Image>("./resources/hidden.png")});
    GL_Textures.insert({"login", std::make_unique<Image>("./resources/login.png")});
    GL_Textures.insert({"logout", std::make_unique<Image>("./resources/logout.png")});
    GL_Textures.insert({"hammer", std::make_unique<Image>("./resources/hammer.png")});
    GL_Textures.insert({"hammer_cristal", std::make_unique<Image>("./resources/hammer_cristal.png")});
    GL_Textures.insert({"hammer_red", std::make_unique<Image>("./resources/hammer_red.png")});
    GL_Textures.insert({"close_reject", std::make_unique<Image>("./resources/close_reject.png")});
    GL_Textures.insert({"warning", std::make_unique<Image>("./resources/warning.png")});
    GL_Textures.insert({"danger", std::make_unique<Image>("./resources/danger.png")});
}

static void set_fsm_states(std::vector<std::unique_ptr<IScreen>>& FSM, App::Spec& spec) {
    FSM.push_back(std::make_unique<Screen1>("Screen1", spec.window_size, spec.bg_color));
    FSM.push_back(std::make_unique<Screen2>("Screen2", spec.window_size, spec.bg_color));
    FSM.push_back(std::make_unique<Screen3>("Screen3", spec.window_size, spec.bg_color));
    FSM.push_back(std::make_unique<Screen4>("Screen4", spec.window_size, spec.bg_color));
    FSM.push_back(std::make_unique<Screen5>("Screen5", spec.window_size, spec.bg_color));
}

int main(int argc, char* argv[]) {
    logger.info(TAG,"APP start");

    App::Spec spec = {
        .title = (char*)"IMGUI APP OpenGL3 / GLFW3",
        .window_size = ImVec2(1280,720),
        .bg_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f),
        .enable_vsync = 1
    };
    static App::UI app{spec, App::eBackend::OPENGLES, "ES 3.0"};
    // Load GL textures resources
    load_gl_textures_resources(Global::GL_Textures);
    // Setup FSM
    set_fsm_states(Global::FSM, spec);
    // Container of threads
    std::vector<std::jthread> workers;
    // PLC data loader
    // PLC keep a live
    workers.emplace_back([&](){
        while (!app.is_close()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        app.close();
    });

    // Main thread
    while(!app.is_close()) {
        try {
            app.run([&]() {
                Global::plc.read_plc_variable(&Global::variable_list["reg0"]);
                Global::FSM[static_cast<int>(Global::current_state)]->render(app);
                debug_screen(app);
            });
        } catch (...) {
            logger.error("Main thread error");
        }
    }

    return EXIT_SUCCESS;
}

void debug_screen(App::UI& app) {
    static bool show_demo_window = false;
    if(show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

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

