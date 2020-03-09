#pragma once

#include <ogl/ogl.h>

namespace oen {

class mesh {
public:
  explicit mesh(ogl::vertex_array const &vao) : vao_(vao) {}

  virtual ~mesh() {}

  virtual auto draw() const -> void { vao_.draw(); }

  auto id() -> GLuint { return vao_.id(); };
  // vertex array
private:
  ogl::vertex_array vao_;
};

} // namespace oen
