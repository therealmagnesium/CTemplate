#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Math.h"
#include "Core/Log.h"
#include "Core/Time.h"
#include "cglm/vec3.h"

#include <cglm/cglm.h>

Camera CreateCamera(vec3 position, vec3 up, float fov)
{
    Camera camera;
    glm_vec3_copy(position, camera.position);
    glm_vec3_copy(up, camera.up);
    glm_vec3_copy((vec3){0.f, 0.f, 0.f}, camera.target);
    camera.fov = fov;

    vec3 cameraToTarget;
    glm_vec3_sub(camera.target, camera.position, cameraToTarget);
    glm_normalize(cameraToTarget);
    glm_vec3_copy(cameraToTarget, camera.direction);

    glm_mat4_identity(camera.projection);
    glm_mat4_identity(camera.view);

    return camera;
}

static void UpdateCameraFree()
{
    float speed = 3.f;

    vec3 right;
    glm_vec3_cross((vec3){0.f, 0.f, -1.f}, Renderer.state.primaryCamera->up, right);
    glm_vec3_normalize(right);

    if (IsKeyDown(KEY_W))
        glm_vec3_add((vec3){0.f, 0.f, -1.f * 3 * Time.delta}, Renderer.state.primaryCamera->position,
                     Renderer.state.primaryCamera->position);
    if (IsKeyDown(KEY_S))
        glm_vec3_sub(Renderer.state.primaryCamera->position, (vec3){0.f, 0.f, -1.f * 3 * Time.delta},
                     Renderer.state.primaryCamera->position);

    if (IsKeyDown(KEY_D))
    {
        vec3 horizontalMovement;
        glm_vec3_muladds(right, speed * Time.delta, horizontalMovement);
        glm_vec3_add(Renderer.state.primaryCamera->position, horizontalMovement,
                     Renderer.state.primaryCamera->position);
    }

    if (IsKeyDown(KEY_A))
    {
        vec3 horizontalMovement;
        glm_vec3_muladds(right, speed * Time.delta, horizontalMovement);
        glm_vec3_sub(Renderer.state.primaryCamera->position, horizontalMovement,
                     Renderer.state.primaryCamera->position);
    }
}

static void UpdateCameraOrbital() {}

void UpdateCamera(CameraType type)
{
    if (Renderer.state.primaryCamera)
    {
        switch (type)
        {
            case CAMERA_FREE:
            {
                UpdateCameraFree();
                break;
            }

            case CAMERA_ORBITAL:
            {
                UpdateCameraOrbital();
                break;
            }

            default:
                break;
        }
    }
}

void UpdateCameraMatrices()
{
    if (Renderer.state.primaryCamera)
    {
        vec3 center;
        float aspect = (float)App.window.width / App.window.height;
        glm_vec3_add(Renderer.state.primaryCamera->position, (vec3){0.f, 0.f, -1.f}, center);
        glm_lookat(Renderer.state.primaryCamera->position, center, Renderer.state.primaryCamera->up,
                   Renderer.state.primaryCamera->view);
        glm_perspective(glm_rad(45.f), aspect, 0.1f, 100.f, Renderer.state.primaryCamera->projection);

        Renderer.state.defaultShader.Bind(Renderer.state.defaultShader.id);
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                                             (float*)Renderer.state.primaryCamera->view);
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                                             (float*)Renderer.state.primaryCamera->projection);
        Renderer.state.defaultShader.Unbind();
    }
}

void LogCameraInfo(const Camera* camera)
{
    INFO("Camera position: " V3_FMT, V3FP_OPEN(camera->position));
    INFO("Camera target: " V3_FMT, V3FP_OPEN(camera->target));
    INFO("Camera up: " V3_FMT, V3FP_OPEN(camera->up));
    INFO("Camera direction: " V3_FMT, V3FP_OPEN(camera->direction));
    INFO("Camera fov: %.1f", camera->fov);
}
