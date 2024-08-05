#include "Core/List.h"
#include "Core/Base.h"
#include <stdlib.h>

List CreateList(u64 capacity, u64 itemSize)
{
    List list;
    list.data = calloc(capacity, itemSize);
    list.capacity = capacity;
    list.itemSize = itemSize;

    return list;
}

void ResizeList(List* list, u64 newCapacity)
{
    list->data = realloc(list->data, newCapacity * list->itemSize);
    list->capacity = newCapacity;
}

void FreeList(List* list)
{
    free(list->data);
    list->data = NULL;
}
