#pragma once
#include <memory>
#include <functional>
#include <string>
#include <glad/glad.h>

#include "resource.h"

namespace ogl {

class shader : public resource {
public:
  explicit shader(GLenum type, std::string const &src);
  explicit shader(GLuint id, GLenum type, std::string const &src);

  auto attach(GLuint const &program) const -> void;

private:
  // shader object
  GLuint id_;
  GLenum type_;
};

} // namespace ogl
