#pragma once

#include <functional>
#include <memory>

namespace ogl {
class resource {
public:
  resource(std::function<void()> deleter);

private:
  std::shared_ptr<void> life;
};
} // namespace ogl
