#pragma once

#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Ember/Renderer/GraphicsContext.h"
#include "Ember/Platform/Vulkan/VulkanDevice.h"
#include "Ember/Platform/Vulkan/VulkanDebugUtils.h"

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
    VkInstance CreateInstance();

  private:
    GLFWwindow* m_WindowHandle;

    VkInstance m_Instance;
    std::unique_ptr<VulkanDevice> m_Device;

    VulkanDebugUtils m_DebugUtils;
};

} // namespace Ember