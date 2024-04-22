#include "VulkanContext.h"

namespace Ember
{

VulkanContext::VulkanContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
{
    EM_CORE_ASSERT(windowHandle, "Window handle is null!")
}

void VulkanContext::Init()
{
    m_Device = std::make_unique<VulkanDevice>(m_WindowHandle);

    EM_CORE_INFO("Device Info:");
    EM_CORE_INFO("  Vendor: {0}", m_Device->GetDeviceVendor());
    EM_CORE_INFO("  Name: {0}", m_Device->GetProperties().deviceName);
    EM_CORE_INFO("  Type: {0}", m_Device->GetDeviceType());
    EM_CORE_INFO("  API Version: {0}.{1}.{2}", VK_VERSION_MAJOR(m_Device->GetProperties().apiVersion),
                 VK_VERSION_MINOR(m_Device->GetProperties().apiVersion),
                 VK_VERSION_PATCH(m_Device->GetProperties().apiVersion));
    EM_CORE_INFO("  Driver Version: {0}", m_Device->GetProperties().driverVersion);
}

void VulkanContext::SwapBuffers()
{
}

} // namespace Ember