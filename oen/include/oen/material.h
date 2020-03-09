#pragma once

#include <ogl/ogl.h>

namespace oen {

class material {
public:
  material(ogl::program const &p)
      : program_(p), view_(1.0), model_(1.0), projection_(1.0) {}

  virtual auto active() const -> void {
    program_.bind();
    program_.set("u_view", view_);
    program_.set("u_projection", projection_);
    program_.set("u_model", model_);
  }

  glm::mat4 view_;
  glm::mat4 model_;
  glm::mat4 projection_;

protected:
  ogl::program program_;
};
} // namespace oen
