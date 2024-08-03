#include "Player.h"

#include <Core/Input.h>
#include <Core/Log.h>
#include <Core/Time.h>
#include <Graphics/Renderer.h>

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

void DrawPlayer(Player* player) { Renderer.DrawRectangle(player->position, player->size, player->color); }

Player CreatePlayer()
{
    Player player;

    player.speed = 800.f;
    player.position = (v2){200.f, 200.f};
    player.velocity = (v2){0.f, 0.f};
    player.direction = (v2){0.f, 0.f};
    player.size = (v2){64.f, 64.f};
    player.color = CreateColor(0x55, 0xBA, 0xA1, 0xFF);

    return player;
}
