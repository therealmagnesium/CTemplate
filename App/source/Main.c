#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Log.h>

#include <Graphics/Renderer.h>

int main(int argc, char* argv[])
{
    AppInfo appInfo;
    appInfo.title = "C Template";
    appInfo.screenWidth = 1280;
    appInfo.screenHeight = 720;

    CreateApplication(&appInfo);
    Renderer.clearColor = (Color){15, 15, 15, 255};
    RunApplication();

    return 0;
}
