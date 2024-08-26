#pragma once
#include "Core/Base.h"
#include <cglm/cglm.h>

typedef enum CameraType_t
{
    CAMERA_FREE = 0,
    CAMERA_ORBITAL,
    CAMERA_TYPE_COUNT,
} CameraType;

typedef struct Camera_t
{
    float fov;
    float pitch;
    float yaw;

    vec3 position;
    vec3 target;
    vec3 direction;
    vec3 up;

    mat4 view;
    mat4 projection;
} Camera;

/*!
 * @brief Creates a new camera, can be set to primary camera with SetPrimaryCamera(Camera*)
 * @param[in] position - The starting position of the camera in world coordinates
 * @param[in] up - A normalized vector, which defines which direction is up for the camera
 * @param[in] fov - Specifically, the field of view for the camera's pitch (fovy)
 */
Camera CreateCamera(vec3 position, vec3 up, float fov);

/*!
 * @brief Updates the primary camera with a camera type
 * @param[in] type - The way the camera should behave when updating (freelook, orbital)
 */
void UpdateCamera(CameraType type);

// @brief Update the primary camera's matrices
void UpdateCameraMatrices();

// @brief Log information about a camera
void LogCameraInfo(const Camera* camera);
