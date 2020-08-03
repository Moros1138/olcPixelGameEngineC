#define OLC_PGE_APPLICATION
#include "../olcPixelGameEngineC.h"

olc_Sprite* sprite;
olc_Decal* decal;



// START WARPING EXAMPLE
olc_vf2d* points;
int nSelected = -1;

float mag(olc_vf2d lhs, olc_vf2d rhs)
{
    olc_vf2d t = olc_VF2D(lhs.x - rhs.x, lhs.y - rhs.y);
    return sqrtf(t.x * t.x + t.y * t.y);
}

olc_vf2d* decalInitPosition(olc_vf2d pos, olc_vf2d size)
{
    olc_vf2d* p = malloc(sizeof(olc_vf2d) * 4);

    p[0] = pos;
    p[1] = olc_VF2D( pos.x, pos.y + size.y );
    p[2] = olc_VF2D( pos.x + size.x, pos.y + size.y );
    p[3] = olc_VF2D( pos.x + size.x, pos.y );
    
    return p;
}
// END WARPING EXAMPLE


// START ROTATING EXAMPLE
float fRotation = 0.0f;
// END ROTATING EXAMPLE

bool OnUserCreate()
{
    points = decalInitPosition(olc_VF2D(200, 100), olc_VF2D(96, 96));

    sprite = olc_Sprite_Load("../assets/test.png");
    decal = olc_Decal_Create(sprite);

    return true;
}

bool OnUserUpdate(float fElapsedTime)
{

    // O------------------------------------------------------------------------------O
    // | EXAMPLE: Drawing a Decal                                                     |
    // O------------------------------------------------------------------------------O

    PGE_DrawDecal(
        olc_VF2D(50, 50), // position x/y
        decal,            // the decal
        olc_VF2D(1,1),    // scale
        olc_WHITE         // tint
    );

    // O------------------------------------------------------------------------------O
    // | EXAMPLE: Drawing Partial Decals                                              |
    // O------------------------------------------------------------------------------O

    // Draw only the 1 Square
    PGE_DrawPartialDecal(
        olc_VF2D(0,0),   // position x/y
        decal,           // the decal
        olc_VF2D(0,0),   // source position
        olc_VF2D(16,16), // source size
        olc_VF2D(1,1),   // scale
        olc_WHITE        // tint
    );
    
    // Draw only the 2 Square
    PGE_DrawPartialDecal(
        olc_VF2D(PGE_ScreenWidth()-16,0),   // position x/y
        decal,           // the decal
        olc_VF2D(0,16),  // source position
        olc_VF2D(16,16), // source size
        olc_VF2D(1,1),   // scale
        olc_WHITE        // tint
    );

    // Draw only the 3 Square
    PGE_DrawPartialDecal(
        olc_VF2D(0,PGE_ScreenHeight()-16),   // position x/y
        decal,           // the decal
        olc_VF2D(16,16), // source position
        olc_VF2D(16,16), // source size
        olc_VF2D(1,1),   // scale
        olc_WHITE        // tint
    );

    // Draw only the 4 Square
    PGE_DrawPartialDecal(
        olc_VF2D(PGE_ScreenWidth()-16,PGE_ScreenHeight()-16),   // position x/y
        decal,           // the decal
        olc_VF2D(16,0),  // source position
        olc_VF2D(16,16), // source size
        olc_VF2D(1,1),   // scale
        olc_WHITE        // tint
    );

    // O------------------------------------------------------------------------------O
    // | EXAMPLE: Drawing Rotated Decals                                              |
    // O------------------------------------------------------------------------------O

    // update rotation angle
    fRotation += 5.0f * fElapsedTime;

    PGE_DrawRotatedDecal(
        olc_VF2D(66,100),                               // Drawing Position
        decal,                                          // the decal
        fRotation,                                      // rotation angle (radians)
        olc_VF2D(sprite->width / 2, sprite->height/2),  // center point
        olc_VF2D(1, 1),                                 // scale
        olc_WHITE                                       // tint
    );
    
    
    // O------------------------------------------------------------------------------O
    // | EXAMPLE: Drawing Warped Decals                                               |
    // O------------------------------------------------------------------------------O

    // cache our mouse position
    olc_vf2d vMouse = { (float)PGE_GetMouseX(), (float)PGE_GetMouseY() };

    // select on mouse down
    if(PGE_GetMouse(0).bPressed)
    {
        // ensure we have no selection
        nSelected = -1;
        
        // cycle through the points
        for(int i = 0; i < 4; i++)
        {
            // if mouse is in range is point, mark it as selected
            if(mag(points[i], vMouse) < 10.0)
            {
                nSelected = i;
                break;
            }
        }
    }
    
    // move the selected point with the mouse while the button is down
    if(PGE_GetMouse(0).bHeld)
        points[nSelected] = vMouse;

    // de-select on mouse up
    if(PGE_GetMouse(0).bReleased)
        nSelected = -1;
    
    // do the drawing

    // clear the screen sprite
    PGE_Clear(olc_BLACK);
    // curcle through the points
    for(int i = 0; i < 4; i++)
    {
        // selected points are yellow
        // un-selected points the mouse hovers near are blue
        // all other points are white
        if(nSelected == i)
            PGE_FillCircle(points[i].x, points[i].y, 2, olc_YELLOW);
        else if(mag(points[i], vMouse) < 10.0 && nSelected == -1)
            PGE_FillCircle(points[i].x, points[i].y, 2, olc_BLUE);
        else
            PGE_FillCircle(points[i].x, points[i].y, 2, olc_WHITE);
    }
    
    PGE_DrawStringDecal(olc_VF2D(200, 80), "Click/Drag\nMy Corners", olc_WHITE, olc_VF2D(1,1));
    PGE_DrawWarpedDecal(
        decal,      // the decal
        points,     // array of 4 points starting top-left going anti-clockwise
        olc_WHITE   // tint
    );

    // END WARPED EXAMPLE



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