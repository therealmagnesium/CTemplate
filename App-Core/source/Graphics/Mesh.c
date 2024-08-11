#include "Graphics/Mesh.h"
#include "Core/List.h"
#include "Core/Log.h"
#include "Graphics/Renderer.h"

#include "Core/Base.h"
#include <string.h>

Mesh CreateMesh(const Vertex* vertices, u64 vertexCount, const u32* indices, u64 indexCount)
{
    Mesh mesh;
    mesh.vertices = CreateList(vertexCount, sizeof(Vertex));
    mesh.indices = CreateList(indexCount, sizeof(u32));

    memcpy(mesh.vertices.data, vertices, sizeof(Vertex) * vertexCount);
    memcpy(mesh.indices.data, indices, sizeof(u32) * indexCount);

    RenderInitMesh(&Renderer.state, &mesh);

    return mesh;
}

void UnloadMesh(Mesh* mesh)
{
    FreeList(&mesh->vertices);
    FreeList(&mesh->indices);
}
