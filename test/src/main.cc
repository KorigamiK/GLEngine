#include "Engine/Application.hh"
#include "Engine/Util/Logger.hh"

#include <GL/glew.h>

using namespace Engine::Logger;

class TestLayer : public Engine::GLCore::Layer {
  virtual void OnUpdate(double deltaTime) override {}

  virtual void OnRender() override {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  virtual void OnEvent(Engine::Events::BaseEvent& event) override {
    Engine::Events::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Engine::Events::WindowCloseEvent>([&](auto& e) {
      Info("WindowCloseEvent");
      this->OnDetach();
      return true;
    });
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

auto main() -> int {
  std::unique_ptr<TestApplication> app = std::make_unique<TestApplication>();
  app->Run();

  return 0;
}
