#include "Player.h"

#include <Core/Input.h>
#include <Core/Log.h>
#include <Core/Time.h>

#include <Graphics/Renderer.h>
#include <Graphics/Texture.h>
#include <Graphics/Mesh.h>

#include <glad/glad.h>

static Mesh test;

void UpdatePlayer(Player* player)
{
    player->direction.x = GetInputAxis(INPUT_AXIS_HORIZONTAL);
    player->direction.y = GetInputAxis(INPUT_AXIS_VERTICAL);
    NormalizeV2(&player->direction);
    player->velocity.x = player->speed * player->direction.x;
    player->velocity.y = player->speed * player->direction.y;

    player->position.x += player->velocity.x * Time.delta;
    player->position.y += player->velocity.y * Time.delta;
}

void DrawPlayer(Player* player)
{
    BindTexture(&player->texture, 0);
    Renderer.DrawRectangle(player->position, player->size, player->color);
}

Player CreatePlayer()
{
    Player player;

    player.speed = 800.f;
    player.position = (v2){200.f, 200.f};
    player.velocity = (v2){0.f, 0.f};
    player.direction = (v2){0.f, 0.f};
    player.size = (v2){200.f, 200.f};
    player.color = CreateColor(0x55, 0xBA, 0xA1, 0xFF);
    player.texture = LoadTexture("assets/textures/small_checker.png", GL_RGB);

    Vertex vertices[4];
    vertices[0].position = (v3){0.5f, 0.5f, 0.f};
    vertices[1].position = (v3){0.5f, -0.5f, 0.f};
    vertices[2].position = (v3){-0.5f, -0.5f, 0.f};
    vertices[3].position = (v3){-0.5f, 0.5f, 0.f};

    for (u8 i = 0; i < 4; i++)
        vertices[i].normal = (v3){0.f, 0.f, -1.f};

    vertices[0].texCoords = (v2){1.f, 1.f};
    vertices[1].texCoords = (v2){1.f, 0.f};
    vertices[2].texCoords = (v2){0.f, 0.f};
    vertices[3].texCoords = (v2){0.f, 1.f};

    u32 indices[] = {
        0, 1, 3, // i0
        1, 2, 3, // i1
    };

    test = CreateMesh(vertices, indices, &player.texture);

    return player;
}
