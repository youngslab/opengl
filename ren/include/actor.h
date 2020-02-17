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

class material {
public:
  material(ogl::program const &p) : program_(p) {}

  auto active() const -> void { program_.bind(); }

private:
  ogl::program program_;
};

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
