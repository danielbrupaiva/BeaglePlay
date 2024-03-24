#include <memory>

#include "glfw.hpp"
#include "GLFW/glfw3.h"

static const std::string TAG = "GLFW";

/*
 * WindowHints
 * Code from glfwpp lib at glfwpp/windows.h
 * */
enum class App::GLFW::ClientApi
{
    OpenGl = GLFW_OPENGL_API,
    OpenGles = GLFW_OPENGL_ES_API,
    None = GLFW_NO_API
};

enum class App::GLFW::ContextCreationApi
{
    Native = GLFW_NATIVE_CONTEXT_API,
    Egl = GLFW_EGL_CONTEXT_API,
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    OsMesa = GLFW_OSMESA_CONTEXT_API
#endif
};
enum class App::GLFW::ContextRobustness
{
    NoRobustness = GLFW_NO_ROBUSTNESS,
    NoResetNotification = GLFW_NO_RESET_NOTIFICATION,
    LoseContextOnReset = GLFW_LOSE_CONTEXT_ON_RESET
};
enum class App::GLFW::ContextReleaseBehavior
{
    Any = GLFW_ANY_RELEASE_BEHAVIOR,
    Flush = GLFW_RELEASE_BEHAVIOR_FLUSH,
    None = GLFW_RELEASE_BEHAVIOR_NONE
};
enum class App::GLFW::OpenGlProfile
{
    Any = GLFW_OPENGL_ANY_PROFILE,
    Compat = GLFW_OPENGL_COMPAT_PROFILE,
    Core = GLFW_OPENGL_CORE_PROFILE
};

struct App::GLFW::WindowHints
{
    bool resizable = true;
    bool visible = true;
    bool decorated = true;
    bool focused = true;
    bool autoIconify = true;
    bool floating = false;
    bool maximized = false;
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    bool centerCursor = true;
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    bool transparentFramebuffer = false;
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    bool focusOnShow = true;
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    bool scaleToMonitor = false;
#endif

    int redBits = 8;
    int greenBits = 8;
    int blueBits = 8;
    int alphaBits = 8;
    int depthBits = 24;
    int stencilBits = 8;
    int accumRedBits = 0;
    int accumGreenBits = 0;
    int accumBlueBits = 0;
    int accumAlphaBits = 0;

    int auxBuffers = 0;
    int samples = 0;
    int refreshRate = dontCare;
    bool stereo = false;
    bool srgbCapable = false;
    bool doubleBuffer = true;

    ClientApi clientApi = ClientApi::OpenGl;
    ContextCreationApi contextCreationApi = ContextCreationApi::Native;
    int contextVersionMajor = 1;
    int contextVersionMinor = 0;
    ContextRobustness contextRobustness = ContextRobustness::NoRobustness;
    ContextReleaseBehavior contextReleaseBehavior = ContextReleaseBehavior::Any;
    bool openglForwardCompat = false;
    bool openglDebugContext = false;
    OpenGlProfile openglProfile = OpenGlProfile::Any;

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    bool cocoaRetinaFramebuffer = true;
    const char *cocoaFrameName = "";
    bool cocoaGraphicsSwitching = false;
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    const char *x11ClassName = "";
    const char *x11InstanceName = "";
#endif

