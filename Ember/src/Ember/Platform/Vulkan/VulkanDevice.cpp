#include "VulkanDevice.h"

#include <map>

namespace Ember
{

VulkanDevice::VulkanDevice(GLFWwindow* window, VkInstance& instance) : m_Window(window)
{
    PickPhysicalDevice(instance);
}

VulkanDevice::~VulkanDevice()
{
    vkDestroyDevice(m_Device, nullptr);
}

void VulkanDevice::PickPhysicalDevice(VkInstance& instance)
{
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    EM_CORE_ASSERT(deviceCount, "Vulkan: Failed to find GPU's that support Vulkan!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    // Use an ordered map to automatically sort candidates by increasing score
    std::multimap<int, VkPhysicalDevice> candidates;
    for (auto& device : devices)
    {
        int score = RateDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }

    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0)
        physicalDevice = candidates.rbegin()->second;
    else
        EM_CORE_ERROR("Vulkan: Failed to find suitable GPU!");

    // Retrieve properties of the selected device
    vkGetPhysicalDeviceProperties(physicalDevice, &m_DeviceProperties);
}

int VulkanDevice::RateDeviceSuitability(VkPhysicalDevice& device) const
{
    int score = 0;

    // Discrete GPU's have a significant performance advantage
    if (m_DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    // Maximum possible size of textures affects graphics quality
    score += m_DeviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!m_DeviceFeatures.geometryShader)
        return 0;

    return score;
}

bool VulkanDevice::IsDeviceSuitable(VkPhysicalDevice& device)
{
    vkGetPhysicalDeviceProperties(device, &m_DeviceProperties);
    vkGetPhysicalDeviceFeatures(device, &m_DeviceFeatures);

    return m_DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && m_DeviceFeatures.geometryShader;
}

std::string VulkanDevice::GetAPIVersion() const
{
    std::ostringstream oss;
    oss << VK_VERSION_MAJOR(m_DeviceProperties.apiVersion) << "." << VK_VERSION_MINOR(m_DeviceProperties.apiVersion)
        << "." << VK_VERSION_PATCH(m_DeviceProperties.apiVersion);
    return oss.str();
}

std::string VulkanDevice::GetDeviceVendor() const
{
    switch (m_DeviceProperties.vendorID)
    {
        case 0x1022:
            return "AMD";
        case 0x10DE:
            return "NVIDIA";
        case 0x8086:
            return "Intel";
        case 0x106B:
            return "Apple";
        default:
            return "Unknown Vendor";
    }
}

std::string VulkanDevice::GetDeviceName() const
{
    return m_DeviceProperties.deviceName;
}

std::string VulkanDevice::GetDeviceType() const
{
    switch (m_DeviceProperties.deviceType)
    {
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
            return "Integrated GPU";
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
            return "Discrete GPU";
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
            return "Virtual GPU";
        case VK_PHYSICAL_DEVICE_TYPE_CPU:
            return "CPU";
        case VK_PHYSICAL_DEVICE_TYPE_OTHER:
            return "Other";
        default:
            return "Unknown";
    }
}

std::string VulkanDevice::GetDriverVersion() const
{
    return std::to_string(m_DeviceProperties.driverVersion);
}

} // namespace Ember