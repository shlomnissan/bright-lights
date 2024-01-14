// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include "grid.h"

#include <fmt/printf.h>

#include "shaders/headers/grid_vertex.h"
#include "shaders/headers/grid_fragment.h"

#define BUFFER_OFFSET(offset) ((void*)(offset * sizeof(GLfloat)))
#define STRIDE(stride) (sizeof(GLfloat) * stride)

Grid::Grid(unsigned int dimensions) : dimensions_(dimensions) {
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    ConfigureVertices();    

    // clean-up
    glBindVertexArray(0);
    glDeleteBuffers(1, &vbo_);
}

auto Grid::ConfigureVertices() -> void {
    auto vertex_data = std::vector<float>{};

    auto d = static_cast<float>(dimensions_);

    auto x = -(d / 2);
    for (auto i = 0; i <= dimensions_; ++i) {
        auto line = std::vector<float> {
            x, -0.0f, -(d / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            x, -0.0f, (d / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        };
        vertex_data.insert(vertex_data.end(), line.begin(), line.end());
        x += 1.0f;
    }

    auto z = -(d / 2);
    for (auto i = 0; i <= dimensions_; ++i) {
        auto line = std::vector<float> {
            -(d / 2), -0.0f, z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            (d / 2), -0.0f, z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        };
        vertex_data.insert(vertex_data.end(), line.begin(), line.end());
        z += 1.0f;
    }

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertex_data.size() * sizeof(float),
        vertex_data.data(),
        GL_STATIC_DRAW
    );

    // vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, STRIDE(8), BUFFER_OFFSET(0));
}

auto Grid::Draw(const Shader& shader) const -> void {
    shader.Use();
    glBindVertexArray(vao_);
    glDrawArrays(GL_LINES, 0, dimensions_ * 6);
}