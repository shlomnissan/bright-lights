// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/shader.h"

class Grid {
public:
    Grid(unsigned int dimensions);

    auto Draw(const Shader& shader) const -> void;

private:
    unsigned int dimensions_ {0};
    unsigned int vao_ {0};
    unsigned int vbo_ {0};

    auto ConfigureVertices() -> void; 
};