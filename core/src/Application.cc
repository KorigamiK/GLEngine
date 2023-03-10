#include "Engine/Application.hh"

namespace Engine {

Application::Application(const char* name,
                         unsigned int width,
                         unsigned int height)
    : _title(name), _width(width), _height(height) {}

void Application::Run() const {
  while (_running) {
    // Handle events
    // Update game state
    // Render
  }
}

void Application::Init() {
  _window = std::make_unique<GLCore::Window>(_title, _width, _height);
}

}  // namespace Engine
