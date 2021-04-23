#version 400 


layout(triangles, equal_spacing, ccw) in;

in vec3 tesEvalNormal[];
out vec3 fragNormal;

vec4 interpolateVec4(vec4 v0, vec4 v1, vec4 v2)
{
  return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec3 interpolateVec3(vec3 v0, vec3 v1, vec3 v2)
{
  return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

void main()
{
  gl_Position = interpolateVec4(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
  fragNormal = interpolateVec3(tesEvalNormal[0], tesEvalNormal[1], tesEvalNormal[2]);

}
