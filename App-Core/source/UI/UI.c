#include "UI/UI.h"
#include "Core/Application.h"
#include "Core/Log.h"

#include <nuklear.h>
#include <nuklear_sdl_opengl3.h>

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

UIState UI;

void InitUI()
{
    // TODO: Allocate memory
    UI.context = nk_sdl_init(App.window.handle);
    if (!UI.context)
    {
        ERROR("Failed to initialize UI context!");
        return;
    }

    nk_sdl_font_stash_begin(&UI.fontAtlas);
    nk_sdl_font_stash_end();
}

void ShutdownUI() { nk_sdl_shutdown(); }

void BeginUIEventCheck() { nk_input_begin(UI.context); }

void EndUIEventCheck()
{
    nk_input_end(UI.context);
    nk_sdl_handle_grab();
}

void HandleUIEvents(SDL_Event* event) { nk_sdl_handle_event(event); }

void DrawUILayer() { nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY); }
