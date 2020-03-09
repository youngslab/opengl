#pragma once

namespace oen {

auto calc_proj(GLfloat fov) -> glm::mat4 {
  return glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
}

auto calc_view(glm::vec3 pos, glm::vec3 front, glm::vec3 up) {
  return glm::lookAt(pos, pos + front, up);
}

auto calc_dir(float yaw, float pitch) {
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  return direction;
}

class camera {
public:
  camera()
      : camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f),
	       glm::vec3(0.0f, 1.0f, 0.0f), 45.0f) {}
  camera(glm::vec3 pos, glm::vec3 front, glm::vec3 up, GLfloat fov)
      : pos_(pos), front_(front), up_(up), dirty_v_(false), fov_(fov),
	dirty_p_(false), view_(calc_view(pos, front, up)),
	proj_(calc_proj(fov)) {}
  virtual ~camera() {}

  virtual auto get_view() -> glm::mat4 {
    if (dirty_v_) {
      view_ = calc_view(pos_, front_, up_);
      dirty_v_ = false;
    }
    return view_;
  }
  virtual auto get_proj() -> glm::mat4 {
    if (dirty_p_) {
      proj_ = calc_proj(fov_);
      dirty_p_ = false;
    }
    return proj_;
  }

  auto set_pos(glm::vec3 pos) {
    pos_ = pos;
    dirty_v_ = true;
  }
  auto set_front(glm::vec3 front) {
    front_ = front;
    dirty_v_ = true;
  }
  auto set_up(glm::vec3 up) {
    up_ = up;
    dirty_v_ = true;
  }

  auto set_fov(GLfloat fov) {
    fov_ = fov;
    dirty_p_ = true;
  }

private:
  glm::vec3 pos_;
  glm::vec3 front_;
  glm::vec3 up_;
  bool dirty_v_;
  glm::mat4 view_;

  GLfloat fov_;
  bool dirty_p_;
  glm::mat4 proj_;
};
} // namespace oen
