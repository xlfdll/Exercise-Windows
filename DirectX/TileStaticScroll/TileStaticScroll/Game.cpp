#include "Game.h"

bool InitializeGame()
{
    if (!InitializeDirect3D())
    {
        return false;
    }

    InitializeDirectInput();

    // Initialization

    if (!LoadMap())
    {
        return false;
    }

    BuildGameWorld();

    positionFont = GetFont(TEXT("Arial"), 24);
    frameRate = GetTickCount();

    return true;
}

void UpdateGame()
{
    UpdateDirectInputDevices();
    UpdateController();

    // Logic

    if (KEYDOWN(DIK_DOWN) || controllerStates[0].sThumbLY < -2000)
    {
        scrollY += 1;
    }
    if (KEYDOWN(DIK_UP) || controllerStates[0].sThumbLY > 2000)
    {
        scrollY -= 1;
    }
    if (KEYDOWN(DIK_LEFT) || controllerStates[0].sThumbLX < -2000)
    {
        scrollX -= 1;
    }
    if (KEYDOWN(DIK_RIGHT) || controllerStates[0].sThumbLX > 2000)
    {
        scrollX += 1;
    }

    // Keep steady 60 fps frame rate

    if (GetTickCount() - frameRate < 60)
    {
        return;
    }

    frameRate = GetTickCount();

    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

    if (d3ddev->BeginScene() == D3D_OK)
    {
        // Render

        ScrollScreen();

        dxsprite->Begin(D3DXSPRITE_ALPHABLEND);

        tstringstream tss;

        tss << "Scroll Position: (" << scrollX << "," << scrollY << ")";

        PrintText(positionFont, tss.str(), 0, 0);

        dxsprite->End();

        d3ddev->EndScene();
        d3ddev->Present(NULL, NULL, NULL, NULL);
    }

    // Use Esc key to quit

    if (KEYDOWN(DIK_ESCAPE) || CONTROLLER_BUTTONDOWN(0, XINPUT_GAMEPAD_BACK))
    {
        PostMessage(hWnd, WM_DESTROY, NULL, NULL);
    }
}

void ShutdownGame()
{
    // Exit

    if (gameWorldSurface)
    {
        gameWorldSurface->Release();
    }

    ResetController();

    ShutdownDirectInput();
    ShutdownDirect3D();
}

bool LoadMap()
{
    fstream mapDataFile;

    mapDataFile.open("map", fstream::in);

    if (!mapDataFile.is_open())
    {
        return false;
    }

    char delimiter;

    for (int i = 0; i < mapWidth * mapHeight; i++)
    {
        mapDataFile >> skipws >> mapData[i] >> delimiter;
    }

    return true;
}

void BuildGameWorld()
{
    LPDIRECT3DSURFACE9 tiles = LoadDirect3DSurfaceFromFile(TEXT("tiles.bmp"));
    HRESULT result = d3ddev->CreateOffscreenPlainSurface
    (
        gameWorldWidth,
        gameWorldHeight,
        D3DFMT_X8R8G8B8,
        D3DPOOL_DEFAULT,
        &gameWorldSurface,
        NULL
    );

    if (result != D3D_OK)
    {
        MessageBox(NULL, TEXT("Offscreen working surface creation failed!"), szTitle, 0);

        return;
    }

    for (int x = 0; x < mapWidth; x++)
        for (int y = 0; y < mapHeight; y++)
        {
            DrawTile(tiles, mapData[y * mapWidth + x], tileWidth, tileHeight, 16, gameWorldSurface, x * tileWidth, y * tileHeight);
        }

    tiles->Release();
}

void ScrollScreen()
{
    scrollX += speedX;

    if (scrollX < 0)
    {
        scrollX = 0;
        speedX = 0;
    }
    else if (scrollX > gameWorldWidth - screenWidth)
    {
        scrollX = gameWorldWidth - screenWidth;
        speedX = 0;
    }

    scrollY += speedY;

    if (scrollY < 0)
    {
        scrollY = 0;
        speedY = 0;
    }
    else if (scrollY > gameWorldHeight - screenHeight)
    {
        scrollY = gameWorldHeight - screenHeight;
        speedY = 0;
    }

    RECT rectSource = { scrollX, scrollY, scrollX + screenWidth - 1,scrollY + screenHeight - 1 };
    RECT rectDest = { 0, 0, screenWidth - 1, screenHeight - 1 };

    d3ddev->StretchRect(gameWorldSurface, &rectSource, backbuffer, &rectDest, D3DTEXF_NONE);
}