#pragma once

#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "image.hpp"

#include "ui.hpp"
#include "screen_1.hpp"
#include "screen_2.hpp"
#include "screen_3.hpp"
#include "screen_4.hpp"
#include "screen_5.hpp"

using namespace std;

static Core::Logger logger{"App",spdlog::level::debug};

namespace Global {
/*GLOBAL VARIABLES*/
static shared_ptr<Core::Database> db = Core::Database::create("localhost", "5432", "imgui", "1234", "project");
static Core::User system_user;
static map< string, GLuint > GL_textures_resources;
//FSM definition
#define NUM_OF_STATES 5
enum class eSystemState { SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5 };

unique_ptr<Screen1> screen1 = make_unique<Screen1>("Screen1", ImVec2(1024,720), ImVec4(0,0,0,0));
unique_ptr<Screen2> screen2 = make_unique<Screen2>("Screen2", ImVec2(1024,720), ImVec4(0,0,0,0));
unique_ptr<Screen3> screen3 = make_unique<Screen3>("Screen3", ImVec2(1024,720), ImVec4(0,0,0,0));
unique_ptr<Screen4> screen4 = make_unique<Screen4>("Screen4", ImVec2(1024,720), ImVec4(0,0,0,0));
unique_ptr<Screen5> screen5 = make_unique<Screen5>("Screen5", ImVec2(1024,720), ImVec4(0,0,0,0));

static eSystemState current_state = eSystemState::SCREEN1;
static bool isTransition[NUM_OF_STATES];

struct SystemState_t {
    eSystemState currentState;
    bool (*transition);
    eSystemState nextState[2];
    void (*pfHandler)(App::UI& app);
    unsigned int delayTime = 0U;
};

static vector<SystemState_t> FSM = {
    { eSystemState::SCREEN1, &isTransition[0], {eSystemState::SCREEN2, eSystemState::SCREEN5}, &Screen1::render, 0U },
    { eSystemState::SCREEN2, &isTransition[1], {eSystemState::SCREEN3, eSystemState::SCREEN1}, &Screen2::render, 0U },
    { eSystemState::SCREEN3, &isTransition[2], {eSystemState::SCREEN4, eSystemState::SCREEN2}, &Screen3::render, 0U },
    { eSystemState::SCREEN4, &isTransition[3], {eSystemState::SCREEN5, eSystemState::SCREEN3}, &Screen4::render, 0U },
    { eSystemState::SCREEN5, &isTransition[4], {eSystemState::SCREEN1, eSystemState::SCREEN4}, &Screen5::render, 0U }
};

};//namespace Global