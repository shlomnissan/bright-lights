// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/camera.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/vertex.h"
#include "shaders/fragment.h"

#include "shared/grid.h"

#include "mesh/cube.h"

auto main() -> int {
    auto window = Window {1024, 768, "Simple Light"};
    auto camera = Camera{45.0f, 1024.0f, 768.0f};
    auto grid = Grid{24};

    auto shader = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex},
        {ShaderType::kFragmentShader, _SHADER_fragment}
    }};
    
    glEnable(GL_DEPTH_TEST);    

    auto cube = Mesh {cube_vertex_0, cube_index_0};
    window.Start([&](const double delta){
        glClearColor(0.06f, 0.06f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(window);
        shader.Use();

        auto model = glm::mat4{1.0f};
        model = glm::translate(model, {0.0f, 1.0f, 0.0f});
        model = glm::scale(model, {2.0f, 2.0f, 2.0f});
        shader.SetMat4("Projection", camera.Projection());
        shader.SetMat4("ModelView", camera.View() * model);

        cube.Draw(shader); 
        grid.Draw(camera);
    });

    return 0;
}