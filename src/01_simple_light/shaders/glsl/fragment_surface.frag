#version 460 core
#pragma debug(on)
#pragma optimize(off)

in vec3 normal_position;
in vec3 fragment_position;

out vec4 final_color;

uniform vec3 SurfaceColor;

void main() {
    // ambient
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * SurfaceColor;

    // TODO: diffuse
    // TODO: specular

    final_color = vec4(ambient * SurfaceColor, 1.0);
}