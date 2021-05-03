#version 400

in vec2 fragUv;
in mat3 fragTBN;

layout(location = 0)out vec4 frag_colour;

uniform vec3 lightDir;
uniform sampler2D normalMap;
uniform sampler2D diffuseMap;

void main() {
  vec3 normal = texture(normalMap, fragUv).xyz * 2.0 - 1.0; 
  normal = normalize(fragTBN * normal);
  frag_colour = vec4(texture(diffuseMap, fragUv).xyz * dot(normalize(normal),lightDir), 1.0);
}
