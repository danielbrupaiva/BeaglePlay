#pragma once
#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "image.hpp"

#include "imgui.h"

static Core::Logger logger{"App",spdlog::level::debug};

extern void screen1_render();
extern void screen2_render();
extern void screen3_render();
extern void screen4_render();
extern void screen5_render();

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
    void (*pfHandler)();
    unsigned int delayTime = 0U;
};

std::vector<SystemState_t> FSM = {
    { eSystemState::SCREEN1, &isTransition[static_cast<int>(eSystemState::SCREEN1)], {eSystemState::SCREEN2, eSystemState::SCREEN5}, &screen1_render, 0U },
    { eSystemState::SCREEN2, &isTransition[static_cast<int>(eSystemState::SCREEN2)], {eSystemState::SCREEN3, eSystemState::SCREEN1}, &screen2_render, 0U },
    { eSystemState::SCREEN3, &isTransition[static_cast<int>(eSystemState::SCREEN3)], {eSystemState::SCREEN4, eSystemState::SCREEN2}, &screen3_render, 0U },
    { eSystemState::SCREEN4, &isTransition[static_cast<int>(eSystemState::SCREEN4)], {eSystemState::SCREEN5, eSystemState::SCREEN3}, &screen4_render, 0U },
    { eSystemState::SCREEN5, &isTransition[static_cast<int>(eSystemState::SCREEN5)], {eSystemState::SCREEN1, eSystemState::SCREEN4}, &screen5_render, 0U }
};


};//namespace Global