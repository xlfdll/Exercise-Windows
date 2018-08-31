#pragma once

#include "Include.h"
#include "Configuration.h"
#include "State.h"

bool InitializeDirect3D();
void ShutdownDirect3D();

void InitializeDirectInput();
void UpdateDirectInputDevices();
void ShutdownDirectInput();

LPDIRECT3DSURFACE9 LoadDirect3DSurfaceFromFile(LPTSTR filename);
void DrawDirect3DSurface(LPDIRECT3DSURFACE9 source, LPDIRECT3DSURFACE9 dest, LONG lX, LONG lY);

#define KEYDOWN(index) (keys[index] & 0x80)
#define MOUSEDOWN(index) (mouseState.rgbButtons[index] & 0x80)