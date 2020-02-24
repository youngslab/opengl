#pragma once

#include <glad/glad.h>
#include <optional>
#include <vector>

#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexattribute.h"

namespace ogl {

class vertex_array : public resource {
public:
  vertex_array(vertex_buffer const &vbo, std::vector<vertex_attr> const &as);
  vertex_array(vertex_buffer const &vbo, std::vector<vertex_attr> const &as,
	       index_buffer const &ibo);
  vertex_array(GLuint const &id, vertex_buffer const &vbo,
	       std::vector<vertex_attr> const &as);
  vertex_array(GLuint const &id, vertex_buffer const &vbo,
	       std::vector<vertex_attr> const &as, index_buffer const &ibo);
  auto draw() const -> void;
  auto id() const { return vao_; }

private:
  GLuint const vao_;
  vertex_buffer const vbo_;
  std::optional<index_buffer> const ibo_;
  GLuint const stride_;

  auto bind() const -> void;
  auto unbind() const -> void;
  auto data(vertex_buffer const &vbo, std::vector<vertex_attr> const &attrs)
      -> void;
};
} // namespace ogl
