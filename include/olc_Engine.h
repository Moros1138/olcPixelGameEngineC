#ifndef OLC_ENGINE_H
#define OLC_ENGINE_H

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#if defined(__linux__) || defined(__MINGW32__)
#include <pthread.h>
#define olc_CrossPlatform_StartThread() pthread_t t; pthread_create(&t, NULL, &EngineThread, NULL)
#define olc_CrossPlatform_JoinThread() pthread_join(t, NULL)
#define olc_CrossPlatform_GetTime(t) clock_gettime(CLOCK_MONOTONIC, &t)
#endif

#if defined(_WIN32) && !defined(__MINGW32__)
#define olc_CrossPlatform_GetTime(t) timespec_get(&t, TIME_UTC)
#endif

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void* allocate_t(size_t);
typedef void* reallocate_t(void*, size_t);
typedef void release_t(void*);

typedef struct {
	allocate_t* allocate;
	reallocate_t* reallocate;
	release_t* release;
} AllocatorCallbacks;

typedef struct {
	size_t allocation;
	size_t size;
	size_t elementSize;
	size_t staticSize;
	AllocatorCallbacks callbacks;
} CVector;

void* vector_alloc_static(size_t elementSize, size_t elements);
#define vector_type_alloc_static(type, elements) vector_alloc_static(sizeof(type), elements)
void* vector_alloc_initial_capacity_callbacks(size_t elementSize, size_t initialSize, AllocatorCallbacks* callbacks);
#define cvactor_type_alloc_capacity(type, initialSize) vector_alloc_initial_capacity(sizeof(type), initialSize)
void* vector_alloc(size_t elementSize);
#define vector_type_alloc(type) vector_alloc(sizeof(type))
void vector_free(void* vect);
void* _vector_push(void** vect);
#define vector_push(vect) _vector_push((void**)&vect)
void vector_pop(void* vect);
size_t vector_size(void* vect);
//Not really needed..
void* vector_front(void* vect);
void* vector_back(void* vect);
size_t vector_element_size(void* vect);
void* vector_at(void* vect, size_t index);
void vector_clear(void* vect);

typedef struct 
{
    size_t key;
    uint8_t val;
} inputdata;

static inputdata mapKeys[256];

void    inputmap_init();
uint8_t inputmap_get(size_t key);
void    inputmap_set(size_t key, uint8_t val);

#define UNUSED(x) (void)(x)
#define olc_MIN(a, b) (a < b) ? a : b
#define olc_MAX(a, b) (a > b) ? a : b

#define olc_nMouseButtons 5
#define olc_nDefaultAlpha 0xFF
#define olc_nDefaultPixel (olc_nDefaultAlpha << 24)

#define olc_SOLID 0xffffffff

enum olc_rcode
{
    olc_RCODE_FAIL = 0,
    olc_RCODE_OK = 1,
    olc_RCODE_NO_FILE = -1
};

// O------------------------------------------------------------------------------O
// | olc_Pixel - Represents a 32-Bit RGBA colour                                  |
// O------------------------------------------------------------------------------O
typedef union Pixel
{
    struct { uint8_t r; uint8_t g; uint8_t b; uint8_t a; };
    uint32_t n;
} olc_Pixel;

enum olc_PixelMode
{
    olc_PIXELMODE_NORMAL,
    olc_PIXELMODE_MASK,
    olc_PIXELMODE_ALPHA,
    olc_PIXELMODE_CUSTOM
};

olc_Pixel olc_PixelDefault();
olc_Pixel olc_PixelRAW(uint32_t p);
olc_Pixel olc_PixelRGB(uint8_t red, uint8_t green, uint8_t blue);
olc_Pixel olc_PixelRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
olc_Pixel olc_PixelF(float red, float green, float blue, float alpha);
bool      olc_PixelCompare(olc_Pixel a, olc_Pixel b);
void olc_PixelColourInit();

// O------------------------------------------------------------------------------O
// | USEFUL CONSTANTS / AND SOME JUST STATIC ONES                                 |
// O------------------------------------------------------------------------------O

