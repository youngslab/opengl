#pragma once

#include "oen/mesh.h"

namespace oen {
namespace meshes {

class rectangle : public mesh {
public:
  rectangle()
      : mesh(ogl::vertex_array(ogl::vertex_buffer(vertices, sizeof(vertices)),
			       {ogl::vertex_attr(GL_FLOAT, 3, true)},
			       ogl::index_buffer(indices, sizeof(indices)))) {}

  virtual ~rectangle() {}

private:
  static constexpr float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  static constexpr unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
  };
};

} // namespace meshes
} // namespace oen
