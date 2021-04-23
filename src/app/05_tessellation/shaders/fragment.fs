#version 400

in vec3 fragNormal;

layout(location = 0)out vec4 frag_colour;

uniform vec3 lightDir;

void main() {
    frag_colour = vec4(dot(fragNormal,lightDir));
}
