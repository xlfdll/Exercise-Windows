#include "Game.h"

bool InitializeGame()
{
	if (!InitializeDirect3D())
	{
		return false;
	}

	InitializeDirectInput();

	bombSurface = LoadDirect3DSurfaceFromFile(TEXT("bomb.png"));
	bucketSurface = LoadDirect3DSurfaceFromFile(TEXT("bucket.png"));

	if (bombSurface == NULL || bucketSurface == NULL)
	{
		MessageBox(hWnd, TEXT("Error initializing sprites."), szTitle, MB_OK);

		return false;
	}

	srand((unsigned int)time(NULL));

	ResetSprite(&bomb);

	bucket.x = 256;
	bucket.y = 500;

	return true;
}

void UpdateGame()
{
	UpdateDirectInputDevices();
	UpdateController();

	// Bomb movement

	bomb.y += 2.0f;

	if (bomb.y > iScreenHeight)
	{
		MessageBox(hWnd, TEXT("Crap! You were ba-bombed!"), szTitle, MB_OK);

		ResetSprite(&bomb);

		score = 0;
	}

	// Bucket movement - Mouse

	float mx = mouseState.lX;

	if (mx < 0)
	{
		bucket.x -= 6.0f;
	}
	else if (mx > 0)
	{
		bucket.x += 6.0f;
	}

	// Bucket movement - Keyboard

	if (KEYDOWN(DIK_LEFT))
	{
		bucket.x -= 6.0f;
	}
	else if (KEYDOWN(DIK_RIGHT))
	{
		bucket.x += 6.0f;
	}

	// Bucket movement - Controller

	if (DetectController(0) == ERROR_SUCCESS)
	{
		// D-Pad

		if (controllerStates[0].wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			bucket.x -= 6.0f;
		}
		else if (controllerStates[0].wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			bucket.x += 6.0f;
		}

		// Right analog stick

		if (controllerStates[0].sThumbRX < -CONTROLLER_ANALOG_DEADZONERANGE)
		{
			bucket.x -= 6.0f;
		}
		else if (controllerStates[0].sThumbRX > CONTROLLER_ANALOG_DEADZONERANGE)
		{
			bucket.x += 6.0f;
		}
	}

	// Keep bucket inside the screen

	if (bucket.x < 0)
	{
		bucket.x = 0;
	}
	else if (bucket.x > (iScreenWidth - 128))
	{
		bucket.x = iScreenWidth - 128;
	}

	// Keep controller vibration for some time

	if (vibrating > 0)
	{
		vibrating++;

		if (vibrating > 20)
		{
			VibrateController(0, 0, 0);
		}
	}

	// Hit detection

	int cx = bomb.x + 64;
	int cy = bomb.y + 64;

	if (cx > bucket.x && cx < (bucket.x + 128) &&
		cy > bucket.y && cy < (bucket.y + 128))
	{
		// Bome got caught

		score++;

		wostringstream woss;
		woss << szTitle << TEXT(" (Score: ") << score << TEXT(")");

		SetWindowText(hWnd, woss.str().c_str());

		VibrateController(0, 65000, 65000);
		vibrating = 1;

		ResetSprite(&bomb);
	}

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	if (d3ddev->BeginScene())
	{
		DrawDirect3DSurface(bombSurface, backbuffer, bomb.x, bomb.y);
		DrawDirect3DSurface(bucketSurface, backbuffer, bucket.x, bucket.y);

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
	// TODO: Exit

	if (bombSurface != NULL)
	{
		bombSurface->Release();
		bombSurface = NULL;
	}

	if (bucketSurface != NULL)
	{
		bucketSurface->Release();
		bucketSurface = NULL;
	}

	ResetController();

	ShutdownDirectInput();
	ShutdownDirect3D();
}