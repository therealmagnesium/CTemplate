#include "Graphics/Shader.h"

#include "Core/Base.h"
#include "Core/IO.h"
#include "Core/Log.h"

#include <glad/glad.h>
#include <stdlib.h>

static void BindShader(u32 id) { glUseProgram(id); }
static void UnbindShader() { glUseProgram(0); }

static void SetInt(s32 location, s32 val) { glUniform1i(location, val); }
static void SetVec2(s32 location, float* vec2) { glUniform2fv(location, 1, vec2); }
static void SetVec4(s32 location, float* vec4) { glUniform4fv(location, 1, vec4); }
static void SetMat4(s32 location, float* mat4) { glUniformMatrix4fv(location, 1, GL_FALSE, mat4); }

static u32 CompileShader(u32 target, const char* path)
{
    s32 success;
    char log[512];

    File file = ReadFile(path);
    if (!file.isValid)
    {
        WARN("Failed to read shader %s!", path);
        return 0;
    }

    u32 targetId = glCreateShader(target);
    glShaderSource(targetId, 1, (const char* const*)&file.data, NULL);
    glCompileShader(targetId);
    glGetShaderiv(targetId, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(targetId, 512, NULL, log);
        ERROR("Failed to compile shader!\n%s", log);
    }

    free(file.data);
    return targetId;
}

Shader CreateShader(const char* vertexPath, const char* fragmentPath)
{
    Shader shader;
    shader.id = glCreateProgram();
    shader.Bind = BindShader;
    shader.Unbind = UnbindShader;
    shader.SetInt = SetInt;
    shader.SetVec2 = SetVec2;
    shader.SetVec4 = SetVec4;
    shader.SetMat4 = SetMat4;

    u32 vertex = CompileShader(GL_VERTEX_SHADER, vertexPath);
    u32 fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentPath);

    int success;
    char log[512];

    glAttachShader(shader.id, vertex);
    glAttachShader(shader.id, fragment);
    glLinkProgram(shader.id);
    glGetProgramiv(shader.id, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shader.id, 512, NULL, log);
        ERROR("Failed to link shader!\n%s", log);
        return (Shader){};
    }

    return shader;
}

s32 GetUniformLocation(Shader* shader, const char* name)
{
    s32 location = glGetUniformLocation(shader->id, name);
    return location;
}
