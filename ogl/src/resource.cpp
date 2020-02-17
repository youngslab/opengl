#include "ogl/resource.h"

namespace ogl {
resource::resource(std::function<void()> deleter)
    : life(std::shared_ptr<uint32_t>(new uint32_t(0), [deleter](uint32_t *x) {
	deleter();
	delete (uint32_t *)x;
      })) {}

}; // namespace ogl
