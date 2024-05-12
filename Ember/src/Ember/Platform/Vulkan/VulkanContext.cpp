#include "VulkanContext.h"

namespace Ember
{

VulkanContext::VulkanContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{
    EM_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void VulkanContext::Init()
{
    m_Instance = CreateInstance();

    m_Device = std::make_unique<VulkanDevice>(m_WindowHandle, m_Instance);
    EM_CORE_INFO("Vulkan Info:");
    EM_CORE_INFO("  API Version: {0}", m_Device->GetAPIVersion());
    EM_CORE_INFO("  Device Vendor: {0}", m_Device->GetDeviceVendor());
    EM_CORE_INFO("  Device Name: {0}", m_Device->GetDeviceName());
    EM_CORE_INFO("  Device Type: {0}", m_Device->GetDeviceType());
    EM_CORE_INFO("  Driver Version: {0}", m_Device->GetDriverVersion());

    m_DebugUtils.SetupDebugUtils(m_Instance);
}

VulkanContext::~VulkanContext()
{
    vkDestroyInstance(m_Instance, nullptr);
}

void VulkanContext::SwapBuffers()
{
}

VkInstance VulkanContext::CreateInstance()
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
    const uint32_t glfwExtensionCount = 2;
    const char** glfwExtensions       = (const char**)malloc(sizeof(const char*) * 3);
    glfwExtensions[0]                 = "VK_KHR_surface";
    glfwExtensions[1]                 = "VK_EXT_metal_surface";
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    VkInstance instance;
    const VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    EM_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan instance!");

    return instance;
}

} // namespace Ember