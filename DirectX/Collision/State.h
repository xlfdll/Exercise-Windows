#pragma once

#include "Include.h"
#include "Structure.h"

// States

extern bool gameExit;

extern BYTE keys[256];
extern DIMOUSESTATE2 mouseState;
extern XINPUT_GAMEPAD controllerStates[4];

// Objects

extern HWND hWnd;

extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;

extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;

extern LPD3DXSPRITE dxsprite;

extern SPRITE ship;
extern SPRITE asteroid1;
extern SPRITE asteroid2;