#pragma once

#include <SDL2/SDL.h>
#include <functional>

#include "Engine/Events/Event.hh"

namespace Engine::GLCore {

using EventCallbackFn = std::function<void(Engine::Events::BaseEvent&)>;

class Window {
 public:
  Window(const char* name, unsigned int width, unsigned int height);
  ~Window();

  void OnUpdate() const;
  void PollEvents() const;

  inline unsigned int GetWidth() const { return _width; }
  inline unsigned int GetHeight() const { return _height; }

  inline void SetEventCallback(const EventCallbackFn& callback) {
    _eventCallback = callback;
  }

 private:
  const char* _name;
  unsigned int _width;
  unsigned int _height;

  SDL_Window* _window;
  SDL_GLContext _glContext;
  EventCallbackFn _eventCallback;

  /**
   * @brief Initialize the window
   * @throws std::runtime_error if SDL or OpenGL fails to initialize
   */
  void Init();
  void Shutdown();
};

}  // namespace Engine::GLCore
