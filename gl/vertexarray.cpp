#include "vertexarray.h"
#include <numeric>

namespace gl {

auto gen_vertex_array() -> GLuint {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  return vao;
}

auto del_vertex_array(GLuint const &id) -> void {
  glDeleteVertexArrays(1, &id);
}

auto calc_stride(std::vector<VertexAttribute> const &attrs) -> GLsizei {
  return std::accumulate(std::begin(attrs), std::end(attrs), 0u,
			 [](GLsizei const &acc, VertexAttribute const &attr) {
			   return acc + attr.size();
			 });
}

VertexArray::VertexArray(VertexBuffer const &vbo,
			 std::vector<VertexAttribute> const &as)
    : vao(gen_vertex_array()), vbo(vbo),
      resource([=]() { del_vertex_array(vao); }) {
  this->bind();
  this->data(vbo, as);
  this->unbind();
}
auto VertexArray::bind() -> void { glBindBuffer(GL_ARRAY_BUFFER, vao); }
auto VertexArray::unbind() -> void { glBindBuffer(GL_ARRAY_BUFFER, 0); }

auto VertexArray::data(VertexBuffer const &vbo,
		       std::vector<VertexAttribute> const &attrs) -> void {
  vbo.bind();

  auto stride = calc_stride(attrs);
  auto offset = 0;
  for (auto i = 0u; i < attrs.size(); i++) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attrs[i].count(), attrs[i].type(),
			  attrs[i].is_normalized(), stride,
			  (const void *)(&offset));
    offset += attrs[i].size();
  }

  vbo.unbind();
}
}; // namespace gl
