#include "MacOSWindow.h"

#include "Ember/Core/Log.h"

namespace Ember
{

static bool s_GLFWInitialized = false;

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

        s_GLFWInitialized = true;
    }

    m_Window = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), m_Data.Title.c_str(),
                                nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);
}

void MacOSWindow::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

void MacOSWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);
}

void MacOSWindow::SetVSync(const bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

bool MacOSWindow::IsVSync() const
{
    return m_Data.VSync;
}

} // namespace Ember