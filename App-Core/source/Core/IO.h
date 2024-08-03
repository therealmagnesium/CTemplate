#pragma once
#include "Core/Base.h"

typedef struct File
{
    char* data;
    u64 length;
    b8 isValid;
} File;

File ReadFile(const char* path);
