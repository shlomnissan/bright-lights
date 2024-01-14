// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/camera.h"
#include "core/grid.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/headers/vertex.h"
#include "shaders/headers/fragment.h"

#include "mesh/cube.h"

auto main() -> int {
    auto window = Window {1024, 768, "Simple Light"};
    auto camera = Camera{};
    auto grid = Grid{24};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex},
        {ShaderType::kFragmentShader, _SHADER_fragment}
    }};
    
    glEnable(GL_DEPTH_TEST);    

    auto cube = Mesh {cube_vertex_0, cube_index_0};
    window.Start([&](const double delta){
        glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(window);

        shader.Use();
        shader.SetMat4("Projection",
            glm::perspective(camera.zoom(), 1024.0f / 768.0f, 0.1f, 2000.0f)
        );

        auto model = glm::mat4{1.0f};
        model = glm::scale(model, {0.3f, 0.3f, 0.3f});
        shader.SetMat4("ModelView", camera.View() * model);

        cube.Draw(shader); 
        grid.Draw(shader);
    });

    return 0;
}