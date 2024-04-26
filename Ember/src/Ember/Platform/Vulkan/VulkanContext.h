#pragma once

#include "Ember/Renderer/GraphicsContext.h"

#include "Ember/Platform/Vulkan/VulkanDevice.h"

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Ember
{

class VulkanContext final : public GraphicsContext
{
  public:
    explicit VulkanContext(GLFWwindow* windowHandle);
    ~VulkanContext() override;

    void Init() override;
    void SwapBuffers() override;

  private:
    void CreateInstance();

  private:
    GLFWwindow* m_WindowHandle;
    VkInstance m_Instance;

    std::unique_ptr<VulkanDevice> m_Device;
};

} // namespace Ember