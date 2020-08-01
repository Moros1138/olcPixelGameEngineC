#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

float fTimeTracker = 0.0f;

bool OnUserCreate()
{ return true; }

bool OnUserUpdate(float fElapsedTime)
{

    fTimeTracker += fElapsedTime;

    // Delay (so we can observe the random drawings)
    if(fTimeTracker < 0.1f)
        return !GetKey(olc_ESCAPE).bPressed;

    // Reset Delay
    fTimeTracker -= 0.1f;

    Clear(olc_BLACK);

    // draw 50 random pixels
    for(int i = 0; i < 50; i++)
        Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // draw random line
    DrawLine(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), olc_SOLID);
    
    // draw random circle
    DrawCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), (uint8_t)olc_SOLID);
    
    // draw random filled circle
    FillCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // draw random rectangle
    DrawRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    // draw random filled rectangle
    FillRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // draw random triangle
    DrawTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    // draw random filled triangle
    FillTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    return !GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{ return true; }

int main(int argc, char* argv[])
{
    if(Construct(320, 240, 3, 3, false, false))
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}