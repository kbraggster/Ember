#include "Application.h"

namespace Ember
{

Application* Application::s_Instance = nullptr;

Application::Application()
{
    EM_CORE_ASSERT(!s_Instance, "Application already exists!")
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(EM_BIND_EVENT_FN(Application::OnEvent));

    // TODO: Reimplement ImGui for Vulkan
    // m_ImGuiLayer = new ImGuiLayer();
    // PushOverlay(m_ImGuiLayer);
}

Application::~Application() = default;

void Application::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(EM_BIND_EVENT_FN(OnWindowClose));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
}

void Application::PushLayer(Layer* layer)
{
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::Run()
{
    while (m_Running)
    {
        for (Layer* layer : m_LayerStack)
            layer->OnUpdate();

        // ImGui layer creation
        // m_ImGuiLayer->Begin();
        // for (Layer* layer : m_LayerStack)
        //     layer->OnImGuiRender();
        // m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}

} // namespace Ember