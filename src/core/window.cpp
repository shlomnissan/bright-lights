// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "window.h"

#include <GLFW/glfw3.h>
#include <fmt/format.h>

constexpr auto callback_error =
[](int error, const char* message) {
    fmt::print("Error ({}): {}\n", error, message);
};

constexpr auto callback_resize =
[](GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
};

constexpr auto callback_mouse =
[](GLFWwindow *window, double x, double y) {
    auto instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    instance->SetMousePosition(x, y);
};

Window::Window(int width, int height, std::string_view title) {
    glfwSetErrorCallback(callback_error);

    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window_ = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

    if (window_ == nullptr) {
        glfwTerminate();
        return;
    }

     glfwMakeContextCurrent(window_);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return;
    }

    glfwSwapInterval(1);
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, callback_resize);
    glfwSetCursorPosCallback(window_, callback_mouse);

    glViewport(0, 0, width, height);
}

auto Window::Start(const std::function<void(const double delta)> &program) -> void {
    auto last_frame = 0.0f;
    while(!glfwWindowShouldClose(window_)) {
        auto time = glfwGetTime();
        auto delta = time - last_frame;
        last_frame = time;

        program(delta);

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}

auto Window::GetKey(int key, int action) const -> bool {
    return glfwGetKey(window_, key) == action;
}

auto Window::GetMouseButton(int key, int action) const -> bool {
    return glfwGetMouseButton(window_, key) == action;
}

auto Window::SetMousePosition(double x, double y) -> void {
    mouse_pos_ = std::pair{
        static_cast<float>(x),
        static_cast<float>(y)
    };
}

Window::~Window() {
    glfwDestroyWindow(window_);
    glfwTerminate();
}