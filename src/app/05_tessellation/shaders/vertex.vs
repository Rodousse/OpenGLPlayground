#version 400
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

out vec3 tesControlNormal;

uniform mat4 PV_mat;

void main() {
  gl_Position = PV_mat * vec4(position, 1.0f);
  tesControlNormal = normal;
}
