#pragma once

namespace oen {

auto calc_model(glm::vec3 trans, GLfloat angle, glm::vec3 axis) -> glm::mat4 {
  auto model = glm::mat4(1.0f);
  model = glm::translate(model, trans);
  model = glm::rotate(model, glm::radians(angle), axis);
  return model;
}

class translation {

public:
  translation() : translation(glm::vec3(0), 0, glm::vec3(1.0)) {}
  translation(glm::vec3 trans) : translation(trans, 0, glm::vec3(1.0)) {}
  translation(GLfloat angle, glm::vec3 axis)
      : translation(glm::vec3(0), angle, axis) {}
  translation(glm::vec3 trans, GLfloat angle, glm::vec3 axis)
      : translate_(trans), rotate_angle_(angle), rotate_axis_(axis),
	model_(calc_model(trans, angle, axis)) {}

  virtual ~translation() {}

  auto set_roate(GLfloat const &angle, glm::vec3 const &axis) {
    rotate_angle_ = angle;
    rotate_axis_ = axis;
    dirty = true;
  }

  auto set_translate(glm::vec3 const &trans) {
    translate_ = trans;
    dirty = true;
  }

  auto get_model() -> glm::mat4 {
    if (dirty) {
      model_ = calc_model(translate_, rotate_angle_, rotate_axis_);
      dirty = false;
    }

    return model_;
  }

private:
  bool dirty;

  glm::mat4 model_;

  GLfloat rotate_angle_;
  glm::vec3 rotate_axis_;

  glm::vec3 translate_;
};
} // namespace oen
