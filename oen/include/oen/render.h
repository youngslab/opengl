#pragma once
#include <ogl/shader.h>
#include <ogl/program.h>
#include <ogl/vertexarray.h>

#include <variant>
#include <vector>
#include <memory>

#include <oen/mesh.h>
#include <oen/entity.h>
#include <oen/camera.h>

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts>
overloaded(Ts...)->overloaded<Ts...>; // not needed as of C++20

namespace oen {

auto render(std::shared_ptr<camera> c,
	    std::vector<std::shared_ptr<entity>> const &es) {

  for (auto &e : es) {
    std::shared_ptr<mesh> me;
    std::shared_ptr<material> ma;
    std::shared_ptr<translation> tr;

    for (auto &c : e->get_components()) {
      // TODO: make sured that material is prior to mesh
      // clang-format off
      std::visit(overloaded{
					[&](std::shared_ptr<material> m) { ma = m; },
			    [&](std::shared_ptr<mesh> m) { me = m;},
			    [&](std::shared_ptr<translation> t) { tr = t; }},
		      c);
      // clang-format on
    }

    ma->set_model(tr->get_model());
    ma->set_view(c->get_view());
    ma->set_proj(c->get_proj());
    ma->active();
    me->draw();
  }
}
auto render(std::vector<std::shared_ptr<entity>> const &es) {

  for (auto &e : es) {
    std::shared_ptr<mesh> me;
    std::shared_ptr<material> ma;
    std::shared_ptr<translation> tr;

    for (auto &c : e->get_components()) {
      // TODO: make sured that material is prior to mesh
      // clang-format off
      std::visit(overloaded{
					[&](std::shared_ptr<material> m) { ma = m; },
			    [&](std::shared_ptr<mesh> m) { me = m;},
			    [&](std::shared_ptr<translation> t) { tr = t; }},
		      c);
      // clang-format on
    }

    ma->set_model(tr->get_model());
    ma->active();
    me->draw();
  }
}
} // namespace oen
