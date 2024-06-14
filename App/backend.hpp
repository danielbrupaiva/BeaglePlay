#pragma once

#include <iostream>
#include <memory>
#include <map>

#include "glfw.hpp"

namespace App
{

enum class eGraphicAPI{ GLFW }; //TODO: Implement SDL2, SDL3
enum class eBackend{ OPENGL, OPENGLES }; //TODO:: Implement VULKAN

class Backend
{
    eBackend m_type;
    std::string m_shader_version;
public:
    // GLSL version
    std::map<std::string, std::string> glsl_versions = {
        {"2.0", "#version 110"},
        {"2.1", "#version 120"},
        {"3.0", "#version 130"},
        {"3.1", "#version 140"},
        {"3.2", "#version 150"},
        {"3.3", "#version 330 core"},
        {"4.0", "#version 400 core"},
        {"4.1", "#version 410 core"},
        {"4.2", "#version 410 core"},
        {"4.3", "#version 430 core"},
        {"ES 2.0", "#version 100"},
        {"ES 3.0", "#version 300 es"}
    };

public:
    Backend(eBackend type, const std::string &version)
        : m_type{type}
    {
        if(m_type == eBackend::OPENGL || m_type == eBackend::OPENGLES)
        {
            m_shader_version = glsl_versions[version];
        }
    }

public:
    inline const std::string &get_version() const { return m_shader_version; }
    inline void set_version(const std::string &version) { m_shader_version = version; }
    inline eBackend get_type() const { return m_type; }
    inline void set_type(eBackend type) { m_type = type; }
};
}; //namespace App