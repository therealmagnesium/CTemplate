#pragma once
#include "Core/Base.h"

#include <SDL2/SDL.h>

struct AppInfo; // Forward declaration

typedef struct Window
{
    u16 width;
    u16 height;
    b8 vsync;
    b8 fullscreen;
    const char* title;
    SDL_Window* handle;

    void (*HandleEvents)(void);
    void (*Close)(void);

} Window;

Window CreateWindow(struct AppInfo* info);
