#include "ogl/shader.h"
#include <optional>
#include <fmt/format.h>

namespace ogl {

auto is_compiled(GLuint const &shader) -> bool {
  GLint status;
  // Query the compile status
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status != GL_TRUE) {
    char buffer[512];
    memset(buffer, 0, 512);
    glGetShaderInfoLog(shader, 511, nullptr, buffer);
    fmt::print("GLSL Compile Failed:\n {}", buffer);
    return false;
  }

  return true;
}

auto compile_shader(GLuint id, std::string const &src) -> bool {
  auto interm = src.data();
  // Set the source characters and try to compile
  glShaderSource(id, 1, &interm, nullptr);
  glCompileShader(id);
  return is_compiled(id);
}

auto gen_shader(GLenum const &type) -> GLuint { return glCreateShader(type); }

auto del_shader(GLuint id) -> void { glDeleteShader(id); }

shader::shader(GLuint id, GLenum type, std::string const &src)
    : id_(id), type_(type), resource([id]() { del_shader(id); }) {
  if (!compile_shader(id_, src)) {
    throw std::runtime_error(fmt::format("failed to compile a shader source.\n{}\n ", src));
  }
}

shader::shader(GLenum type, std::string const &src)
    : shader(gen_shader(type), type, src) {}

auto shader::attach(GLuint const &program) const -> void {
  glAttachShader(program, id_);
}

} // namespace ogl
