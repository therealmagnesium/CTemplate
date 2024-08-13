#pragma once
#include "Core/Base.h"
#include <cglm/cglm.h>

typedef struct Camera_t
{
    float fov;
    vec3 position;
    vec3 target;
    vec3 direction;
    vec3 up;
    mat4 view;
    mat4 projection;
} Camera;

Camera CreateCamera(vec3 position, vec3 target, vec3 up, float fov);
void UpdateCameraMatrices(Camera* camera);
void LogCameraInfo(const Camera* camera);
