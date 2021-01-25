#version 400

in vec3 vertexColor;

layout(location = 0)out vec4 frag_colour;


void main() {
    frag_colour = vec4(vertexColor, 1.0f);
}