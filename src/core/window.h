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

    ~Window();

private:
    GLFWwindow* window_ {nullptr};

    std::pair<double, double> mouse_pos_ {0.0, 0.0};
};