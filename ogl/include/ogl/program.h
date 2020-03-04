#pragma once

#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

  template <> auto set<glm::mat4>(const char *name, glm::mat4 const &value) {
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, GL_FALSE,
		       glm::value_ptr(value)); // set it manually
  }

private:
  GLuint id_;
};
} // namespace ogl
