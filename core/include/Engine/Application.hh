#pragma once

#include "Event.hh"

#include <string>

namespace Engine {

class Application {
 public:
  Application(const char* name = "Engine Application",
              unsigned int width = 480,
              unsigned int height = 272);
  ~Application() = default;

  void Run() const;
  virtual void OnAttach(){};
  virtual void OnUpdate(double deltaTime) = 0;
  virtual void OnRender() = 0;
  virtual void OnEvent(Engine::Event::BaseEvents event) = 0;
  virtual void OnDetach(){};

 private:
  bool _running = true;
  const char* _title;
  unsigned int _width;
  unsigned int _height;
};

}  // namespace Engine
