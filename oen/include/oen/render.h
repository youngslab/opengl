#pragma once 
#include <ogl/shader.h>
#include <ogl/program.h>
#include <ogl/vertexarray.h>

#include <variant>
#include <vector>
#include <memory>

#include <oen/mesh.h>
#include <oen/entity.h>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>; // not needed as of C++20

namespace oen {

auto render(std::vector<std::shared_ptr<entity>> const &es) {
  for (auto &e : es) {
    for (auto &c : e->get_components()) {

      // TODO: make sured that material is prior to mesh
      std::visit(overloaded{[=](std::shared_ptr<material> m) { m->active(); },
			    [](std::shared_ptr<mesh> m) { m->draw(); }},
		 c);
    }
  }
}

} // namespace oen
