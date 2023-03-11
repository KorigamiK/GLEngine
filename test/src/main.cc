#include "Engine/Application.hh"
#include "Engine/Events/ApplicationEvent.hh"
#include "Engine/Util/Logger.hh"

#include <GL/glew.h>

using namespace Engine::Logger;

class TestLayer : public Engine::GLCore::Layer {
  virtual void OnUpdate(double deltaTime) override { Info("OnUpdate"); }

  virtual void OnRender() override { Info("OnRender"); }

  virtual void OnEvent(Engine::Events::BaseEvent& event) override {
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

class TestApplication : public Engine::Application {
 public:
  TestApplication() : Engine::Application() { PushLayer(new TestLayer()); }
};

auto main(int argc, const char* argv[]) -> int {
  std::unique_ptr<TestApplication> app = std::make_unique<TestApplication>();
  app->Run();
  return 0;
}
