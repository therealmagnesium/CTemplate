#pragma once
#include "Core/Base.h"

typedef struct
{
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} Color;

Vector4 NormalizeColor(Color color);
