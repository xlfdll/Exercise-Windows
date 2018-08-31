#include "XInput.h"

DWORD DetectController(DWORD dwUserIndex)
{
	XINPUT_CAPABILITIES caps;

	// Return ERROR_SUCCESS if connected, or ERROR_DEVICE_NOT_CONNECTED if not
	return XInputGetCapabilities(dwUserIndex, XINPUT_FLAG_GAMEPAD, &caps);
}

void UpdateController()
{
	for (int i = 0; i < 4; i++)
	{
		XINPUT_STATE state;

		DWORD result = XInputGetState(i, &state);

		if (result == ERROR_SUCCESS)
		{
			controllerStates[i] = state.Gamepad;
		}
	}
}

void VibrateController(DWORD dwUserIndex, WORD wLeftMotorSpeed, WORD wRightMotorSpeed)
{
	XINPUT_VIBRATION vibration;

	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = wLeftMotorSpeed;
	vibration.wRightMotorSpeed = wRightMotorSpeed;

	XInputSetState(dwUserIndex, &vibration);
}

void ResetController()
{
	for (int i = 0; i < 4; i++)
	{
		VibrateController(i, 0, 0);
	}
}