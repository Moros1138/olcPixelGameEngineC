#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

olc_Sprite* sprite;
olc_Decal* decal;
olc_vf2d points[4];
int nSelected = -1;

float mag(olc_vf2d lhs, olc_vf2d rhs)
{
    olc_vf2d t = olc_VF2D(lhs.x - rhs.x, lhs.y - rhs.y);
    return sqrtf(t.x * t.x + t.y * t.y);
}

bool OnUserCreate()
{
    points[0] = olc_VF2D(0, 0);
    points[1] = olc_VF2D(0,  32);
    points[2] = olc_VF2D(32, 32);
    points[3] = olc_VF2D(32, 0);

    sprite = olc_Sprite_Load("../assets/test.png");
    decal = olc_Decal_Create(sprite);

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{
    olc_vf2d vMouse = { (float)PGE_GetMouseX(), (float)PGE_GetMouseY() };

    if(PGE_GetMouse(0).bPressed)
    {
        nSelected = -1;
        for(int i = 0; i < 4; i++)
        {
            if(mag(points[i], vMouse) < 10.0)
            {
                nSelected = i;
                break;
            }
        }
    }
    
    if(PGE_GetMouse(0).bHeld)
        points[nSelected] = vMouse;

    if(PGE_GetMouse(0).bReleased)
        nSelected = -1;
    
    PGE_Clear(olc_BLACK);
    for(int i = 0; i < 4; i++)
    {
        if(nSelected == i)
            PGE_FillCircle(points[i].x, points[i].y, 2, olc_YELLOW);
        else if(mag(points[i], vMouse) < 10.0 && nSelected == -1)
            PGE_FillCircle(points[i].x, points[i].y, 2, olc_BLUE);
        else
            PGE_FillCircle(points[i].x, points[i].y, 2, olc_WHITE);
    }
        
    PGE_DrawWarpedDecal(decal, points, olc_WHITE);

    return !PGE_GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{ return true; }

int main(int argc, char* argv[])
{
    if(Construct(320, 240, 3, 3, false, false))
        Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}