#include "Graphics/Color.h"
#include "Core/Base.h"

Vector4 NormalizeColor(Color color)
{
    Vector4 normalizedColor;
    normalizedColor.x = color.red / 255.f;
    normalizedColor.y = color.green / 255.f;
    normalizedColor.z = color.blue / 255.f;
    normalizedColor.w = color.alpha / 255.f;
    return normalizedColor;
}
