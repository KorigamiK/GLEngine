#pragma once

#include "Engine/Events/Event.hh"

#include <string>

namespace Engine::GLCore {

class Layer {
 public:
  Layer(const std::string& name = "Layer");
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnUpdate(double deltaTime) = 0;
  virtual void OnRender() = 0;
  virtual void OnEvent(Engine::Events::BaseEvent& event) = 0;
  virtual void OnDetach() {}

 protected:
  std::string _name;
};

}  // namespace Engine::GLCore
