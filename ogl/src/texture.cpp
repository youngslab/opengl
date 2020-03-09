#include "ogl/texture.h"

#include <fmt/format.h>

namespace ogl {

auto gen_texture() -> GLuint {
  GLuint id;
  glGenTextures(1, &id);
  fmt::print("create tex: {}\n", id);
  return id;
}

auto del_texture(GLuint id) {
  fmt::print("delete tex: {}\n", id);
  glDeleteTextures(1, &id);
}

texture::texture(GLsizei width, GLsizei height, GLenum format, GLenum type,
		 const void *data)
    : texture(gen_texture(), width, height, format, type, data) {}

texture::texture(GLuint id, GLsizei width, GLsizei height, GLenum format,
		 GLenum type, const void *data)
    : id_(id), width_(width), height_(height), format_(format),
      resource([id]() { del_texture(id); }) {
  this->bind();
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);

  // Enable bilinear filteringi
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  this->unbind();
}

auto texture::bind() const -> void { glBindTexture(GL_TEXTURE_2D, id_); }

auto texture::unbind() const -> void { glBindTexture(GL_TEXTURE_2D, 0); }

auto texture::size() -> std::pair<uint32_t, uint32_t> {
  return {width_, height_};
}

} // namespace ogl
