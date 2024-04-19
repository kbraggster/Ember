#pragma once

#include "Ember/Renderer/GraphicsContext.h"

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Ember
{

class VulkanContext final : public GraphicsContext
{
  public:
    explicit VulkanContext(GLFWwindow* windowHandle);

    void Init() override;
    void SwapBuffers() override;

    void CreateInstance();

  private:
    GLFWwindow* m_WindowHandle;
    VkInstance m_Instance;
};

} // namespace Ember