#include "EntryPoint.h"

int main()
{
    Ember::Log::Init();
    EM_CORE_INFO("Initialized Log");

    const auto app = Ember::CreateApplication();
    app->Run();
    delete app;
}