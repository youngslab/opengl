#pragma once

#include "oen/material.h"
#include "ogl/loader.h"

namespace oen {
namespace materials {

auto make_texture(std::string const &path) -> ogl::texture {
  auto [w, h, f, t, d] = ogl::load_texture(path);
  return ogl::texture{w, h, f, t, d.get()};
}

class textured : public material {

public:
  textured(std::string const &path)
      : material(ogl::program(
	    ogl::shader(GL_VERTEX_SHADER,
			ogl::load_shader("res/shader/textured.vs")),
	    ogl::shader(GL_FRAGMENT_SHADER,
			ogl::load_shader("res/shader/textured.fs")))),
	tex_(make_texture(path)) {
    program_.bind();
    program_.set("texture", 0);
  }

  virtual auto active() const -> void {
    material::active();
    glActiveTexture(GL_TEXTURE0);
    tex_.bind();
  }

private:
  ogl::texture tex_;
};

} // namespace materials
} // namespace oen
