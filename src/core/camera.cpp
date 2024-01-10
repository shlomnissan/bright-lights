// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "camera.h"

#include <fmt/printf.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
    UpdateVectors();
}

auto Camera::View() const -> glm::mat4 {
    return glm::lookAt(position_, position_ + front_, up_);
}

auto Camera::Update(Window& window) -> void {
    auto control_key = window.GetKey(GLFW_KEY_LEFT_ALT, GLFW_PRESS);
    if (control_key) {
        auto curr_pos = window.mouse_pos();

        if (first_pos_) {
            first_pos_ = false;
            last_pos_ = curr_pos;
        }

        auto offset_pos = MousePosition {
            curr_pos.first - last_pos_.first,
            last_pos_.second - curr_pos.second
        };

        if (window.GetMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS)) {
            Zoom(offset_pos);
        }

        if (window.GetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE, GLFW_PRESS)) {
            Pan(offset_pos);
        }

        last_pos_ = curr_pos;
        UpdateVectors();
    }
}

auto Camera::Zoom(const MousePosition& offset_pos) -> void {
    auto speed = offset_pos.first * -0.002f;
    position_.z += speed;
}

auto Camera::Pan(const MousePosition& offset_pos) -> void {
    auto speed_x = offset_pos.first * -0.002f;
    auto speed_y = offset_pos.second * -0.002f;
    position_ += glm::normalize(glm::cross(front_, up_)) * speed_x;
    position_ += up_ * speed_y;
}

auto Camera::Rotate(const MousePosition& offset_pos) -> void {
    // TODO: Rotate
}

auto Camera::UpdateVectors() -> void {
    auto front = glm::vec3 {0.0f};
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
}