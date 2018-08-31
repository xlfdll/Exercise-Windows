#include "Game.h"

bool InitializeGame()
{
	if (!InitializeDirect3D())
	{
		return false;
	}

	InitializeDirectInput();

	ship.x = 450;
	ship.y = 300;
	ship.width = 128;
	ship.height = 128;
	ship.texture = LoadDirect3DTexture(TEXT("fatship.tga"));

	if (ship.texture == NULL)
	{
		return false;
	}

	asteroid1.x = 50;
	asteroid1.y = 200;
	asteroid1.width = 60;
	asteroid1.height = 60;
	asteroid1.frameColumnCount = 8;
	asteroid1.frameStart = 0;
	asteroid1.frameEnd = 63;
	asteroid1.vx = -2.0f;
	asteroid1.texture = LoadDirect3DTexture(TEXT("asteroid.tga"));

	if (asteroid1.texture == NULL)
	{
		return false;
	}

	asteroid2.x = 900;
	asteroid2.y = 500;
	asteroid2.width = 60;
	asteroid2.height = 60;
	asteroid2.frameColumnCount = 8;
	asteroid2.frameStart = 0;
	asteroid2.frameEnd = 63;
	asteroid2.vx = 2.0f;
	asteroid2.texture = asteroid1.texture;

	return true;
}

void UpdateGame()
{
	UpdateDirectInputDevices();
	UpdateController();

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 100), 1.0f, 0);

	// Move ship

	if (KEYDOWN(DIK_UP))
	{
		ship.y -= 1.0f;

		if (ship.y < 0.0f)
		{
			ship.y = 0.0f;
		}
	}

	if (KEYDOWN(DIK_DOWN))
	{
		ship.y += 1.0f;

		if (ship.y > (screenHeight - ship.height))
		{
			ship.y = screenHeight - ship.height;
		}
	}

	// Move asteroids

	asteroid1.x += asteroid1.vx;

	if (asteroid1.x < 0.0f || asteroid1.x >(screenWidth - asteroid1.width))
	{
		asteroid1.vx *= -1.0f;
	}

	SetSpriteFrameIndex(asteroid1);

	asteroid2.x += asteroid2.vx;

	if (asteroid2.x < 0.0f || asteroid2.x >(screenWidth - asteroid2.width))
	{
		asteroid2.vx *= -1.0f;
	}

	SetSpriteFrameIndex(asteroid2);

	// Collision test

	if (CollisionDelta(ship, asteroid1))
	{
		asteroid1.vx *= -1;
	}

	if (CollisionDelta(ship, asteroid2))
	{
		asteroid2.vx *= -1;
	}

	if (d3ddev->BeginScene())
	{
		dxsprite->Begin(D3DXSPRITE_ALPHABLEND);

		DrawSprite(ship);
		DrawSprite(asteroid1);
		DrawSprite(asteroid2);

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
	(ship.texture)->Release();
	(asteroid1.texture)->Release();

	ResetController();

	ShutdownDirectInput();
	ShutdownDirect3D();
}