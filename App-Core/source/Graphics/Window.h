#pragma once
#include "Core/Application.h"
#include "Core/Base.h"

#include <SDL2/SDL.h>

typedef struct
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

Window CreateWindow();
