#include "ogl/program.h"

#include <fmt/format.h>

namespace ogl {
auto is_linked(GLuint const &program) {
  GLint status;
  // Query the link status
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    memset(buffer, 0, 512);
    glGetProgramInfoLog(program, 511, nullptr, buffer);
    fmt::print("GLSL Link Status:\n%s", buffer);
    return false;
  }

  return true;
}

auto link_program(GLuint const &id) -> bool {
  glLinkProgram(id);
  return is_linked(id);
}

auto gen_program() -> GLuint { return glCreateProgram(); }

auto del_program(GLuint id) { glDeleteProgram(id); }

program::program(shader const &vertex, shader const &fragment)
    : id_(gen_program()), resource([=]() { del_program(id_); }) {
  vertex.attach(id_);
  fragment.attach(id_);
  if (!link_program(id_)) {
    throw std::runtime_error("failed to link a program");
  }
}

auto program::bind() const -> void { glUseProgram(id_); }
auto program::unbind() const -> void { glUseProgram(0); }

} // namespace ogl
