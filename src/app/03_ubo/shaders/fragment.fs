#version 420

in vec3 vertNormal;
in vec3 vertPosition;
in vec3 camPosition;

layout(location = 0)out vec4 frag_colour;

layout(std140, binding = 0) uniform UBOData
{
    vec3 lightPosition;
    float lightIntensity;
    vec3 lightDiffuseColor;
    float materialSpecularity;
    vec3 lightAmbientColor;
    float _1;
    vec3 lightSpecularColor;
    float _2;
    vec3 materialColor;
};

void main() {
    vec3 N = normalize(vertNormal);
    vec3 V = normalize(camPosition - vertPosition);
    vec3 L = normalize(lightPosition - vertPosition);
    float NL = max(dot(L,N), 0.0);
    vec3 R = -reflect(L, N);
    float RV = max(dot(R, V), 0.0);
    float lightDist = length(vertPosition - lightPosition);
    float fallOff = lightIntensity / (1.0f + 1.0f * lightDist + 0.5 * pow(lightDist, 2.0));
    vec3 color = lightAmbientColor + fallOff * (NL * lightDiffuseColor * materialColor)  + (lightSpecularColor * pow(RV, materialSpecularity));
    frag_colour = vec4(color, 1.0f);

}