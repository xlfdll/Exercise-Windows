#include "GameLogic.h"

bool GameRunInit()
{
	srand((unsigned int)time(NULL));

	HRESULT result = d3ddev->CreateOffscreenPlainSurface(100, 100, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);

	if (result != D3D_OK)
	{
		MessageBox(hWnd, TEXT("Error initializing Direct3D surface."), szTitle, MB_OK);

		return false;
	}

	return true;
}

void GameRun()
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (d3ddev->BeginScene())
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		d3ddev->ColorFill(surface, NULL, D3DCOLOR_XRGB(r, g, b));

		RECT rect;

		rect.left = rand() % iScreenWidth / 2;
		rect.right = rect.left + rand() % iScreenWidth / 2;
		rect.top = rand() % iScreenHeight;
		rect.bottom = rect.top + rand() % iScreenHeight / 2;

		d3ddev->StretchRect(surface, NULL, backbuffer, &rect, D3DTEXF_NONE);

		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	// Use Esc key to quit

	if (KEY_DOWN(VK_ESCAPE))
	{
		PostMessage(hWnd, WM_DESTROY, NULL, NULL);
	}
}

void GameRunExit()
{
	if (surface != NULL)
	{
		surface->Release();
	}
}