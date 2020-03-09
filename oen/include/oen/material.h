#pragma once

#include <ogl/ogl.h>

namespace oen {

class material {
public:
  material(ogl::program const &p) : program_(p) {}

  virtual auto active() const -> void { program_.bind(); }

private:
  ogl::program program_;
};
} // namespace oen
