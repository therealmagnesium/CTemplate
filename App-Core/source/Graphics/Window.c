#include "Core/Application.h"
#include "Graphics/Window.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include <SDL2/SDL_video.h>

static void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
            {
                App.isRunning = false;
                break;
            };

            default:
                break;
        }
    }
}

static void Close()
{
    SDL_DestroyWindow(App.window.handle);
    SDL_Quit();
}

Window CreateWindow()
{
    // Setup window to be created
    Window window;
    window.width = App.info.screenWidth;
    window.height = App.info.screenHeight;
    window.title = App.info.title;
    window.vsync = true;
    window.fullscreen = false;
    window.handle = NULL;
    window.HandleEvents = HandleEvents;
    window.Close = Close;

    // Initialize SDL2
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        FATAL("Failed to init sdl2!");
        return (Window){};
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create the window handle
    s32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
    window.handle = SDL_CreateWindow(window.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window.width,
                                     window.height, flags);

    // Check if creating the window handle failed
    if (!window.handle)
    {
        FATAL("Failed to create window!");
        return (Window){};
    }

    void* glContext = SDL_GL_CreateContext(window.handle);

    return window;
}
