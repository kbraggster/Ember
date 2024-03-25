#pragma once
#include "Window.h"

namespace Ember
{
class Application
{
  public:
    Application();
    ~Application();
    void Run();

  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
};

// To be defined in CLIENT
Application* CreateApplication();

} // namespace Ember