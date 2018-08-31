#include "WinMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	if (!InitializeGame())
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

		UpdateGame();
	}

	ShutdownGame();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		bGameExit = true;

		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	LPCTSTR szWindowClass = szTitle;

	if (!MyRegisterClass(hInstance, szWindowClass))
	{
		return FALSE;
	}

	if (bFullscreen)
	{
		hWnd = CreateWindow(szWindowClass, szTitle, WS_EX_TOPMOST | WS_POPUP,
			0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	}
	else
	{
		hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, iScreenWidth, iScreenHeight, NULL, NULL, hInstance, NULL);
	}

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

ATOM MyRegisterClass(HINSTANCE hInstance, LPCTSTR szWindowClass)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hIconSm = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWindowClass;

	return RegisterClassEx(&wc);
}