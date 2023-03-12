# The OpenGL Engine

The OpenGL Engine is a cross-platform modern graphics library designed
to provide a simpler environment for learning and
experimentation with OpenGL and graphics programming.

Built using modern C++, this library offers advanced features
and tools that make it easy to render 2D and 3D graphic scenes with ease.

You can compile the library for Windows, Linux, macOS and
Android.Compiling for the web is also supported using [Emscripten](https://emscripten.org/).

## Getting Started

### Building and Installing

See the [BUILDING](BUILDING.md) document.

The project uses CMake for its build system. To use the library in your project,
simply add this repository as a submodule and add the following lines to your CMakeLists.txt file.

```cmake
add_subdirectory(Engine)
target_link_libraries(<target> Engine)
```

See the [BUILDING](BUILDING.md) document.

## Basic Usage

An example of a basic usage of the library is shown below.

```cpp
#include "Engine/Application.hh"
#include "Engine/Util/Logger.hh"

#include <GL/glew.h>

using namespace Engine::Logger;

class TestLayer : public Engine::GLCore::Layer {
  virtual void OnUpdate(double deltaTime) override {}

  virtual void OnRender() override {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  virtual void OnEvent(Engine::Events::BaseEvent& event) override {
    Engine::Events::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Engine::Events::WindowResizeEvent>([&](auto& e) {
      Info("WindowResizeEvent");
      Info("Width: %d, Height: %d", e.GetWidth(), e.GetHeight());
      return true;
    });
  }

  virtual void OnAttach() override {
    Info("OnAttach");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
};

class TestApplication : public Engine::Application {
 public:
  TestApplication() : Engine::Application() { PushLayer(new TestLayer()); }
};

auto main() -> int {
  std::unique_ptr<TestApplication> app = std::make_unique<TestApplication>();
  app->Run();

  return 0;
}
```

Check out the [sample](sample) directory to get the full source code.

## Contributing

See the [CONTRIBUTING](CONTRIBUTING.md) document.
