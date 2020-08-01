#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

bool OnUserCreate()
{ return true; }

bool OnUserUpdate(float fElapsedTime)
{
    for(int y = 0; y < ScreenHeight(); y++)
        for(int x = 0; x < ScreenWidth(); x++)
            Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
            
    return true;
}

bool OnUserDestroy()
{ return true; }

int main(int argc, char* argv[])
{
    if(Construct(320, 240, 3, 3, false, false))
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}