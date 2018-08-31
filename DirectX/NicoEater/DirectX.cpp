#include "DirectX.h"

bool InitializeDirect3D()
{
	// Direct3D

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (d3d == NULL)
	{
		MessageBox(hWnd, TEXT("Error initializing Direct3D."), szTitle, MB_OK);

		return false;
	}

	// Direct3D Display Device

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = !bFullscreen;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferCount = 1;

	if (bFullscreen)
	{
		D3DDISPLAYMODE dm;

		d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

		d3dpp.BackBufferFormat = dm.Format;
		d3dpp.BackBufferWidth = dm.Width;
		d3dpp.BackBufferHeight = dm.Height;
	}
	else
	{
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		d3dpp.BackBufferWidth = iScreenWidth;
		d3dpp.BackBufferHeight = iScreenHeight;
	}

	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hWnd, TEXT("Error initializing Direct3D device."), szTitle, MB_OK);

		return false;
	}

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backbuffer);

	return true;
}

void ShutdownDirect3D()
{
	if (backbuffer != NULL)
	{
		backbuffer->Release();
		backbuffer = NULL;
	}

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

void InitializeDirectInput()
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID *)&dinput, NULL);

	// Keyboard
	dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);

	dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	dikeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dikeyboard->Acquire();

	// Mouse
	dinput->CreateDevice(GUID_SysMouse, &dimouse, NULL);

	dimouse->SetDataFormat(&c_dfDIMouse2); // Over 5 buttons
	dimouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dimouse->Acquire();
}

void UpdateDirectInputDevices()
{
	HRESULT hr = dikeyboard->GetDeviceState(sizeof(keys), &keys);

	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	{
		dikeyboard->Acquire();
	}

	hr = dimouse->GetDeviceState(sizeof(mouseState), &mouseState);

	if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
	{
		dimouse->Acquire();
	}
}

void ShutdownDirectInput()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}

	if (dimouse != NULL)
	{
		dimouse->Unacquire();
		dimouse->Release();
		dimouse = NULL;
	}

	if (dinput != NULL)
	{
		dinput->Release();
		dinput = NULL;
	}
}

LPDIRECT3DSURFACE9 LoadDirect3DSurfaceFromFile(LPTSTR fileName)
{
	LPDIRECT3DSURFACE9 surface = NULL;

	D3DXIMAGE_INFO info;
	HRESULT hr = D3DXGetImageInfoFromFile(fileName, &info);

	if (hr != D3D_OK)
	{
		return NULL;
	}

	hr = d3ddev->CreateOffscreenPlainSurface(info.Width, info.Height, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);

	if (hr != D3D_OK)
	{
		return NULL;
	}

	hr = D3DXLoadSurfaceFromFile(surface, NULL, NULL, fileName, NULL, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0), NULL);

	if (hr != D3D_OK)
	{
		return NULL;
	}

	return surface;
}

void DrawDirect3DSurface(LPDIRECT3DSURFACE9 source, LPDIRECT3DSURFACE9 dest, LONG lX, LONG lY)
{
	D3DSURFACE_DESC desc;

	source->GetDesc(&desc);

	RECT rectSource = { 0L, 0L, (LONG)desc.Width, (LONG)desc.Height };
	RECT rectDest = { lX, lY, lX + (LONG)desc.Width, lY + (LONG)desc.Height };

	d3ddev->StretchRect(source, &rectSource, dest, &rectDest, D3DTEXF_NONE);
}