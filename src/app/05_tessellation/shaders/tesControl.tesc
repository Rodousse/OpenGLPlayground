#version 400

layout (vertices = 3) out;

in vec3 tesControlNormalDisplacement[];
in vec2 tesControlUv[];
in mat3 tesControlTBN[];

out vec3 tesEvalNormalDisplacement[];
out vec2 tesEvalUv[];
out mat3 tesEvalTBN[];


void main()
{
  tesEvalNormalDisplacement[gl_InvocationID] = tesControlNormalDisplacement[gl_InvocationID];
  tesEvalUv[gl_InvocationID] = tesControlUv[gl_InvocationID];
  tesEvalTBN[gl_InvocationID] = tesControlTBN[gl_InvocationID];
  gl_TessLevelOuter[0] = 7;
  gl_TessLevelOuter[1] = 7;
  gl_TessLevelOuter[2] = 7;

  gl_TessLevelInner[0] = 7;
  gl_TessLevelInner[1] = 7;
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
