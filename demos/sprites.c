#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

olc_Sprite* sprite;

bool OnUserCreate()
{
    sprite = olc_Sprite_Load("../assets/test.png");
    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    PGE_Clear(olc_BLACK);

    PGE_DrawSprite(0, 0, sprite, 1, 0);

    PGE_DrawPartialSprite(100,  0, sprite,  0,  0, 16, 16, 1, 0);
    PGE_DrawPartialSprite(100, 50, sprite,  0, 16, 16, 16, 1, 0);
    PGE_DrawPartialSprite(150, 50, sprite, 16, 16, 16, 16, 1, 0);
    PGE_DrawPartialSprite(150,  0, sprite, 16,  0, 16, 16, 1, 0);

    return !PGE_GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{
    olc_Sprite_Destroy(sprite);
    return true;
}

int main(int argc, char* argv[])
{
    PGE_SetAppName("Example");
    if(PGE_Construct(320, 240, 3, 3, false, false))
        PGE_Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}