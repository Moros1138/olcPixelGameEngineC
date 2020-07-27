#include "engine.h"

// init vector struct
void vector_init(vector* v)
{
    // init vector capacity
    v->capacity = 0;
    // init vector size
    v->size = 0;
    // no items
    v->items = NULL;
}

// resize the capacity of the vector
void vector_resize(vector* v, size_t capacity)
{
    // attempt reallocation
    void** items = realloc(v->items, sizeof(void *) * capacity);
    
    // if success
    if(items != NULL)
    {
        // ensure vector items is pointing to the newly allocated memory
        v->items = items;
        // update vector's new capacity
        v->capacity = capacity;
    }
}

// free the memory used by the provided vector and reset capacity and size to 0
void vector_free(vector* v)
{
    // free individual items
    for(int i = 0; i < vector_size(v); i++)
    {
        free(v->items[i]);
        v->items[i] = NULL;
    }

    // free the items array
    free(v->items);

    // reset vector variables
    v->capacity = 0;
    v->items = NULL;
    v->size = 0;
}

// alias of vector_free
void vector_clear(vector* v)
{ vector_free(v); }

// push the provided item at the end of the provided vector
size_t vector_push(vector* v, void* item)
{
    // do nothing if no item is provided
    if(item == NULL) -1;

    // determine if array needs to be resized
    if(v->size + 1 > v->capacity)
    {
        // resize the array
        if(v->capacity == 0)
            vector_resize(v, 1);
        else
            vector_resize(v, v->capacity * 2);
    }

    // increment the size of the array
    v->size++;
    
    // put the item at the end of the array
    v->items[v->size-1] = item;
    
    // return the index of the pushed item
    return v->size-1;
}

// set, at the provided index, the provided item into the provided vector
void vector_set(vector* v, size_t index, void* item)
{
    // do nothing if no item is provided
    if(item == NULL) return;
    
    // bounds sanity check
    if(index >= 0 && index < v->size)
    {
        // put the item at the provided index
        v->items[index] = item;
    }
}

// get, from the provided index, the provided item from the provided vector
void* vector_get(vector* v, size_t index)
{
    if(index >= 0 && index < v->size)
        return v->items[index];
    
    return NULL;
}

// delete the item at the provided index
void vector_remove(vector* v, size_t index)
{
    // bounds sanity check
    if(index >= 0 && index < v->size)
    {
        // free the item's memory
        free(v->items[index]);
        
        // set the item to NULL
        v->items[index] = NULL;

        // shift the rest of the array by 1
        for(int i = index; i < v->size - 1; i++)
        {
            v->items[i] = v->items[i+1];
            v->items[i+1] = NULL;
        }
        
        // decrement the size of the array
        v->size--;
        
        // if the size is low enough to resize the array
        if(v->size > 0 && v->size < v->capacity / 4)
            vector_resize(v, v->capacity / 2);
    }
}

// get number of elements currently stored in the provided vector
size_t vector_size(vector* v)
{ return v->size; }


olc_Pixel olc_PixelDefault()
{ return olc_PixelRAW(olc_nDefaultPixel); }

olc_Pixel olc_PixelRAW(uint32_t p)
{ olc_Pixel a; a.n = p; return a; }

olc_Pixel olc_PixelRGB(uint8_t red, uint8_t green, uint8_t blue)
{ olc_Pixel a; a.r = red; a.g = green; a.b = blue; a.a = 255; return a; }

olc_Pixel olc_PixelRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{ olc_Pixel a; a.r = red; a.g = green; a.b = blue; a.a = alpha; return a; }

olc_Pixel olc_PixelF(float red, float green, float blue, float alpha)
{
    olc_Pixel a;
    
    a.r = (uint8_t)(red * 255); 
    a.g = (uint8_t)(green * 255); 
    a.b = (uint8_t)(blue * 255); 
    a.a = (uint8_t)(alpha * 255); 
    
    return a;
}

bool olc_PixelCompare(olc_Pixel a, olc_Pixel b)
{ return (a.n == b.n) ? true : false; }

