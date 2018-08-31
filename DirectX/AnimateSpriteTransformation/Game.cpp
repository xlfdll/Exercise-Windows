#include "Game.h"

bool InitializeGame()
{
	if (!InitializeDirect3D())
	{
		return false;
	}

	InitializeDirectInput();

	paladin = LoadDirect3DTexture(TEXT("paladin_walk.png"));

	if (paladin == NULL)
	{
		return false;
	}

	return true;
}

void UpdateGame()
{
	UpdateDirectInputDevices();
	UpdateController();

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (d3ddev->BeginScene())
	{
		dxsprite->Begin(D3DXSPRITE_ALPHABLEND);

		scaling += scalingOffset;

		if (scaling < 0.5f || scaling > 6.0f)
		{
			scaling *= -1;
		}

		SetTextureFrameIndex(frame, 24, 31, 1, timeStamp, 90);
		DrawTextureFrame(paladin, frame, 300, 200, 96L, 96L, 8, D3DCOLOR_XRGB(255, 255, 255), 0.0f, scaling);

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
	paladin->Release();

	ResetController();

	ShutdownDirectInput();
	ShutdownDirect3D();
}