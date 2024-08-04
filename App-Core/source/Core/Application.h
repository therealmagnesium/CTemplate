#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"
#include <nuklear.h>

typedef struct AppInfo_t
{
    u32 screenWidth;
    u32 screenHeight;
    const char* title;
} AppInfo;

typedef struct GameState_t
{
    AppInfo info;

    void (*OnCreate)(void);
    void (*OnUpdate)(void);
    void (*OnRender)(void);
    void (*OnRenderUI)(void);
} GameState;

typedef struct AppState_t
{
    b8 isRunning;
    Window window;
    GameState* game;
} AppState;

extern AppState App;

void CreateApplication(GameState* game);
void RunApplication();
