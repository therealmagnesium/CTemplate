#pragma once
#include "Core/Base.h"

typedef struct List_t
{
    u8* data;
    u64 capacity;
    u64 itemSize;
} List;

List CreateList(u64 capacity, u64 itemSize);
void ResizeList(List* list, u64 newCapacity);
void FreeList(List* list);
