#include "Graphics/Camera.h"
#include "Core/KeyCodes.h"
#include "Graphics/Renderer.h"

#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Input.h"
#include "Core/Math.h"
#include "Core/Log.h"
#include "Core/Time.h"
#include "cglm/cam.h"

#include <cglm/cglm.h>

Camera CreateCamera(vec3 position, vec3 up, float fov)
{
    Camera camera;
    glm_vec3_copy(position, camera.position);
    glm_vec3_copy(up, camera.up);
    glm_vec3_zero(camera.target);
    camera.fov = fov;

    glm_vec3_sub(camera.target, camera.position, camera.direction);
    glm_normalize(camera.direction);

    glm_mat4_identity(camera.projection);
    glm_mat4_identity(camera.view);

    camera.pitch = 0.f;
    camera.yaw = -90.f;

    return camera;
}

static void UpdateCameraFree()
{
    Camera* camera = Renderer.state.primaryCamera;
    float speed = 3.f;
    vec3 camForward = {0.f, 0.f, -1.f};

    // Calculate the camera's right vector, by normalizing the cross product between the forward and up vector
    vec3 camRight;
    glm_vec3_cross(camForward, camera->up, camRight);
    glm_vec3_normalize(camRight);

    // Walk forward
    if (IsKeyDown(KEY_W))
    {
        vec3 forwardMovement;
        glm_vec3_muladds(camForward, speed * Time.delta, forwardMovement);
        glm_vec3_add(forwardMovement, camera->position, camera->position);
    }

    // Walk backward
    if (IsKeyDown(KEY_S))
    {
        vec3 forwardMovement;
        glm_vec3_muladds(camForward, speed * Time.delta, forwardMovement);
        glm_vec3_sub(camera->position, forwardMovement, camera->position);
    }

    // Walk right
    if (IsKeyDown(KEY_D))
    {
        vec3 horizontalMovement;
        glm_vec3_muladds(camRight, speed * Time.delta, horizontalMovement);
        glm_vec3_add(camera->position, horizontalMovement, camera->position);
    }

    // Walk left
    if (IsKeyDown(KEY_A))
    {
        vec3 horizontalMovement;
        glm_vec3_muladds(camRight, speed * Time.delta, horizontalMovement);
        glm_vec3_sub(camera->position, horizontalMovement, camera->position);
    }

    // Fly upwards
    if (IsKeyDown(KEY_SPACE))
    {
        vec3 verticalMovement;
        glm_vec3_muladds(camera->up, speed * Time.delta, verticalMovement);
        glm_vec3_add(camera->position, verticalMovement, camera->position);
    }

    // Fly downwards
    if (IsKeyDown(KEY_LEFT_CTRL))
    {
        vec3 verticalMovement;
        glm_vec3_muladds(camera->up, speed * Time.delta, verticalMovement);
        glm_vec3_sub(camera->position, verticalMovement, camera->position);
    }

    // Initially set the last mouse position to the center of the screen
    static Vector2 lastMousePosition;
    b8 isFirstClick = true;

    if (isFirstClick && IsMouseClicked(MOUSE_BUTTON_LEFT))
    {
        lastMousePosition.x = Input.mouse.position.x;
        lastMousePosition.y = Input.mouse.position.y;
        isFirstClick = false;
    }

    v2 mouseOffset = (v2){0.f, 0.f};

    if (IsMouseDown(MOUSE_BUTTON_LEFT))
    {
        mouseOffset.x = Input.mouse.position.x - lastMousePosition.x;
        mouseOffset.y = lastMousePosition.y - Input.mouse.position.y;
        lastMousePosition.x = Input.mouse.position.x;
        lastMousePosition.y = Input.mouse.position.y;

        mouseOffset.x *= 0.1f;
        mouseOffset.y *= 0.1f;
    }

    // Apply the mouse offset by the pitch and yaw rotation
    camera->yaw += mouseOffset.x;
    camera->pitch += mouseOffset.y;

    // Cap the camera's pitch
    if (camera->pitch > 90.f)
        camera->pitch = 90.f;
    if (camera->pitch < -90.f)
        camera->pitch = -90.f;

    // Calculate the camera's direction using some trig
    camera->direction[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    camera->direction[1] = sin(glm_rad(camera->pitch));
    camera->direction[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_normalize(camera->direction);
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
    Camera* camera = Renderer.state.primaryCamera;

    if (camera)
    {
        float aspect = (float)App.window.width / App.window.height;

        // glm_lookat(camera->position, camera->direction, camera->up, camera->view);
        glm_look(camera->position, camera->direction, camera->up, camera->view);
        glm_perspective(glm_rad(45.f), aspect, 0.1f, 100.f, camera->projection);

        Renderer.state.defaultShader.Bind(Renderer.state.defaultShader.id);
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_VIEW],
                                             (float*)camera->view);
        Renderer.state.defaultShader.SetMat4(Renderer.state.defaultShader.uniformLocs[SHADER_LOC_MATRIX_PROJECTION],
                                             (float*)camera->projection);
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
