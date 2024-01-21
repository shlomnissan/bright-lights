#version 430
#pragma debug(on)
#pragma optimize(off)

in vec3 normal_pos;
in vec3 fragment_pos;

layout (location = 0) out vec3 color;

uniform mat4 View;
uniform vec3 LightPosition;
uniform vec3 ViewPosition;

void main() {
    vec3 light_color = {1.0, 1.0, 1.0};

    // ambient
    float ambient_factor = 0.2;
    vec3 ambient = ambient_factor * light_color;

    // diffuse
    vec3 light_pos = vec3(View * vec4(LightPosition, 1.0));
    vec3 light_dir = normalize(light_pos - fragment_pos);
    vec3 normal = normalize(normal_pos);
    float diffuse_factor = max(dot(normal, light_dir), 0.0);
    vec3 diffuse = diffuse_factor * light_color;

    // specular
    vec3 view_dir = normalize(ViewPosition - vec3(fragment_pos));
    vec3 reflect_dir = reflect(-light_dir, normal);
    float specular_factor = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
    vec3 specular = 3 * specular_factor * light_color; 

    color = (ambient + diffuse + specular) * vec3(1.0, 0.1, 0.1);
}