// EXTERN!!! Thanks Gusgo
extern olc_Pixel olc_GREY, olc_DARK_GREY, olc_VERY_DARK_GREY,
    olc_RED,     olc_DARK_RED,     olc_VERY_DARK_RED,
    olc_YELLOW,  olc_DARK_YELLOW,  olc_VERY_DARK_YELLOW,
    olc_GREEN,   olc_DARK_GREEN,   olc_VERY_DARK_GREEN,
    olc_CYAN,    olc_DARK_CYAN,    olc_VERY_DARK_CYAN,
    olc_BLUE,    olc_DARK_BLUE,    olc_VERY_DARK_BLUE,
    olc_MAGENTA, olc_DARK_MAGENTA, olc_VERY_DARK_MAGENTA,
    olc_WHITE,   olc_BLACK, olc_BLANK;

enum olc_Key
{
    olc_NONE,
    olc_A, olc_B, olc_C, olc_D, olc_E, olc_F, olc_G, olc_H, olc_I, olc_J,
    olc_K, olc_L, olc_M, olc_N, olc_O, olc_P, olc_Q, olc_R, olc_S, olc_T,
    olc_U, olc_V, olc_W, olc_X, olc_Y, olc_Z,
    olc_K0, olc_K1, olc_K2, olc_K3, olc_K4, olc_K5, olc_K6, olc_K7, olc_K8, olc_K9,
    olc_F1, olc_F2, olc_F3, olc_F4, olc_F5, olc_F6, olc_F7, olc_F8, olc_F9, olc_F10, olc_F11, olc_F12,
    olc_UP, olc_DOWN, olc_LEFT, olc_RIGHT,
    olc_SPACE, olc_TAB, olc_SHIFT, olc_CTRL, olc_INS, olc_DEL, olc_HOME, olc_END, olc_PGUP, olc_PGDN,
    olc_BACK, olc_ESCAPE, olc_RETURN, olc_ENTER, olc_PAUSE, olc_SCROLL,
    olc_NP0, olc_NP1, olc_NP2, olc_NP3, olc_NP4, olc_NP5, olc_NP6, olc_NP7, olc_NP8, olc_NP9,
    olc_NP_MUL, olc_NP_DIV, olc_NP_ADD, olc_NP_SUB, olc_NP_DECIMAL, olc_PERIOD
};

// O------------------------------------------------------------------------------O
// | olc_vX2d - A generic 2D vector type                                          |
// O------------------------------------------------------------------------------O

typedef struct
{
    int x; int y;
} olc_vi2d;

typedef struct
{
    float x; float y;
} olc_vf2d;

typedef struct
{
    double x; double y;
} olc_vd2d;

olc_vi2d olc_VI2D(int x, int y);
olc_vf2d olc_VF2D(float x, float y);
olc_vd2d olc_VD2D(double x, double y);

// O------------------------------------------------------------------------------O
// | olc_HWButton - Represents the state of a hardware button (mouse/key/joy)     |
// O------------------------------------------------------------------------------O
typedef struct HWButton
{
    bool bPressed;	// Set once during the frame the event occurs
    bool bReleased;	// Set once during the frame the event occurs
    bool bHeld;		// Set true for all frames between pressed and released events
} olc_HWButton;

// TODO: RESOURCE PACKS


// O------------------------------------------------------------------------------O
// | olc_Sprite - An image represented by a 2D array of olc_Pixel                 |
// O------------------------------------------------------------------------------O
enum olc_SpriteMode
{
    olc_SPRITEMODE_NORMAL,
    olc_SPRITEMODE_PERIODIC
};

enum olc_SpriteFlip
{
    olc_SPRITEFLIP_NONE = 0,
    olc_SPRITEFLIP_HORIZ = 1,
    olc_SPRITEFLIP_VERT = 2
};

typedef struct Sprite
{
    int32_t width;
    int32_t height;
    uint32_t* pixels;
    uint32_t modeSample;
} olc_Sprite;

olc_Sprite* olc_Sprite_Create(int32_t w, int32_t h);
olc_Sprite* olc_Sprite_Load(const char *sImageFile);
void        olc_Sprite_Destroy(olc_Sprite* sprite);

olc_Sprite* olc_Sprite_LoadFromFile(const char *sImageFile);
olc_Sprite* olc_Sprite_LoadFromPGESprFile(const char *sImageFile);
int32_t   olc_Sprite_SaveToPGESprFile(olc_Sprite* sprite, const char *sImageFile);

