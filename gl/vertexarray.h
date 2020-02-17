#pragma once

#include <glad/glad.h>
#include <optional>
#include <vector>

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexattribute.h"

namespace gl {

class vertex_array : public resource {
public:
  vertex_array(vertex_buffer const &vbo, std::vector<vertex_attr> const &as);
  vertex_array(vertex_buffer const &vbo, std::vector<vertex_attr> const &as,
	      index_buffer const &ibo);
  auto draw() -> void;

private:
  vertex_buffer const vbo;
  std::optional<index_buffer> const ibo;
  GLuint const vao;
  GLuint const stride_;

  auto bind() -> void;
  auto unbind() -> void;
  auto data(vertex_buffer const &vbo, std::vector<vertex_attr> const &attrs)
      -> void;
};
} // namespace gl
