#include "Game.h"
#include "Player.h"

#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/IO.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>
#include <Core/Math.h>

#include <Graphics/Color.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shader.h>

#include <SDL2/SDL.h>

static Player player;

static void OnCreate()
{
    Renderer.clearColor = CreateColor(20, 20, 20, 255);
    player = CreatePlayer();
}

static void OnUpdate() { UpdatePlayer(&player); }

static void OnRender() { DrawPlayer(&player); }

static void OnRenderUI() {}

Game SetupGame()
{
    Game game;

    // Set function pointers for our game
    game.OnCreate = OnCreate;
    game.OnUpdate = OnUpdate;
    game.OnRender = OnRender;
    game.OnRenderUI = OnRenderUI;

    return game;
}
