#pragma once
#include <variant>
#include <vector>
#include <memory>

#include "oen/mesh.h"
#include "oen/material.h"
#include "oen/translation.h"

namespace oen {

// component classes aggreator.
using component = std::variant<std::shared_ptr<material>, std::shared_ptr<mesh>,
			       std::shared_ptr<translation>>;

template <typename... Ts>
auto make_components(Ts... ts) -> std::vector<component> {
  return {ts...};
}
} // namespace oen
