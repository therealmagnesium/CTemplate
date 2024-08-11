#include "Graphics/RendererInternal.h"
#include "Core/List.h"
#include "Core/Log.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"

#include "Core/Application.h"
#include "Core/Base.h"

#include <cglm/cam.h>
#include <glad/glad.h>

static void BindVertexArray(s32 vaoId) { glBindVertexArray(vaoId); }
static void UnbindVertexArray() { glBindVertexArray(0); }
static void BindVertexBuffer(s32 vboId) { glBindBuffer(GL_ARRAY_BUFFER, vboId); }
static void UnbindVertexBuffer() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
static void BindIndexBuffer(s32 eboId) { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId); }
static void UnbindIndexBuffer() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

static void SetVertexBufferData(float* vertices, u64 size)
{
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

static void SetIndexBufferData(u32* indices, u64 size)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

static void SetVertexArrayAttributes(u8 location, u8 numElements, u64 offset)
{
    glEnableVertexAttribArray(location);
    glVertexAttribPointer(location, numElements, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offset);
}

VertexArray CreateVertexArray()
{
    VertexArray vao;
    vao.id = 0;
    vao.Bind = BindVertexArray;
    vao.Unbind = UnbindVertexArray;
    vao.SetAttributes = SetVertexArrayAttributes;

    glGenVertexArrays(1, &vao.id);
    return vao;
}

VertexBuffer CreateVertexBuffer()
{
    VertexBuffer vbo;
    vbo.id = 0;
    vbo.Bind = BindVertexBuffer;
    vbo.Unbind = UnbindVertexBuffer;
    vbo.SetData = SetVertexBufferData;

    glGenBuffers(1, &vbo.id);
    return vbo;
}

IndexBuffer CreateIndexBuffer()
{
    IndexBuffer ebo;
    ebo.id = 0;
    ebo.Bind = BindIndexBuffer;
    ebo.Unbind = UnbindIndexBuffer;
    ebo.SetData = SetIndexBufferData;

    glGenBuffers(1, &ebo.id);
    return ebo;
}

InternalRenderState CreateInternalRenderState()
{
    InternalRenderState renderState;
    renderState.vaoRect = CreateVertexArray();
    renderState.vboRect = CreateVertexBuffer();
    renderState.eboRect = CreateIndexBuffer();

    renderState.vaoMesh = CreateVertexArray();
    renderState.vboMesh = CreateVertexBuffer();
    renderState.eboMesh = CreateIndexBuffer();

    return renderState;
}

void RenderInitRect(InternalRenderState* renderState)
{
    Vertex vertices[4];
    vertices[0].position = (v3){0.5f, 0.5f, 0.f};
    vertices[1].position = (v3){0.5f, -0.5f, 0.f};
    vertices[2].position = (v3){-0.5f, -0.5f, 0.f};
    vertices[3].position = (v3){-0.5f, 0.5f, 0.f};

    for (u8 i = 0; i < 4; i++)
        vertices[i].normal = (v3){0.f, 0.f, -1.f};

    vertices[0].texCoords = (v2){1.f, 1.f};
    vertices[1].texCoords = (v2){1.f, 0.f};
    vertices[2].texCoords = (v2){0.f, 0.f};
    vertices[3].texCoords = (v2){0.f, 1.f};

    u32 indices[] = {
        0, 1, 3, // i0
        1, 2, 3, // i1
    };

    renderState->vaoRect.Bind(renderState->vaoRect.id);

    renderState->vboRect.Bind(renderState->vboRect.id);
    renderState->vboRect.SetData((void*)vertices, sizeof(vertices));

    renderState->eboRect.Bind(renderState->eboRect.id);
    renderState->eboRect.SetData(indices, sizeof(indices));

    renderState->vaoRect.SetAttributes(0, 3, 0);
    renderState->vaoRect.SetAttributes(1, 2, sizeof(float) * 3);
    renderState->vaoRect.SetAttributes(2, 3, sizeof(float) * 5);

    renderState->vaoRect.Unbind();
}

void RenderInitMesh(InternalRenderState* renderState, const Mesh* mesh)
{
    renderState->vaoMesh.Bind(renderState->vaoMesh.id);

    renderState->vboMesh.Bind(renderState->vboMesh.id);
    renderState->vboMesh.SetData(mesh->vertices.data, mesh->vertices.itemSize * mesh->vertices.capacity);

    renderState->eboMesh.Bind(renderState->eboMesh.id);
    renderState->eboMesh.SetData(mesh->indices.data, mesh->indices.itemSize * mesh->indices.capacity);

    renderState->vaoMesh.SetAttributes(0, 3, 0);
    renderState->vaoMesh.SetAttributes(1, 2, sizeof(float) * 3);
    renderState->vaoMesh.SetAttributes(2, 3, sizeof(float) * 5);

    renderState->vaoMesh.Unbind();
}

void RenderInitShaders(InternalRenderState* renderState)
{
    // Create default shader and set uniform locations
    renderState->defaultShader = CreateShader("assets/shaders/default_vs.glsl", "assets/shaders/default_fs.glsl");
    renderState->defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION] =
        GetUniformLocation(&renderState->defaultShader, "projection");
    renderState->defaultShader.uniformLocs[SHADER_LOC_MATRIX_MODEL] =
        GetUniformLocation(&renderState->defaultShader, "model");
    renderState->defaultShader.uniformLocs[SHADER_LOC_COLOR_DIFFUSE] =
        GetUniformLocation(&renderState->defaultShader, "tint");
    renderState->defaultShader.uniformLocs[SHADER_LOC_MAP_DIFFUSE] =
        GetUniformLocation(&renderState->defaultShader, "material.diffuseMap");

    glm_ortho(0.f, App.window.width, App.window.height, 0.f, -2.f, 2.f, renderState->projection);

    renderState->defaultShader.Bind(renderState->defaultShader.id);
    renderState->defaultShader.SetMat4(renderState->defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                                       (float*)renderState->projection);
}
