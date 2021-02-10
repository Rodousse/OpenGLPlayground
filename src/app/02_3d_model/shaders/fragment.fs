#version 400

in vec3 vertNormal;

layout(location = 0)out vec4 frag_colour;

uniform vec3 lightDir;

void main() {
    frag_colour = vec4(clamp(dot(vertNormal,lightDir), 0.0f, 1.0f));
}