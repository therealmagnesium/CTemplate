#pragma once
#include "Core/Base.h"
#include "Graphics/Color.h"

typedef struct RenderState
{
    Color clearColor;

    void (*BeginDrawing)(void);
    void (*EndDrawing)(void);
    void (*DrawRectangle)(v2 position, v2 size, Color color);
} RenderState;

extern RenderState Renderer;

void InitRenderer();
