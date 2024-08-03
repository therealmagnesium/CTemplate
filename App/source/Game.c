#include "Game.h"

#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/IO.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>

#include <Graphics/Color.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shader.h>

#include <SDL2/SDL.h>

typedef struct Rect
{
    Vector2 position;
    Vector2 size;
    Color color;
} Rect;

static Rect rect;

static void OnCreate()
{
    Renderer.clearColor = CreateColor(20, 20, 20, 255);

    rect.position = (v2){200.f, 200.f};
    rect.size = (v2){64.f, 64.f};
    rect.color = CreateColor(0x55, 0xBA, 0xA1, 0xFF);
}

static void OnUpdate()
{
    if (IsKeyDown(KEY_RIGHT))
        rect.position.x += 20.f;
    if (IsKeyDown(KEY_LEFT))
        rect.position.x -= 20.f;
    if (IsKeyDown(KEY_DOWN))
        rect.position.y += 20.f;
    if (IsKeyDown(KEY_UP))
        rect.position.y -= 20.f;
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
