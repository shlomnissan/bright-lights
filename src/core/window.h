// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include <utility>
#include <functional>
#include <string_view>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, std::string_view title);

    auto Start(const std::function<void(const double delta)>& program) -> void;
    auto GetKey(int key, int action) const -> bool;
    auto GetMouseButton(int key, int action) const -> bool;
    auto GetMousePosition() const -> std::pair<double, double>;
    auto SetMousePosition(double x, double y) -> void;

    auto mouse_pos() const { return mouse_pos_; }

    ~Window();

private:
    GLFWwindow* window_ {nullptr};

    std::pair<float, float> mouse_pos_ {0.0, 0.0};
};