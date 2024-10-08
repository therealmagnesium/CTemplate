#pragma once
#include "Core/Base.h"

#include "Graphics/Camera.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"

#include <cglm/types.h>

typedef struct VertexArray_t
{
    u32 id;

    void (*Bind)(s32 vaoId);
    void (*Unbind)(void);
    void (*SetAttributes)(u8 location, u8 numElements, u64 offset);
} VertexArray;

typedef struct VertexBuffer_t
{
    u32 id;

    void (*Bind)(s32 vboId);
    void (*Unbind)(void);
    void (*SetData)(float* vertices, u64 size);
} VertexBuffer;

typedef struct IndexBuffer_t
{
    u32 id;

    void (*Bind)(s32 eboId);
    void (*Unbind)(void);
    void (*SetData)(u32* indices, u64 size);
} IndexBuffer;

typedef struct InternalRenderState_t
{
    VertexArray vaoRect;
    VertexBuffer vboRect;
    IndexBuffer eboRect;

    VertexArray vaoMesh;
    VertexBuffer vboMesh;
    IndexBuffer eboMesh;

    Shader defaultShader;
    Camera* primaryCamera;
} InternalRenderState;

VertexArray CreateVertexArray();
VertexBuffer CreateVertexBuffer();
IndexBuffer CreateIndexBuffer();
InternalRenderState CreateInternalRenderState();

void RenderInitRect(InternalRenderState* renderState);
void RenderInitMesh(InternalRenderState* renderState, const Mesh* mesh);
void RenderInitShaders(InternalRenderState* renderState);
