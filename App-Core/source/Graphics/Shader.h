#pragma once
#include "Core/Base.h"

typedef enum ShaderLocation
{
    SHADER_LOC_MATRIX_PROJECTION = 0,
    SHADER_LOC_MATRIX_MODEL,
    SHADER_LOC_COLOR_DIFFUSE,
} ShaderLocation;

typedef struct Shader
{
    u32 id;
    s32 uniformLocs[3];

    void (*Bind)(u32 id);
    void (*Unbind)(void);

    void (*SetVec4)(s32 location, float* vec4);
    void (*SetMat4)(s32 location, float* mat4);
} Shader;

Shader CreateShader(const char* vertexPath, const char* fragmentPath);
s32 GetUniformLocation(Shader* shader, const char* name);
