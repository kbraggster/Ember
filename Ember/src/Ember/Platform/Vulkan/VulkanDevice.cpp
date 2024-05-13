#include "VulkanDevice.h"

#include <map>

namespace Ember
{

VulkanDevice::VulkanDevice(GLFWwindow* window, const VkInstance& instance) : m_Window(window)
{
    PickPhysicalDevice(instance);
}

VulkanDevice::~VulkanDevice()
{
}

QueueFamilyIndices VulkanDevice::FindQueueFamilies(const VkPhysicalDevice& device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    for (int i = 0; const auto& queueFamily : queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.GraphicsFamily = i;
        if (indices.IsComplete())
            break;
        i++;
    }

    return indices;
}

void VulkanDevice::PickPhysicalDevice(const VkInstance& instance)
{

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    EM_CORE_ASSERT(deviceCount, "Vulkan: Failed to find GPU's that support Vulkan!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    std::multimap<int, VkPhysicalDevice> candidates;
    for (auto& device : devices)
    {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);

        int score = RateDeviceSuitability(device, m_DeviceProperties, m_DeviceFeatures);
        candidates.insert(std::make_pair(score, device));
    }

    if (!candidates.empty())
    {
        VkPhysicalDevice physicalDevice = candidates.rbegin()->second;
        vkGetPhysicalDeviceProperties(physicalDevice, &m_DeviceProperties);
    }
    else
        EM_CORE_ASSERT(false, "Vulkan: Failed to find GPU's that support Vulkan!");
}

int VulkanDevice::RateDeviceSuitability(const VkPhysicalDevice& device,
                                        const VkPhysicalDeviceProperties& deviceProperties,
                                        const VkPhysicalDeviceFeatures& deviceFeatures) const
{
    int score = 0;

    // Discrete GPU's have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        score += 1000;

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader)
        return 0;

    return score;
}

bool VulkanDevice::IsDeviceSuitable(const VkPhysicalDevice& device)
{
    const QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.IsComplete();
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