#include "Game.h"

#include <Core/Base.h>
#include <Core/EntryPoint.h>

void CreateGameState(GameState* gameState)
{
    Game game = SetupGame(); // Setup the game with correct function pointers

    // Set application info
    gameState->info.screenWidth = 1280;
    gameState->info.screenHeight = 720;
    gameState->info.title = "C Template";

    // Set the game state's function pointers
    gameState->OnCreate = game.OnCreate;
    gameState->OnUpdate = game.OnUpdate;
    gameState->OnRender = game.OnRender;
    gameState->OnRenderUI = game.OnRenderUI;
}
