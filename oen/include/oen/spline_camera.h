#pragma once

namespace oen {

auto calc_front(float yaw, float pitch) {
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  return glm::normalize(direction);
}

class spline_camera : public camera {
public:
  spline_camera() : yaw_(-90.0f), pitch_(0.0f), dirty_(false), camera() {}

  virtual ~spline_camera() {}

  auto get_yaw() -> GLfloat { return yaw_; }
  auto get_pitch() -> GLfloat { return pitch_; }
  auto set_yaw(GLfloat yaw) {
    yaw_ = yaw;
    dirty_ = true;
  }
  auto set_pitch(GLfloat pitch) {
    pitch_ = pitch;
    dirty_ = true;
  }

  auto get_view() -> glm::mat4 override {
    if (dirty_) {
      auto front = calc_front(yaw_, pitch_);
      set_front(front);
      dirty_ = false;
    }
    return camera::get_view();
  }

private:
  bool dirty_;
  GLfloat yaw_;
  GLfloat pitch_;
};
} // namespace oen
