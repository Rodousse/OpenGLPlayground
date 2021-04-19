#include "fbo/Types.hpp"

#include <functional>

GLuint getAttachmentTextureFromGBufferTextures(const GBufferTextures& targets, GBufferAttachment attachment)
{
    switch(attachment)
    {
        case GBufferAttachment::Position: return targets[0].first; break;
        case GBufferAttachment::Normal: return targets[1].first; break;
        case GBufferAttachment::Depth: return targets[2].first; break;
    }
    throw std::bad_function_call();
}
const TextureProperties& getTexturePropertiesFromGBufferTextures(const GBufferTextures& targets,
                                                                 GBufferAttachment attachment)
{
    switch(attachment)
    {
        case GBufferAttachment::Position: return targets[0].second; break;
        case GBufferAttachment::Normal: return targets[1].second; break;
        case GBufferAttachment::Depth: return targets[2].second; break;
    }
    throw std::bad_function_call();
}
