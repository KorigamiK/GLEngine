#include "Engine/Application.hh"
#include "Engine/Event.hh"
#include "Engine/Util/Logger.hh"

#include <GL/glew.h>

using namespace Engine::Logger;

class TestApplication : public Engine::Application {
 public:
  TestApplication() : Engine::Application() {}

  virtual void OnUpdate(double deltaTime) override { Info("OnUpdate"); }

  virtual void OnRender() override { Info("OnRender"); }

  virtual void OnEvent(Engine::Event::BaseEvents event) override {
    Info("OnEvent");
  }

  virtual void OnAttach() override {
    Info("OnAttach");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
};

auto main(int argc, const char* argv[]) -> int {
  TestApplication app;
  app.Run();
  return 0;
}
