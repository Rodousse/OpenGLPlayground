#version 400

in vec2 vertexUv;

uniform sampler2D textureSampler;

layout(location = 0)out vec4 frag_colour;

void main() {
    frag_colour = texture(textureSampler, vertexUv);
}