#pragma once

#include "oen/material.h"
#include "ogl/loader.h"

namespace oen {
namespace materials {

class solid_color : public material {

public:
  solid_color() : solid_color(glm::vec4{1.0}) {}

  solid_color(glm::vec4 const &color)
      : material(ogl::program(
	    ogl::shader(GL_VERTEX_SHADER,
			ogl::load_shader("res/shader/solid_color.vs")),
	    ogl::shader(GL_FRAGMENT_SHADER,
			ogl::load_shader("res/shader/solid_color.fs")))),
	color_(color) {}

  virtual auto active() const -> void {
    material::active();
    program_.set("u_color", color_);
  }

  auto set_color(glm::vec4 const &c) { color_ = c; }

private:
  glm::vec4 color_;
};

} // namespace materials
} // namespace oen
