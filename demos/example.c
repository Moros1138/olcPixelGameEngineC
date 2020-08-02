#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

bool OnUserCreate()
{ return true; }

bool OnUserUpdate(float fElapsedTime)
{
    for(int y = 0; y < PGE_ScreenHeight(); y++)
        for(int x = 0; x < PGE_ScreenWidth(); x++)
            PGE_Draw(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
            
    return !PGE_GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{ return true; }

int main(int argc, char* argv[])
{
    PGE_SetAppName("Example");
    if(PGE_Construct(320, 240, 3, 3, false, false))
        PGE_Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}