#version 430
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 ModelView;
uniform mat4 Projection;

out vec3 normal_pos;
out vec3 fragment_pos;

void main() {
    gl_Position = Projection * ModelView * vec4(position, 1.0);

    normal_pos = mat3(transpose(inverse(ModelView))) * normal;
    fragment_pos = vec3(ModelView * vec4(position, 1.0));
}