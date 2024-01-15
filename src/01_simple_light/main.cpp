// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/camera.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/vertex_scene.h"
#include "shaders/fragment_light_source.h"
#include "shaders/fragment_surface.h"

#include "shared/grid.h"

#include "mesh/cube.h"

auto main() -> int {
    auto window = Window {1024, 768, "Simple Light"};
    auto camera = Camera{45.0f, 1024.0f, 768.0f};
    auto grid = Grid{24};

    auto shader_surface = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex_scene},
        {ShaderType::kFragmentShader, _SHADER_fragment_surface}
    }};

    auto shader_light_source = Shader {{
        {ShaderType::kVertexShader, _SHADER_vertex_scene},
        {ShaderType::kFragmentShader, _SHADER_fragment_light_source}
    }};
    
    glEnable(GL_DEPTH_TEST);    

    auto cube = Mesh {cube_vertex_0, cube_index_0};
    auto light_pos = glm::vec3 {5.0f, 5.0f, 2.0f};

    const auto DrawSurface = [&]() {
        shader_surface.Use();

        auto model = glm::mat4{1.0f};
        model = glm::translate(model, {0.0f, 1.0f, 0.0f});
        model = glm::scale(model, {2.0f, 2.0f, 2.0f});

        shader_surface.SetMat4("Projection", camera.Projection());
        shader_surface.SetMat4("View", camera.View());
        shader_surface.SetMat4("ModelView", camera.View() * model);
        shader_surface.SetVec3("LightColor", {1.0f, 1.0f, 1.0f});
        shader_surface.SetVec3("LightPosition", light_pos);
        shader_surface.SetVec3("SurfaceColor", {1.0f, 0.5f, 0.31f});
        shader_surface.SetVec3("ViewPosition", camera.Position());

        cube.Draw(shader_surface); 
    };

    const auto DrawLightSource = [&]() {
        shader_light_source.Use();

        auto model = glm::mat4{1.0f};
        model = glm::translate(model, light_pos);
        model = glm::scale(model, {0.3f, 0.3f, 0.3f});

        shader_light_source.SetMat4("Projection", camera.Projection());
        shader_light_source.SetMat4("ModelView", camera.View() * model);

        cube.Draw(shader_light_source);
    };

    window.Start([&](const double delta){
        glClearColor(0.06f, 0.06f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(window);
        grid.Draw(camera);

        DrawSurface();
        DrawLightSource();
    });

    return 0;
}