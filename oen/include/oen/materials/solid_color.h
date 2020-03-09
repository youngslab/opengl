#pragma once

#include "oen/material.h"

namespace oen{
namespace materials {

class solid_color : public material {

public:
  solid_color()
      : material(
	    ogl::program(ogl::shader(GL_VERTEX_SHADER, std::string(v)),
			 ogl::shader(GL_FRAGMENT_SHADER, std::string(f)))) {}

private:
  // shaders
  //
  static constexpr char f[] = "#version 330 core\n"
			      "out vec4 FragColor;\n"
			      "void main()\n"
			      "{\n"
			      "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			      "}\n\0";

  static constexpr char v[] =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main()\n"
      "{\n"
      "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\0";
};

} // namespace materials
}
