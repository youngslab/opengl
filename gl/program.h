#pragma once

#include "shader.h"

namespace gl {
class program : public resource {
public:
  program(shader const &vertex, shader const &fragment);

  auto bind() const -> void;
  auto unbind() const -> void;

private:
  shader vertex_;
  shader fragment_;
  GLuint id_;
};
} // namespace gl
