#include "engine.h"

bool OnUserCreate()
{
    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    for(int y = 0; y < ScreenHeight(); y++)
        for(int x = 0; x < ScreenWidth(); x++)
            Draw(x, y, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    return !GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{
    return true;
}


int main(int argc, char* argv[])
{
    SetAppName("IT FUCKING WORKS!!!");
    if(Construct(320, 240, 3, 3, false, false))
    {
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);
    }
        

    return 0;
}
