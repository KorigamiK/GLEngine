#include "Engine/Application.hh"

#include "Engine/Events/ApplicationEvent.hh"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace Engine {

Application* Application::__instance = nullptr;

Application::Application(const char* name,
                         unsigned int width,
                         unsigned int height) {
  if (__instance == nullptr) {
    __instance = this;
    _window = std::make_unique<GLCore::Window>(name, width, height);
    _window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
  } else {
    throw std::runtime_error("Application already exists");
  }
}

void Application::_MainLoop(unsigned lastTime) {
  // Update game state
  unsigned currentTime = SDL_GetTicks();
  double deltaTime = (currentTime - lastTime) / 1000.0;
  lastTime = currentTime;
  for (GLCore::Layer* layer : _layerStack)
    layer->OnUpdate(deltaTime);

  // Handle events
  _window->PollEvents();

  // Render
  for (GLCore::Layer* layer : _layerStack)
    layer->OnRender();

  // Swap buffers
  _window->OnUpdate();
}

void Application::Run() {
#ifndef __EMSCRIPTEN__
  while (_running)
    _MainLoop();
#else
  emscripten_set_main_loop([]() { __instance->_MainLoop(); }, 0, 1);
#endif
}

void Application::OnEvent(Engine::Events::BaseEvent& event) {
  Engine::Events::EventDispatcher dispatcher(event);

  dispatcher.Dispatch<Engine::Events::WindowCloseEvent>(
      BIND_EVENT_FN(Application::OnWindowClose));

  for (auto it = _layerStack.end(); it != _layerStack.begin();) {
    (*--it)->OnEvent(event);
    if (event.handled)
      break;
  }
}

void Application::PushLayer(GLCore::Layer* layer) {
  _layerStack.PushLayer(layer);
}

void Application::PopLayer(GLCore::Layer* layer) {
  _layerStack.PopLayer(layer);
}

}  // namespace Engine
