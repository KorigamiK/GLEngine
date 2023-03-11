#pragma once

#include "Engine/GLCore/Layer.hh"

#include <vector>

namespace Engine::GLCore {

class LayerStack {
 public:
  LayerStack();
  ~LayerStack();

  void PushLayer(Layer* layer);
  void PopLayer(Layer* layer);

  std::vector<Layer*>::iterator begin() { return _layers.begin(); }
  std::vector<Layer*>::iterator end() { return _layers.end(); }

 private:
  std::vector<Layer*> _layers;
  unsigned int _layerInsertIndex = 0;
};

}  // namespace Engine::GLCore
