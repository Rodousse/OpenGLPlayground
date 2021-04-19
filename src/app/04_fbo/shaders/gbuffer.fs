#version 420

in vec3 vertNormal;
in vec3 vertPosition;

layout(location = 0)out vec3 frag_position;
layout(location = 1)out vec3 frag_normal;


void main() {
    frag_normal = normalize(vertNormal);
    frag_position = vertPosition;
}