void      olc_Sprite_SetSampleMode(olc_Sprite* sprite, uint32_t mode);
olc_Pixel olc_Sprite_GetPixel(olc_Sprite* sprite, int32_t x, int32_t y);
bool      olc_Sprite_SetPixel(olc_Sprite* sprite, int32_t x, int32_t y, olc_Pixel p);
olc_Pixel olc_Sprite_Sample(olc_Sprite* sprite, float x, float y);
olc_Pixel olc_Sprite_SampleBL(olc_Sprite* sprite, float u, float v);
uint32_t* olc_Sprite_GetData(olc_Sprite* sprite);

// O------------------------------------------------------------------------------O
// | olc_Decal - A GPU resident storage of an olc_Sprite                          |
// O------------------------------------------------------------------------------O
typedef struct Decal
{
    int32_t id;
    olc_Sprite* sprite;
    olc_vf2d vUVScale;
} olc_Decal;

olc_Decal* olc_Decal_Create(olc_Sprite* sprite);
void       olc_Decal_Destroy(olc_Decal* decal);
void       olc_Decal_Update(olc_Decal* decal);

// O------------------------------------------------------------------------------O
// | olc_Renderable - Convenience class to keep a sprite and decal together       |
// O------------------------------------------------------------------------------O
typedef struct Renderable
{
    olc_Sprite* sprite;
    olc_Decal*  decal;
} olc_Renderable;

olc_Renderable* olc_Renderable_Create(uint32_t width, uint32_t height);
olc_Renderable* olc_Renderable_Load(const char* sFile);
olc_Sprite*     olc_Renderable_GetSprite(olc_Renderable* renderable);
olc_Decal*      olc_Renderable_GetDecal(olc_Renderable* renderable);


// O------------------------------------------------------------------------------O
// | Auxilliary components internal to engine                                     |
// O------------------------------------------------------------------------------O
typedef struct DecalInstance 
{
    olc_Decal* decal;
    olc_vf2d pos[4];
    olc_vf2d uv[4];
    float w[4];
    olc_Pixel tint[4];
} olc_DecalInstance;

void olc_DecalInstance_Create(olc_DecalInstance* di);

// NOT IMPLEMENTED IN SDL - Here for Reasons
typedef struct DecalTriangleInstance
{
    olc_vf2d points[3];
    olc_vf2d texture[3];
    olc_Pixel colours[3];
    olc_Decal* decal;
} olc_DecalTriangleInstance;

typedef struct LayerDesc
{
    olc_vf2d vOffset;
    olc_vf2d vScale;
    bool bShow;
    bool bUpdate;
    olc_Sprite* pDrawTarget;
    uint32_t nResID;
    olc_DecalInstance* vecDecalInstance;
    olc_Pixel tint;
    void (*funcHook)();
} olc_LayerDesc;

// State Machine!
typedef struct
{
    // User Override Interfaces
    bool (*OnUserCreate)();
    bool (*OnUserUpdate)(float);
    bool (*OnUserDestroy)();

    // Branding
    char* sAppName;
    char sTitle[256];

    // Inner mysterious workings
    olc_Sprite* pDrawTarget;
    int32_t     nPixelMode;
    float		fBlendFactor;
    olc_vi2d    vScreenSize;
    olc_vf2d    vInvScreenSize;
    olc_vi2d    vPixelSize;
    olc_vi2d    vMousePos;
    int32_t     nMouseWheelDelta;
    olc_vi2d    vMousePosCache;
    olc_vi2d    vMouseWindowPos;
    int32_t     nMouseWheelDeltaCache;
    olc_vi2d    vWindowSize;
    olc_vi2d    vViewPos;
    olc_vi2d    vViewSize;
    bool		bFullScreen;
    olc_vf2d	vPixel;
    bool		bHasInputFocus;
    bool		bHasMouseFocus;
    bool		bEnableVSYNC;
    float		fFrameTimer;
    float		fLastElapsed;
    int			nFrameCount;
    olc_Sprite* fontSprite;
    olc_Decal*  fontDecal;
    olc_Sprite* pDefaultDrawTarget;
    olc_LayerDesc* vLayers;
    uint8_t		nTargetLayer;
    uint32_t	nLastFPS;
    olc_Pixel (*funcPixelMode)(int x, int y, olc_Pixel p1, olc_Pixel p2);
    struct timespec tp1, tp2;

    // State of keyboard		
    bool         pKeyNewState[256];
    bool         pKeyOldState[256];
    olc_HWButton pKeyboardState[256];

    // State of mouse
    bool         pMouseNewState[olc_nMouseButtons];
    bool         pMouseOldState[olc_nMouseButtons];
    olc_HWButton pMouseState[olc_nMouseButtons];

    // State of mouse cursor
    bool		bMouseIsVisible;

    // If anything sets this flag to false, the engine
    // "should" shut down gracefully
    bool bActive;
} olc_PixelGameEngine;

