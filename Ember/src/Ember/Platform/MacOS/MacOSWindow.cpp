#include "MacOSWindow.h"

#include "Ember/Events/ApplicationEvent.h"
#include "Ember/Events/KeyEvent.h"
#include "Ember/Events/MouseEvent.h"

#include "Ember/Platform/Vulkan/VulkanContext.h"

namespace Ember
{

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
    EM_CORE_ERROR("GLFW Error: ({0}): {1}", error, description);
}

Window* Window::Create(const WindowProps& props)
{
    return new MacOSWindow(props);
}

MacOSWindow::MacOSWindow(const WindowProps& props)
{
    MacOSWindow::Init(props);
}

MacOSWindow::~MacOSWindow()
{
    MacOSWindow::Shutdown();
}

void MacOSWindow::Init(const WindowProps& props)
{
    m_Data.Title  = props.Title;
    m_Data.Width  = props.Width;
    m_Data.Height = props.Height;

    EM_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized)
    {
        // TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        EM_CORE_ASSERT(success, "Could not initialize GLFW!");
        glfwSetErrorCallback(GLFWErrorCallback);

        s_GLFWInitialized = true;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
                                nullptr, nullptr);

    m_Context = new VulkanContext(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        data.Width  = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action)
        {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            default:;
        }
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        switch (action)
        {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            default:;
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseScrolledEvent event((float)xoffset, (float)yoffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        MouseMovedEvent event((float)xpos, (float)ypos);
        data.EventCallback(event);
    });
}

void MacOSWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

void MacOSWindow::OnUpdate()
{
    glfwPollEvents();
    // m_Context->SwapBuffers();
}

void MacOSWindow::SetVSync(const bool enabled)
{

    m_Data.VSync = enabled;
}

bool MacOSWindow::IsVSync() const
{
    return m_Data.VSync;
}

} // namespace Ember