#pragma once
#include "Core/Math.h"

#include "Graphics/Color.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/RendererInternal.h"
#include "Graphics/Shader.h"

#include <cglm/types.h>

typedef struct RenderState_t
{
    Color clearColor;
    InternalRenderState state;

    void (*BeginDrawing)(void);
    void (*EndDrawing)(void);
    void (*DrawRectangle)(vec2 position, vec2 size, Color color);
    void (*DrawMesh)(const Mesh* mesh, const mat4* transform, Material* material);
} RenderState;

extern RenderState Renderer;

void InitRenderer();
inline void SetPrimaryCamera(Camera* camera) { Renderer.state.primaryCamera = camera; }
