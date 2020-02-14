#pragma once

#include <glad/glad.h>
#include "resource.h"

namespace gl {

class index_buffer : public resource {
public:
  index_buffer(GLuint const *data, GLsizei const &size);
  auto bind() -> void;
  auto unbind() -> void;

private:
  auto data(GLuint const *data, GLsizei const &size) -> void;
  GLuint const ibo;
};

} // namespace gl
