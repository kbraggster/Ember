#include "Application.h"

#include "Ember/Core/Log.h"
#include "Ember/Events/ApplicationEvent.h"

namespace Ember
{

Application::Application() = default;

Application::~Application() = default;

void Application::Run()
{
    WindowResizeEvent e(1280, 720);
    EM_TRACE(e);

    while (true)
        ;
}

} // namespace Ember