#pragma once
#include <Core/Math.h>
#include <Graphics/Color.h>
#include <Graphics/Texture.h>

typedef struct Player_t
{
    float speed;
    Vector2 position;
    Vector2 direction;
    Vector2 velocity;
    Vector2 size;
    Color color;
    Texture texture;
} Player;

Player CreatePlayer();
void UpdatePlayer(Player* player);
void DrawPlayer(Player* player);
