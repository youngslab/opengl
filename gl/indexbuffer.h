#pragma once

#include <glad/glad.h>
#include "resource.h"

namespace gl {

class index_buffer : public resource {
public:
  index_buffer(GLuint const *data, GLsizei const &size);
  auto bind() const -> void;
  auto unbind() const -> void;
  auto size() const -> GLsizei;

private:
  auto data(GLuint const *data, GLsizei const &size) -> void;
  GLuint const ibo;
  GLsizei const count_;
  GLenum const type_;
};

} // namespace gl
