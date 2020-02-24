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

vertex_buffer::vertex_buffer(GLuint id, const void *data, unsigned int size)
    : resource([id]() { delete_buffer(id); }), vbo_(id), size_(size) {
  this->bind();
  this->data(data, size);
  this->unbind();
}

vertex_buffer::vertex_buffer(const void *data, unsigned int size)
    : vertex_buffer(gen_buffer(), data, size) {}

vertex_buffer::~vertex_buffer() {}

auto vertex_buffer::bind() const -> void {
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
}

auto vertex_buffer::unbind() const -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto vertex_buffer::size() const -> GLsizei { return size_; }

} // namespace ogl
