#pragma once

#include <glad/glad.h>
#include "resource.h"

namespace gl {

class VertexBuffer : public resource {

public:
  VertexBuffer(const void *data, unsigned int size);

  auto bind() const -> void;
  auto unbind() const -> void;

private:
  // Vertex buffer object.
  GLuint vbo;
  auto data(const void *data, unsigned int size) -> void;
};
} // namespace gl
