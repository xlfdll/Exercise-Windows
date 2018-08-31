#include "State.h"

// States

bool gameExit = false;

BYTE keys[256];
DIMOUSESTATE2 mouseState;
XINPUT_GAMEPAD controllerStates[4];

// Objects

HWND hWnd = NULL;

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

LPDIRECTINPUT8 dinput = NULL;
LPDIRECTINPUTDEVICE8 dimouse = NULL;
LPDIRECTINPUTDEVICE8 dikeyboard = NULL;

LPD3DXSPRITE dxsprite = NULL;

SPRITE ship;
SPRITE asteroid1;
SPRITE asteroid2;