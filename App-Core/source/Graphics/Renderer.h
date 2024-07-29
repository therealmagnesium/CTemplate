#pragma once
#include "Core/Base.h"
#include "Graphics/Color.h"

typedef struct
{
    Color clearColor;

    void (*BeginDrawing)(void);
    void (*EndDrawing)(void);
} RenderState;

extern RenderState Renderer;

void InitRenderer();
