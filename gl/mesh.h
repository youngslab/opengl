#include "vertexarray.h"

namespace re {

class Mesh {
public:
  Mesh(VertextArray const &vao, std::vector<Texture> const &ts)
      : vao(vao), textures(ts) {}

  auto draw() {
    vao.bind();
    vao.draw();
    vao.unbind();
  }

private:
  VertexArray const vao;
  std::vector<Texture> textures;
};
} // namespace re
