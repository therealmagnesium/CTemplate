#pragma once
#include "Core/Base.h"
#include "Core/Math.h"

typedef enum
{
    RGB = 0,
    RGBA,
} TextureFormat;

typedef struct Texture_t
{
    u32 id;
    b8 isValid;
    s32 width;
    s32 height;
    s32 channelCount;
} Texture;

Texture LoadTexture(const char* path, TextureFormat format);
void BindTexture(Texture* texture, u8 slot);
