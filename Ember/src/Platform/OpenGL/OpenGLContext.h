#pragma once

#include "Ember/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Ember
{

class OpenGLContext final : public GraphicsContext
{
  public:
    explicit OpenGLContext(GLFWwindow* windowHandle);

    void Init() override;
    void SwapBuffers() override;

  private:
    GLFWwindow* m_WindowHandle;
};

} // namespace Ember