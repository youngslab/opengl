#pragma once
#include <memory>
#include <functional>
#include <string>
#include <filesystem>
#include <glad/glad.h>

#include "resource.h"

namespace gl {

namespace stdfs = std::filesystem;

class shader : public resource {
public:
  shader(GLenum const &type, std::string const &src);
  shader(GLenum const &type, stdfs::path const &file);

  auto attach(GLuint const &program) -> void;

private:
  // shader object
  GLuint id_;
};

} // namespace gl
