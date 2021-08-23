#version 400

in vec3 fragNormal;

layout(location = 0)out vec4 frag_colour;

uniform vec3 lightDir;
uniform sampler2D shadowMap;

void main() {
  vec3 normal = normalize(fragNormal);
  frag_colour = vec4(normal / 2.0f + vec3(0.5f), 1.0f); 
}
