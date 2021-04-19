#pragma once
#include <GL/glew.h>
#include <array>
#include <engine/CommonTypes.hpp>

struct LightMaterial
{
    Vector3 lightPosition{0.0f, 0.0f, 0.0f};
    float lightIntensity{1000.0f};
    Vector3 lightDiffuseColor{1.0f, 1.0f, 1.0f};
    float materialSpecularity{5.0f};
    Vector3 lightAmbientColor{0.0f, 0.0f, 0.0f};
    float _1;
    Vector3 lightSpecularColor{1.0f, 1.0f, 1.0f};
    float _2;
    Vector3 materialColor{1.0f, 1.0f, 1.0f};
};

enum class GBufferAttachment
{
    Position,
    Normal,
    Depth
};

constexpr int GBUFFER_NB_ATTACHMENTS{3};

struct TextureProperties
{
    GLenum format;
    GLint internalFormat;
    GLenum type;
    GLenum attachment;
};

using GBufferTextures = std::array<std::pair<GLuint, TextureProperties>, GBUFFER_NB_ATTACHMENTS>;

GLuint getAttachmentTextureFromGBufferTextures(const GBufferTextures& targets, GBufferAttachment attachment);

const TextureProperties& getTexturePropertiesFromGBufferTextures(const GBufferTextures& targets,
                                                                 GBufferAttachment attachment);
