#include "Engine/GLCore/Window.hh"

#include "Engine/Events/ApplicationEvent.hh"
#include "Engine/Events/KeyEvent.hh"
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

  Info("OpenGL Vendor: ", glGetString(GL_VENDOR));
  Info("OpenGL Renderer: ", glGetString(GL_RENDERER));
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

void Window::OnUpdate() const {
  SDL_GL_SwapWindow(_window);
}

void Window::PollEvents() const {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        Engine::Events::WindowCloseEvent windowCloseEvent;
        _eventCallback(windowCloseEvent);
        break;
      }
      case SDL_WINDOWEVENT: {
        switch (event.window.event) {
          case SDL_WINDOWEVENT_RESIZED: {
            Engine::Events::WindowResizeEvent windowResizeEvent(
                event.window.data1, event.window.data2);
            _eventCallback(windowResizeEvent);
            break;
          }
        }
        break;
      }
      case SDL_KEYDOWN: {
        Engine::Events::KeyPressedEvent keyPressedEvent(event.key.keysym,
                                                        event.key.repeat);
        _eventCallback(keyPressedEvent);
        break;
      }
      case SDL_KEYUP: {
        Engine::Events::KeyReleasedEvent keyReleasedEvent(event.key.keysym);
        _eventCallback(keyReleasedEvent);
        break;
      }
      case SDL_MOUSEBUTTONDOWN: {
        // Engine::Events::MouseButtonPressedEvent mouseButtonPressedEvent(
        //     event.button.button);
        // _eventCallback(mouseButtonPressedEvent);
        break;
      }
      case SDL_MOUSEBUTTONUP: {
        // Engine::Events::MouseButtonReleasedEvent mouseButtonReleasedEvent(
        //     event.button.button);
        // _eventCallback(mouseButtonReleasedEvent);
        break;
      }
      case SDL_MOUSEMOTION: {
        // Engine::Events::MouseMovedEvent mouseMovedEvent(event.motion.x,
        //                                                 event.motion.y);
        // _eventCallback(mouseMovedEvent);
        break;
      }
      case SDL_MOUSEWHEEL: {
        // Engine::Events::MouseScrolledEvent mouseScrolledEvent(event.wheel.x,
        //                                                       event.wheel.y);
        // _eventCallback(mouseScrolledEvent);
        break;
      }
    }
  }
}