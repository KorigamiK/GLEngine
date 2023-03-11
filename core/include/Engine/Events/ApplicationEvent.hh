#pragma once

#include "Engine/Events/Event.hh"

#include <sstream>

namespace Engine::Events {

class WindowResizeEvent : public BaseEvent {
 public:
  WindowResizeEvent(unsigned int width, unsigned int height)
      : _width(width), _height(height) {}

  inline unsigned int GetWidth() const { return _width; }
  inline unsigned int GetHeight() const { return _height; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << _width << ", " << _height;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)

  EVENT_CLASS_CATEGORY(EventCategoryApplication)

 private:
  unsigned int _width, _height;
};

class WindowCloseEvent : public BaseEvent {
 public:
  WindowCloseEvent() = default;

  EVENT_CLASS_TYPE(WindowClose)

  EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}  // namespace Engine::Events