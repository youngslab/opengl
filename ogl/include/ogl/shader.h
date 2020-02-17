#pragma once
#include <memory>
#include <functional>
#include <string>
#include <filesystem>
#include <glad/glad.h>

#include "resource.h"

namespace ogl {

namespace stdfs = std::filesystem;

class shader : public resource {
public:
  explicit shader(GLenum const &type, std::string const &src);
  explicit shader(GLenum const &type, stdfs::path const &file);

  auto attach(GLuint const &program) const -> void;

private:
  // shader object
  GLuint id_;
};

} // namespace ogl
