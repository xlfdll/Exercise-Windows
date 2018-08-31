#pragma once

#include "GameInclude.h"
#include "GameInstance.h"
#include "GameConfiguration.h"
#include "GameState.h"

ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR szWindowClass);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);