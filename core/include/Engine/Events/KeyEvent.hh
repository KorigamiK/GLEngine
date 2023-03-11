#pragma once

#include "Engine/Events/Event.hh"

#include <SDL2/SDL.h>
#include <sstream>

namespace Engine::Events {

class KeyEvent : public BaseEvent {
 public:
  SDL_Keysym& KeySym;

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

 protected:
  KeyEvent(SDL_Keysym& KeySym) : KeySym(KeySym) {}
};

class KeyPressedEvent : public KeyEvent {
 public:
  KeyPressedEvent(SDL_Keysym& keySym, int repeatCount)
      : KeyEvent(keySym), _repeatCount(repeatCount) {}

  inline int GetRepeatCount() const { return _repeatCount; }

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyPressedEvent: " << KeySym.sym << " (" << _repeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPressed)

 private:
  int _repeatCount;
};

class KeyReleasedEvent : public KeyEvent {
 public:
  KeyReleasedEvent(SDL_Keysym& keySym) : KeyEvent(keySym) {}

  std::string ToString() const override {
    std::stringstream ss;
    ss << "KeyReleasedEvent: " << KeySym.sym;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyReleased)
};

}  // namespace Engine::Events