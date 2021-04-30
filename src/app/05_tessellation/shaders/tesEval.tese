#version 400 


layout(triangles, equal_spacing, ccw) in;

in vec3 tesEvalNormal[];
in vec2 tesEvalUv[];
in vec3 tesEvalNormalDisplacement[];
in mat3 tesEvalTBN[];

out vec2 fragUv;
out mat3 fragTBN;

uniform sampler2D heightMap;
uniform float displacementAmplitude;

mat3 interpolateMat3(in mat3 m0, in mat3 m1, in mat3 m2)
{
  return gl_TessCoord.x * m0 + gl_TessCoord.y * m1 + gl_TessCoord.z * m2;
}

vec4 interpolateVec4(in vec4 v0, in vec4 v1, in vec4 v2)
{
  return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec3 interpolateVec3(in vec3 v0, in vec3 v1, in vec3 v2)
{
  return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec2 interpolateVec2(in vec2 v0, in vec2 v1, in vec2 v2)
{
  return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

void main()
{
  fragTBN = interpolateMat3(tesEvalTBN[0], tesEvalTBN[1], tesEvalTBN[2]);
  fragUv = interpolateVec2(tesEvalUv[0], tesEvalUv[1], tesEvalUv[2]);
  vec3 displacementNormal = normalize(interpolateVec3(tesEvalNormalDisplacement[0], tesEvalNormalDisplacement[1], tesEvalNormalDisplacement[2]));
  gl_Position = interpolateVec4(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
  gl_Position = vec4(texture(heightMap, fragUv).x * normalize(displacementNormal) * displacementAmplitude, 0.0) + gl_Position;

}
