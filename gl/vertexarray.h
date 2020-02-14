#pragma once

#include <glad/glad.h>
#include <optional>
#include <vector>

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexattribute.h"

namespace gl {

class VertexArray : public resource {
public:
  VertexArray(VertexBuffer const &vbo, std::vector<VertexAttribute> const &as);
  auto bind() -> void;
  auto unbind() -> void;

private:
  VertexBuffer const vbo;
  std::optional<index_buffer> const ebo;
  GLuint const vao;

  auto data(VertexBuffer const &vbo, std::vector<VertexAttribute> const &attrs)
      -> void;
};
} // namespace gl