void olc_PixelColourInit()
{
    olc_GREY = olc_PixelRGB(192, 192, 192); olc_DARK_GREY = olc_PixelRGB(128, 128, 128); olc_VERY_DARK_GREY = olc_PixelRGB(64, 64, 64);
    olc_RED = olc_PixelRGB(255, 0, 0);       olc_DARK_RED = olc_PixelRGB(128, 0, 0);       olc_VERY_DARK_RED = olc_PixelRGB(64, 0, 0);
    olc_YELLOW = olc_PixelRGB(255, 255, 0);  olc_DARK_YELLOW = olc_PixelRGB(128, 128, 0);  olc_VERY_DARK_YELLOW = olc_PixelRGB(64, 64, 0);
    olc_GREEN = olc_PixelRGB(0, 255, 0);     olc_DARK_GREEN = olc_PixelRGB(0, 128, 0);     olc_VERY_DARK_GREEN = olc_PixelRGB(0, 64, 0);
    olc_CYAN = olc_PixelRGB(0, 255, 255);    olc_DARK_CYAN = olc_PixelRGB(0, 128, 128);    olc_VERY_DARK_CYAN = olc_PixelRGB(0, 64, 64);
    olc_BLUE = olc_PixelRGB(0, 0, 255);      olc_DARK_BLUE = olc_PixelRGB(0, 0, 128);      olc_VERY_DARK_BLUE = olc_PixelRGB(0, 0, 64);
    olc_MAGENTA = olc_PixelRGB(255, 0, 255); olc_DARK_MAGENTA = olc_PixelRGB(128, 0, 128); olc_VERY_DARK_MAGENTA = olc_PixelRGB(64, 0, 64);
    olc_WHITE = olc_PixelRGB(255, 255, 255); olc_BLACK = olc_PixelRGB(0, 0, 0);            olc_BLANK = olc_PixelRGBA(0, 0, 0, 0);
}

olc_Sprite* olc_SpriteCreate(int32_t w, int32_t h)
{
    olc_Sprite* sprite;

    sprite = (olc_Sprite*)malloc(sizeof(olc_Sprite));
    if(sprite == NULL)
    {
        fprintf(stderr, "Failed to allcoate ram for sprite.\n");
        exit(EXIT_FAILURE);
    }

    sprite->width = w;
    sprite->height = h;
    sprite->pixels = (unsigned int*)calloc(sizeof(uint32_t), w * h);
    
    if(sprite->pixels == NULL)
    {
        fprintf(stderr, "Failed to allcoate ram for sprite pixel data.\n");
        exit(EXIT_FAILURE);
    }

    return sprite;
}

olc_Sprite* olc_SpriteLoad(const char *sImageFile)
{
    return NULL;
}

void olc_SpriteDestroy(olc_Sprite* sprite)
{
    free(sprite->pixels);
    sprite->pixels = NULL;
    
    free(sprite);
    sprite = NULL;
}

// olc_Sprite* olc_SpriteLoadFromFile(const char *sImageFile);
// olc_Sprite* olc_SpriteLoadFromPGESprFile(const char *sImageFile);
// olc_rcode   olc_SpriteSaveToPGESprFile(olc_Sprite* sprite, const char *sImageFile);

void olc_Sprite_SetSampleMode(olc_Sprite* sprite, uint32_t mode)
{
    sprite->modeSample = mode;
}

olc_Pixel olc_Sprite_GetPixel(olc_Sprite* sprite, int32_t x, int32_t y)
{
    if(x >= 0 && y >= 0 && x < sprite->width && y < sprite->height)
    {
        return olc_PixelRAW(sprite->pixels[y * sprite->width + x]);
    }

    return olc_PixelDefault();
}

bool olc_Sprite_SetPixel(olc_Sprite* sprite, int32_t x, int32_t y, olc_Pixel p)
{
    if(x >= 0 && y >= 0 && x < sprite->width && y < sprite->height)
    {
        sprite->pixels[y * sprite->width + x] = p.n;
        return true;
    }
    
    return false;
}

