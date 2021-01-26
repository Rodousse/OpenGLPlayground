#version 400

in vec3 vertNormal;

layout(location = 0)out vec4 frag_colour;

void main() {
    frag_colour = vec4(dot(vertNormal,vec3(-1.0f, 0.0f, 0.0f)));
}