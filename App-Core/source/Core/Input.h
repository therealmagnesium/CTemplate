#pragma once
#include "Core/Base.h"
#include "Core/KeyCodes.h"

typedef struct MouseInputState
{
    Vector2 position;
    b8 held;
    b8 clicked;
    u32 button;
} MouseInputState;

typedef struct KeyboardInputState
{
    b8 held[KEY_COUNT];
    b8 pressed[KEY_COUNT];
} KeyboardInputState;

typedef struct InputState
{
    MouseInputState mouse;
    KeyboardInputState key;
} InputState;

extern InputState Input;

bool IsMouseDown(MouseButton button);
bool IsMouseClicked(MouseButton button);
bool IsKeyDown(u32 scancode);
bool IsKeyPressed(u32 scancode);
