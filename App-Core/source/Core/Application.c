#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"

AppState App;
static b8 initialized = false;

void CreateApplication(GameState* game)
{
    if (initialized)
    {
        ERROR("CreateApplication(AppInfo*) can only be called once!");
        return;
    }

    InitLogging();

    App.isRunning = true;
    App.game = game;
    App.window = CreateWindow(&game->info);

    InitRenderer();
    App.game->OnCreate();

    initialized = true;
    INFO("Successfully created the application!");
}

void RunApplication()
{
    while (App.isRunning)
    {
        App.window.HandleEvents();
        App.game->OnUpdate();

        Renderer.BeginDrawing();
        {
            App.game->OnRender();
            App.game->OnRenderUI();
        }
        Renderer.EndDrawing();
    }

    App.window.Close();
    INFO("Successfully ended the application!");
}
