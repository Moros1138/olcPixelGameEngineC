#include "engine.h"

olc_Sprite* sprite;
float fTimeTracker = 0.0f;

bool OnUserCreate()
{
    sprite = olc_Sprite_Create(50, 50);
    
    SetDrawTarget(sprite);
    FillCircle(25, 25, 23, olc_RED);
    SetDrawTarget(NULL);

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    // artificially slow down the frames
    // fTimeTracker += fElapsedTime;
    // if(fTimeTracker < 0.2f) return !GetKey(olc_ESCAPE).bPressed;
    // fTimeTracker -= 0.2f;

    Clear(olc_BLACK);

    DrawLine(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), olc_SOLID);

    DrawCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), (uint8_t)olc_SOLID);
    
    FillCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    DrawRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    FillRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    DrawTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    FillTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    SetPixelMode(olc_PIXELMODE_ALPHA);
    // DrawPartialSprite(GetMouseX()+sprite->width, GetMouseY()+sprite->height, sprite, 25, 25, 16, 16, 1, olc_SPRITEFLIP_NONE);
    DrawSprite(GetMouseX()-(sprite->width/2), GetMouseY()-(sprite->height/2), sprite, 1, olc_SPRITEFLIP_NONE);
    SetPixelMode(olc_PIXELMODE_NORMAL);

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
