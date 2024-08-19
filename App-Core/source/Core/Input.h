#pragma once
#include "Core/Base.h"
#include "Core/Math.h"
#include "Core/KeyCodes.h"

typedef enum InputAxis_t
{
    INPUT_AXIS_HORIZONTAL = 0,
    INPUT_AXIS_VERTICAL,
} InputAxis;

typedef struct MouseInputState_t
{
    Vector2 position;
    b8 held;
    b8 clicked;
    u32 button;
} MouseInputState;

typedef struct KeyboardInputState_t
{
    b8 held[KEY_COUNT];
    b8 pressed[KEY_COUNT];
} KeyboardInputState;

typedef struct InputState_t
{
    MouseInputState mouse;
    KeyboardInputState key;
} InputState;

extern InputState Input;

bool IsMouseDown(MouseButton button);
bool IsMouseClicked(MouseButton button);
bool IsKeyDown(u32 scancode);
bool IsKeyPressed(u32 scancode);
float GetInputAxis(InputAxis axis);
float GetInputAxisAlt(InputAxis axis);
