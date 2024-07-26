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
static std::map<std::string, PLC::Modbus::Data> variable_list = {
    {"var0", {PLC::Modbus::DataType::COIL, 0, false}},
    {"var1", {PLC::Modbus::DataType::COIL, 1, false}},
    {"var2", {PLC::Modbus::DataType::COIL, 2, false}},
    {"var3", {PLC::Modbus::DataType::COIL, 3, false}},
    {"var4", {PLC::Modbus::DataType::HOLDING_REGISTER, 0, 0}},
    {"var5", {PLC::Modbus::DataType::HOLDING_REGISTER, 1, 0}},
    {"var6", {PLC::Modbus::DataType::HOLDING_REGISTER, 2, 0}},
    {"var7", {PLC::Modbus::DataType::HOLDING_REGISTER, 3, 0}},
};
static PLC::Modbus plc{"TM241", "127.0.0.1", 1502, variable_list};
};//namespace Global