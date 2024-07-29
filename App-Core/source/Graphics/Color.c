#include "Graphics/Color.h"
#include "Core/Base.h"

Color CreateColor(u8 r, u8 g, u8 b, u8 a)
{
    Color color;
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;

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
