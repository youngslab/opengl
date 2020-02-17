#include "ogl/texture.h"

#include <SOIL2/SOIL2.h>
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
auto create(std::string const &file)
    -> std::optional<std::tuple<GLuint, GLsizei, GLsizei, GLenum>> {
  GLsizei width = 0, height = 0, channels = 0;

  auto image =
      SOIL_load_image(file.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

  if (!image) {
    fmt::print("SOIL failed to load image %s: %s", file.c_str(),
	       SOIL_last_result());
    return std::nullopt;
  }

  // setup forrmat
  auto format = (channels == 4) ? GL_RGBA : GL_RGB;

  // create
  GLuint id;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);

  // init
  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
	       GL_UNSIGNED_BYTE, image);

  SOIL_free_image_data(image);

  // Enable bilinear filteringi
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // unbind
  glBindTexture(GL_TEXTURE_2D, 0);

  return std::tuple{id, width, height, format};
}

texture::texture(std::string const &f) : texture(*create(f)) {}

texture::texture(std::tuple<GLuint, GLsizei, GLsizei, GLenum> const &data)
    : texture(std::get<0>(data), std::get<1>(data), std::get<2>(data),
	      std::get<3>(data)) {}

texture::texture(GLuint const &id, GLsizei const &w, GLsizei const &h,
		 GLenum const &c)
    : id(id), width(w), height(h), channel(c),
      shared_life(std::shared_ptr<void>(new int(0), [id](void *mem) {
	delete (int *)mem;
	glDeleteTextures(1, &id);
      })) {}

texture::texture(std::nullopt_t const &f)
    : id(0), width(0), height(0), channel(0) {
  throw std::runtime_error("");
}

auto texture::bind() -> void { glBindTexture(GL_TEXTURE_2D, id); }

auto texture::size() -> std::pair<uint32_t, uint32_t> {
  return {width, height};
}

} // namespace ogl
