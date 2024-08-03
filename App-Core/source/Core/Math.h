#pragma once

#include "Core/Base.h"
#include <math.h>
typedef struct
{
    float x;
    float y;
} Vector2;

typedef struct
{
    float x;
    float y;
    float z;
} Vector3;

typedef struct
{
    float x;
    float y;
    float z;
    float w;
} Vector4;

typedef Vector2 v2;
typedef Vector3 v3;
typedef Vector4 v4;

inline float MagV2(Vector2* v)
{
    float mag = sqrt(pow(v->x, 2) + pow(v->y, 2));
    return mag;
}

inline void NormalizeV2(Vector2* v)
{
    float mag = MagV2(v);

    if (mag != 0.f)
    {
        v->x /= mag;
        v->y /= mag;
    }
}
