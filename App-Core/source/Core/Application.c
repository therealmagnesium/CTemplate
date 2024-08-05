#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Log.h"
#include "Core/Time.h"

#include "Graphics/Window.h"
#include "Graphics/Renderer.h"

#include "UI/UI.h"

#include <glad/glad.h>

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
    InitTimeState(60);

    App.isRunning = true;
    App.game = game;
    App.window = CreateWindow(&game->info);
    App.isDebugEnabled = false;

    InitRenderer();
    InitUI();
    App.game->OnCreate();

    initialized = true;

    INFO("Successfully created the application!");
    INFO("GPU vendor - %s", glGetString(GL_VENDOR));
    INFO("Renderer - %s", glGetString(GL_RENDERER));
    INFO("OpenGL version - %s", glGetString(GL_VERSION));
}

void RunApplication()
{
    while (App.isRunning)
    {
        App.window.HandleEvents();
        App.game->OnUpdate();
        App.game->OnRenderUI();

        Renderer.BeginDrawing();
        {
            App.game->OnRender();
        }
        Renderer.EndDrawing();
        UpdateTimeLate();
    }

    ShutdownUI();
    App.window.Close();

    INFO("Successfully ended the application!");
}
