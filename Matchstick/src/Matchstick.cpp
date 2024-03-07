#include <Ember.h>

class Matchstick : public Ember::Application
{
  public:
    Matchstick()
    {
    }

    ~Matchstick()
    {
    }
};

Ember::Application* Ember::CreateApplication()
{
    return new Matchstick();
}