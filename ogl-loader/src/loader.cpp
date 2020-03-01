#include "ogl/loader.h"
#include <SOIL2/SOIL2.h>
#include <fmt/format.h>

namespace ogl {
auto load_texture(std::string const &file)
    -> std::tuple<GLsizei, GLsizei, GLenum, GLenum, std::shared_ptr<void>> {
  GLsizei width = 0, height = 0, channels = 0;

  unsigned char *image =
      SOIL_load_image(file.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

  if (!image) {
    fmt::print("SOIL failed to load image %s: %s", file.c_str(),
	       SOIL_last_result());
    return {};
  }

  auto data = std::shared_ptr<void>(
      image, [](unsigned char *i) { SOIL_free_image_data(i); });

  // setup forrmat
  auto format = (channels == 4) ? GL_RGBA : GL_RGB;

  return {width, height, format, GL_UNSIGNED_INT, data};
}
} // namespace ogl
