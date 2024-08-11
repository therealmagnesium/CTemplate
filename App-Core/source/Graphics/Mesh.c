#include "Graphics/Mesh.h"
#include "Graphics/Renderer.h"

#include "Core/Base.h"

Mesh CreateMesh(const List* vertices, const List* indices)
{
    Mesh mesh;
    mesh.vertices = *vertices;
    mesh.indices = *indices;

    RenderInitMesh(&Renderer.state, &mesh);

    return mesh;
}
