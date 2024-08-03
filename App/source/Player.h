#pragma once
#include "Core/Math.h"
#include "Graphics/Color.h"

typedef struct Player_t
{
    float speed;
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    Vector2 size;
    Color color;
} Player;

Player CreatePlayer();
void UpdatePlayer(Player* player);
void DrawPlayer(Player* player);
