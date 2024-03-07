#pragma once

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
