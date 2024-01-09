// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "camera.h"

#include <fmt/printf.h>
#include <glm/gtc/matrix_transform.hpp>

auto Camera::View() const -> glm::mat4 {
    return glm::lookAt(position_, front_, up_);
}

auto Camera::Update(Window& window) -> void {
    auto control_key = window.GetKey(GLFW_KEY_LEFT_ALT, GLFW_PRESS);
    if (control_key) {
        auto curr_pos = MousePosition {
            static_cast<float>(window.GetMousePosition().first),
            static_cast<float>(window.GetMousePosition().second)
        };

        fmt::print("x: {}, y: {}\n", curr_pos.first, curr_pos.second);

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

        last_pos_ = curr_pos;
    }
}

auto Camera::Zoom(const MousePosition& offset_pos) -> void {
    // TODO: Zoom
}

auto Camera::Pan(const MousePosition& offset_pos) -> void {
    // TODO: Pan
}

auto Camera::Rotate(const MousePosition& offset_pos) -> void {
    // TODO: Rotate
}