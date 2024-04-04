#pragma once
#include "Ember/Events/Event.h"
#include <functional>

namespace Ember
{

struct WindowProps
{
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    explicit WindowProps(const std::string& title = "Ember Engine", const unsigned int width = 1280,
                         const unsigned int height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

class Window
{
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const  = 0;
    virtual unsigned int GetHeight() const = 0;

    // Window attributes
    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled)                            = 0;
    virtual bool IsVSync() const                                   = 0;

    virtual void* GetNativeWindow() const = 0;

    static Window* Create(const WindowProps& props = WindowProps());
};

} // namespace Ember