#pragma once
#include "Core/Base.h"

#include "Graphics/Color.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

typedef enum MaterialMapIndex_t
{
    MATERIAL_MAP_DIFFUSE = 0,
    MATERIAL_MAP_SPECULAR,
    MATERIAL_MAP_COUNT
} MaterialMapIndex;

typedef struct MaterialMap_t
{
    float value;
    Color color;
    Texture texture;
} MaterialMap;

typedef struct Material_t
{
    Shader shader;
    MaterialMap maps[MATERIAL_MAP_COUNT];
} Material;
