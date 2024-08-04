#include "Graphics/Color.h"
#include "Core/Base.h"
#include "Core/Log.h"

Color CreateColor(u8 r, u8 g, u8 b, u8 a)
{
    Color color;
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;

    return color;
}

Color NormalizedToColor(const Vector4* normalized)
{
    Color color;
    color.red = normalized->x * 255;
    color.green = normalized->y * 255;
    color.blue = normalized->z * 255;
    color.alpha = normalized->w * 255;

    return color;
}

Vector4 NormalizeColor(Color color)
{
    Vector4 normalizedColor;
    normalizedColor.x = color.red / 255.f;
    normalizedColor.y = color.green / 255.f;
    normalizedColor.z = color.blue / 255.f;
    normalizedColor.w = color.alpha / 255.f;
    return normalizedColor;
}
