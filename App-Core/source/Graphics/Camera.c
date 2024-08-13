#include "Graphics/Camera.h"
#include "Graphics/Renderer.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Math.h"
#include "Core/Log.h"

#include <cglm/cglm.h>

Camera CreateCamera(vec3 position, vec3 target, vec3 up, float fov)
{
    Camera camera;
    glm_vec3_copy(position, camera.position);
    glm_vec3_copy(target, camera.target);
    glm_vec3_copy(up, camera.up);
    camera.fov = fov;

    vec3 cameraToTarget;
    glm_vec3_sub(camera.position, camera.target, cameraToTarget);
    glm_normalize(cameraToTarget);
    glm_vec3_copy(cameraToTarget, camera.direction);

    glm_mat4_identity(camera.projection);
    glm_mat4_identity(camera.view);

    return camera;
}

void UpdateCameraMatrices(Camera* camera)
{
    if (camera)
    {
        glm_perspective(glm_rad(45.f), (float)App.window.width / App.window.height, 0.1f, 100.f, camera->projection);
        glm_lookat(camera->position, camera->target, camera->up, camera->view);

        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                                             (float*)camera->projection);
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                                             (float*)camera->view);
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
