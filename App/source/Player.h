#pragma once
#include <Graphics/Color.h>
#include <Graphics/Mesh.h>
#include <Graphics/Texture.h>

#include <cglm/cglm.h>

typedef struct Player_t
{
    vec3 position;
    vec3 scale;
    vec3 rotationAxis;
    float rotationAngle;
    float speed;

    vec2 direction;
    vec2 velocity;
    Mesh mesh;
} Player;

Player CreatePlayer();
void UpdatePlayer(Player* player);
void DrawPlayer(Player* player);
