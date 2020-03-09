#pragma once

#include <string>
#include <optional>
#include <memory>
#include <utility>

#include <glad/glad.h>

#include "resource.h"

namespace ogl {

class texture : public resource {
public:
  /**
   * @brief Bind the current texture
   *
   * @return None.
   */
  auto bind() const -> void;

  auto unbind() const -> void;
  /**
   * @brief Get a size of a texture.
   *
   * @return A pair of width and height of the texture.
   */
  auto size() -> std::pair<uint32_t, uint32_t>;

  texture(GLsizei width, GLsizei height, GLenum format, GLenum type,
	  const void *data);

  texture(GLuint id, GLsizei width, GLsizei height, GLenum format, GLenum type,
	  const void *data);

  /*
texture(GLenum target, GLint level, GLint internalformat, GLsizei width,
    GLsizei height, GLint border, GLenum format, GLenum type,
    const void *data);
	  */
private:
  GLuint const id_;
  GLsizei const width_;
  GLsizei const height_;
  GLenum const format_;
};

} // namespace ogl
