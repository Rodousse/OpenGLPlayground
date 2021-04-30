#version 400
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 uv;
layout(location=3) in vec3 tangent;
layout(location=4) in vec3 bitangent;

out vec3 tesControlNormalDisplacement;
out vec2 tesControlUv;
out mat3 tesControlTBN;

uniform mat4 PV_mat;

void main() {
  gl_Position = PV_mat * vec4(position, 1.0f);
  tesControlNormalDisplacement = normalize((PV_mat * vec4(normal, 0.0)).xyz);
  tesControlUv = uv;
  tesControlTBN = mat3(tangent, bitangent, normal);
}
