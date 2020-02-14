#pragma once

#include <string>
#include <optional>
#include <memory>
#include <utility>

#include <glad/glad.h>

namespace gl {

class texture {
public:
  /**
   * @brief Bind the current texture
   *
   * @return None.
   */
  auto bind() -> void;

  /**
   * @brief Get a size of a texture.
   *
   * @return A pair of width and height of the texture.
   */
  auto size() -> std::pair<uint32_t, uint32_t>;

  texture(std::string const &filepath);
  texture() = delete;

private:
  texture(std::nullopt_t const &f);
  texture(std::tuple<GLuint, GLsizei, GLsizei, GLenum> const &data);
  texture(GLuint const &id, GLsizei const &w, GLsizei const &h,
	  GLenum const &c);

  uint32_t const width;
  uint32_t const height;
  uint32_t const id;
  uint32_t const channel;
  // extend object lifetime by sharing id;
  std::shared_ptr<void> shared_life;
};

} // namespace gl
