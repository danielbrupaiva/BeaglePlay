#pragma once
#include "FSM.hpp"
#include "logger.hpp"
#include "user.hpp"
#include "database.hpp"
#include "image.hpp"
static Core::Logger logger{"App",spdlog::level::debug};

/*GLOBAL VARIABLES*/
namespace Global {
    static std::shared_ptr<Core::Database> db = Core::Database::create("localhost", "5432", "imgui", "1234", "project");
    static Core::User system_user;
    static std::map< std::string, GLuint > GL_textures_resources;

};//namespace Global
