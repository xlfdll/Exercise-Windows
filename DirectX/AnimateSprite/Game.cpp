#include "Game.h"

bool InitializeGame()
{
	if (!InitializeDirect3D())
	{
		return false;
	}

	InitializeDirectInput();

	explosion = LoadDirect3DTexture(TEXT("explosion_30_128.tga"));

	if (explosion == NULL)
	{
		return false;
	}

	return true;
}

void UpdateGame()
{
	UpdateDirectInputDevices();
	UpdateController();

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);

	if (d3ddev->BeginScene())
	{
		dxsprite->Begin(D3DXSPRITE_ALPHABLEND);

		SetTextureFrameIndex(nFrame, 0, 29, 1, dwTimeStamp, 30);
		DrawTextureFrame(explosion, 200, 200, nFrame, 128, 128, 4);

		dxsprite->End();

		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	// Use Esc key to quit

	if (KEYDOWN(DIK_ESCAPE) || CONTROLLER_BUTTONDOWN(0, XINPUT_GAMEPAD_BACK))
	{
		PostMessage(hWnd, WM_DESTROY, NULL, NULL);
	}
}

void ShutdownGame()
{
	explosion->Release();

	ResetController();

	ShutdownDirectInput();
	ShutdownDirect3D();
}