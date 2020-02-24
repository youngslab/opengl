#include "ogl/indexbuffer.h"

#include <iostream>

namespace ogl {

auto gen_index_buffer() -> GLuint {
  GLuint ibo;
  glGenBuffers(1, &ibo);
  std::cout << "create ibo: " << ibo << "\n";
  return ibo;
}

auto del_index_buffer(GLuint const &ibo) {
  std::cout << "delete ibo: " << ibo << "\n";
  glDeleteBuffers(1, &ibo);
}

index_buffer::index_buffer(GLuint const &id, GLuint const *data,
			   GLsizei const &count)
    : ibo_(id), count_(count), type_(GL_UNSIGNED_INT),
      resource([id]() { del_index_buffer(id); }) {
  this->bind();
  this->data(data, count);
  this->unbind();
}
index_buffer::index_buffer(GLuint const *data, GLsizei const &count)
    : index_buffer(gen_index_buffer(), data, count) {}

index_buffer::~index_buffer() {}

auto index_buffer::bind() const -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_);
}

auto index_buffer::unbind() const -> void {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

auto index_buffer::data(GLuint const *data, GLsizei const &count) -> void {
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count_ * sizeof(GLuint), data,
	       GL_STATIC_DRAW);
}
auto index_buffer::size() const -> GLsizei { return count_; }
} // namespace ogl
