#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Ember
{

class VulkanDevice
{
  public:
    explicit VulkanDevice(GLFWwindow* window, VkInstance instance);
    ~VulkanDevice();

    std::string GetAPIVersion() const;
    std::string GetDeviceVendor() const;
    std::string GetDeviceName() const;
    std::string GetDeviceType() const;
    std::string GetDriverVersion() const;

  private:
    void PickPhysicalDevice(VkInstance instance);

    // int RateDeviceSuitability(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device);

    GLFWwindow* m_Window;

    VkDevice m_Device;
    VkPhysicalDeviceProperties m_DeviceProperties;
    VkPhysicalDeviceFeatures m_DeviceFeatures;
};

} // namespace Ember