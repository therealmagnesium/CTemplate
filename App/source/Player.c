#include "Player.h"

#include <Core/Input.h>
#include <Core/Log.h>
#include <Core/Time.h>

#include <Graphics/Material.h>
#include <Graphics/Renderer.h>
#include <Graphics/Texture.h>
#include <Graphics/Mesh.h>

#include <stdlib.h>
#include <cglm/cglm.h>

static Mesh test;
static Material material;
static mat4 transform;

static void CreatePlayerMesh()
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

    u32 indices[] = {
        0, 1, 3, // i0
        1, 2, 3, // i1
    };

    List vList, iList;
    vList.data = vertices;
    vList.itemSize = sizeof(Vertex);
    vList.capacity = 4;

    iList.data = indices;
    iList.itemSize = sizeof(u32);
    iList.capacity = 6;

    test = CreateMesh(&vList, &iList);
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
    player->position.y += player->velocity.y * Time.delta;
}

void DrawPlayer(Player* player)
{
    glm_mat4_identity(transform);
    glm_translate(transform, (float*)&player->position);
    glm_scale(transform, (float*)&player->size);
    Renderer.DrawMesh(&test, &transform, &material);

    // Renderer.DrawRectangle(player->position, player->size, player->color);
}

Player CreatePlayer()
{
    Player player;

    player.speed = 800.f;
    player.position = (v3){200.f, 200.f, 0.f};
    player.size = (v3){200.f, 200.f, 0.f};
    player.velocity = (v2){0.f, 0.f};
    player.direction = (v2){0.f, 0.f};
    player.color = CreateColor(0xFF, 0xFF, 0xFF, 0xFF);

    CreatePlayerMesh();

    return player;
}
