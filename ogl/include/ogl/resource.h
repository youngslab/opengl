#pragma once

#include <functional>
#include <memory>

namespace ogl {
class resource {
public:
  resource(std::function<void()> deleter);
  virtual ~resource() {}

private:
  std::shared_ptr<void> life;
};
} // namespace ogl