// EXTERN!!! Thanks Gusgo
extern olc_PixelGameEngine PGE;
void olc_DefaultState();

int32_t Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
    bool full_screen, bool vsync);
int32_t Start(bool (*create)(), bool (*update)(float), bool (*destroy)());
    
bool DefaultOnUserCreate();
bool DefaultOnUserUpdate(float);
bool DefaultOnUserDestroy();

void* EngineThread();


// Hardware Interfaces


// Returns true if window is currently in focus
bool IsFocused();
// Get the state of a specific keyboard button
olc_HWButton GetKey(uint8_t k);
// Get the state of a specific mouse button
olc_HWButton GetMouse(uint32_t b);
// Get Mouse X coordinate in "xel" space
int32_t GetMouseX();
// Get Mouse Y coordinate in "pixel" space
int32_t GetMouseY();
// Get Mouse Wheel Delta
int32_t GetMouseWheel();
// Get the ouse in window space
olc_vi2d GetWindowMouse();


// Utility


// Returns the width of the screen in "pixels"
int32_t ScreenWidth();
// Returns the height of the screen in "pixels"
int32_t ScreenHeight();
// Returns the width of the currently selected drawing target in "pixels"
int32_t GetDrawTargetWidth();
// Returns the height of the currently selected drawing target in "pixels"
int32_t GetDrawTargetHeight();
// Returns the currently active draw target
olc_Sprite* GetDrawTarget();
// Resize the primary screen sprite
void SetScreenSize(int w, int h);
// Specify which Sprite should be the target of drawing functions, use nullptr
// to specify the primary screen
void SetDrawTarget(olc_Sprite *target);
// Gets the current Frames Per Second
uint32_t GetFPS();
// Gets last update of elapsed time
const float GetElapsedTime();
// Gets Actual Window size
const olc_vi2d GetWindowSize();
// Is system mouse cursor currently visible?
bool IsMouseCursorVisible();


// DRAWING ROUTINES


// Draws a single Pixel
bool Draw(int32_t x, int32_t y, olc_Pixel p);
// Draws a line from (x1,y1) to (x2,y2)
void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, olc_Pixel p, uint32_t pattern);
// Draws a circle located at (x,y) with radius
void DrawCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p, uint8_t mask);
// Fills a circle located at (x,y) with radius
void FillCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p);
// Draws a rectangle at (x,y) to (x+w,y+h)
void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p);
// Fills a rectangle at (x,y) to (x+w,y+h)
void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p);
// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p);
// Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p);
// Draws an entire sprite at well in my defencelocation (x,y)
void DrawSprite(int32_t x, int32_t y, olc_Sprite *sprite, uint32_t scale, uint8_t flip);
// Draws an area of a sprite at location (x,y), where the
// selected area is (ox,oy) to (ox+w,oy+h)
void DrawPartialSprite(int32_t x, int32_t y, olc_Sprite *sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip);


// Decal Quad functions

// Draws a whole decal, with optional scale and tinting
void DrawDecal(olc_vf2d pos, olc_Decal *decal, olc_vf2d scale, const olc_Pixel tint);
// Draws a region of a decal, with optional scale and tinting
void DrawPartialDecal(olc_vf2d pos, olc_Decal* decal, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint);
// NOT IMPLEMENTED IN SDL! - Draws fully user controlled 4 vertices, pos(pixels), uv(pixels), colours
void DrawExplicitDecal(olc_Decal* decal, olc_vf2d *pos, olc_vf2d *uv, const olc_Pixel *col);
// NOT IMPLEMENTED IN SDL! - Draws a decal with 4 arbitrary points, warping the texture to look "correct"
void DrawWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], const olc_Pixel tint);
// NOT IMPLEMENTED IN SDL! - As above, but you can specify a region of a decal source sprite
void DrawPartialWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], olc_vf2d source_pos, olc_vf2d source_size, const olc_Pixel tint);
// Draws a decal rotated to specified angle, wit point of rotation offset
void DrawRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d scale, const olc_Pixel tint);
void DrawPartialRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint);
// Draws a multiline string as a decal, with tiniting and scaling
void DrawStringDecal(olc_vf2d pos, const char* sText, const olc_Pixel col, olc_vf2d scale);
// NOT IMPLEMENTED IN SDL! - Draws a single shaded filled rectangle as a decal
void FillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel col);
// NOT IMPLEMENTED IN SDL! - Draws a corner shaded rectangle as a decal
void GradientFillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel colTL, const olc_Pixel colBL, const olc_Pixel colBR, const olc_Pixel colTR);


