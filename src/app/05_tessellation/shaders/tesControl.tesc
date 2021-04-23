#version 400

layout (vertices = 3) out;

in vec3 tesControlNormal[];

out vec3 tesEvalNormal[];


void main()
{
  tesEvalNormal[gl_InvocationID] = tesControlNormal[gl_InvocationID];
  gl_TessLevelOuter[0] = 7;
  gl_TessLevelOuter[1] = 7;
  gl_TessLevelOuter[2] = 7;

  gl_TessLevelInner[0] = 7;
  gl_TessLevelInner[1] = 7;
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
