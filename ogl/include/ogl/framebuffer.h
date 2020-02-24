#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace ogl {

class frame_buffer {

  // using buffer = std::variant<texture>;

  // frame_buffer(std::initializer_list<std::pair<GLenum, buffer>>> bs) {
  // this->bind();
  // for (auto &[t, b] : bs) {
  // std::visit([t](auto &v) { attach(t, v); }, b);
  //}
  //}

public:
  frame_buffer(GLbitfield attch_mask, glm::vec4 color);

  auto clear() -> void;
  auto set_size(uint32_t w, uint32_t h) -> void;
  auto bind() const -> void;
  auto unbind() const -> void;

private:
  GLuint id_;
  GLbitfield mask_;
  glm::vec4 color_;
};
} // namespace ogl
