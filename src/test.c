// #define OLC_PGE_APPLICATION
#include "engine.h"

char buf[256];
olc_Sprite* sprite;
olc_Decal* decal;
float fTimeTracker = 0.0f;
float fAngle = 0.0f;

bool OnUserCreate()
{
    sprite = olc_Sprite_Create(32, 32);
        
    SetDrawTarget(sprite);
    Clear(olc_RED);

    DrawRect( 0,  0, 15, 15, olc_WHITE);
    DrawRect( 0, 16, 15, 15, olc_WHITE);
    DrawRect(16, 16, 15, 15, olc_WHITE);
    DrawRect(16,  0, 15, 15, olc_WHITE);

    DrawString( 4,  4, "1", olc_WHITE, 1);
    DrawString( 4, 20, "2", olc_WHITE, 1);
    DrawString(20, 20, "3", olc_WHITE, 1);
    DrawString(20,  4, "4", olc_WHITE, 1);

    SetDrawTarget(NULL);
    sprite = olc_Sprite_LoadFromPGESprFile("test.spr");
    decal = olc_Decal_Create(sprite);

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    // if(GetKey(olc_SPACE).bPressed) ShowSystemMouseCursor(!IsMouseCursorVisible());

    // for(int i = 0; i < 50; i++)
    //     Draw(rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // DrawLine(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % ScreenWidth(), rand() % ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), olc_SOLID);

    // DrawCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255), (uint8_t)olc_SOLID);
    
    // FillCircle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // DrawRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // FillRect(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // DrawTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    
    // FillTriangle(rand() % ScreenWidth(), rand() % ScreenHeight(), rand() % 50, rand() % 50, rand() % 100, rand() % 100, olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
    // Clear(olc_BLACK);
    // SetPixelMode(olc_PIXELMODE_ALPHA);
    // DrawPartialSprite(GetMouseX()+sprite->width, GetMouseY()+sprite->height, sprite, 25, 25, 16, 16, 1, olc_SPRITEFLIP_NONE);
    // DrawSprite(GetMouseX()-(sprite->width/2), GetMouseY()-(sprite->height/2), sprite, 1, olc_SPRITEFLIP_NONE);
    // SetPixelMode(olc_PIXELMODE_NORMAL);

    // olc_vf2d pos[4] = {
    //     olc_VF2D( 0,  0),
    //     olc_VF2D( 0, 32),
    //     olc_VF2D(32, 32),
    //     olc_VF2D(32,  0)
    // };

    // olc_vf2d src[4] = {
    //     olc_VF2D(  0.0f,  0.0f),
    //     olc_VF2D(  0.0f, 16.0f),
    //     olc_VF2D( 16.0f, 16.0f),
    //     olc_VF2D( 16.0f,  0.0f)
    // };

    // olc_vf2d src_size = olc_VF2D(16.0f, 16.0f);
    // olc_vf2d scale    = olc_VF2D( 1.0f,  1.0f);
    // for(int i = 0; i < 4; i++)
    // {
        // DrawPartialSprite(
        //     pos[i].x, pos[i].y,
        //     sprite,
        //     src[i].x, src[i].y,
        //     src_size.x, src_size.y,
        //     1, olc_SPRITEFLIP_NONE
        // );
    //     DrawPartialDecal(pos[i], decal, src[i], src_size, scale, olc_WHITE);
    // }

    Clear(olc_CYAN);
    float fSpeed = 6.0f;
    if(GetKey(olc_LEFT).bHeld)  fAngle -= fSpeed * fElapsedTime;
    if(GetKey(olc_RIGHT).bHeld) fAngle += fSpeed * fElapsedTime;

    olc_vf2d vScale  = {   1.0f, 1.0f };
    olc_vf2d vCenter = {   (float)sprite->width / 2, (float)sprite->height / 2 };
    olc_vf2d vPos    = { 150.0f, 20.0f };

    // DrawDecal(vPos, decal, vScale, olc_WHITE);
    // DrawSprite(150, 0, sprite, 1, olc_SPRITEFLIP_NONE);
    // DrawPartialRotatedDecal(olc_VF2D(150.0f, 120.0f), decal, fAngle, olc_VF2D(8,8), olc_VF2D(0, 0), olc_VF2D(16, 16), vScale, olc_WHITE);
    DrawPartialRotatedDecal(olc_VF2D(150.0f, 120.0f), decal, fAngle, olc_VF2D(0,0), olc_VF2D(0,0), olc_VF2D(16, 16), vScale, olc_WHITE);
    DrawRotatedDecal(olc_VF2D(150.0f, 150.0f), decal, fAngle, vCenter, vScale, olc_WHITE);
    
    // sprintf(buf, "%f", fAngle);
    // DrawStringDecal(olc_VF2D(6, 6), buf, olc_WHITE, vScale);

    // DrawStringDecal(olc_VF2D(10, 80), "abcdefghijklmnopqrstuvwxyz", olc_WHITE, vScale);
    // DrawString(10, 50, "abcdefghijklmnopqrstuvwxyz", olc_WHITE, 1);

    return !GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{
    olc_Decal_Destroy(decal);
    olc_Sprite_Destroy(sprite);
    return true;
}


int main(int argc, char* argv[])
{
    SetAppName("IT WORKS!!!");
    if(Construct(320, 240, 3, 3, false, false))
    {
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);
    }

    SetAppName("IT WORKS!!!");
    if(Construct(320, 240, 3, 3, false, false))
    {
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);
    }

    return 0;
}
