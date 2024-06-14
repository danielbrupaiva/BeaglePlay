#pragma once

#include <memory>
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "igraphicAPI.hpp"

namespace App{

class GLFW : public IGraphicApi{
    // Custom deleter for Window
    struct WindowDeleter{
        void operator()(GLFWwindow *window) const {
            glfwDestroyWindow(window);
        };
    };

    ImGui::Spec& m_spec;
    std::unique_ptr<GLFWwindow, WindowDeleter> m_window;

    int8_t init() override;
    void shutdown() override;
    static void glfw_error_callback(int errorCode_, const char *what_);

    /*
     * ErrorHandler
     * Code from glfwpp lib at glfwpp/error.h
     * */
#define GLFWPP_ERROR_CLASS(NAME, BASE)                \
    class NAME : public BASE                          \
    {                                                 \
    public:                                           \
        explicit NAME(const char* message) noexcept : \
            BASE(message) {}                          \
                                                      \
        const char* what() const noexcept             \
        {                                             \
            return BASE::what();                      \
        }                                             \
    };

    GLFWPP_ERROR_CLASS(Error, std::runtime_error);
    GLFWPP_ERROR_CLASS(APIUnavailableError, Error);
    GLFWPP_ERROR_CLASS(VersionUnavailableError, Error);
    GLFWPP_ERROR_CLASS(PlatformError, Error);
    GLFWPP_ERROR_CLASS(FormatUnavailableError, Error);
    /*
     * WindowHints
     * Code from glfwpp lib at glfwpp/windows.h
     * */
    static constexpr int dontCare = GLFW_DONT_CARE;
    enum class ClientApi;
    enum class ContextCreationApi;
    enum class ContextRobustness;
    enum class ContextReleaseBehavior;
    enum class OpenGlProfile;

    struct WindowHints;

public:
    ~GLFW()
    {
        shutdown();
    }
    explicit GLFW(ImGui::Spec& spec): m_spec{spec}, m_window{nullptr}
    {
        init();
    }
    // Prevent copying
    GLFW(const GLFW &) = delete;
    GLFW &operator=(const GLFW &) = delete;

    inline void * get_window() { return GLFW::m_window.get(); }
    inline bool is_close() override { return glfwWindowShouldClose(m_window.get()); };
};

} //App namespace