#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 View;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;

out vec3 color;

void main() {
    vec4 position = ModelView * vec4(aPosition, 1.0);
    gl_Position = Projection * position;

    // ambient
    float ambient_factor = 0.2;
    vec3 ambient = ambient_factor * LightColor;

    // diffuse
    vec3 normal_pos = normalize(mat3(transpose(inverse(ModelView))) * aNormal);
    vec3 light_pos = vec3(View * vec4(LightPosition, 1.0));
    vec3 light_dir = normalize(light_pos - vec3(position));
    float diffuse_factor = max(dot(normal_pos, light_dir), 0.0);
    vec3 diffuse = diffuse_factor * LightColor;

    // specular
    vec3 view_dir = normalize(ViewPosition - vec3(position));
    vec3 reflect_dir = reflect(-light_dir, normal_pos);
    float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = 5 * specular_factor * LightColor; 

    color = (ambient + specular + diffuse) * vec3(1.0, 0.1, 0.1);
}