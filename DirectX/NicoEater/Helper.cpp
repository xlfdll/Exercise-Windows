#include "Helper.h"

void ResetSprite(SPRITE *sprite)
{
	sprite->x = (float)(rand() % (iScreenWidth - 128));
	sprite->y = 0;
}