#pragma once

#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "image.hpp"

#include "ui.hpp"
#include "screen_1.hpp"

static Core::Logger logger{"App",spdlog::level::debug};

namespace Global {
/*GLOBAL VARIABLES*/
static std::shared_ptr<Core::Database> db = Core::Database::create("localhost", "5432", "imgui", "1234", "project");
static Core::User system_user;
static std::map< std::string, GLuint > GL_textures_resources;
//FSM definition
#define NUM_OF_STATES 5
enum class eSystemState { SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5 };

static eSystemState current_state = eSystemState::SCREEN1;
static bool isTransition[NUM_OF_STATES];

struct SystemState_t {
    eSystemState currentState;
    bool (*transition);
    eSystemState nextState[2];
    void (*pfHandler)(App::UI& app);
    unsigned int delayTime = 0U;
};

std::vector<SystemState_t> FSM = {
    { eSystemState::SCREEN1, &isTransition[0], {eSystemState::SCREEN2, eSystemState::SCREEN5}, &Screen1::render, 0U },
    { eSystemState::SCREEN2, &isTransition[1], {eSystemState::SCREEN3, eSystemState::SCREEN1}, &Screen1::render, 0U },
    { eSystemState::SCREEN3, &isTransition[2], {eSystemState::SCREEN4, eSystemState::SCREEN2}, &Screen1::render, 0U },
    { eSystemState::SCREEN4, &isTransition[3], {eSystemState::SCREEN5, eSystemState::SCREEN3}, &Screen1::render, 0U },
    { eSystemState::SCREEN5, &isTransition[4], {eSystemState::SCREEN1, eSystemState::SCREEN4}, &Screen1::render, 0U }
};


};//namespace Global