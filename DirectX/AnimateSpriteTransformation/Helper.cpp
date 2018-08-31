#include "Helper.h"

void SetTextureFrameIndex(int &frame, int frameStart, int frameEnd, int rate, DWORD &timeStamp, DWORD delay)
{
	DWORD currentTickCount = GetTickCount();

	if (currentTickCount > (timeStamp + delay))
	{
		timeStamp = currentTickCount;
		frame += rate;

		if (frame > frameEnd)
		{
			frame = frameStart;
		}
		else if (frame < frameStart)
		{
			frame = frameEnd;
		}
	}
}

double DegreeToRadian(double degrees)
{
	return degrees * PART_RADIAN;
}