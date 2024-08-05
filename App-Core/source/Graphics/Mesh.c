#include "Graphics/Mesh.h"
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"

#include "Core/Base.h"
#include "Core/Math.h"

Mesh CreateMesh(Vertex* vertices, u32* indices, Texture* textures)
{
    Mesh mesh;
    mesh.vertices.data = vertices;
    mesh.indices.data = indices;
    mesh.textures.data = textures;

    RenderInitMesh(&Renderer.state, &mesh);

    return mesh;
}
