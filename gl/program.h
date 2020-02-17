#pragma once

#include "shader.h"

namespace gl {
class program : public resource {
public:
  program(shader const &vertex, shader const &fragment);

  auto bind() const -> void;
  auto unbind() const -> void;

private:
  GLuint id_;
};
} // namespace gl
