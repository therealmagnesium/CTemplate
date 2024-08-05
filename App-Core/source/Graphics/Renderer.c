#include "Graphics/Renderer.h"
#include "Graphics/RendererInternal.h"
#include "Graphics/Color.h"
#include "Graphics/Shader.h"

#include "UI/UI.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <cglm/types.h>
#include <cglm/mat4.h>
#include <cglm/affine.h>

RenderState Renderer;
static bool initialized = false;

static void BeginDrawing()
{
    Vector4 normalizedClearColor = NormalizeColor(Renderer.clearColor);
    glClearColor(V4_OPEN(normalizedClearColor));
    glClear(GL_COLOR_BUFFER_BIT);
}

static void EndDrawing()
{
    DrawUILayer();
    SDL_GL_SwapWindow(App.window.handle);
}

static void DrawRectangle(v2 position, v2 size, Color color)
{
    v3 p = {position.x, position.y, 0.f};
    v3 s = {size.x, size.y, 0.f};

    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, (float*)&p);
    glm_scale(model, (float*)&s);

    Vector4 normalizedColor = NormalizeColor(color);

    Renderer.state.defaultShader.Bind(Renderer.state.defaultShader.id);
    Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_MODEL],
                                         (float*)model);
    Renderer.state.defaultShader.SetVec4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_COLOR_DIFFUSE],
                                         (float*)&normalizedColor);

    Renderer.state.vaoRect.Bind(Renderer.state.vaoRect.id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    Renderer.state.vaoRect.Unbind();
}

void InitRenderer()
{
    if (initialized)
    {
        ERROR("Renderer is already initialized!");
        return;
    }

    Renderer.clearColor = (Color){0xFF, 0xFF, 0xFF, 0xFF};
    Renderer.BeginDrawing = BeginDrawing;
    Renderer.EndDrawing = EndDrawing;
    Renderer.DrawRectangle = DrawRectangle;

    Renderer.state = CreateInternalRenderState();
    RenderInitShaders(&Renderer.state);
    RenderInitRect(&Renderer.state);

    initialized = true;
}
