#version 420
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;

out vec3 vertNormal;
out vec3 vertPosition;
out vec3 camPosition;

uniform mat4 PV_mat;
uniform mat4 VI_mat;


void main() {
  gl_Position = PV_mat * vec4(position, 1.0f);
  vertNormal = normal;
  vertPosition = position;
  vec4 camPositionW = VI_mat * vec4(vec3(0.0f), 1.0f);
  camPosition = vec3(camPositionW);
}
