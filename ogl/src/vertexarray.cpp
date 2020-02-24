#include "ogl/vertexarray.h"
#include <numeric>

#include <iostream>

namespace ogl {

auto gen_vertex_array() -> GLuint {
  GLuint vao;
  glGenVertexArrays(1, &vao);
  std::cout << "create vao: " << vao << "\n";
  return vao;
}

auto del_vertex_array(GLuint const &id) -> void {
  GLuint temp = id;
  std::cout << "delete vao: " << temp << "\n";
  glDeleteVertexArrays(1, &id);
}

auto calc_stride(std::vector<vertex_attr> const &attrs) -> GLsizei {
  return std::accumulate(std::begin(attrs), std::end(attrs), 0u,
			 [](GLsizei const &acc, vertex_attr const &attr) {
			   return acc + attr.size();
			 });
}

vertex_array::vertex_array(GLuint const &id, vertex_buffer const &vbo,
			   std::vector<vertex_attr> const &as)
    : vao_(id), vbo_(vbo), stride_(calc_stride(as)),
      resource([id]() { del_vertex_array(id); }) {
  this->bind();
  this->data(vbo_, as);
  this->unbind();
}

vertex_array::vertex_array(vertex_buffer const &vbo,
			   std::vector<vertex_attr> const &as)
    : vertex_array(gen_vertex_array(), vbo, as) {}

vertex_array::vertex_array(GLuint const &id, vertex_buffer const &vbo,
			   std::vector<vertex_attr> const &as,
			   index_buffer const &ibo)
    : vao_(id), vbo_(vbo), stride_(calc_stride(as)), ibo_(ibo),
      resource([id]() { del_vertex_array(id); }) {
  this->bind();
  this->data(vbo_, as);
  ibo.bind();
  this->unbind();
}

vertex_array::vertex_array(vertex_buffer const &vbo,
			   std::vector<vertex_attr> const &as,
			   index_buffer const &ibo)
    : vertex_array(gen_vertex_array(), vbo, as, ibo) {}

auto vertex_array::bind() const -> void { glBindVertexArray(vao_); }

auto vertex_array::unbind() const -> void { glBindVertexArray(0); }

auto vertex_array::data(vertex_buffer const &vbo,
			std::vector<vertex_attr> const &attrs) -> void {
  vbo.bind();
  auto offset = 0ll;
  for (auto i = 0u; i < attrs.size(); i++) {
    glVertexAttribPointer(i, attrs[i].count(), attrs[i].type(),
			  attrs[i].is_normalized(), stride_, (void *)(offset));
    offset += attrs[i].size();
    glEnableVertexAttribArray(i);
  }

  vbo.unbind();
}

auto vertex_array::draw() const -> void {
  this->bind();
  if (ibo_) {
    glDrawElements(GL_TRIANGLES, ibo_->size() / sizeof(uint32_t),
		   GL_UNSIGNED_INT, 0);
  } else {
    // how much vetices in vbo?
    glDrawArrays(GL_TRIANGLES, 0 /*first*/, vbo_.size() / stride_);
  }
  this->unbind();
}

}; // namespace ogl
