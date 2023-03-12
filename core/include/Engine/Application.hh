#pragma once

#include "Events/ApplicationEvent.hh"
#include "Events/Event.hh"
#include "GLCore/LayerStack.hh"
#include "GLCore/Window.hh"

#include <memory>
#include <string>

namespace Engine {

class Application {
 public:
  Application(const char* name = "Engine Application",
              unsigned int width = 480,
              unsigned int height = 272);
  virtual ~Application() = default;

  Application(const Application&) = delete;

  Application& operator=(const Application&) = delete;

  static Application& Get() { return *__instance; }

  void Run();

  void OnEvent(Engine::Events::BaseEvent& event);

  void PushLayer(GLCore::Layer* layer);

  void PopLayer(GLCore::Layer* layer);

 private:
  static Application* __instance;
  bool _running = true;
  GLCore::LayerStack _layerStack;

 protected:
  std::unique_ptr<GLCore::Window> _window;

  inline bool OnWindowClose(Engine::Events::WindowCloseEvent& event) {
    _running = false;
    return true;
  }
};

}  // namespace Engine
