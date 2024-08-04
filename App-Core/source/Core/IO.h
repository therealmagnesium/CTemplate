#pragma once
#include "Core/Base.h"

typedef struct File_t
{
    char* data;
    u64 length;
    b8 isValid;
} File;

File ReadFile(const char* path);
void WriteFile(void* buffer, u64 size, const char* path);
