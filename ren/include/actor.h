#include <ogl/shader.h>
#include <ogl/program.h>
#include <ogl/vertexarray.h>

#include <variant>
#include <vector>
#include <memory>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>; // not needed as of C++20

namespace ren {

class mesh {
public:
  mesh(ogl::vertex_array const &vao) : vao_(vao) {}

  auto draw() const -> void { vao_.draw(); }
  // vertex array
private:
  ogl::vertex_array vao_;
};

namespace meshes {

class rectangle : public mesh {
public:
  rectangle()
      : mesh(ogl::vertex_array(ogl::vertex_buffer(vertices, sizeof(vertices)),
			       {ogl::vertex_attr(GL_FLOAT, 3, true)},
			       ogl::index_buffer(indices, sizeof(indices)))) {}

private:
  static constexpr float vertices[] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  static constexpr unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first Triangle
      1, 2, 3  // second Triangle
  };
};
} // namespace meshes

class material {
public:
  material(ogl::program const &p) : program_(p) {}

  auto active() const -> void { program_.bind(); }

private:
  ogl::program program_;
};

namespace materials {
class solid_color : public material {

public:
  solid_color()
      : material(ogl::program(ogl::shader(GL_FRAGMENT_SHADER, vertex),
			      ogl::shader(GL_FRAGMENT_SHADER, fragment))) {}

private:
  static const std::string vertex;
  static const std::string fragment;
};

const std::string solid_color::vertex =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const std::string solid_color::fragment =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

} // namespace materials

// component classes aggreator.
using component =
    std::variant<std::shared_ptr<material>, std::shared_ptr<mesh>>;

class entity {
public:
  entity(std::initializer_list<component> comps) : comps_(comps) {}

  auto get_components() const -> std::vector<component> const & {
    return comps_;
  }

private:
  std::vector<component> comps_;
};

auto render(std::vector<std::shared_ptr<entity>> const &es) {
  for (auto &e : es) {
    for (auto &c : e->get_components()) {
      std::visit(overloaded{[=](std::shared_ptr<material> m) { m->active(); },
			    [](std::shared_ptr<mesh> m) { m->draw(); }},
		 c);
    }
  }
}
} // namespace ren
