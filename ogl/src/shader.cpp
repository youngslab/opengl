#include "ogl/shader.h"

#include <optional>
#include <fstream>
#include <sstream>
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
    fmt::print("GLSL Compile Failed:\n%s", buffer);
    return false;
  }

  return true;
}

auto f2s(stdfs::path const &p) -> std::string {
  std::ifstream fs(p.string());
  if (!fs.is_open()) {
    return "";
  }

  // Read all the text into a string
  std::stringstream ss;
  ss << fs.rdbuf();
  return ss.str();
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

shader::shader(GLenum const &type, std::string const &src)
    : id_(gen_shader(type)), resource([=]() { del_shader(id_); }) {
  if (!compile_shader(id_, src)) {
    throw std::runtime_error("failed to compile a shader source.");
  }
}

shader::shader(GLenum const &type, stdfs::path const &file)
    : shader(type, f2s(file)) {}

auto shader::attach(GLuint const &program) const -> void {
  glAttachShader(program, id_);
}

} // namespace ogl
