#include "State.h"

// States

bool bGameExit = false;

BYTE keys[256];
DIMOUSESTATE2 mouseState;
XINPUT_GAMEPAD controllerStates[4];

SPRITE bomb;
SPRITE bucket;

int score = 0;
int vibrating = 0;

// Objects

HWND hWnd = NULL;

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
LPDIRECT3DSURFACE9 backbuffer = NULL;

LPDIRECTINPUT8 dinput = NULL;
LPDIRECTINPUTDEVICE8 dimouse = NULL;
LPDIRECTINPUTDEVICE8 dikeyboard = NULL;

LPDIRECT3DSURFACE9 bombSurface = NULL;
LPDIRECT3DSURFACE9 bucketSurface = NULL;