#include "ogl/texture.h"

#include <fmt/format.h>

namespace ogl {

/**
 * @brief Create data for a texture from a file.
 *
 * @param file
 *
 * @return If it's not a file, return nullopt. Othrewise it returns id, width,
 * hegith and its format.
 */
// auto create(std::string const &file)
//-> std::optional<std::tuple<GLuint, GLsizei, GLsizei, GLenum>> {
// GLsizei width = 0, height = 0, channels = 0;

// auto image =
// SOIL_load_image(file.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

// if (!image) {
// fmt::print("SOIL failed to load image %s: %s", file.c_str(),
// SOIL_last_result());
// return std::nullopt;
//}

//// setup forrmat
// auto format = (channels == 4) ? GL_RGBA : GL_RGB;

//// create
// GLuint id;
// glGenTextures(1, &id);
// glBindTexture(GL_TEXTURE_2D, id);

//// init
// glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
// GL_UNSIGNED_BYTE, image);

// SOIL_free_image_data(image);

//// Enable bilinear filteringi
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//// unbind
// glBindTexture(GL_TEXTURE_2D, 0);

// return std::tuple{id, width, height, format};
//}

auto gen_texture() -> GLuint {
  GLuint id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  return id;
}

auto del_texture(GLuint id) { glDeleteTextures(1, &id); }

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

auto texture::bind() -> void { glBindTexture(GL_TEXTURE_2D, id_); }

auto texture::unbind() -> void { glBindTexture(GL_TEXTURE_2D, 0); }

auto texture::size() -> std::pair<uint32_t, uint32_t> {
  return {width_, height_};
}

} // namespace ogl
