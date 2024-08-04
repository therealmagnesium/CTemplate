#pragma once
#include "Core/Math.h"
#include "Graphics/Color.h"

typedef struct RenderState_t
{
    Color clearColor;

    void (*BeginDrawing)(void);
    void (*EndDrawing)(void);
    void (*DrawRectangle)(v2 position, v2 size, Color color);
} RenderState;

extern RenderState Renderer;

void InitRenderer();
