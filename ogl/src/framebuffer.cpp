#include "ogl/framebuffer.h"

namespace ogl {
auto attach(GLenum attachment, GLuint texture) -> void {
  // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
  // texColorBuffer, 0);
  glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);
}

frame_buffer::frame_buffer(GLbitfield mask, glm::vec4 color)
    : id_(0), mask_(mask), color_(color) {}

auto frame_buffer::clear() -> void {
  glClearColor(color_.r, color_.g, color_.b, color_.a);
  glClear(mask_);
}

auto frame_buffer::set_size(uint32_t w, uint32_t h) -> void {
  glViewport(0, 0, w, h);
}

auto frame_buffer::bind() const -> void {
  glBindFramebuffer(GL_FRAMEBUFFER, id_);
}

auto frame_buffer::unbind() const -> void {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
} // namespace ogl
