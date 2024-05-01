#include "VulkanDebugUtils.h"

namespace Ember
{

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                             VkDebugUtilsMessageTypeFlagsEXT messageType,
                                             const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData)
{
    EM_CORE_ERROR("Validation Layer: {0}", callbackData->pMessage);
    return VK_FALSE;
}

void VulkanDebugUtils::SetupDebugUtils(VkInstance& instance)
{
    VkDebugUtilsMessageSeverityFlagsEXT severityFlags =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;

    VkDebugUtilsMessageTypeFlagsEXT messageTypeFlags = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType                              = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity                    = severityFlags;
    createInfo.messageType                        = messageTypeFlags;
    createInfo.pfnUserCallback                    = DebugCallback;

    VkDebugUtilsMessengerEXT debugMessenger;
    VkResult result = vkCreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
    if (result != VK_SUCCESS)
        EM_CORE_ERROR("Vulkan: Failed to setup debug messenger!");
}

} // namespace Ember