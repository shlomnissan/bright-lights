static const char* _SHADER_grid_fragment = R"(#version 460 core
#pragma debug(on)
#pragma optimize(off)

out vec4 final_color;

void main() {
    final_color = vec4(0.22, 0.22, 0.22, 1.0);
})";