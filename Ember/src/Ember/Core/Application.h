#pragma once

#include "GLFW/glfw3.h"
namespace Ember
{
class Application
{
  public:
    Application();
    ~Application();
    void Run();
};

Application* CreateApplication();

} // namespace Ember