#include "Configuration.h"

const LPCTSTR szTitle = TEXT("DirectX Demo - Tile-based Static Scrolling");

int screenWidth = 1280;
int screenHeight = 720;

bool fullscreen = false;

// Configuration

// Scroller Settings
int tileWidth = 64;
int tileHeight = 64;
int mapWidth = 25;
int mapHeight = 18;
int scrollWindowWidth = (screenWidth / tileWidth) * tileWidth;
int scrollWindowHeight = (screenHeight / tileHeight) * tileHeight;
int gameWorldWidth = tileWidth * mapWidth;
int gameWorldHeight = tileHeight * mapHeight;