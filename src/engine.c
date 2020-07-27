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

// O------------------------------------------------------------------------------O
// | olc::Sprite - An image represented by a 2D array of olc::Pixel               |
// O------------------------------------------------------------------------------O

olc_Sprite* olc_Sprite_Create(int32_t w, int32_t h)
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

olc_Sprite* olc_Sprite_Load(const char *sImageFile)
{
    return olc_Sprite_LoadFromFile(sImageFile);
}

void olc_Sprite_Destroy(olc_Sprite* sprite)
{
    free(sprite->pixels);
    sprite->pixels = NULL;
    
    free(sprite);
    sprite = NULL;
}

// olc_Sprite* olc_SpriteLoadFromPGESprFile(const char *sImageFile);
// int32_t olc_SpriteSaveToPGESprFile(olc_Sprite* sprite, const char *sImageFile);

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

// O------------------------------------------------------------------------------O
// | olc::Decal - A GPU resident storage of an olc::Sprite                        |
// O------------------------------------------------------------------------------O
olc_Decal* olc_Decal_Create(olc_Sprite* sprite)
{ return NULL; }

void       olc_Decal_Destroy(olc_Decal* decal)
{}

void       olc_Decal_Update(olc_Decal* decal)
{}

// O------------------------------------------------------------------------------O
// | olc::Renderable - Convenience class to keep a sprite and decal together      |
// O------------------------------------------------------------------------------O
olc_Renderable* olc_Renderable_Create(uint32_t width, uint32_t height)
{ return NULL; }

olc_Renderable* olc_Renderable_Load(const char* sFile)
{ return NULL; }

olc_Sprite* olc_Renderable_GetSprite(olc_Renderable* renderable)
{ return renderable->sprite; }

olc_Decal* olc_Renderable_GetDecal(olc_Renderable* renderable)
{ return renderable->decal; }

void olc_DefaultState()
{
    SetAppName("");
    PGE.nPixelMode = olc_PIXELMODE_NORMAL;
    PGE.fBlendFactor = 1.0f;
    PGE.bHasInputFocus = true;
    PGE.bHasMouseFocus = true;
    PGE.bEnableVSYNC = false;
    PGE.fFrameTimer = 0.0f;
    PGE.fLastElapsed = 0.0f;
    PGE.nFrameCount = 0;
    PGE.nTargetLayer = 0;
    PGE.nLastFPS = 0.0f;;
};

int32_t Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync)
{
    PGE.vScreenSize.x = screen_w;
    PGE.vScreenSize.y = screen_h;

    PGE.vInvScreenSize.x = 1.0f / (float)screen_w;
    PGE.vInvScreenSize.y = 1.0f / (float)screen_h;
    
    PGE.vPixelSize.x = pixel_w;
    PGE.vPixelSize.y = pixel_h;
    
    PGE.vWindowSize.x = PGE.vScreenSize.x * PGE.vPixelSize.x;
    PGE.vWindowSize.y = PGE.vScreenSize.y * PGE.vPixelSize.y;
    
    PGE.bFullScreen = full_screen;
    PGE.bEnableVSYNC = vsync;
    
    PGE.vPixel.x = 2.0f / PGE.vScreenSize.x;
    PGE.vPixel.y = 2.0f / PGE.vScreenSize.y;

    if(PGE.vPixelSize.x <= 0 || PGE.vPixelSize.y <= 0 || PGE.vScreenSize.x <= 0 || PGE.vScreenSize.y <= 0)
        return olc_RCODE_FAIL;

    olc_PixelColourInit();
    olc_DefaultState();

    return olc_RCODE_OK;
}

#if !defined(PGE_USE_CUSTOM_START)

int32_t Start(bool (*create)(), bool (*update)(float), bool (*destroy)())
{
    PGE.OnUserCreate = create;
    PGE.OnUserUpdate = update;
    PGE.OnUserDestroy = destroy;
    
    if(olc_Platform_ApplicationStartUp() != olc_RCODE_OK) return olc_RCODE_FAIL;
    
    olc_vi2d vWinPos;
    
    vWinPos.x = 30;
    vWinPos.y = 30;

    // Construct the window
    if(olc_Platform_CreateWindowPane(vWinPos, PGE.vWindowSize, PGE.bFullScreen) != olc_RCODE_OK) return olc_RCODE_FAIL;
    olc_PGE_UpdateWindowSize(PGE.vWindowSize.x, PGE.vWindowSize.y);

    // Start the thread
    PGE.bActive = true;
    
    // std::thread t = std::thread(&PixelGameEngine::EngineThread, this);
    EngineThread();


    // Some implementations may form an event loop here
    olc_Platform_StartSystemEventLoop();
    
    // Wait for thread to be exited
    // t.join();

    if(olc_Platform_ApplicationCleanUp() != olc_RCODE_OK) return olc_RCODE_FAIL;

    return olc_RCODE_OK;
}

