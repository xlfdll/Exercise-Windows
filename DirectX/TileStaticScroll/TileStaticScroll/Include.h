#pragma once

#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

#include "tstring.h"

#include <Windows.h>

#include <d3d9.h>
#include <dinput.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "dxguid.lib") // Need for IID_ symbols
#pragma comment(lib, "dinput8.lib")

// Use only when targeting DirectX SDK (June 2010)

#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\d3dx9.h"
#include "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xinput.h"

#ifdef _WIN64

#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64\\d3dx9.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x64\\xinput.lib")

#else

#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\d3dx9.lib")
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\xinput.lib")

#endif // _WIN64

// System Includes

#include <fstream>
#include <memory>

using namespace std;