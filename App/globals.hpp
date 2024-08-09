#pragma once
#include "utils.hpp"
#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "modbus.hpp"
#include "image.hpp"

#include "ui.hpp"
#include "IScreen.hpp"

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
static std::map<std::string, Core::PLC::Modbus::Data> variable_list = {
    {"bit0", {Core::PLC::Modbus::Data::Type::COIL, 0U, false}},
    {"bit1", {Core::PLC::Modbus::Data::Type::COIL, 1U, false}},
    {"bit2", {Core::PLC::Modbus::Data::Type::COIL, 2U, false}},
    {"bit3", {Core::PLC::Modbus::Data::Type::COIL, 3U, false}},
    {"bit4", {Core::PLC::Modbus::Data::Type::COIL, 4U, false}},
    {"bit5", {Core::PLC::Modbus::Data::Type::COIL, 5U, false}},
    {"bit6", {Core::PLC::Modbus::Data::Type::COIL, 6U, false}},
    {"bit7", {Core::PLC::Modbus::Data::Type::COIL, 7U, false}},
    {"reg0", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 0U, 0}},
    {"reg1", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 1U, 0}},
    {"reg2", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 2U, 0}},
    {"reg3", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 3U, 0}},
    {"reg4", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 4U, 0}},
    {"reg5", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 5U, 0}},
    {"reg6", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 6U, 0}},
    {"reg7", {Core::PLC::Modbus::Data::Type::HOLDING_REGISTER, 7U, 0}},
};

Core::PLC::Modbus plc{"TM241", "127.0.0.1", 1502, 5U, variable_list};
};//namespace Global