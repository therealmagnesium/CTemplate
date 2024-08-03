#pragma once
#include "Core/Base.h"

typedef struct Shader
{
    u32 id;

    void (*Bind)(u32 id);
    void (*Unbind)(void);
} Shader;

Shader CreateShader(const char* vertexPath, const char* fragmentPath);