#endif

void EngineThread()
{
    // Allow platform to do stuff here if needed, since its now in the
    // context of this thread
    if(olc_Platform_ThreadStartUp() == olc_RCODE_FAIL)	return;

    // Do engine context specific initialisation
    olc_PGE_PrepareEngine();

    // Create user resources as part of this thread
    if (!PGE.OnUserCreate()) PGE.bActive = false;

    while(PGE.bActive)
    {
        // Run as fast as possible
        while(PGE.bActive)	{ olc_PGE_CoreUpdate();	}

        // Allow the user to free resources if they have overrided the destroy function
        if (!PGE.OnUserDestroy())
        {
            // User denied destroy for some reason, so continue running
            PGE.bActive = true;
        }
    }

    olc_Platform_ThreadCleanUp();
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
        olc_Sprite_Destroy(ld->pDrawTarget);
        ld->pDrawTarget = olc_Sprite_Create(PGE.vScreenSize.x, PGE.vScreenSize.y);
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


// DRAWING ROUTINES


// Draws a single Pixel
bool Draw(int32_t x, int32_t y, olc_Pixel p)
{
    if(!PGE.pDrawTarget) return false;

    if(PGE.nPixelMode == olc_PIXELMODE_NORMAL)
    {
        return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, p);
    }

    if(PGE.nPixelMode == olc_PIXELMODE_MASK)
    {
        if(p.a == 255)
            return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, p);
    }

    if(PGE.nPixelMode == olc_PIXELMODE_ALPHA)
    {
        olc_Pixel d = olc_Sprite_GetPixel(PGE.pDrawTarget, x, y);
        float a = (float)(p.a / 255.0f) * PGE.fBlendFactor;
        float c = 1.0f - a;
        float r = a * (float)p.r + c * (float)d.r;
        float g = a * (float)p.g + c * (float)d.g;
        float b = a * (float)p.b + c * (float)d.b;
        return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, olc_PixelRGB((uint8_t)r, (uint8_t)g, (uint8_t)b));
    }

    if(PGE.nPixelMode == olc_PIXELMODE_CUSTOM)
    {
        return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, PGE.funcPixelMode(x, y, p, olc_Sprite_GetPixel(PGE.pDrawTarget, x, y)));
    }

    return false;
}

// Draws a line from (x1,y1) to (x2,y2)
void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, olc_Pixel p, uint32_t pattern)
{}

// Draws a circle located at (x,y) with radius
void DrawCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p, uint8_t mask)
{}

// Fills a circle located at (x,y) with radius
void FillCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p)
{}

// Draws a rectangle at (x,y) to (x+w,y+h)
void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p)
{}

// Fills a rectangle at (x,y) to (x+w,y+h)
void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p)
{}

// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p)
{}

// Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p)
{}

// Draws an entire sprite at well in my defencelocation (x,y)
void DrawSprite(int32_t x, int32_t y, olc_Sprite *sprite, uint32_t scale, uint8_t flip)
{}

// Draws an area of a sprite at location (x,y), where the
// selected area is (ox,oy) to (ox+w,oy+h)
void DrawPartialSprite(int32_t x, int32_t y, olc_Sprite *sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip)
{}


