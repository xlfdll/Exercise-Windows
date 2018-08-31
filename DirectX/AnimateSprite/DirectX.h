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

LPDIRECT3DTEXTURE9 LoadDirect3DTexture(LPTSTR filename, D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));

void DrawTextureFrame(LPDIRECT3DTEXTURE9 texture, float fDrawX, float fDrawY, int nFrame, LONG lFrameWidth, LONG lFrameHeight, int nFrameColumns);
void SetTextureFrameIndex(int &nFrame, int nFrameStart, int nFrameEnd, int nRate, DWORD &dwTimestamp, DWORD dwDelay);

#define KEYDOWN(index) (keys[index] & 0x80)
#define MOUSEDOWN(index) (mouseState.rgbButtons[index] & 0x80)