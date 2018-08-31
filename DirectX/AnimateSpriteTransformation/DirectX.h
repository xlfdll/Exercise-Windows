#pragma once

#include "Include.h"
#include "Configuration.h"
#include "State.h"

bool InitializeDirect3D();
void ShutdownDirect3D();

void InitializeDirectInput();
void UpdateDirectInputDevices();
void ShutdownDirectInput();

LPDIRECT3DSURFACE9 LoadDirect3DSurfaceFromFile(LPTSTR fileName);
void DrawDirect3DSurface(LPDIRECT3DSURFACE9 source, LPDIRECT3DSURFACE9 dest, LONG x, LONG y);

LPDIRECT3DTEXTURE9 LoadDirect3DTexture(LPTSTR fileName, D3DCOLOR transparentColor = D3DCOLOR_XRGB(0, 0, 0));

void DrawTextureFrame(LPDIRECT3DTEXTURE9 texture, int frame, float x = 0.0f, float y = 0.0f,
	LONG width = 64L, LONG height = 64L, int frameColumns = 1, D3DCOLOR drawColor = D3DCOLOR_XRGB(255, 255, 255));
void DrawTextureFrame(LPDIRECT3DTEXTURE9 texture, int frame, float x = 0.0f, float y = 0.0f,
	LONG width = 64L, LONG height = 64L, int frameColumns = 1, D3DCOLOR drawColor = D3DCOLOR_XRGB(255, 255, 255),
	float rotation = 0.0f, float scaling = 1.0f);

#define KEYDOWN(index) (keys[index] & 0x80)
#define MOUSEDOWN(index) (mouseState.rgbButtons[index] & 0x80)