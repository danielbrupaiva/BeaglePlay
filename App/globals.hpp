#pragma once

#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "image.hpp"

#include "ui.hpp"
#include "IScreen.hpp"

static Core::Logger logger{"App", spdlog::level::debug};

namespace Global {
//GLOBAL VARIABLES
static std::shared_ptr<Core::Database> db = Core::Database::create("localhost", "5432", "imgui", "1234", "project");
static Core::User system_user;
static std::map< std::string, std::unique_ptr<Image> > GL_Textures;
//FSM definition
enum class eSystemState { SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5 };
static eSystemState current_state = eSystemState::SCREEN1;
static std::vector<std::unique_ptr<IScreen>> FSM;

};//namespace Global