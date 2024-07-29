#include "Game.h"

#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>

#include <Graphics/Renderer.h>
#include <Graphics/Color.h>

static void OnCreate() { Renderer.clearColor = CreateColor(20, 20, 20, 255); }

static void OnUpdate()
{
    if (IsMouseClicked(MOUSE_BUTTON_LEFT))
        INFO("Left mouse button clicked");

    if (IsKeyPressed(KEY_SPACE))
        INFO("Space key pressed");
}

static void OnRender() {}

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
