#pragma once
#include <Core/Base.h>

typedef struct Game
{
    void (*OnCreate)(void);
    void (*OnUpdate)(void);
    void (*OnRender)(void);
    void (*OnRenderUI)(void);
} Game;

Game SetupGame();
