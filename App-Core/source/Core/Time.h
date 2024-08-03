#pragma once
#include "Core/Base.h"

typedef struct TimeState_t
{
    float delta;
    float now;
    float last;

    float lastFrame;
    float frameDelay;
    float frameTime;

    u32 frameRate;
    u32 frameCount;
} TimeState;

extern TimeState Time;

void InitTimeState(u32 frameRate);
void UpdateTime();
void UpdateTimeLate();
