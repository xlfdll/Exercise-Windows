#pragma once

#include "Include.h"
#include "State.h"

#define CONTROLLER_ANALOG_DEADZONERANGE 5000 // TO avoid dead zone (approx. 1500) on analog sticks

DWORD DetectController(DWORD dwUserIndex);
void UpdateController();
void VibrateController(DWORD dwUserIndex, WORD wLeftMotorSpeed, WORD wRightMotorSpeed);
void ResetController();

#define CONTROLLER_BUTTONDOWN(dwUserIndex, dwButton) (controllerStates[dwUserIndex].wButtons & dwButton)