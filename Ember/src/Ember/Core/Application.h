#pragma once
#include "Window.h"
#include "Ember/Events/ApplicationEvent.h"

namespace Ember
{
class Application
{
  public:
    Application();
    ~Application();
    void Run() const;

    void OnEvent(Event& e);

  private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// To be defined in CLIENT
Application* CreateApplication();

} // namespace Ember