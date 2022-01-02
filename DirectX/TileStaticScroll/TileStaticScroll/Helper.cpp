#include "Helper.h"

double DegreeToRadian(double degrees)
{
    return degrees * PART_RADIAN;
}

void SetSpriteFrameIndex(SPRITE sprite)
{
    DWORD currentTickCount = GetTickCount();

    if (currentTickCount > (sprite.timeStamp + sprite.delay))
    {
        sprite.timeStamp = currentTickCount;
        sprite.frame += sprite.rate;

        if (sprite.frame > sprite.frameEnd)
        {
            sprite.frame = sprite.frameStart;
        }
        else if (sprite.frame < sprite.frameStart)
        {
            sprite.frame = sprite.frameEnd;
        }
    }
}

void DrawSprite(SPRITE sprite)
{
    DrawTextureFrame(sprite.texture, sprite.frame, sprite.x, sprite.y, sprite.width, sprite.height, sprite.frameColumnCount, sprite.color);
}

int CollisionIntersect(SPRITE sprite1, SPRITE sprite2)
{
    RECT rect1 = { (long)sprite1.x,(long)sprite1.y,
        (long)(sprite1.x + sprite1.width * sprite1.scaling),
        (long)(sprite1.y + sprite1.height * sprite1.scaling) };
    RECT rect2 = { (long)sprite2.x,(long)sprite2.y,
        (long)(sprite2.x + sprite2.width * sprite2.scaling),
        (long)(sprite2.y + sprite2.height * sprite2.scaling) };
    RECT dest; // Ignored

    return IntersectRect(&dest, &rect1, &rect2);
}

bool CollisionDelta(SPRITE sprite1, SPRITE sprite2)
{
    double radius1 = (sprite1.width > sprite1.height) ?
        (sprite1.width * sprite1.scaling) / 2.0 :
        (sprite1.height * sprite1.scaling) / 2.0;
    double radius2 = (sprite2.width > sprite2.height) ?
        (sprite2.width * sprite2.scaling) / 2.0 :
        (sprite2.height * sprite2.scaling) / 2.0;

    double center1_x = sprite1.x + radius1;
    double center1_y = sprite1.y + radius1;

    double center2_x = sprite2.x + radius2;
    double center2_y = sprite2.y + radius2;

    double delta_x = center2_x - center1_x;
    double delta_y = center2_y - center1_y;

    double dist = sqrt((delta_x * delta_x) + (delta_y * delta_y));

    return (dist < (radius1 + radius2));
}

LPD3DXFONT GetFont(tstring name, INT size)
{
    LPD3DXFONT font = NULL;

    D3DXFONT_DESC desc =
    {
        size,
        0,
        0,
        0,
        false,
        DEFAULT_CHARSET,
        OUT_TT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_PITCH,
        TEXT("")
    };

    wcscpy_s(desc.FaceName, name.c_str());

    D3DXCreateFontIndirect(d3ddev, &desc, &font);

    return font;
}

void PrintText(LPD3DXFONT font, tstring text, LONG x, LONG y, D3DCOLOR color)
{
    RECT rect = { x, y, 0, 0 };

    font->DrawTextW(NULL, text.c_str(), text.length(), &rect, DT_CALCRECT, color);
    font->DrawTextW(dxsprite, text.c_str(), text.length(), &rect, DT_LEFT, color);
}

void PrintText(LPD3DXFONT font, tstring text, RECT rect, DWORD format, D3DCOLOR color)
{
    font->DrawTextW(dxsprite, text.c_str(), text.length(), &rect, format, color);
}