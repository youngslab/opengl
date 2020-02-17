#pragma once

#include <glad/glad.h>
#include "resource.h"

namespace ogl {

class vertex_buffer : public resource {

public:
  vertex_buffer(const void *data, unsigned int size);

  auto bind() const -> void;
  auto unbind() const -> void;
  auto size() const -> GLsizei;

private:
  // Vertex buffer object.
  GLuint vbo;
  GLsizei size_;
  auto data(const void *data, unsigned int size) -> void;
};
} // namespace ogl
