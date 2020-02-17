#include "ogl/vertexbuffer.h"
#include <iostream>

namespace ogl {

auto gen_buffer() -> GLuint {
  GLuint vbo;
  glGenBuffers(1, &vbo);
  std::cout << "create vbo: " << vbo << "\n";
  return vbo;
}

auto delete_buffer(GLuint const &vbo) -> void {
  std::cout << "delete vbo: " << vbo << "\n";
  glDeleteBuffers(1, &vbo);
}

auto vertex_buffer::data(const void *data, unsigned int size) -> void {
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vertex_buffer::vertex_buffer(const void *data, unsigned int size)
    : vbo(gen_buffer()), size_(size), resource([=]() { delete_buffer(vbo); }) {
  this->bind();
  this->data(data, size);
  this->unbind();
}

auto vertex_buffer::bind() const -> void { glBindBuffer(GL_ARRAY_BUFFER, vbo); }
auto vertex_buffer::unbind() const -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto vertex_buffer::size() const -> GLsizei { return size_; }
} // namespace ogl
