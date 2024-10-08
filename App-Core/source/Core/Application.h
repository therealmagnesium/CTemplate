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
    void (*OnShutdown)(void);
} GameState;

typedef struct AppState_t
{
    b8 isRunning;
    b8 isDebugEnabled;
    Window window;
    GameState* game;
} AppState;

extern AppState App;

void CreateApplication(GameState* game);
void RunApplication();
