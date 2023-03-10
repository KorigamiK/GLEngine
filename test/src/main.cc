#include "Engine/Application.hh"
#include "Engine/Event.hh"
#include "Engine/Util/Logger.hh"

using namespace Engine::Logger;

class TestApplication : public Engine::Application {
 public:
  TestApplication() : Engine::Application() {}

  virtual void OnUpdate(double deltaTime) override { Info("OnUpdate"); }

  virtual void OnRender() override { Info("OnRender"); }

  virtual void OnEvent(Engine::Event::BaseEvents event) override {
    Info("OnEvent");
  }
};

auto main(int argc, const char* argv[]) -> int {
  TestApplication app;
  app.Run();
  return 0;
}
