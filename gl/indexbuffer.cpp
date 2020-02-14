#include "indexbuffer.h"

namespace gl {

auto gen_index_buffer() -> GLuint {
  GLuint ibo;
  glGenBuffers(1, &ibo);
  return ibo;
}

auto del_index_buffer(GLuint const &ibo) { glDeleteBuffers(1, &ibo); }

index_buffer::index_buffer(GLuint const *data, GLsizei const &size)
    : ibo(gen_index_buffer()), resource([=]() { del_index_buffer(ibo); }) {
  this->bind();
  this->data(data, size);
  this->unbind();
}

auto index_buffer::bind() -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

auto index_buffer::unbind() -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto index_buffer::data(GLuint const *data, GLsizei const &size) -> void {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), data,
	       GL_STATIC_DRAW);
}
} // namespace gl
