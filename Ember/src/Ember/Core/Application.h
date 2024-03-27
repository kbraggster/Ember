#pragma once

#include "Ember/Core/Window.h"
#include "Ember/Core/Layer.h"
#include "Ember/Core/LayerStack.h"
#include "Ember/Events/ApplicationEvent.h"

namespace Ember
{
class Application
{
  public:
    Application();
    ~Application();
    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

  private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
};

// To be defined in CLIENT
Application* CreateApplication();

} // namespace Ember