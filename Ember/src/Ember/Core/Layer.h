#pragma once

#include "Ember/Events/Event.h"

namespace Ember
{

class Layer
{
  public:
    explicit Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& event) {}

    const std::string& GetName() const { return m_DebugName; }

  protected:
    std::string m_DebugName;
};

} // namespace Ember