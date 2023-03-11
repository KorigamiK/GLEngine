#include "Engine/GLCore/LayerStack.hh"

#include <algorithm>

using namespace Engine::GLCore;

LayerStack::LayerStack() {}

LayerStack::~LayerStack() {
  for (Layer* layer : _layers) {
    delete layer;
  }
}

void LayerStack::PushLayer(Layer* layer) {
  _layers.emplace(_layers.begin() + _layerInsertIndex, layer);
  _layerInsertIndex++;
}

void LayerStack::PopLayer(Layer* layer) {
  auto it = std::find(_layers.begin(), _layers.end(), layer);
  if (it != _layers.end()) {
    _layers.erase(it);
    _layerInsertIndex--;
  }
}
