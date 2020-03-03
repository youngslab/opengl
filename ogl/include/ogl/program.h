#pragma once

#include "shader.h"

namespace ogl {
class program : public resource {
public:
  program(shader const &vertex, shader const &fragment);

  auto bind() const -> void;
  auto unbind() const -> void;

  template <typename T> auto set(const char *name, T const &value);

  template <> auto set<int>(const char *name, int const &value) {
    glUniform1i(glGetUniformLocation(id_, name), value); // set it manually
  }

private:
  GLuint id_;
};
} // namespace ogl
