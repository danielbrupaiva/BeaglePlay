#pragma once

#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "modbus.hpp"
#include "image.hpp"

#include "ui.hpp"
#include "IScreen.hpp"

// Macro for maximum of two values
#define MAX(x, y) ((x) > (y) ? (x) : (y))
// Macro for minimum of two values
#define MIN(x, y) ((x) < (y) ? (x) : (y))
// Macro for average of two values
#define AVG(x, y) (((x) + (y)) / 2)

#define TOGGLE(var) (var = ! var)

namespace Global {
//GLOBAL VARIABLES
static std::shared_ptr<Core::Database> db = Core::Database::create("localhost", "5432", "imgui", "1234", "project");
static Core::User system_user;
static std::map< std::string, std::unique_ptr<Image> > GL_Textures;
//FSM definition
enum class eSystemState { SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5 };
static eSystemState current_state = eSystemState::SCREEN2;
static std::vector<std::unique_ptr<IScreen>> FSM;
//PLC Modbus
static Modbus plc{"127.0.0.1", 1502};
};//namespace Global