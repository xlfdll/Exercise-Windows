#include "Game.h"

bool GameInit()
{
	D3DPRESENT_PARAMETERS d3dpp;

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d == NULL)
	{
		MessageBox(hWnd, TEXT("Error initializing Direct3D."), szTitle, MB_OK);

		return false;
	}

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	if (bFullscreen)
	{
		D3DDISPLAYMODE dm;

		d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

		d3dpp.Windowed = FALSE;
		d3dpp.BackBufferFormat = dm.Format;
		d3dpp.BackBufferWidth = dm.Width;
		d3dpp.BackBufferHeight = dm.Height;
	}
	else
	{
		d3dpp.Windowed = TRUE;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth = iScreenWidth;
		d3dpp.BackBufferHeight = iScreenHeight;
	}

	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = 1;

	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hWnd, TEXT("Error initializing Direct3D device."), szTitle, MB_OK);

		return false;
	}

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	if (!GameRunInit())
	{
		MessageBox(hWnd, TEXT("Error initializing Direct3D runtime objects."), szTitle, MB_OK);

		return false;
	}

	return true;
}

void GameExit()
{
	GameRunExit();

	if (d3ddev != NULL)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}

	if (d3d != NULL)
	{
		d3d->Release();
		d3d = NULL;
	}
}