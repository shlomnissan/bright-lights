#version 460 core
#pragma debug(on)
#pragma optimize(off)

in vec3 normal_position;
in vec3 fragment_position;

out vec4 final_color;

uniform mat4 View;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 SurfaceColor;

void main() {
    // ambient
    float ambient_factor = 0.3;
    vec3 ambient = ambient_factor * LightColor;

    // diffuse
    vec3 light_pos = vec3(View * vec4(LightPosition, 1.0));
    vec3 light_dir = normalize(light_pos - fragment_position);
    vec3 normal_pos = normalize(normal_position);
    float diffuse_factor = max(dot(normal_pos, light_dir), 0);
    vec3 diffuse = diffuse_factor * LightColor;

    // TODO: specular

    final_color = vec4((ambient + diffuse) * SurfaceColor, 1.0);
}