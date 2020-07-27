#include "engine.h"

bool OnUserCreate()
{
    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    
    DrawLine(
        rand() % ScreenWidth(), rand() % ScreenHeight(),
        rand() % ScreenWidth(), rand() % ScreenHeight(),
        olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), olc_SOLIDLINE);

    DrawString(12, 12, "Hello, World", olc_BLACK, 1);
    DrawString(10, 10, "Hello, World", olc_WHITE, 1);
    
    return !GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{
    return true;
}


int main(int argc, char* argv[])
{
    SetAppName("IT WORKS!!!");
    if(Construct(320, 240, 3, 3, false, false))
    {
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);
    }
        

    return 0;
}
