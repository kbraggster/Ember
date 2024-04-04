#pragma once

#include "Ember/Core/Window.h"
#include "Ember/Core/Layer.h"
#include "Ember/Core/LayerStack.h"
#include "Ember/Events/ApplicationEvent.h"

#include "Ember/ImGui/ImGuiLayer.h"

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

    Window& GetWindow() const { return *m_Window; }

    static Application& Get() { return *s_Instance; }

  private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    LayerStack m_LayerStack;

    static Application* s_Instance;
};

// To be defined in CLIENT
Application* CreateApplication();

} // namespace Ember