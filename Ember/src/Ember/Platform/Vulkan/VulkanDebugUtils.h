#pragma once
#include <vulkan/vulkan.h>

namespace Ember
{

class VulkanDebugUtils
{
  public:
    VulkanDebugUtils()  = default;
    ~VulkanDebugUtils() = default;

    void SetupDebugUtils(VkInstance& instance);
};

} // namespace Ember