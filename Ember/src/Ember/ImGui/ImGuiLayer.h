#pragma once

#include "Ember/Core/Layer.h"

namespace Ember
{

class ImGuiLayer : public Layer
{
  public:
    ImGuiLayer();
    ~ImGuiLayer() override = default;

    void OnAttach() override;
    void OnDetach() override;
    void OnImGuiRender() override;

    void Begin();
    void End();

  private:
    float m_Time       = 0.0f;
    bool m_BlockEvents = true;
};

} // namespace Ember