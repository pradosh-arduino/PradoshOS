#pragma once

#include <stdint.h>
#include <string.h>
#include "kbScancodeTranslation.h"
#include "../BasicRenderer.h"

extern bool halt;

void HandleKeyboard(uint8_t scancode);