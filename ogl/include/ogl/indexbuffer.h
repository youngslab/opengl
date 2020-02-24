#pragma once

#include <glad/glad.h>
#include "resource.h"

namespace ogl {

class index_buffer : public resource {
public:
  index_buffer(GLuint const *data, GLsizei const &size);
  index_buffer(GLuint const &id, GLuint const *data, GLsizei const &size);
  ~index_buffer();
  auto bind() const -> void;
  auto unbind() const -> void;
  auto size() const -> GLsizei;

private:
  auto data(GLuint const *data, GLsizei const &size) -> void;
  GLuint const ibo_;
  GLsizei const count_;
  GLenum const type_;
};

} // namespace ogl