olc_Pixel olc_Sprite_Sample(olc_Sprite* sprite, float x, float y)
{
    // int32_t sx = min((int32_t)((x * (float)sprite->width)), sprite->width - 1);
    // int32_t sy = min((int32_t)((y * (float)sprite->height)), sprite->height - 1);
    int32_t sx, sy;

    return olc_Sprite_GetPixel(sprite, sx, sy);
}

// olc_Pixel olc_Sprite_SampleBL(olc_Sprite* sprite, float u, float v);
uint32_t* olc_Sprite_GetData(olc_Sprite* sprite)
{
    return sprite->pixels;
}


// Hardware Interfaces


// Returns true if window is currently in focus
bool IsFocused()
{ return PGE.bHasInputFocus; }

// Get the state of a specific keyboard button

olc_HWButton GetKey(uint8_t k)
{ return PGE.pKeyboardState[k]; }

// Get the state of a specific mouse button
olc_HWButton GetMouse(uint32_t b)
{ return PGE.pMouseState[b]; }

// Get Mouse X coordinate in "xel" space
int32_t GetMouseX()
{ return PGE.vMousePos.x; }

// Get Mouse Y coordinate in "pixel" space
int32_t GetMouseY()
{ return PGE.vMousePos.y; }

// Get Mouse Wheel Delta
int32_t GetMouseWheel()
{ return PGE.nMouseWheelDelta; }

// Get the ouse in window space
olc_vi2d GetWindowMouse()
{ return PGE.vMouseWindowPos; }


// Utility


// Returns the width of the screen in "pixels"
int32_t ScreenWidth()
{ return PGE.vScreenSize.x; }

// Returns the height of the screen in "pixels"
int32_t ScreenHeight()
{ return PGE.vScreenSize.y; }

// Returns the width of the currently selected drawing target in "pixels"
int32_t GetDrawTargetWidth()
{ return PGE.pDrawTarget->width; }

// Returns the height of the currently selected drawing target in "pixels"
int32_t GetDrawTargetHeight()
{ return PGE.pDrawTarget->height; }

// Returns the currently active draw target
olc_Sprite* GetDrawTarget()
{ return PGE.pDrawTarget; }

// Resize the primary screen sprite
void SetScreenSize(int w, int h)
{
    PGE.vScreenSize.x = w;
    PGE.vScreenSize.y = h;

    for(int i = 0; i < PGE.vLayers.size; i++)
    {
        olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, i);
        olc_SpriteDestroy(ld->pDrawTarget);
        ld->pDrawTarget = olc_SpriteCreate(PGE.vScreenSize.x, PGE.vScreenSize.y);
        ld->bUpdate = true;
    }
        
    SetDrawTarget(NULL);

    olc_Renderer_ClearBuffer(olc_BLACK, true);
    olc_Renderer_DisplayFrame();
    olc_Renderer_ClearBuffer(olc_BLACK, true);
    olc_Renderer_UpdateViewport(PGE.vViewPos, PGE.vViewSize);
}

// Specify which Sprite should be the target of drawing functions, use NULL
// to specify the primary screen
void SetDrawTarget(olc_Sprite *target)
{
    if(target == NULL)
    {
        olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, 0);
        PGE.pDrawTarget = ld->pDrawTarget;
        PGE.nTargetLayer = 0;
    }
    else
    {
        PGE.pDrawTarget = target;
    }
}

// Gets the current Frames Per Second
uint32_t GetFPS()
{ return PGE.nLastFPS; }

// Gets last update of elapsed time
const float GetElapsedTime()
{ return PGE.fLastElapsed; }

// Gets Actual Window size
const olc_vi2d GetWindowSize()
{ return PGE.vWindowSize; }

// Is system mouse cursor currently visible?
bool IsMouseCursorVisible()
{ return PGE.bMouseIsVisible; }



// CONFIGURATION ROUTINES


// Layer targeting functions
void SetLayerDrawTarget(uint8_t layer)
{
    olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, layer);
    PGE.pDrawTarget = ld->pDrawTarget;
    ld->bUpdate = true;
    PGE.nTargetLayer = layer;
}

void EnableLayer(uint8_t layer, bool b)
{
    if(layer < PGE.vLayers.size)
    {
        olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, layer);
        ld->bShow = b;
    }
}

