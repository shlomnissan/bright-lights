// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <glm/glm.hpp>

#include <core/window.h>

using MousePosition = std::pair<float, float>;

class Camera {
public:
    auto zoom() { return zoom_; }

    auto Update(Window& window) -> void;
    auto View() const -> glm::mat4;

private:
    bool first_pos_ {true};

    float zoom_ = 45.0f;
    float distance_ = 3.0f;
    float horizontal_angle = 0.0f;
    float vertical_angle = 0.0f;

    glm::vec3 world_pos_ {0.0f};
    glm::vec3 position_ {0.0f, 0.0f, distance_};
    glm::vec3 target_ {0.0f, 0.0f, 0.0f};
    glm::vec3 up_ {0.0f, 1.0f, 0.0f};

    MousePosition last_pos_ {0.0f, 0.0f};

    auto Zoom(const MousePosition& offset_pos) -> void;
    auto Pan(const MousePosition& offset_pos) -> void;
    auto Rotate(const MousePosition& offset_pos) -> void;
};