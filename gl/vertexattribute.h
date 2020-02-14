#pragma once

#include <glad/glad.h>

namespace gl {

class VertexAttribute {
public:
  VertexAttribute(GLenum type, GLuint count, GLboolean normalized);

  auto size() const -> GLsizei;
  auto type() const -> GLenum;
  auto count() const -> GLuint;
  auto is_normalized() const -> GLboolean;

private:
  GLenum const type_;
  GLuint const count_;
  GLboolean const normalized_;
};

} // namespace gl
