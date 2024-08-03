#pragma once
#include "Core/Base.h"
#include "Graphics/Shader.h"

#include <cglm/types.h>

typedef struct VertexArray
{
    u32 id;

    void (*Bind)(s32 vaoId);
    void (*Unbind)(void);
    void (*SetAttributes)(u8 location, u8 numElements, u64 offset);
} VertexArray;

typedef struct VertexBuffer
{
    u32 id;

    void (*Bind)(s32 vboId);
    void (*Unbind)(void);
    void (*SetData)(float* vertices, u64 size);
} VertexBuffer;

typedef struct IndexBuffer
{
    u32 id;

    void (*Bind)(s32 eboId);
    void (*Unbind)(void);
    void (*SetData)(u32* indices, u64 size);
} IndexBuffer;

typedef struct InternalRenderState
{
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;
    Shader shader;

    mat4 projection;
} InternalRenderState;

VertexArray CreateVertexArray();
VertexBuffer CreateVertexBuffer();
IndexBuffer CreateIndexBuffer();
InternalRenderState CreateInternalRenderState();

void RenderInitRect(InternalRenderState* renderState);
void RenderInitShaders(InternalRenderState* renderState);
