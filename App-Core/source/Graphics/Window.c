#include "Core/Application.h"
#include "Graphics/Window.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"

#include <SDL2/SDL_video.h>
#include <glad/glad.h>

static void HandleEvents()
{
    Input.mouse.clicked = false;
    Input.key.pressed = false;

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

            case SDL_MOUSEMOTION:
            {
                Input.mouse.position.x = event.motion.x;
                Input.mouse.position.y = event.motion.y;

                break;
            }

            case SDL_MOUSEBUTTONDOWN:
            {
                Input.mouse.clicked = !Input.mouse.held;
                Input.mouse.held = true;
                Input.mouse.button = event.button.button;

                break;
            }

            case SDL_MOUSEBUTTONUP:
            {
                Input.mouse.clicked = false;
                Input.mouse.held = false;
                Input.mouse.button = 0;

                break;
            }

            case SDL_KEYDOWN:
            {
                Input.key.pressed = !Input.key.held;
                Input.key.held = true;
                Input.key.scancode = event.key.keysym.scancode;

                break;
            }

            case SDL_KEYUP:
            {
                Input.key.pressed = false;
                Input.key.held = false;
                Input.key.scancode = 0;

                break;
            }

            default:
                break;
        }
    }

    if (IsKeyPressed(KEY_ESCAPE))
        App.isRunning = false;
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
    s32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    window.handle = SDL_CreateWindow(window.title, 200, 200, window.width, window.height, flags);

    // Check if creating the window handle failed
    if (!window.handle)
    {
        FATAL("Failed to create window!");
        return (Window){};
    }

    void* glContext = SDL_GL_CreateContext(window.handle);
    gladLoadGL();

    return window;
}
