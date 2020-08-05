#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

float fTimeTracker = 0.0f;

bool OnUserCreate()
{ return true; }

bool OnUserUpdate(float fElapsedTime)
{

    fTimeTracker += fElapsedTime;

    // Delay (so we can observe the random PGE_Drawings)
    if(fTimeTracker < 0.1f)
        return !PGE_GetKey(olc_ESCAPE).bPressed;

    // Reset Delay
    fTimeTracker -= 0.1f;

    PGE_Clear(olc_BLACK);

    // PGE_Draw 50 random pixels
    for(int i = 0; i < 50; i++)
        PGE_Draw(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // PGE_Draw random line
    PGE_DrawLine(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), olc_SOLID);
    
    // PGE_Draw random circle
    PGE_DrawCircle(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), (uint8_t)olc_SOLID);
    
    // PGE_Draw random PGE_Filled circle
    PGE_FillCircle(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // PGE_Draw random rectangle
    PGE_DrawRect(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    // PGE_Draw random PGE_Filled rectangle
    PGE_FillRect(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // PGE_Draw random triangle
    PGE_DrawTriangle(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    // PGE_Draw random PGE_Filled triangle
    PGE_FillTriangle(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));

    return !PGE_GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{ return true; }

int main(int argc, char* argv[])
{
    if(PGE_Construct(320, 240, 3, 3, false, false))
        PGE_Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}