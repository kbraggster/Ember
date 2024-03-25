#include "Application.h"

#include "Ember/Core/Log.h"

namespace Ember
{

Application::Application()
{
    m_Window = std::unique_ptr<Window>(Window::Create());
}

Application::~Application() = default;

void Application::Run()
{
    while (m_Running)
    {
        m_Window->OnUpdate();
    }
}

} // namespace Ember