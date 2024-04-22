#include "VulkanDevice.h"

namespace Ember
{

VulkanDevice::VulkanDevice(GLFWwindow* window) : m_Window(window)
{
    CreateInstance();
    PickPhysicalDevice();
}

VulkanDevice::~VulkanDevice()
{
    vkDestroyDevice(m_Device, nullptr);
    vkDestroyInstance(m_Instance, nullptr);
}

void VulkanDevice::CreateInstance()
{
    VkApplicationInfo appInfo{};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "Ember Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "Ember";
    appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // TODO: Platform specific extensions
    const uint32_t glfwExtensionCount = 3;
    const char** glfwExtensions       = (const char**)malloc(sizeof(const char*) * 3);
    glfwExtensions[0]                 = "VK_KHR_surface";
    glfwExtensions[1]                 = "VK_EXT_metal_surface";
    glfwExtensions[2]                 = "VK_KHR_portability_enumeration";
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    const VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
    EM_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan instance!");
}

void VulkanDevice::PickPhysicalDevice()
{
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
    EM_CORE_ASSERT(deviceCount, "Failed to find GPU's that support Vulkan!");

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, devices.data());

    for (const auto& device : devices)
    {
        if (IsDeviceSuitable(device))
        {
            physicalDevice = device;
            break;
        }
    }

    EM_CORE_ASSERT(physicalDevice == VK_NULL_HANDLE, "Failed to find suitable GPU!");
}

bool VulkanDevice::IsDeviceSuitable(const VkPhysicalDevice device)
{
    vkGetPhysicalDeviceProperties(device, &m_DeviceProperties);
    vkGetPhysicalDeviceFeatures(device, &m_DeviceFeatures);

    return m_DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && m_DeviceFeatures.geometryShader;
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

} // namespace Ember