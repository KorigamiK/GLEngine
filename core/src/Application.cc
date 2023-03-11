#include "Engine/Application.hh"

namespace Engine {

Application* Application::__instance = nullptr;

Application::Application(const char* name,
                         unsigned int width,
                         unsigned int height) {
  if (__instance == nullptr) {
    __instance = this;
    _window = std::make_unique<GLCore::Window>(name, width, height);
    _window->SetEventCallback(
        std::bind(&Application::OnEvent, this, std::placeholders::_1));
  } else {
    throw std::runtime_error("Application already exists");
  }
}

void Application::Run() {
  unsigned lastTime = SDL_GetTicks();
  while (_running) {
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

    _window->OnUpdate();  // Swap buffers
  }
}

void Application::OnEvent(Engine::Events::BaseEvent& event) {
  for (auto it = _layerStack.end(); it != _layerStack.begin();) {
    (*--it)->OnEvent(event);
    if (event.handled) {
      break;
    }
  }
}

void Application::PushLayer(GLCore::Layer* layer) {
  _layerStack.PushLayer(layer);
}

void Application::PopLayer(GLCore::Layer* layer) {
  _layerStack.PopLayer(layer);
}

}  // namespace Engine
