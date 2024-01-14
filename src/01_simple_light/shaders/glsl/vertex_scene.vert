#version 460 core
#pragma debug(on)
#pragma optimize(off)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;

uniform mat4 Projection;
uniform mat4 ModelView;

out vec3 normal_position;
out vec3 fragment_position;

void main() {
    vec4 position = vec4(aPosition, 1.0);

    gl_Position = Projection * ModelView * position;
    normal_position = mat3(transpose(inverse(ModelView))) * aNormal;
    fragment_position = vec3(ModelView * position);
}