#pragma once
#include "Core/Base.h"

typedef enum ShaderLocation_t
{
    SHADER_LOC_MATRIX_PROJECTION = 0,
    SHADER_LOC_MATRIX_VIEW,
    SHADER_LOC_MATRIX_MODEL,
    SHADER_LOC_COLOR_DIFFUSE,
    SHADER_LOC_MAP_DIFFUSE,
    SHADER_LOC_COUNT
} ShaderLocation;

typedef struct Shader
{
    u32 id;
    s32 uniformLocs[SHADER_LOC_COUNT];

    void (*Bind)(u32 id);
    void (*Unbind)(void);

    void (*SetInt)(s32 location, s32 val);
    void (*SetVec2)(s32 location, float* vec2);
    void (*SetVec4)(s32 location, float* vec4);
    void (*SetMat4)(s32 location, float* mat4);
} Shader;

Shader CreateShader(const char* vertexPath, const char* fragmentPath);
s32 GetUniformLocation(Shader* shader, const char* name);
