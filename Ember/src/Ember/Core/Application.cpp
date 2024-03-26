#include "Application.h"

namespace Ember
{

Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(EM_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application() = default;

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(EM_BIND_EVENT_FN(OnWindowClose));

    EM_CORE_TRACE(e);
}

void Application::Run() const
{
    while (m_Running)
    {
        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}

} // namespace Ember