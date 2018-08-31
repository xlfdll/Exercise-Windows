#pragma once

#include "GameInclude.h"

#define KEY_DOWN(VK_CODE) ((GetAsyncKeyState(VK_CODE) & 0x8000) ? 1 : 0)