    void apply() const
    {
        glfwWindowHint(GLFW_RESIZABLE, resizable);
        glfwWindowHint(GLFW_VISIBLE, visible);
        glfwWindowHint(GLFW_DECORATED, decorated);
        glfwWindowHint(GLFW_FOCUSED, focused);
        glfwWindowHint(GLFW_AUTO_ICONIFY, autoIconify);
        glfwWindowHint(GLFW_FLOATING, floating);
        glfwWindowHint(GLFW_MAXIMIZED, maximized);
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        glfwWindowHint(GLFW_CENTER_CURSOR, centerCursor);
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, transparentFramebuffer);
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        glfwWindowHint(GLFW_FOCUS_ON_SHOW, focusOnShow);
#endif
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, scaleToMonitor);
#endif

        glfwWindowHint(GLFW_RED_BITS, redBits);
        glfwWindowHint(GLFW_GREEN_BITS, greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, blueBits);
        glfwWindowHint(GLFW_ALPHA_BITS, alphaBits);
        glfwWindowHint(GLFW_DEPTH_BITS, depthBits);
        glfwWindowHint(GLFW_STENCIL_BITS, stencilBits);
        glfwWindowHint(GLFW_ACCUM_RED_BITS, accumRedBits);
        glfwWindowHint(GLFW_ACCUM_GREEN_BITS, accumGreenBits);
        glfwWindowHint(GLFW_ACCUM_BLUE_BITS, accumBlueBits);
        glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, accumAlphaBits);

        glfwWindowHint(GLFW_AUX_BUFFERS, auxBuffers);
        glfwWindowHint(GLFW_SAMPLES, samples);
        glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
        glfwWindowHint(GLFW_STEREO, stereo);
        glfwWindowHint(GLFW_SRGB_CAPABLE, srgbCapable);
        glfwWindowHint(GLFW_DOUBLEBUFFER, doubleBuffer);

        glfwWindowHint(GLFW_CLIENT_API, static_cast<int>(clientApi));
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, static_cast<int>(contextCreationApi));
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, static_cast<int>(contextRobustness));
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, static_cast<int>(contextReleaseBehavior));
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, openglForwardCompat);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, openglDebugContext);
        glfwWindowHint(GLFW_OPENGL_PROFILE, static_cast<int>(openglProfile));

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, cocoaRetinaFramebuffer);
        glfwWindowHintString(GLFW_COCOA_FRAME_NAME, cocoaFrameName);
        glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, cocoaGraphicsSwitching);
#endif

#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        glfwWindowHintString(GLFW_X11_CLASS_NAME, x11ClassName);
        glfwWindowHintString(GLFW_X11_INSTANCE_NAME, x11InstanceName);
#endif
    }
};

/*
 * ErrorHandler
 * Code from glfwpp lib at glfwpp/error.h
 * */
void App::GLFW::glfw_error_callback(int errorCode_, const char *what_)
{
    // Error handling philosophy as per http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0709r4.pdf (section 1.1)

    // Application programmer errors. See the GLFW docs and fix the code.
    assert(errorCode_ != GLFW_NOT_INITIALIZED);
    assert(errorCode_ != GLFW_NO_CURRENT_CONTEXT);
    assert(errorCode_ != GLFW_NO_WINDOW_CONTEXT);
    assert(errorCode_ != GLFW_INVALID_VALUE);

    // These errors should never occur
#if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
    assert(errorCode_ != GLFW_NO_ERROR);
#endif
    assert(errorCode_ != GLFW_INVALID_ENUM);

    // Allocation failure must be treated separately
    if (errorCode_ == GLFW_OUT_OF_MEMORY) {
        throw std::bad_alloc();
    }

    switch (errorCode_) {
        case GLFW_API_UNAVAILABLE:throw APIUnavailableError(what_);
        case GLFW_VERSION_UNAVAILABLE:throw VersionUnavailableError(what_);
        case GLFW_PLATFORM_ERROR:throw PlatformError(what_);
        case GLFW_FORMAT_UNAVAILABLE:throw FormatUnavailableError(what_);
        default:
            // There should be no other error possible
            assert(false);
    }
};


void App::GLFW::shutdown()
{
    if (m_window) { glfwDestroyWindow(m_window.get()); }
    glfwTerminate();
};

int8_t App::GLFW::init()
{

    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit()) { throw GLFW::Error("Could not initialize GLFW"); }

    WindowHints hints;
    hints.clientApi = ClientApi::OpenGl;
    hints.contextVersionMajor = 3;
    hints.contextVersionMinor = 0;
    hints.apply();

    m_window = std::unique_ptr<GLFWwindow, WindowDeleter>(glfwCreateWindow((int32_t) m_spec.window_size.x,
                                                                           (int32_t) m_spec.window_size.y,
                                                                           m_spec.title.c_str(),
                                                                           nullptr,
                                                                           nullptr), WindowDeleter());
    if (nullptr == m_window) { throw std::runtime_error("GLFW window not created"); }

    glfwMakeContextCurrent(m_window.get());

    glfwSwapInterval(m_spec.enable_vsync); // Enable vsync

    return EXIT_SUCCESS;
};