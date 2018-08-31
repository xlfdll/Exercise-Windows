#pragma once

#include "Include.h"

void SetTextureFrameIndex(int &frame, int frameStart, int frameEnd, int rate, DWORD &timeStamp, DWORD delay);

const double PI = 3.141592653589793;
const double PART_RADIAN = PI / 180.0; // Avoid repeated calculation

double DegreeToRadian(double degrees);