#pragma once

#include <SDL2/SDL.h>

namespace Engine::GLCore {

class Window {
 public:
  Window(const char* name, unsigned int width, unsigned int height);
  ~Window();

  void OnUpdate() const;

 private:
  const char* _name;
  unsigned int _width;
  unsigned int _height;

  SDL_Window* _window;
  SDL_GLContext _glContext;

  /**
   * @brief Initialize the window
   * @throws std::runtime_error if SDL or OpenGL fails to initialize
   */
  void Init();
  void Shutdown();
};

}  // namespace Engine::GLCore
