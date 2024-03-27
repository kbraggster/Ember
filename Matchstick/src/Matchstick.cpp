#include <Ember.h>

class ExampleLayer final : public Ember::Layer
{
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override { EM_INFO("ExampleLayer::Update"); }

    void OnEvent(Ember::Event& event) override { EM_TRACE("{0}", event); }
};

class Matchstick : public Ember::Application
{
  public:
    Matchstick() { PushLayer(new ExampleLayer()); }

    ~Matchstick() {}
};

Ember::Application* Ember::CreateApplication()
{
    return new Matchstick();
}