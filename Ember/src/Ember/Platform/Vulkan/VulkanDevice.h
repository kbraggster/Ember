#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Ember
{

struct QueueFamilyIndices
{
    std::optional<uint32_t> GraphicsFamily;

    bool IsComplete() const { return GraphicsFamily.has_value(); }
};

class VulkanDevice
{
  public:
    explicit VulkanDevice(GLFWwindow* window, VkInstance& instance);
    ~VulkanDevice();

    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice& device);

    std::string GetAPIVersion() const;
    std::string GetDeviceVendor() const;
    std::string GetDeviceName() const;
    std::string GetDeviceType() const;
    std::string GetDriverVersion() const;

  private:
    void PickPhysicalDevice(VkInstance& instance);

    int RateDeviceSuitability(VkPhysicalDevice& device) const;
    bool IsDeviceSuitable(VkPhysicalDevice& device);

    GLFWwindow* m_Window;

    VkPhysicalDeviceProperties m_DeviceProperties;
    VkPhysicalDeviceFeatures m_DeviceFeatures;
};

} // namespace Ember