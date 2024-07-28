#pragma once
#include "Core/Base.h"
#include "Graphics/Window.h"

typedef struct
{
    u32 screenWidth;
    u32 screenHeight;
    const char* title;
} AppInfo;

typedef struct
{
    b8 isRunning;
    AppInfo info;
    Window window;
} AppState;

extern AppState App;

void CreateApplication(AppInfo* info);
void RunApplication();
