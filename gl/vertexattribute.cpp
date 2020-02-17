#include "vertexattribute.h"

#include <stdexcept>

namespace gl {

auto get_type_sizeof(GLenum const &type) -> GLsizei {
  switch (type) {
  case GL_FLOAT:
    return sizeof(GLfloat);
  case GL_INT:
    return sizeof(GLint);
  }
  throw std::runtime_error("unkonwn type ");
}

vertex_attr::vertex_attr(GLenum type, GLuint count,
				 GLboolean normalized)
    : type_(type), count_(count), normalized_(normalized){};

auto vertex_attr::size() const -> GLsizei {
  return get_type_sizeof(type_) * count_;
}

auto vertex_attr::type() const -> GLenum { return this->type_; }
auto vertex_attr::count() const -> GLuint { return this->count_; }
auto vertex_attr::is_normalized() const -> GLboolean {
  return this->normalized_;
}
} // namespace gl
