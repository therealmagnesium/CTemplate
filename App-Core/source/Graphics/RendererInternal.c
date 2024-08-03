#include "Graphics/RendererInternal.h"
#include "Core/Base.h"
#include "Graphics/Color.h"

#include <glad/glad.h>

#define VAO_STRIDE 3 * sizeof(float)

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
    glVertexAttribPointer(location, numElements, GL_FLOAT, GL_FALSE, VAO_STRIDE, (void*)offset);
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
    renderState.vao = CreateVertexArray();
    renderState.vbo = CreateVertexBuffer();
    renderState.ebo = CreateIndexBuffer();

    return renderState;
}

void RenderInitRect(VertexBuffer* vbo, IndexBuffer* ebo, VertexArray* vao)
{
    float vertices[] = {
        0.5f,  0.5f,  0.f, // v0
        0.5f,  -0.5f, 0.f, // v1
        -0.5f, -0.5f, 0.f, // v2
        -0.5f, 0.5f,  0.f, // v3
    };

    u32 indices[] = {
        0, 1, 3, // i0
        1, 2, 3, // i1
    };

    vao->Bind(vao->id);

    vbo->Bind(vbo->id);
    vbo->SetData(vertices, sizeof(vertices));

    ebo->Bind(ebo->id);
    ebo->SetData(indices, sizeof(indices));

    vao->SetAttributes(0, 3, 0);

    vao->Unbind();
}
