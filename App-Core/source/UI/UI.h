#pragma once
#include <nuklear.h>
#include <SDL2/SDL_events.h>

typedef struct nk_context UIContext;
typedef struct nk_font_atlas UIFontAtlas;

typedef struct UIState_t
{
    UIContext* context;
    UIFontAtlas* fontAtlas;
} UIState;

extern UIState UI;

void InitUI();
void ShutdownUI();
void BeginUIEventCheck();
void EndUIEventCheck();
void HandleUIEvents(SDL_Event* event);
void DrawUILayer();
