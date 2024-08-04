#pragma once
#include "Core/Base.h"
#include "Core/Math.h"

typedef struct Color_t
{
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Color;

Color CreateColor(u8 r, u8 g, u8 b, u8 a);
Color NormalizedToColor(const Vector4* normalized);
Vector4 NormalizeColor(Color color);
