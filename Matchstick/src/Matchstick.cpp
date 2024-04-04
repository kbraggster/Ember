#include <Ember.h>

class ExampleLayer final : public Ember::Layer
{
  public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {}

    void OnEvent(Ember::Event& event) override {}
};

class Matchstick : public Ember::Application
{
  public:
    Matchstick() { PushLayer(new ExampleLayer()); }

    ~Matchstick() = default;
};

Ember::Application* Ember::CreateApplication()
{
    return new Matchstick();
}