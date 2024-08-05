#pragma once
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Math.h"

#include "Graphics/Texture.h"

typedef struct Vertex_t
{
    Vector3 position;
    Vector2 texCoords;
    Vector3 normal;
} Vertex;

typedef struct Mesh_t
{
    List vertices;
    List indices;
    List textures;
} Mesh;

Mesh CreateMesh(Vertex* vertices, u32* indices, Texture* textures);
