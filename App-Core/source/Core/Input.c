#include "Core/Input.h"
#include "Core/Base.h"

InputState Input;

bool IsMouseDown(MouseButton button) { return Input.mouse.held && Input.mouse.button == button; }

bool IsMouseClicked(MouseButton button) { return Input.mouse.clicked && Input.mouse.button == button; }

bool IsKeyDown(u32 scancode) { return Input.key.held[scancode] == true; }

bool IsKeyPressed(u32 scancode) { return Input.key.pressed[scancode] == true; }
