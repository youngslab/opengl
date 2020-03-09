#pragma once 
#include <vector>
#include "component.h"

namespace oen {
class entity {
public:
  entity(std::initializer_list<component> const &comps) : comps_(comps) {}
  entity(std::vector<component> const &comps) : comps_(comps) {}

  // TODO: make safer using concept.
  template <typename... Ts>
  entity(Ts... ts) : comps_(std::initializer_list<component>{ts...}) {}

  auto get_components() const -> std::vector<component> const & {
    return comps_;
  }

private:
  std::vector<component> comps_;
};

} // namespace oen
