#version 420

in vec3 vertNormal;
in vec3 vertPosition;
in vec3 camPosition;

layout(location = 0)out vec4 frag_colour;

layout(std140, binding = 0) uniform UBOData
{
    vec3 lightPosition;
    float _1;
    vec3 lightDiffuseColor;
    float _2;
    vec3 lightAmbientColor;
    float _3;
    vec3 lightSpecularColor;
    float _4;
    vec3 materialColor;
    float materialSpecularity;
};

void main() {
    vec3 V = normalize(camPosition - vertPosition);
    vec3 L = normalize(lightPosition - vertPosition);
    float NL = dot(L,vertNormal);
    vec3 R = reflect(L, vertNormal);
    float RV = clamp(dot(R, V), 0.0, 1.0);
    frag_colour = vec4(lightAmbientColor + NL * lightDiffuseColor * materialColor + lightSpecularColor * pow(RV, materialSpecularity), 1.0f);

}