// Draws a single line of text
void DrawString(int32_t x, int32_t y, const char* sText, olc_Pixel col, uint32_t scale);
olc_vi2d GetTextSize(const char* s);
// Clears entire draw target to Pixel
void Clear(olc_Pixel p);


// CONFIGURATION ROUTINES


void SetAppName(const char *title);

// Layer targeting functions
void SetLayerDrawTarget(uint8_t layer);
void EnableLayer(uint8_t layer, bool b);
void SetLayerOffset(uint8_t layer, float x, float y);
void SetLayerScale(uint8_t layer, float x, float y);
void SetLayerTint(uint8_t layer, const olc_Pixel tint);
void SetLayerCustomRenderFunction(uint8_t layer, void (*f)());

olc_LayerDesc* GetLayers();
uint32_t CreateLayer();

// Change the pixel mode for different optimisations
// olc_PIXELMODE_NORMAL = No transparency
// olc_PIXELMODE_MASK   = Transparent if alpha is < 255
// olc_PIXELMODE_ALPHA  = Full transparency
void SetPixelMode(int32_t m);
int32_t GetPixelMode();
// Use a custom blend function
void SetCustomPixelMode(olc_Pixel (*f)(int x, int y, olc_Pixel p1, olc_Pixel p2));
// Change the blend factor form between 0.0f to 1.0f;
void SetPixelBlend(float fBlend);
// Offset texels by sub-pixel amount (advanced, do not use)
void SetSubPixelOffset(float ox, float oy);

// show the system mouse cursor (true: visible, false: invisible)
void ShowSystemMouseCursor(bool state);


// "Break In" Functions
void olc_PGE_UpdateMouse(int32_t x, int32_t y);
void olc_PGE_UpdateMouseWheel(int32_t delta);
void olc_PGE_UpdateWindowSize(int32_t x, int32_t y);
void olc_PGE_UpdateViewport();
void olc_PGE_ConstructFontSheet();
void olc_PGE_DestroyFontSheet();
void olc_PGE_CoreUpdate();
void olc_PGE_PrepareEngine();
void olc_PGE_UpdateMouseState(int32_t button, bool state);
void olc_PGE_UpdateKeyState(int32_t key, bool state);
void olc_PGE_UpdateMouseFocus(bool state);
void olc_PGE_UpdateKeyFocus(bool state);
void olc_PGE_Terminate();

// RENDERER

void       olc_Renderer_PrepareDevice();
int32_t    olc_Renderer_CreateDevice(bool bFullScreen, bool bVSYNC);
int32_t    olc_Renderer_DestroyDevice();
void       olc_Renderer_DisplayFrame();
void       olc_Renderer_PrepareDrawing();
void       olc_Renderer_DrawLayerQuad(olc_vf2d offset, olc_vf2d scale, const olc_Pixel tint);
void       olc_Renderer_DrawDecalQuad(olc_DecalInstance* decal);
uint32_t   olc_Renderer_CreateTexture(const uint32_t width, const uint32_t height);
void       olc_Renderer_UpdateTexture(uint32_t id, olc_Sprite* spr);
uint32_t   olc_Renderer_DeleteTexture(const uint32_t id);
void       olc_Renderer_ApplyTexture(uint32_t id);
void       olc_Renderer_UpdateViewport(const olc_vi2d pos, const olc_vi2d size);
void       olc_Renderer_ClearBuffer(olc_Pixel p, bool bDepth);

// PLATFORM

int32_t olc_Platform_ApplicationStartUp();
int32_t olc_Platform_ApplicationCleanUp();
int32_t olc_Platform_ThreadStartUp();
int32_t olc_Platform_ThreadCleanUp();
int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize);
int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen);
int32_t olc_Platform_SetWindowTitle(const char* s);
int32_t olc_Platform_StartSystemEventLoop();
int32_t olc_Platform_HandleSystemEvent();

#endif