void SetLayerOffset(uint8_t layer, float x, float y)
{
    if(layer < PGE.vLayers.size)
    {
        olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, layer);
        ld->vOffset.x = x;
        ld->vOffset.y = y;
    }

}

void SetLayerScale(uint8_t layer, float x, float y)
{
    if(layer < PGE.vLayers.size)
    {
        olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, layer);
        ld->vScale.x = x;
        ld->vScale.y = y;
    }
}

void SetLayerTint(uint8_t layer, const olc_Pixel tint)
{
    if(layer < PGE.vLayers.size)
    {
        olc_LayerDesc* ld = (olc_LayerDesc*)vector_get(&PGE.vLayers, layer);
        ld->tint = tint;
    }
}

void SetLayerCustomRenderFunction(uint8_t layer, void (*f)())
{
    if(layer < PGE.vLayers.size)
    {
        olc_LayerDesc* ld = vector_get(&PGE.vLayers, layer);
        ld->funcHook = f;
    }
}

vector GetLayers()
{ return PGE.vLayers; }

uint32_t CreateLayer()
{
    olc_LayerDesc* ld = (olc_LayerDesc*)malloc(sizeof(olc_LayerDesc));
    ld->pDrawTarget = olc_SpriteCreate(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->nResID = olc_Renderer_CreateTexture(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->funcHook = NULL;
    vector_init(&ld->vecDecalInstance);
    olc_Renderer_UpdateTexture(ld->nResID, ld->pDrawTarget);
    vector_push(&PGE.vLayers, ld);
    return (uint32_t)(PGE.vLayers.size - 1);
}

// Change the pixel mode for different optimisations
// olc_PIXELMODE_NORMAL = No transparency
// olc_PIXELMODE_MASK   = Transparent if alpha is < 255
// olc_PIXELMODE_ALPHA  = Full transparency
void SetPixelMode(int32_t m)
{ PGE.nPixelMode = m; }

int32_t GetPixelMode()
{ return PGE.nPixelMode; }

// Use a custom blend function
void SetCustomPixelMode(olc_Pixel (*funcPixelMode)(int x, int y, olc_Pixel p1, olc_Pixel p2))
{
    PGE.funcPixelMode = funcPixelMode;
    PGE.nPixelMode = olc_PIXELMODE_CUSTOM;
}

// Change the blend factor form between 0.0f to 1.0f;
void SetPixelBlend(float fBlend)
{
    PGE.fFrameTimer = fBlend;
    if(PGE.fBlendFactor < 0.0f) PGE.fBlendFactor = 0.0f;
    if(PGE.fBlendFactor > 1.0f) PGE.fBlendFactor = 1.0f;
}

// Offset texels by sub-pixel amount (advanced, do not use)
void SetSubPixelOffset(float ox, float oy)
{
    //vSubPixelOffset.x = ox * vPixel.x;
    //vSubPixelOffset.y = oy * vPixel.y;
}

// show the system mouse cursor (true: visible, false: invisible)
void ShowSystemMouseCursor(bool state)
{ PGE.bMouseIsVisible = state; }



// DRAWING ROUTINES



// "Break In" Functions
void olc_PGE_UpdateMouse(int32_t x, int32_t y)
{
    // Mouse coords come in screen space
    // But leave in pixel space
    PGE.bHasMouseFocus = true;
    PGE.vMouseWindowPos.x = x;
    PGE.vMouseWindowPos.y = y;

    // Full Screen mode may have a weird viewport we must clamp to
    x -= PGE.vViewPos.x;
    y -= PGE.vViewPos.y;

    PGE.vMousePosCache.x = (int32_t)(((float)x / (float)(PGE.vWindowSize.x - (PGE.vViewPos.x * 2)) * (float)PGE.vScreenSize.x));
    PGE.vMousePosCache.y = (int32_t)(((float)y / (float)(PGE.vWindowSize.y - (PGE.vViewPos.y * 2)) * (float)PGE.vScreenSize.y));
    if(PGE.vMousePosCache.x >= (int32_t)PGE.vScreenSize.x)	PGE.vMousePosCache.x = PGE.vScreenSize.x - 1;
    if(PGE.vMousePosCache.y >= (int32_t)PGE.vScreenSize.y)	PGE.vMousePosCache.y = PGE.vScreenSize.y - 1;
    if(PGE.vMousePosCache.x < 0) PGE.vMousePosCache.x = 0;
    if(PGE.vMousePosCache.y < 0) PGE.vMousePosCache.y = 0;

}

void olc_PGE_UpdateMouseWheel(int32_t delta)
{ PGE.nMouseWheelDeltaCache += delta; }

void olc_PGE_UpdateWindowSize(int32_t x, int32_t y)
{
    PGE.vWindowSize.x = x;
    PGE.vWindowSize.y = y;
    olc_PGE_UpdateViewport();
}

void olc_PGE_UpdateViewport()
{
    int32_t ww = PGE.vScreenSize.x * PGE.vPixelSize.x;
    int32_t wh = PGE.vScreenSize.y * PGE.vPixelSize.y;
    float wasp = (float)ww / (float)wh;

    PGE.vViewSize.x = (int32_t)PGE.vWindowSize.x;
    PGE.vViewSize.y = (int32_t)((float)PGE.vViewSize.x / wasp);

    if(PGE.vViewSize.y > PGE.vWindowSize.y)
    {
        PGE.vViewSize.y = PGE.vWindowSize.y;
        PGE.vViewSize.x = (int32_t)((float)PGE.vViewSize.y * wasp);
    }

    PGE.vViewPos.x = (PGE.vWindowSize.x - PGE.vViewSize.x) / 2;
    PGE.vViewPos.y = (PGE.vWindowSize.y - PGE.vViewSize.y) / 2;
}

void olc_PGE_ConstructFontSheet()
{
    char *data = (char*)calloc(sizeof(char), 1025);
    
    strcat(data, "?Q`0001oOch0o01o@F40o0<AGD4090LAGD<090@A7ch0?00O7Q`0600>00000000");
    strcat(data, "O000000nOT0063Qo4d8>?7a14Gno94AA4gno94AaOT0>o3`oO400o7QN00000400");
    strcat(data, "Of80001oOg<7O7moBGT7O7lABET024@aBEd714AiOdl717a_=TH013Q>00000000");
    strcat(data, "720D000V?V5oB3Q_HdUoE7a9@DdDE4A9@DmoE4A;Hg]oM4Aj8S4D84@`00000000");
    strcat(data, "OaPT1000Oa`^13P1@AI[?g`1@A=[OdAoHgljA4Ao?WlBA7l1710007l100000000");
    strcat(data, "ObM6000oOfMV?3QoBDD`O7a0BDDH@5A0BDD<@5A0BGeVO5ao@CQR?5Po00000000");
    strcat(data, "Oc``000?Ogij70PO2D]??0Ph2DUM@7i`2DTg@7lh2GUj?0TO0C1870T?00000000");
    strcat(data, "70<4001o?P<7?1QoHg43O;`h@GT0@:@LB@d0>:@hN@L0@?aoN@<0O7ao0000?000");
    strcat(data, "OcH0001SOglLA7mg24TnK7ln24US>0PL24U140PnOgl0>7QgOcH0K71S0000A000");
    strcat(data, "00H00000@Dm1S007@DUSg00?OdTnH7YhOfTL<7Yh@Cl0700?@Ah0300700000000");
    strcat(data, "<008001QL00ZA41a@6HnI<1i@FHLM81M@@0LG81?O`0nC?Y7?`0ZA7Y300080000");
    strcat(data, "O`082000Oh0827mo6>Hn?Wmo?6HnMb11MP08@C11H`08@FP0@@0004@000000000");
    strcat(data, "00P00001Oab00003OcKP0006@6=PMgl<@440MglH@000000`@000001P00000000");
    strcat(data, "Ob@8@@00Ob@8@Ga13R@8Mga172@8?PAo3R@827QoOb@820@0O`0007`0000007P0");
    strcat(data, "O`000P08Od400g`<3V=P0G`673IP0`@3>1`00P@6O`P00g`<O`000GP800000000");
    strcat(data, "?P9PL020O`<`N3R0@E4HC7b0@ET<ATB0@@l6C4B0O`H3N7b0?P01L3R000000020");

    PGE.fontSprite = olc_SpriteCreate(128, 48);
    int px = 0, py = 0;
    for (size_t b = 0; b < 1024; b += 4)
    {
        uint32_t sym1 = (uint32_t)data[b + 0] - 48;
        uint32_t sym2 = (uint32_t)data[b + 1] - 48;
        uint32_t sym3 = (uint32_t)data[b + 2] - 48;
        uint32_t sym4 = (uint32_t)data[b + 3] - 48;
        uint32_t r = sym1 << 18 | sym2 << 12 | sym3 << 6 | sym4;

        for (int i = 0; i < 24; i++)
        {
            int k = r & (1 << i) ? 255 : 0;
            olc_Sprite_SetPixel(PGE.fontSprite, px, py, olc_PixelRGBA(k, k, k, k));
            if (++py == 48) { px++; py = 0; }
        }
    }

    PGE.fontDecal = olc_DecalCreate(PGE.fontSprite);
}

void olc_PGE_CoreUpdate()
{
    clock_gettime(CLOCK_MONOTONIC, &PGE.tp2);
    double duration = 1000.0*PGE.tp2.tv_sec + 1e-6*PGE.tp2.tv_nsec - (1000.0*PGE.tp1.tv_sec + 1e-6*PGE.tp1.tv_nsec);
    PGE.tp1 = PGE.tp2;

    float fElapsedTime = (float)(duration / 1000.0f);
    PGE.fLastElapsed = fElapsedTime;

    olc_Platform_HandleSystemEvent();

    // INPUT WRANGLING
    for(int i = 0; i < 256; i++)
    {
        PGE.pKeyboardState[i].bPressed = false;
        PGE.pKeyboardState[i].bReleased = false;

        if(PGE.pKeyNewState[i] != !PGE.pKeyOldState[i])
        {
            if(PGE.pKeyNewState[i])
            {
                PGE.pKeyboardState[i].bPressed = !PGE.pKeyboardState[i].bHeld;
                PGE.pKeyboardState[i].bHeld = true;
            }
            else
            {
                PGE.pKeyboardState[i].bReleased = true;
                PGE.pKeyboardState[i].bHeld = false;
            }
        }
        
        PGE.pKeyOldState[i] = PGE.pKeyNewState[i];
        
        if(i < olc_nMouseButtons)
        {
            PGE.pMouseState[i].bPressed = false;
            PGE.pMouseState[i].bReleased = false;
            
            if(PGE.pMouseNewState[i] != !PGE.pMouseOldState[i])
            {
                if(PGE.pMouseNewState[i])
                {
                    PGE.pMouseState[i].bPressed = !PGE.pMouseState[i].bHeld;
                    PGE.pMouseState[i].bHeld = true;
                }
                else
                {
                    PGE.pMouseState[i].bReleased = true;
                    PGE.pMouseState[i].bHeld = false;
                }
            }
            
            PGE.pMouseOldState[i] = PGE.pMouseNewState[i];
        }
    }

    // Cache mouse coordinates so they remain consistent during frame
    PGE.vMousePos = PGE.vMousePosCache;
    PGE.nMouseWheelDelta = PGE.nMouseWheelDeltaCache;
    PGE.nMouseWheelDeltaCache = 0;

    olc_Renderer_ClearBuffer(olc_BLACK, true);

    // Handle Frame Update
    if(!PGE.OnUserUpdate(fElapsedTime))
        PGE.bActive = false;

    // Display Frame
    olc_Renderer_UpdateViewport(PGE.vViewPos, PGE.vViewSize);
    olc_Renderer_ClearBuffer(olc_BLACK, true);

    // Layer 0
    olc_LayerDesc* ld = vector_get(&PGE.vLayers, 0);
    ld->bUpdate = true;
    ld->bShow = true;
    olc_Renderer_PrepareDrawing();

    for(int i = PGE.vLayers.size-1; i >= 1; i--)
    {
        olc_LayerDesc* layer = vector_get(&PGE.vLayers, i);
        if(layer->bShow)
        {
            if(layer->funcHook == NULL)
            {
                olc_Renderer_ApplyTexture(layer->nResID);
                if(layer->bUpdate)
                {
                    olc_Renderer_UpdateTexture(layer->nResID, layer->pDrawTarget);
                    layer->bUpdate = false;
                }

                olc_Renderer_DrawLayerQuad(layer->vOffset, layer->vScale, layer->tint);

                // Display Decals in order for this layer
                for(int j = 0; j < layer->vecDecalInstance.size; j++)
                {
                    olc_DecalInstance* decal = vector_get(&layer->vecDecalInstance, j);
                    olc_Renderer_DrawDecalQuad(decal);
                }
                // clear the instances
                vector_clear(&layer->vecDecalInstance);
            }
            else
            {
                // Mwa ha ha.... Have Fun!!!
                layer->funcHook();
            }
            
        }
    }
}

void olc_PGE_PrepareEngine()
{
    // Start OpenGL, the context is owned by the game thread
    if (olc_Platform_CreateGraphics(PGE.bFullScreen, PGE.bEnableVSYNC, PGE.vViewPos, PGE.vViewSize) == olc_RCODE_FAIL) return;

    // Construct default font sheet
    olc_PGE_ConstructFontSheet();

    // Initialize Layer Vector
    vector_init(&PGE.vLayers);
    
    // Create Primary Layer "0"
    CreateLayer();

    olc_LayerDesc* ld = vector_get(&PGE.vLayers, 0);
    ld->bUpdate = true;
    ld->bShow = true;
    SetDrawTarget(NULL);

    clock_gettime(CLOCK_MONOTONIC, &PGE.tp1); // POSIX; use timespec_get in C11
    clock_gettime(CLOCK_MONOTONIC, &PGE.tp2);
}

void olc_PGE_UpdateMouseState(int32_t button, bool state)
{ PGE.pMouseNewState[button] = state; }

void olc_PGE_UpdateKeyState(int32_t key, bool state)
{ PGE.pKeyNewState[key] = state; }

void olc_PGE_UpdateMouseFocus(bool state)
{ PGE.bHasMouseFocus = state; }

void olc_PGE_UpdateKeyFocus(bool state)
{ PGE.bHasInputFocus = state; }

void olc_PGE_Terminate()
{ PGE.bActive = false; }


// RENDERER

void       olc_Renderer_PrepareDevice()
{}

int32_t    olc_Renderer_CreateDevice(vector params, bool bFullScreen, bool bVSYNC)
{}

int32_t    olc_Renderer_DestroyDevice()
{}

void       olc_Renderer_DisplayFrame()
{}

void       olc_Renderer_PrepareDrawing()
{}

void       olc_Renderer_DrawLayerQuad(const olc_vf2d offset, const olc_vf2d scale, const olc_Pixel tint)
{}

void       olc_Renderer_DrawDecalQuad(olc_DecalInstance* decal)
{}

uint32_t   olc_Renderer_CreateTexture(const uint32_t width, const uint32_t height)
{}

void       olc_Renderer_UpdateTexture(uint32_t id, olc_Sprite* spr)
{}

uint32_t   olc_Renderer_DeleteTexture(const uint32_t id)
{}

void       olc_Renderer_ApplyTexture(uint32_t id)
{}

void       olc_Renderer_UpdateViewport(const olc_vi2d pos, const olc_vi2d size)
{}

void       olc_Renderer_ClearBuffer(olc_Pixel p, bool bDepth)
{}


// PLATFORM


int32_t olc_Platform_ApplicationStartUp()
{}

int32_t olc_Platform_ApplicationCleanUp()
{}

int32_t olc_Platform_ThreadStartUp()
{}

int32_t olc_Platform_ThreadCleanUp()
{}

int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize)
{}

int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen)
{}

int32_t olc_Platform_SetWindowTitle(const char* s)
{}

int32_t olc_Platform_StartSystemEventLoop()
{}


int32_t olc_Platform_HandleSystemEvent()
{}

