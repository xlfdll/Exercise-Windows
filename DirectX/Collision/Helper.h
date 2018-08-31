#pragma once

#include "Include.h"
#include "Structure.h"
#include "DirectX.h"

const double PI = 3.141592653589793;
const double PART_RADIAN = PI / 180.0; // Avoid repeated calculation

double DegreeToRadian(double degrees);

void SetSpriteFrameIndex(SPRITE sprite);
void DrawSprite(SPRITE sprite);

int CollisionIntersect(SPRITE sprite1, SPRITE sprite2);
bool CollisionDelta(SPRITE sprite1, SPRITE sprite2);