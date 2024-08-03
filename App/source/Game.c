#include "Game.h"

#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/IO.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>

#include <Graphics/Renderer.h>
#include <Graphics/Color.h>

typedef struct Rect
{
    vec2 position;
    vec2 size;
    Color color;
} Rect;

static Rect rect;

static void OnCreate()
{
    Renderer.clearColor = CreateColor(20, 20, 20, 255);

    rect.position = (vec2){200.f, 200.f};
    rect.size = (vec2){64.f, 64.f};
    rect.color = CreateColor(0x55, 0xBA, 0xA1, 0xFF);
}

static void OnUpdate()
{
    if (IsMouseClicked(MOUSE_BUTTON_LEFT))
        INFO("Left mouse button clicked");

    if (IsKeyPressed(KEY_SPACE))
        INFO("Space key pressed");
}

static void OnRender() { Renderer.DrawRectangle(rect.position, rect.size, rect.color); }

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
