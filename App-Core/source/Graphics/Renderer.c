#include "Graphics/Renderer.h"
#include "Graphics/Color.h"
#include "Core/Application.h"
#include "Core/Base.h"

#include <SDL2/SDL_video.h>
#include <glad/glad.h>

RenderState Renderer;

static void BeginDrawing()
{
    Vector4 normalizedClearColor = NormalizeColor(Renderer.clearColor);
    glClearColor(V4_OPEN(normalizedClearColor));
    glClear(GL_COLOR_BUFFER_BIT);
}

static void EndDrawing() { SDL_GL_SwapWindow(App.window.handle); }

void InitRenderer()
{
    Renderer.clearColor = (Color){0xFF, 0xFF, 0xFF, 0xFF};
    Renderer.BeginDrawing = BeginDrawing;
    Renderer.EndDrawing = EndDrawing;
}
