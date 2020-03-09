#pragma once

#include <ogl/ogl.h>

namespace oen {

class material {
public:
  material(ogl::program const &p)
      : program_(p), view_(1.0), model_(1.0), proj_(1.0) {}

  virtual auto active() const -> void {
    program_.bind();
    program_.set("u_view", view_);
    program_.set("u_proj", proj_);
    program_.set("u_model", model_);
  }

  auto set_model(glm::mat4 const &m) { model_ = m; }
  auto set_view(glm::mat4 const &v) { view_ = v; }
  auto set_proj(glm::mat4 const &p) { proj_ = p; }

protected:
  ogl::program program_;

private:
  glm::mat4 view_;
  glm::mat4 model_;
  glm::mat4 proj_;
};
} // namespace oen
