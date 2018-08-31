#include <Windows.h>

#include "XDUser.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int nCmdShow)
{
	//SetProcessDPIAware(); // Old version
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2); // New version

	int cxScreen = GetSystemMetrics(SM_CXSCREEN);
	int cyScreen = GetSystemMetrics(SM_CYSCREEN);

	MessageBoxPrintf(TEXT("Screen Resolution"), TEXT("The current screen resolution is\n\n%d x %d"), cxScreen, cyScreen);

	return 0;
}