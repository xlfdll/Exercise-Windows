#pragma once

#include "Include.h"

typedef struct sprite
{
	float x, y;
	float vx, vy;
	long width, height;
	float scaling, rotation;

	int frame, frameColumnCount;
	int frameStart, frameEnd;

	int rate;
	DWORD delay;

	DWORD timeStamp;

	LPDIRECT3DTEXTURE9 texture;
	D3DCOLOR color;

	sprite()
	{
		x = 0.0f;
		y = 0.0f;

		vx = 0.0f;
		vy = 0.0f;

		width = 0;
		height = 0;

		scaling = 1.0f;
		rotation = 0.0f;

		frame = 0;
		frameColumnCount = 1;
		frameStart = 0;
		frameEnd = 0;

		rate = 0;
		delay = 0;

		timeStamp = 0;

		texture = NULL;
		color = D3DCOLOR_XRGB(255, 255, 255);
	}
} SPRITE;