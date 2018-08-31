#pragma once

#include "Include.h"

#include "Definition.h"

// States

extern bool bGameExit;

extern BYTE keys[256];
extern DIMOUSESTATE2 mouseState;
extern XINPUT_GAMEPAD controllerStates[4];

extern SPRITE bomb;
extern SPRITE bucket;

extern int score;
extern int vibrating;

// Objects

extern HWND hWnd;

extern LPDIRECT3D9 d3d;
extern LPDIRECT3DDEVICE9 d3ddev;
extern LPDIRECT3DSURFACE9 backbuffer;

extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dimouse;
extern LPDIRECTINPUTDEVICE8 dikeyboard;

extern LPDIRECT3DSURFACE9 bombSurface;
extern LPDIRECT3DSURFACE9 bucketSurface;