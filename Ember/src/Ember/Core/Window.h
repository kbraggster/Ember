#pragma once

namespace Ember
{

struct WindowProps
{
    std::string Title;
    uint64_t Width;
    uint64_t Height;

    explicit WindowProps(const std::string& title = "Ember Engine", const uint64_t width = 1280,
                         const uint64_t height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

class Window
{
};

} // namespace Ember