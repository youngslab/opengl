#pragma once

#include <functional>
#include <memory>

namespace gl {
class resource {
public:
  resource(std::function<void()> deleter);

private:
  std::shared_ptr<void> life;
};
} // namespace gl
