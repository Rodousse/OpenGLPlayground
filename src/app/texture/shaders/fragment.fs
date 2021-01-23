#version 400

in vec2 vertexUv;

layout(location = 0)out vec4 frag_colour;

void main() {
    frag_colour = vec4(vertexUv, 1.0f, 1.0f);
}