// CONFIGURATION ROUTINES
void SetAppName(const char* title)
{
    if(PGE.sAppName != NULL)
        free(PGE.sAppName);
    
    PGE.sAppName = (char*)calloc(sizeof(char),strlen(title)+1);
    
    if(PGE.sAppName == NULL)
    {
        fprintf(stderr, "Failed to set sAppName.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(PGE.sAppName, title);
}


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
    
    ld->pDrawTarget = olc_Sprite_Create(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->nResID = olc_Renderer_CreateTexture(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->tint = olc_WHITE;
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
void SetCustomPixelMode(olc_Pixel (*f)(int x, int y, olc_Pixel p1, olc_Pixel p2))
{
    PGE.funcPixelMode = f;
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

    PGE.fontSprite = olc_Sprite_Create(128, 48);
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

    PGE.fontDecal = olc_Decal_Create(PGE.fontSprite);
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

    for(int i = PGE.vLayers.size-1; i >= 0; i--)
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

    // Present Graphics to screen
    olc_Renderer_DisplayFrame();

    // Update Title Bar
    PGE.fFrameTimer += fElapsedTime;
    PGE.nFrameCount++;
    if(PGE.fFrameTimer >= 1.0f)
    {
        PGE.nLastFPS = PGE.nFrameCount;
        PGE.fFrameTimer -= 1.0f;

        sprintf(PGE.sTitle, "OneLoneCoder.com - Pixel Game Engine - %s - FPS: %d", PGE.sAppName, PGE.nFrameCount);
        olc_Platform_SetWindowTitle(PGE.sTitle);
        PGE.nFrameCount = 0;
    }

}

void olc_PGE_PrepareEngine()
{
    // Start OpenGL, the context is owned by the game thread
    if(olc_Platform_CreateGraphics(PGE.bFullScreen, PGE.bEnableVSYNC, PGE.vViewPos, PGE.vViewSize) == olc_RCODE_FAIL) return;

    // Initialize Layer Vector
    vector_init(&PGE.vLayers);
    
    // Create Primary Layer "0"
    CreateLayer();

    olc_LayerDesc* ld = vector_get(&PGE.vLayers, 0);
    ld->bUpdate = true;
    ld->bShow = true;
    SetDrawTarget(NULL);

    // Construct default font sheet
    olc_PGE_ConstructFontSheet();

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


void texturemap_init(vector* v)
{
    vector_init(v);
}

void texturemap_destroy(vector* v)
{
    vector_free(v);
}

void texturemap_delete(vector* v, int id)
{
    for(int i = 0; i < v->size; i++)
    {
        texturedata* temp = (texturedata*)vector_get(v, i);
        if(id == temp->id)
        {
            SDL_DestroyTexture(temp->t);
            temp->t = NULL;
            vector_remove(v, i);
            return;
        }
    }
}

SDL_Texture* texturemap_get(vector* v, int id)
{
    for(int i = 0; i < v->size; i++)
    {
        texturedata* temp = (texturedata*)vector_get(v, i);
        if(id == temp->id)
            return temp->t;
    }
   
    return 0;
}

void texturemap_set(vector* v, int id, SDL_Texture* texture)
{
    // check if key already exists
    for(int i = 0; i < v->size; i++)
    {
        texturedata* temp = (texturedata*)vector_get(v, i);
        if(id == temp->id)
        {
            temp->t = texture;
            return;
        }
    }

    // if we made it here, we have to create a new inputdata
    texturedata* temp = (texturedata*)malloc(sizeof(texturedata));
    if(temp == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    
    // set data
    temp->id = id;
    temp->t = texture;

    // push into vector
    vector_push(v, temp);
}



void olc_Renderer_PrepareDevice()
{}

int32_t olc_Renderer_CreateDevice(bool bFullScreen, bool bVSYNC)
{
    texturemap_init(&mapTextures);
    return olc_RCODE_OK;
}

int32_t olc_Renderer_DestroyDevice()
{
    for(int i = 0; i < mapTextures.size; i++)
    {
        texturemap_delete(&mapTextures, i);
    }
    texturemap_destroy(&mapTextures);
    return olc_RCODE_OK;
}

void olc_Renderer_DisplayFrame()
{
    SDL_RenderPresent(olc_Renderer);
}

void olc_Renderer_PrepareDrawing()
{}

void olc_Renderer_DrawLayerQuad(const olc_vf2d offset, const olc_vf2d scale, const olc_Pixel tint)
{
    SDL_Texture* texture = texturemap_get(&mapTextures, nActiveTexture);
    // printf("DRAW %ld\n", (size_t)texture);

    // Apply Tint
    SDL_SetTextureColorMod(texture, tint.r, tint.g, tint.b);
    SDL_SetTextureAlphaMod(texture, tint.a);

    // Draw Texture
    SDL_RenderCopy(olc_Renderer, texture, NULL, NULL);
}

olc_vf2d PointToScreen(olc_vf2d point)
{
    olc_vf2d ret;

    ret.x = (point.x + 1.0f) * (float)rViewport.w * 0.5f;
    ret.y = (point.y - 1.0f) * (float)rViewport.h * 0.5f * -1.0f;
    
    return ret;
}

SDL_Rect GetSubTexture(const olc_vf2d uv[4], olc_Decal *decal)
{
    // get the top left of the sub-texture
    olc_vf2d topLeft, bottomRight;
    
    topLeft.x = uv[0].x / decal->vUVScale.x;
    topLeft.y = uv[0].y / decal->vUVScale.y;

    // get the bottom right of the sub-texture
    bottomRight.x = uv[2].x / decal->vUVScale.x;
    bottomRight.y = uv[2].y / decal->vUVScale.y;

    // generate rectangle for the sub-texture
    SDL_Rect rect;
    
    rect.x = topLeft.x;
    rect.y = topLeft.y;
    rect.w = bottomRight.x - topLeft.x;
    rect.h = bottomRight.y - topLeft.x;
    
    return rect;
}

SDL_Rect VecToRect(olc_vf2d pos, olc_vf2d size)
{
    SDL_Rect rect;

    rect.x = pos.x;	rect.y = pos.y;
    rect.w = size.x; rect.h = size.y;

    return rect;
}

void olc_Renderer_DrawDecalQuad(olc_DecalInstance* decal)
{
    if(decal->decal == NULL)
        return;
    
    float fAngle;
    olc_vf2d vSize;

    SDL_Texture* texture = texturemap_get(&mapTextures, decal->decal->id);

    // convert decal positions to screen space
    olc_vf2d pos[4] = {
        PointToScreen(decal->pos[0]),
        PointToScreen(decal->pos[1]),
        PointToScreen(decal->pos[2]),
        PointToScreen(decal->pos[3])
    };

    // only calculate the angle if we have to
    if(pos[0].x == pos[1].x)
    {
        
        vSize.x  = pos[3].x - pos[0].x;
        vSize.y = pos[1].y - pos[0].y;
        fAngle = 0;
    }
    else
    {
        float a = pos[3].x - pos[0].x;
        float b = pos[3].y - pos[0].y;
        
        float c = pos[1].x - pos[0].x;
        float d = pos[1].y - pos[0].y;
        
        vSize.x = sqrt((a * a) + (b * b));
        vSize.y = sqrt((c * c) + (d * d));

        fAngle = (atan2(pos[1].y - pos[0].y, pos[1].x - pos[0].x) * 180 / 3.14159f) - 90;
    }
    
    SDL_Rect src  = GetSubTexture(decal->uv, decal->decal);
    SDL_Rect dest = VecToRect(pos[0], vSize);
    SDL_Point center; center.x = 0; center.y = 0;

    // Apply Tint
    SDL_SetTextureColorMod(texture, decal->tint[0].r, decal->tint[0].g, decal->tint[0].b);
    SDL_SetTextureAlphaMod(texture, decal->tint[0].a);

    // Draw Texture
    SDL_RenderCopyEx(olc_Renderer, texture, &src, &dest, fAngle, &center, SDL_FLIP_NONE);
}

uint32_t olc_Renderer_CreateTexture(const uint32_t width, const uint32_t height)
{
    int id = nTextureID; nTextureID++;
    SDL_Texture* texture = SDL_CreateTexture(olc_Renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if(texture == NULL)
    {
        fprintf(stderr, "Failed to create texture.\n");
        exit(EXIT_FAILURE);
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    texturemap_set(&mapTextures, id, texture);

    return id;
}

void olc_Renderer_UpdateTexture(uint32_t id, olc_Sprite* spr)
{
    SDL_Texture* texture = texturemap_get(&mapTextures, id);
    SDL_UpdateTexture(texture, NULL, (void*)olc_Sprite_GetData(spr), spr->width * 4);
}

uint32_t olc_Renderer_DeleteTexture(const uint32_t id)
{
    texturemap_delete(&mapTextures, id);
    return id;
}

void olc_Renderer_ApplyTexture(uint32_t id)
{
    nActiveTexture = id;
}

void olc_Renderer_UpdateViewport(const olc_vi2d pos, const olc_vi2d size)
{
    rViewport.x = pos.x;  rViewport.y = pos.y;
    rViewport.w = size.x; rViewport.h = size.y;
    
    SDL_RenderSetViewport(olc_Renderer, &rViewport);
}

void olc_Renderer_ClearBuffer(olc_Pixel p, bool bDepth)
{
    SDL_SetRenderDrawColor(olc_Renderer, p.r, p.g, p.b, p.a);
    SDL_RenderClear(olc_Renderer);
}


// PLATFORM


void inputmap_init(vector* v)
{
    vector_init(v);
}

void inputmap_destroy(vector* v)
{
    vector_free(v);
}

void inputmap_delete(vector* v, size_t key)
{
    for(int i = 0; i < v->size; i++)
    {
        inputdata* temp = (inputdata*)vector_get(v, i);
        if(key == temp->key)
        {
            vector_remove(v, i);
            return;
        }
    }
}

uint8_t inputmap_get(vector* v, size_t key)
{
    for(int i = 0; i < v->size; i++)
    {
        inputdata* temp = (inputdata*)vector_get(v, i);
        if(key == temp->key)
            return temp->val;
    }
   
    return 0;
}

void inputmap_set(vector* v, size_t key, uint8_t val)
{
    // check if key already exists
    for(int i = 0; i < v->size; i++)
    {
        inputdata* temp = (inputdata*)vector_get(v, i);
        if(key == temp->key)
        {
            temp->val = val;
            return;
        }
    }

    // if we made it here, we have to create a new inputdata
    inputdata* temp = (inputdata*)malloc(sizeof(inputdata));
    if(temp == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    
    // set data
    temp->key = key;
    temp->val = val;

    // push into vector
    vector_push(v, temp);    
}



int32_t olc_Platform_ApplicationStartUp()
{ return olc_RCODE_OK; }

int32_t olc_Platform_ApplicationCleanUp()
{
    SDL_DestroyRenderer(olc_Renderer);
    SDL_DestroyWindow(olc_Window);
    SDL_Quit();
    return olc_RCODE_OK;
}

int32_t olc_Platform_ThreadStartUp()
{ return olc_RCODE_OK; }

int32_t olc_Platform_ThreadCleanUp()
{ return olc_RCODE_OK; }

int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize)
{
    int flags = (bEnableVSYNC) ? SDL_RENDERER_PRESENTVSYNC : 0;

    olc_Renderer = SDL_CreateRenderer(olc_Window, -1, SDL_RENDERER_ACCELERATED | flags );

    if(olc_Renderer_CreateDevice(bFullScreen, bEnableVSYNC) == olc_RCODE_OK)
    {
        olc_Renderer_UpdateViewport(vViewPos, vViewSize);
        return olc_RCODE_OK;
    }
    else
    {
        return olc_RCODE_FAIL;
    }
    
    return olc_RCODE_OK;
}

int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen)
{
    olc_Window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, vWindowSize.x, vWindowSize.y, SDL_WINDOW_SHOWN);
    SDL_SetWindowResizable(olc_Window, SDL_TRUE);
    SDL_SetWindowFullscreen(olc_Window, (bFullScreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );

    inputmap_init(&mapKeys);
    
    inputmap_set(&mapKeys, SDLK_UNKNOWN, olc_NONE);
    inputmap_set(&mapKeys, SDLK_a, olc_A); inputmap_set(&mapKeys, SDLK_b, olc_B);
    inputmap_set(&mapKeys, SDLK_c, olc_C); inputmap_set(&mapKeys, SDLK_d, olc_D);
    inputmap_set(&mapKeys, SDLK_e, olc_E); inputmap_set(&mapKeys, SDLK_f, olc_F);
    inputmap_set(&mapKeys, SDLK_g, olc_G); inputmap_set(&mapKeys, SDLK_h, olc_H);
    inputmap_set(&mapKeys, SDLK_i, olc_I); inputmap_set(&mapKeys, SDLK_j, olc_J);
    inputmap_set(&mapKeys, SDLK_k, olc_K); inputmap_set(&mapKeys, SDLK_l, olc_L);
    inputmap_set(&mapKeys, SDLK_m, olc_M); inputmap_set(&mapKeys, SDLK_n, olc_N);
    inputmap_set(&mapKeys, SDLK_o, olc_O); inputmap_set(&mapKeys, SDLK_p, olc_P);
    inputmap_set(&mapKeys, SDLK_q, olc_Q); inputmap_set(&mapKeys, SDLK_r, olc_R);
    inputmap_set(&mapKeys, SDLK_s, olc_S); inputmap_set(&mapKeys, SDLK_t, olc_T);
    inputmap_set(&mapKeys, SDLK_u, olc_U); inputmap_set(&mapKeys, SDLK_v, olc_V);
    inputmap_set(&mapKeys, SDLK_w, olc_W); inputmap_set(&mapKeys, SDLK_x, olc_X);
    inputmap_set(&mapKeys, SDLK_y, olc_Y); inputmap_set(&mapKeys, SDLK_z, olc_Z);
    
    inputmap_set(&mapKeys, SDLK_0, olc_K0); inputmap_set(&mapKeys, SDLK_1, olc_K1); 
    inputmap_set(&mapKeys, SDLK_2, olc_K2); inputmap_set(&mapKeys, SDLK_3, olc_K3);
    inputmap_set(&mapKeys, SDLK_4, olc_K4); inputmap_set(&mapKeys, SDLK_5, olc_K5); 
    inputmap_set(&mapKeys, SDLK_6, olc_K6); inputmap_set(&mapKeys, SDLK_7, olc_K7);
    inputmap_set(&mapKeys, SDLK_8, olc_K8); inputmap_set(&mapKeys, SDLK_9, olc_K9);

    inputmap_set(&mapKeys, SDLK_F1,  olc_F1);  inputmap_set(&mapKeys, SDLK_F2,  olc_F2);
    inputmap_set(&mapKeys, SDLK_F3,  olc_F3);  inputmap_set(&mapKeys, SDLK_F4,  olc_F4);
    inputmap_set(&mapKeys, SDLK_F5,  olc_F5);  inputmap_set(&mapKeys, SDLK_F6,  olc_F6);
    inputmap_set(&mapKeys, SDLK_F7,  olc_F7);  inputmap_set(&mapKeys, SDLK_F8,  olc_F8);
    inputmap_set(&mapKeys, SDLK_F9,  olc_F9);  inputmap_set(&mapKeys, SDLK_F10, olc_F10);
    inputmap_set(&mapKeys, SDLK_F11, olc_F11); inputmap_set(&mapKeys, SDLK_F12, olc_F12);

    inputmap_set(&mapKeys, SDLK_DOWN,       olc_DOWN);   inputmap_set(&mapKeys, SDLK_LEFT,   olc_LEFT);
    inputmap_set(&mapKeys, SDLK_RIGHT,      olc_RIGHT);  inputmap_set(&mapKeys, SDLK_UP,     olc_UP);
    inputmap_set(&mapKeys, SDLK_KP_ENTER,   olc_ENTER);  inputmap_set(&mapKeys, SDLK_RETURN, olc_ENTER);
    inputmap_set(&mapKeys, SDLK_BACKSPACE,  olc_BACK);   inputmap_set(&mapKeys, SDLK_ESCAPE, olc_ESCAPE);
    inputmap_set(&mapKeys, SDLK_RETURN,     olc_ENTER);  inputmap_set(&mapKeys, SDLK_PAUSE,  olc_PAUSE);
    inputmap_set(&mapKeys, SDLK_SCROLLLOCK, olc_SCROLL); inputmap_set(&mapKeys, SDLK_TAB,    olc_TAB);
    inputmap_set(&mapKeys, SDLK_DELETE,     olc_DEL);    inputmap_set(&mapKeys, SDLK_HOME,   olc_HOME);
    inputmap_set(&mapKeys, SDLK_END,        olc_END);    inputmap_set(&mapKeys, SDLK_PAGEUP, olc_PGUP);
    inputmap_set(&mapKeys, SDLK_PAGEDOWN,   olc_PGDN);   inputmap_set(&mapKeys, SDLK_INSERT, olc_INS);
    inputmap_set(&mapKeys, SDLK_LSHIFT,     olc_SHIFT);  inputmap_set(&mapKeys, SDLK_RSHIFT, olc_SHIFT);
    inputmap_set(&mapKeys, SDLK_LCTRL,      olc_CTRL);   inputmap_set(&mapKeys, SDLK_RCTRL,  olc_CTRL);
    inputmap_set(&mapKeys, SDLK_SPACE,      olc_SPACE);

    inputmap_set(&mapKeys, SDLK_KP_0, olc_NP0); inputmap_set(&mapKeys, SDLK_KP_1, olc_NP1);
    inputmap_set(&mapKeys, SDLK_KP_2, olc_NP2); inputmap_set(&mapKeys, SDLK_KP_3, olc_NP3);
    inputmap_set(&mapKeys, SDLK_KP_4, olc_NP4); inputmap_set(&mapKeys, SDLK_KP_5, olc_NP5);
    inputmap_set(&mapKeys, SDLK_KP_6, olc_NP6); inputmap_set(&mapKeys, SDLK_KP_7, olc_NP7);
    inputmap_set(&mapKeys, SDLK_KP_8, olc_NP8); inputmap_set(&mapKeys, SDLK_KP_9, olc_NP9);

    inputmap_set(&mapKeys, SDLK_KP_MULTIPLY, olc_NP_MUL); inputmap_set(&mapKeys, SDLK_KP_DIVIDE, olc_NP_DIV);
    inputmap_set(&mapKeys, SDLK_KP_PLUS, olc_NP_ADD); inputmap_set(&mapKeys, SDLK_KP_MINUS, olc_NP_SUB);
    inputmap_set(&mapKeys, SDLK_KP_PERIOD, olc_NP_DECIMAL); inputmap_set(&mapKeys, SDLK_PERIOD, olc_PERIOD);

    return olc_RCODE_OK;
}

int32_t olc_Platform_SetWindowTitle(const char* s)
{
    SDL_SetWindowTitle(olc_Window, s);
    return olc_RCODE_OK;
}

int32_t olc_Platform_StartSystemEventLoop()
{ return olc_RCODE_OK; }


int32_t olc_Platform_HandleSystemEvent()
{
    if(IsMouseCursorVisible())
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
        
    SDL_Event event;
    
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_WINDOWEVENT)
        {
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                olc_PGE_UpdateWindowSize(event.window.data1, event.window.data2);
            }
            else if(event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
            {
                olc_PGE_UpdateKeyFocus(true);
            }
            else if(event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                olc_PGE_UpdateKeyFocus(false);
            }
        }
        else if(event.type == SDL_KEYDOWN)
        {
            olc_PGE_UpdateKeyState(inputmap_get(&mapKeys, event.key.keysym.sym), true);
        }
        else if(event.type == SDL_KEYUP)
        {
            olc_PGE_UpdateKeyState(inputmap_get(&mapKeys, event.key.keysym.sym), false);
        }
        else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:   olc_PGE_UpdateMouseState(0, true);	break;
                case SDL_BUTTON_RIGHT:  olc_PGE_UpdateMouseState(1, true);	break;
                case SDL_BUTTON_MIDDLE: olc_PGE_UpdateMouseState(2, true);	break;
            }
        }
        else if(event.type == SDL_MOUSEBUTTONUP)
        {
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:   olc_PGE_UpdateMouseState(0, false);	break;
                case SDL_BUTTON_RIGHT:  olc_PGE_UpdateMouseState(1, false);	break;
                case SDL_BUTTON_MIDDLE: olc_PGE_UpdateMouseState(2, false);	break;
            }
        }
        else if(event.type == SDL_MOUSEWHEEL)
        {
            if(event.wheel.y < 0)
            {
                olc_PGE_UpdateMouseWheel(120);
            }
            else
            {
                olc_PGE_UpdateMouseWheel(-120);
            }
        }
        else if(event.type == SDL_MOUSEMOTION)
        {
            olc_PGE_UpdateMouse(event.motion.x, event.motion.y);
        }
        else if (event.type == SDL_QUIT)
        {
            olc_PGE_Terminate();
        }
    }
    
    return olc_RCODE_OK;
}

olc_Sprite* olc_Sprite_LoadFromFile(const char* filename)
{
    SDL_Surface* temp = IMG_Load(filename);
    
    if(temp == NULL)
    {
        fprintf(stderr, "%s failed to load.", filename);
        exit(EXIT_FAILURE);
    }

    SDL_Surface* image = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_ABGR8888, 0);

    uint32_t* pixels = (uint32_t*)image->pixels;

    olc_Sprite* sprite = olc_Sprite_Create(image->w, image->h);
    
    for(int y = 0; y < image->h; y++)
    {
        for(int x = 0; x < image->w; x++)
        {
            olc_Pixel p = olc_PixelRAW(pixels[y * image->w + x]);
            
            // obey intent of the alpha channel
            if(p.a == 0)
                p.n = 0;

            olc_Sprite_SetPixel(sprite, x, y, p);
        }
    }

    SDL_FreeSurface(image);
    SDL_FreeSurface(temp);

    return sprite;
}

