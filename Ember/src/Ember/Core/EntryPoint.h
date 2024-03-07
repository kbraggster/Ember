#pragma once

extern Ember::Application* CreateApplication();

int main(int argc, char** argv)
{
    const auto app = Ember::CreateApplication();
    app->Run();
    delete app;
}