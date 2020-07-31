// #define OLC_PGE_APPLICATION
#include "olc_Engine.h"

char buf[256];
float fTimeTracker = 0.0f;
float fAngle = 0.0f;

bool OnUserCreate()
{
    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    if(GetKey(olc_SPACE).bPressed) ShowSystemMouseCursor(!IsMouseCursorVisible());

    fTimeTracker += fElapsedTime;
    if(fTimeTracker < 0.1f)
        return !GetKey(olc_ESCAPE).bPressed;

    fTimeTracker -= 0.1f;

    Clear(olc_BLACK);

    for(int i = 0; i < 50; i++)
        Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    DrawLine(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), olc_SOLID);

    DrawCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), (uint8_t)olc_SOLID);
    
    FillCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    DrawRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    FillRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    DrawTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    FillTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    return !GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{
    return true;
}


int main(int argc, char* argv[])
{
    SetAppName("OpenGL C Demo");
    if(Construct(320, 240, 3, 3, false, false))
    {
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);
    }

    return 0;
}
