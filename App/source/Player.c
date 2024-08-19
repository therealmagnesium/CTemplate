#include "Player.h"
#include "cglm/vec3.h"

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
    player->direction[0] = GetInputAxis(INPUT_AXIS_HORIZONTAL);
    player->direction[1] = GetInputAxis(INPUT_AXIS_VERTICAL);
    glm_normalize(player->direction);

    player->velocity[0] = player->speed * player->direction[0];
    player->velocity[1] = player->speed * player->direction[1];

    player->position[0] += player->velocity[0] * Time.delta;
    player->position[2] -= player->velocity[1] * Time.delta;
}

void DrawPlayer(Player* player)
{
    glm_mat4_identity(transform);
    glm_translate(transform, player->position);
    glm_rotate(transform, glm_rad(player->rotationAngle), player->rotationAxis);
    glm_scale(transform, player->scale);

    Renderer.DrawMesh(&player->mesh, &transform, &material);
}

Player CreatePlayer()
{
    Player player;

    glm_vec3_zero(player.position);
    glm_vec3_copy((vec3){2.f, 2.f, 1.f}, player.scale);
    glm_vec3_copy((vec3){1.f, 0.f, 0.f}, player.rotationAxis);

    player.rotationAngle = -70.f;
    player.speed = 3.f;

    glm_vec2_zero(player.velocity);
    glm_vec2_zero(player.direction);

    CreatePlayerMesh(&player);

    return player;
}
