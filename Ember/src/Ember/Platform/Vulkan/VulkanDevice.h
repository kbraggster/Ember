#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace Ember
{

class VulkanDevice
{
  public:
    explicit VulkanDevice(GLFWwindow* window);
    ~VulkanDevice();

    std::string GetAPIVersion() const;
    std::string GetDeviceVendor() const;
    std::string GetDeviceName() const;
    std::string GetDeviceType() const;
    std::string GetDriverVersion() const;

  private:
    void CreateInstance();
    void PickPhysicalDevice();

    // int RateDeviceSuitability(VkPhysicalDevice device);
    bool IsDeviceSuitable(VkPhysicalDevice device);

    GLFWwindow* m_Window;

    VkInstance m_Instance;
    VkDevice m_Device;
    VkPhysicalDeviceProperties m_DeviceProperties;
    VkPhysicalDeviceFeatures m_DeviceFeatures;
};

} // namespace Ember