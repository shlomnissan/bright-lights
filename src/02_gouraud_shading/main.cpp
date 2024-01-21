// Copyright 2024 Betamark Pty Ltd. All rights reserved.
// Author: Shlomi Nissan (shlomi@betamark.com)

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/camera.h"
#include "core/mesh.h"
#include "core/shader.h"
#include "core/window.h"

#include "shaders/gouraud_frag.h"
#include "shaders/gouraud_vert.h"
#include "shaders/light_source_frag.h"
#include "shaders/phong_frag.h"
#include "shaders/phong_vert.h"

#include "shared/grid.h"

#include "mesh/cube.h"
#include "mesh/sphere.h"

auto main() -> int {
    auto window = Window {1024, 768, "Gouraud Shading"};
    auto camera = Camera{45.0f, 1024.0f, 768.0f};
    auto grid = Grid{24};

    auto shader_phong = Shader {{
        {ShaderType::kVertexShader, _SHADER_phong_vert},
        {ShaderType::kFragmentShader, _SHADER_phong_frag}
    }};

    auto shader_gouraud = Shader {{
        {ShaderType::kVertexShader, _SHADER_gouraud_vert},
        {ShaderType::kFragmentShader, _SHADER_gouraud_frag}
    }};

    auto shader_light_source = Shader {{
        {ShaderType::kVertexShader, _SHADER_phong_vert},
        {ShaderType::kFragmentShader, _SHADER_light_source_frag}
    }};
    
    glEnable(GL_DEPTH_TEST);    

    auto cube = Mesh {cube_vertex_0, cube_index_0};
    auto sphere = Mesh {sphere_vertex_0, sphere_index_0};
    auto light_pos = glm::vec3 {0.0f, 5.0f, 5.0f};

    const auto DrawSurface = [&](Shader& shader_program, float xPos) {
        shader_program.Use();

        auto model = glm::mat4{1.0f};
        model = glm::translate(model, {xPos, 1.0f, 0.0f});

        shader_program.SetMat4("Projection", camera.Projection());
        shader_program.SetMat4("ModelView", camera.View() * model);
        shader_program.SetMat4("View", camera.View());
        shader_program.SetVec3("LightPosition", light_pos);
        shader_program.SetVec3("ViewPosition", camera.Position());

        sphere.Draw(shader_program);
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

        DrawSurface(shader_gouraud, -1.5f);
        DrawSurface(shader_phong, 1.5f);
        DrawLightSource();
    });

    return 0;
}