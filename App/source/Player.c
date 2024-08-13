#include "Player.h"

#include <Core/Input.h>
#include <Core/List.h>
#include <Core/Log.h>
#include <Core/Math.h>
#include <Core/Time.h>

#include <Graphics/Color.h>
#include <Graphics/Material.h>
#include <Graphics/Renderer.h>
#include <Graphics/Texture.h>
#include <Graphics/Mesh.h>

#include <stdlib.h>
#include <cglm/cglm.h>

// TODO: Put mesh, transform, and material into a Model struct

static Material material;
static mat4 transform;

static void CreatePlayerMesh(Player* player)
{
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

    u32 indices[6] = {
        0, 1, 3, // i0
        1, 2, 3, // i1
    };

    player->mesh = CreateMesh(vertices, LEN(vertices), indices, LEN(indices));
    material.maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("assets/textures/small_checker.png", RGB);
    material.shader = Renderer.state.defaultShader;
}

void UpdatePlayer(Player* player)
{
    player->direction.x = GetInputAxis(INPUT_AXIS_HORIZONTAL);
    player->direction.y = GetInputAxis(INPUT_AXIS_VERTICAL);
    NormalizeV2(&player->direction);
    player->velocity.x = player->speed * player->direction.x;
    player->velocity.y = player->speed * player->direction.y;

    player->position.x += player->velocity.x * Time.delta;
    player->position.z -= player->velocity.y * Time.delta;
}

void DrawPlayer(Player* player)
{
    glm_mat4_identity(transform);
    glm_translate(transform, ValuePointerV3(&player->position));
    glm_rotate(transform, glm_rad(player->rotationAngle), ValuePointerV3(&player->rotationAxis));
    glm_scale(transform, ValuePointerV3(&player->scale));

    Renderer.DrawMesh(&player->mesh, &transform, &material);
}

Player CreatePlayer()
{
    Player player;

    player.position = (v3){0.f, 0.f, 0.f};
    player.scale = (v3){2.f, 2.f, 1.f};
    player.rotationAxis = (v3){1.f, 0.f, 0.f};
    player.rotationAngle = -55.f;
    player.speed = 3.f;

    player.velocity = (v2){0.f, 0.f};
    player.direction = (v2){0.f, 0.f};

    CreatePlayerMesh(&player);

    return player;
}
