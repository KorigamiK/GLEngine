#include "Engine/GLCore/Window.hh"

#include "Engine/Util/Logger.hh"

#include <GL/glew.h>
#include <stdexcept>

using namespace Engine::GLCore;
using namespace Engine::Logger;

Window::Window(const char* name, unsigned int width, unsigned int height)
    : _name(name), _width(width), _height(height) {
  Init();
}

void Window::Init() {
  Info("Window::Init()");
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    Error("SDL_Init Error: %s", SDL_GetError());
    throw std::runtime_error("SDL_Init Error");
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  _window = SDL_CreateWindow(_name, SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, _width, _height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  if (_window == nullptr) {
    Error("SDL_CreateWindow Error: %s", SDL_GetError());
    throw std::runtime_error("SDL_CreateWindow Error");
  }

  _glContext = SDL_GL_CreateContext(_window);
  if (_glContext == nullptr) {
    Error("SDL_GL_CreateContext Error: %s", SDL_GetError());
    throw std::runtime_error("SDL_GL_CreateContext Error");
  }

  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    Error("glewInit Error: %s", glewGetErrorString(glewError));
    throw std::runtime_error("glewInit Error");
  }

  // Enable VSync
  SDL_GL_SetSwapInterval(1);

  Info("OpenGL Version: ", glGetString(GL_VERSION));
}

void Window::Shutdown() {
  SDL_GL_DeleteContext(_glContext);
  SDL_DestroyWindow(_window);
  SDL_Quit();
}

Window::~Window() {
  Info("Window::~Window()");
  Shutdown();
}