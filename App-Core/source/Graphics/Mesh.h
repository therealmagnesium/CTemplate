#pragma once
#include "Core/Base.h"
#include "Core/List.h"
#include "Core/Math.h"

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
} Mesh;

Mesh CreateMesh(const List* vertices, const List* indices);
