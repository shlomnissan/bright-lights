// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#pragma once

#include "core/shader.h"
#include "core/camera.h"

#include "shaders/headers/grid_vertex.h"
#include "shaders/headers/grid_fragment.h"

#include <glm/glm.hpp>

class Grid {
public:
    Grid(unsigned int dimensions);

    auto Draw(const Camera& camera) const -> void;

private:
    unsigned int dimensions_ {0};
    unsigned int vao_ {0};
    unsigned int vbo_ {0};

    Shader shader_ {{
        {ShaderType::kVertexShader, _SHADER_grid_vertex},
        {ShaderType::kFragmentShader, _SHADER_grid_fragment}
    }};

    auto ConfigureVertices() -> void; 
};