#include "vertexarray.h"
#include <numeric>

#include <iostream>

namespace gl {

auto gen_vertex_array() -> GLuint {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  std::cout << "create vao: " << vao << "\n";
  return vao;
}

auto del_vertex_array(GLuint const &id) -> void {

  std::cout << "delete vao: " << id << "\n";
  glDeleteVertexArrays(1, &id);
}

auto calc_stride(std::vector<vertex_attr> const &attrs) -> GLsizei {
  return std::accumulate(std::begin(attrs), std::end(attrs), 0u,
			 [](GLsizei const &acc, vertex_attr const &attr) {
			   return acc + attr.size();
			 });
}

vertex_array::vertex_array(vertex_buffer const &vbo,
			 std::vector<vertex_attr> const &as)
    : vao(gen_vertex_array()), vbo(vbo), stride_(calc_stride(as)),
      resource([=]() { del_vertex_array(vao); }) {
  this->bind();
  this->data(vbo, as);
  this->unbind();
}

vertex_array::vertex_array(vertex_buffer const &vbo,
			 std::vector<vertex_attr> const &as,
			 index_buffer const &ibo)
    : vao(gen_vertex_array()), vbo(vbo), stride_(calc_stride(as)), ibo(ibo),
      resource([=]() { del_vertex_array(vao); }) {
  this->bind();
	this->data(vbo, as);
	ibo.bind();
  this->unbind();
}

auto vertex_array::bind() -> void { glBindVertexArray(vao); }

auto vertex_array::unbind() -> void { glBindVertexArray(0); }

auto vertex_array::data(vertex_buffer const &vbo,
		       std::vector<vertex_attr> const &attrs) -> void {
  vbo.bind();
  auto offset = 0ll;
  for (auto i = 0u; i < attrs.size(); i++) {
    glVertexAttribPointer(i, attrs[i].count(), attrs[i].type(),
			  attrs[i].is_normalized(), stride_,
			  (void *)(offset));
    offset += attrs[i].size();
    glEnableVertexAttribArray(i);
  }

  vbo.unbind();
}

auto vertex_array::draw() -> void {
	this->bind();
  if (ibo) {
    glDrawElements(GL_TRIANGLES, ibo->size() / sizeof(uint32_t),
		   GL_UNSIGNED_INT, 0);
  } else {
    // how much vetices in vbo?
    glDrawArrays(GL_TRIANGLES, 0 /*first*/, vbo.size() / stride_);
  }
	this->unbind();
}

}; // namespace gl
