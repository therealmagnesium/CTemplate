#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include "Graphics/Window.h"

AppState App;
static b8 initialized = false;

void CreateApplication(AppInfo* info)
{
    if (initialized)
    {
        ERROR("CreateApplication(AppInfo*) can only be called once!");
        return;
    }

    InitLogging();

    App.isRunning = true;
    App.info = *info;
    App.window = CreateWindow();

    // TODO: Create window

    initialized = true;

    INFO("Successfully created the application!");
}

void RunApplication()
{
    while (App.isRunning)
    {
        App.window.HandleEvents();
    }

    App.window.Close();
    INFO("Successfully ended the application!");
}
