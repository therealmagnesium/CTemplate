#include "Game.h"
#include "Player.h"
#include "DebugLayer.h"

#include <Core/Application.h>
#include <Core/Base.h>
#include <Core/Input.h>
#include <Core/IO.h>
#include <Core/KeyCodes.h>
#include <Core/Log.h>
#include <Core/Math.h>
#include <Core/Time.h>

#include <Graphics/Camera.h>
#include <Graphics/Color.h>
#include <Graphics/Mesh.h>
#include <Graphics/Renderer.h>
#include <Graphics/Shader.h>

#include <UI/UI.h>

#include <cglm/cglm.h>

static Player player;
static Camera camera;

static void OnCreate()
{
    camera = CreateCamera((vec3){0.f, 0.f, 2.f}, (vec3){0.f, 1.f, 0.f}, 45.f);
    SetPrimaryCamera(&camera);

    Renderer.clearColor = CreateColor(20, 20, 20, 255);
    player = CreatePlayer();
}

static void OnUpdate()
{
    if (IsKeyPressed(KEY_F9))
        App.isDebugEnabled = !App.isDebugEnabled;

    if (!App.isDebugEnabled)
        UpdateCamera(CAMERA_FREE);

    if (IsKeyPressed(KEY_F1))
        LogCameraInfo(&camera);
}

static void OnRender() { DrawPlayer(&player); }

static void OnRenderUI()
{
    if (App.isDebugEnabled)
        DrawDebugMenu();
}

static void OnShutdown() { UnloadMesh(&player.mesh); }

Game SetupGame()
{
    Game game;

    // Set function pointers for our game
    game.OnCreate = OnCreate;
    game.OnUpdate = OnUpdate;
    game.OnRender = OnRender;
    game.OnRenderUI = OnRenderUI;
    game.OnShutdown = OnShutdown;

    return game;
}
