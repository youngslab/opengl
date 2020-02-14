#include "vertexbuffer.h"

namespace gl {

auto gen_buffer() -> GLuint {
  GLuint vbo;
  glGenBuffers(1, &vbo);
  return vbo;
}

auto delete_buffer(GLuint const &vbo) -> void { glDeleteBuffers(1, &vbo); }

auto VertexBuffer::data(const void *data, unsigned int size) -> void {
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
    : vbo(gen_buffer()), resource([=]() { delete_buffer(vbo); }) {
  this->bind();
  this->data(data, size);
  this->unbind();
}

auto VertexBuffer::bind() const -> void { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
auto VertexBuffer::unbind() const -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

} // namespace gl
