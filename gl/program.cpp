#include "program.h"

namespace gl {
auto is_linked(GLuint const &program) {
  GLint status;
  // Query the link status
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    // char buffer[512];
    // memset(buffer, 0, 512);
    // glGetProgramInfoLog(program, 511, nullptr, buffer);
    // SDL_Log("GLSL Link Status:\n%s", buffer);
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
    : id_(gen_program()), vertex_(vertex), fragment_(fragment),
      resource([=]() { del_program(id_); }) {
  vertex_.attach(id_);
  fragment_.attach(id_);
  if (!link_program(id_)) {
    throw std::runtime_error("failed to link a program");
  }
}

auto program::bind() const -> void { glUseProgram(id_); }
auto program::unbind() const -> void { glUseProgram(0); }

} // namespace gl
