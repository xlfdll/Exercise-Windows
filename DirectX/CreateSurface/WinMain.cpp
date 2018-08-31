#include <Windows.h>

#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	if (!GameInit())
	{
		return FALSE;
	}

	while (!bGameExit)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		GameRun();
	}

	GameExit();

	return (int)msg.wParam;
}