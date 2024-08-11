#pragma once
#include <Core/Math.h>
#include <Graphics/Color.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>

typedef struct Player_t
{
    float speed;
    Vector3 position;
    Vector3 size;
    Vector2 direction;
    Vector2 velocity;
    Mesh mesh;
} Player;

Player CreatePlayer();
void UpdatePlayer(Player* player);
void DrawPlayer(Player* player);
