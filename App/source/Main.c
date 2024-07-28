#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Log.h>

int main(int argc, char* argv[])
{
    u32 funnyNumber = 420;
    INFO("Funny number - %d", funnyNumber);
    WARN("Funny number - %d", funnyNumber);
    ERROR("Funny number - %d", funnyNumber);
    FATAL("Funny number - %d", funnyNumber);
    TRACE("Funny number - %d", funnyNumber);

    AppInfo appInfo;
    appInfo.title = "C Template";
    appInfo.screenWidth = 1280;
    appInfo.screenWidth = 720;

    CreateApplication(&appInfo);
    // RunApplication();
    return 0;
}
