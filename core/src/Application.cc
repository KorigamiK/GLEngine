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

}  // namespace Engine
