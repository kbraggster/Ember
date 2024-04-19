#include "VulkanContext.h"

namespace Ember
{

VulkanContext::VulkanContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{
    EM_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void VulkanContext::Init()
{
    CreateInstance();
}

void VulkanContext::SwapBuffers()
{
}

void VulkanContext::CreateInstance()
{
    VkApplicationInfo appInfo{};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "Ember Engine";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "No Engine";
    appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 3;
    const char** glfwExtensions = (const char**)malloc(sizeof(const char*) * 3);
    glfwExtensions[0]           = "VK_KHR_surface";
    glfwExtensions[1]           = "VK_EXT_metal_surface";
    glfwExtensions[2]           = "VK_KHR_portability_enumeration";
    createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    createInfo.enabledExtensionCount   = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    const VkResult result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
    if (result != VK_SUCCESS)
        EM_CORE_ERROR("Vulkan: Failed to create instance! Error Code: {0}", result);
}

} // namespace Ember