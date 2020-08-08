/*
    olcPixelGameEngineC.h

    +-------------------------------------------------------------+
    |           OneLoneCoder Pixel Game Engine v2.06              |
    |  "What do you need? Pixels... Lots of Pixels..." - javidx9  |
    +-------------------------------------------------------------+

    What is this?
    ~~~~~~~~~~~~~
    This is a C port of the olcPixelGameEngine by Javidx9

    #include <shrine-to-the-original-therefore-the-best.h>

    https://github.com/OneLoneCoder/olcPixelGameEngine

    Every feature of the olcPixelGameEngine up until, inclusive, v2.06
    has been fully ported, with the exception of the ResourcePack. I
    have personally tested it to work on Linux and Windows, however it
    has NOT been extensively tested. There are likely to be countless
    bugs and optomizations that will be discovered over time and I look
    forward to squashing each of the bugs and optomizing!
    
    License (OLC-3)
    ~~~~~~~~~~~~~~~

    Copyright 2018 - 2020 OneLoneCoder.com

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:

    1. Redistributions or derivations of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

    2. Redistributions or derivative works in binary form must reproduce the above
    copyright notice. This list of conditions and the following	disclaimer must be
    reproduced in the documentation and/or other materials provided with the distribution.

    3. Neither the name of the copyright holder nor the names of its contributors may
    be used to endorse or promote products derived from this software without specific
    prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS	"AS IS" AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE COPYRIGHT	HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL,	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
    TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
    ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.

    Moros1138's Links
    ~~~~~~~~~~~~~~~~~
    YouTube:    https://www.youtube.com/channel/UCcSyeMr3dvXo-R2XNVNRrKA
    Homepage:   https://www.moros1138.com
    

    OneLoneCoder Links
    ~~~~~~~~~~~~~~~~~~
    YouTube:	https://www.youtube.com/javidx9
                https://www.youtube.com/javidx9extra
    Discord:	https://discord.gg/WhwHUMV
    Twitter:	https://www.twitter.com/javidx9
    Twitch:		https://www.twitch.tv/javidx9
    GitHub:		https://www.github.com/onelonecoder
    Homepage:	https://www.onelonecoder.com
    Patreon:	https://www.patreon.com/javidx9
    Community:  https://community.onelonecoder.com

    Compiling in Linux
    ~~~~~~~~~~~~~~~~~~
    You will need a modern C compiler, so update yours!
    To compile use the command:

    gcc -o YourProgName YourSource.c -lm -lX11 -lGL -lpthread -lpng -std=c11

    On some Linux configurations, the frame rate is locked to the refresh
    rate of the monitor. This engine tries to unlock it but may not be
    able to, in which case try launching your program like this:

    vblank_mode=0 ./YourProgName


    Compiling in Code::Blocks on Windows
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Well I wont judge you, but make sure your Code::Blocks installation
    is really up to date - you may even consider updating your C++ toolchain
    to use MinGW32-W64.

    Guide for installing recent GCC for Windows:
    https://www.msys2.org/
    Guide for configuring code::blocks:
    https://solarianprogrammer.com/2019/11/05/install-gcc-windows/
    https://solarianprogrammer.com/2019/11/16/install-codeblocks-gcc-windows-build-c-cpp-fortran-programs/

    Add these libraries to "Linker Options":
    user32 gdi32 opengl32 gdiplus Shlwapi

    Set these compiler options: -std=c11

    Ports
    ~~~~~
    olc::PixelGameEngine has been ported and tested with varying degrees of
    success to: WinXP, Win7, Win8, Win10, Various Linux, Raspberry Pi,
    Chromebook, Playstation Portable (PSP) and Nintendo Switch. If you are
    interested in the details of these ports, come and visit the Discord!

    Official PixelGameEngine Shoutouts!
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Javid has expressed his thanks to the following people whose
    contributions has made the Offical PixelGameEngine what it has
    become today! I too, wish to acknowledge them because without
    their contributions to the original, my C port would not have
    been possible.

    Eremiell, slavka, gurkanctn,  Phantim, IProgramInCPP, JackOJC,
    KrossX,   Huhlig,   Dragoneye,    Appa,   JustinRichardsMusic,
    SliceNDice,  dandistine, Ralakus,  Gorbit99, raoul, joshinils,
    benedani, Moros1138, SaladinAkara & MagetzUb for advice, ideas
    and testing. 

    Moros1138's Acknowledgements.
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    I know it sounds like a copout,  but I too want to thank each
    and  every one  of  those  who  contributed to  the original.
    olcPixelGameEngine  is  an  amazing  tool that  has rekindled
    my desire to program and since I've started I've learned more
    and more each day.

    I want to thank Javid, for the community that  he  has  built.
    It's an inspiration to anybody with a brain. Of course, that's
    just my opinion.

    I also want  to  thank Gusgo and TarriestPython  for  their
    encouragement and help debugging and testing.

    I want to thank MaeGetzUb for his C vector implementation which
    made my life **SO** much easier.

    Author
    ~~~~~~
    Moros Smith, aka Moros1138
    
    olcPixelGameEngine Author
    ~~~~~~
    David Barr, aka javidx9, ©OneLoneCoder 2018, 2019, 2020
*/

//////////////////////////////////////////////////////////////////////////////////////////


// O------------------------------------------------------------------------------O
// | Example "Hello World" Program (main.c)                                     |
// O------------------------------------------------------------------------------O
/*
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngineC.h"

bool OnUserCreate()
{ return true; }

bool OnUserUpdate(float fElapsedTime)
{
    for(int y = 0; y < PGE_ScreenHeight(); y++)
        for(int x = 0; x < PGE_ScreenWidth(); x++)
            PGE_Draw(rand() % PGE_ScreenWidth(), rand() % PGE_ScreenHeight(), olc_PixelRGB(rand() % 255, rand() % 255, rand() % 255));
            
    return !PGE_GetKey(olc_ESCAPE).bPressed;
}

bool OnUserDestroy()
{ return true; }

int main(int argc, char* argv[])
{
    PGE_SetAppName("Example");
    if(PGE_Construct(320, 240, 3, 3, false, false))
        PGE_Start(&OnUserCreate, &OnUserUpdate, &OnUserDestroy);

    return 0;
}
*/

#ifndef OLC_PGE_DEF
#define OLC_PGE_DEF

#if !defined(OLC_GFX_OPENGL33) && !defined(OLC_GFX_DIRECTX10)
#define OLC_GFX_OPENGL10
#endif

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine PLATFORM SPECIFIC DECLARATIONS                            |
// O------------------------------------------------------------------------------O

#if defined(_WIN32) // WINDOWS

#define _CRT_SECURE_NO_WARNINGS

#if !defined(NOMINMAX)
#define NOMINMAX
#endif

// Include WinAPI
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>


// START MAKING GdiPlus work in C
#ifndef GDIPVER
#define GDIPVER 0x0100

typedef struct GdiplusStartupInput {
    UINT32 GdiplusVersion;
    void* DebugEventCallback;
    BOOL SuppressBackgroundThread;
    BOOL SuppressExternalCodecs;
} GdiplusStartupInput;

typedef int32_t(__stdcall* NotificationHookProc)(uint32_t** token);
typedef void(__stdcall* NotificationUnhookProc)(uint32_t* token);

typedef struct GdiplusStartupOutput {
    NotificationHookProc NotificationHook;
    NotificationUnhookProc NotificationUnhook;
} GdiplusStartupOutput;

int32_t __stdcall GdipLoadImageFromFile(const wchar_t*, void**);
int32_t __stdcall GdipGetImageDimension(void*, float*, float*);
int32_t __stdcall GdipBitmapGetPixel(void*, int32_t, int32_t, uint32_t*);
int32_t __stdcall GdipDisposeImage(void*);

int32_t __stdcall GdiplusStartup(uint32_t**, const GdiplusStartupInput*, GdiplusStartupOutput*);
void __stdcall GdiplusShutdown(uint32_t*);
int32_t __stdcall GdiplusNotificationHook(uint32_t**);
void __stdcall GdiplusNotificationUnhook(uint32_t*);
#endif

uint32_t* GDI_TOKEN;
GdiplusStartupInput GDI_INPUT;

// END MAKING GdiPlus work in C

#include <Shlwapi.h>

#if defined(OLC_GFX_OPENGL10) // OPENGL ON WINDOWS
#include <GL/gl.h>
typedef BOOL(WINAPI wglSwapInterval_t) (int interval);
static wglSwapInterval_t* wglSwapInterval = NULL;
typedef HDC glDeviceContext_t;
typedef HGLRC glRenderContext_t;
#endif // OPENGL ON WINDOWS

HCURSOR olc_ArrowCursor;
HCURSOR olc_InvisibleCursor;

HWND olc_hWnd = NULL;
wchar_t wsAppName;

#endif // WINDOWS


#if defined(__linux__) || defined(__FreeBSD__) // LINUX

#if defined(OLC_GFX_OPENGL10) // OPENGL ON LINUX
#include <GL/gl.h>
#include <GL/glx.h>

typedef int(glSwapInterval_t)(Display* dpy, GLXDrawable drawable, int interval);
static glSwapInterval_t* glSwapIntervalEXT;
typedef GLXContext glDeviceContext_t;
typedef GLXContext glRenderContext_t;
#endif // OPENGL ON LINUX

#include <X11/cursorfont.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <png.h>

Display* olc_Display;
Window                  olc_WindowRoot;
Window                  olc_Window;
XVisualInfo* olc_VisualInfo;
Colormap                olc_ColourMap;
XSetWindowAttributes    olc_SetWindowAttribs;

Cursor                  olc_ArrowCursor;
Cursor                  olc_InvisibleCursor;
Pixmap                  olc_BitmapNoData;
XColor                  olc_BlackColor;

#endif // LINUX

// O------------------------------------------------------------------------------O
// | COMPILER CONFIGURATION ODDITIES                                              |
// O------------------------------------------------------------------------------O
// Linux and MinGW Specific Macros
#if defined(__linux__) || defined(__MINGW32__)
#include <pthread.h>
#define olc_CrossPlatform_GetTime(t) clock_gettime(CLOCK_MONOTONIC, &t)
#define olc_CrossPlatform_Thread void*
#define olc_CrossPlatform_Thread_Return NULL
#define olc_CrossPlatform_Thread_Start() pthread_t olc_Thread; pthread_create(&olc_Thread, NULL, PGE_EngineThread, NULL)
#define olc_CrossPlatform_Thread_Join() pthread_join(olc_Thread, NULL)
#endif

// Windows MSVC Specific Macros
#if defined(_WIN32) && !defined(__MINGW32__)
#define olc_CrossPlatform_GetTime(t) timespec_get(&t, TIME_UTC)
#define olc_CrossPlatform_Thread DWORD WINAPI
#define olc_CrossPlatform_Thread_Return 0
#define olc_CrossPlatform_Thread_Start() HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PGE_EngineThread, NULL, 0, NULL)
#define olc_CrossPlatform_Thread_Join() WaitForSingleObject(hThread, INFINITE); CloseHandle(hThread)
#endif

// O------------------------------------------------------------------------------O
// | STANDARD INCLUDES                                                            |
// O------------------------------------------------------------------------------O
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#if defined(UNICODE) || defined(_UNICODE)
#define olcT(s) L##s
#else
#define olcT(s) s
#endif

#define UNUSED(x) (void)(x)

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine C VECTOR ( Thanks for the inspiration MaGetzUb )          |
// O------------------------------------------------------------------------------O
typedef struct
{
    size_t capacity;
    size_t elementSize;
    size_t size;
    void* begin;
    void* end;
} cvector;

#define vector_header(v) size_t stubSize = sizeof(cvector); cvector* cvect = (cvector*)((uint8_t*)v - stubSize)
#define vector_init(t) (t*)_vector_init(sizeof(t))
#define vector_destroy(v) _vector_destroy((void**)&v)
#define vector_reserve(v, c) _vector_reserve((void**)&v, c)
#define vector_push(v, i) _vector_push((void**)&v, i)

void*    _vector_init(size_t elementSize);
void     _vector_destroy(void** vect);
cvector* _vector_reserve(void** vect, size_t capacity);
void     vector_clear(void* vect);

void*    _vector_push(void** vect, void* item);

size_t   vector_capacity(void* vect);
size_t   vector_size(void* vect);

void*    vector_begin(void* vect);
void*    vector_end(void* vect);

bool     vector_empty(void* vect);

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INPUT MAPPING                                             |
// O------------------------------------------------------------------------------O
typedef struct
{
    size_t key;
    uint8_t val;
} inputdata;

void    inputmap_init();
uint8_t inputmap_get(size_t key);
void    inputmap_set(size_t key, uint8_t val);

#define olc_MIN(a, b) (a < b) ? a : b
#define olc_MAX(a, b) (a > b) ? a : b

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INTERFACE DECLARATION                                     |
// O------------------------------------------------------------------------------O

// Pixel Game Engine Advanced Configuration
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
olc_Pixel olc_GREY, olc_DARK_GREY, olc_VERY_DARK_GREY,
olc_RED, olc_DARK_RED, olc_VERY_DARK_RED,
olc_YELLOW, olc_DARK_YELLOW, olc_VERY_DARK_YELLOW,
olc_GREEN, olc_DARK_GREEN, olc_VERY_DARK_GREEN,
olc_CYAN, olc_DARK_CYAN, olc_VERY_DARK_CYAN,
olc_BLUE, olc_DARK_BLUE, olc_VERY_DARK_BLUE,
olc_MAGENTA, olc_DARK_MAGENTA, olc_VERY_DARK_MAGENTA,
olc_WHITE, olc_BLACK, olc_BLANK;

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
    olc_SPRITE_SAMPLEMODE_NORMAL,
    olc_SPRITE_SAMPLEMODE_PERIODIC
};

enum olc_SpriteFlip
{
    olc_SPRITE_FLIP_NONE = 0,
    olc_SPRITE_FLIP_HORIZ = 1,
    olc_SPRITE_FLIP_VERT = 2
};

typedef struct Sprite
{
    int32_t width;
    int32_t height;
    uint32_t* pixels;
    uint32_t modeSample;
} olc_Sprite;

olc_Sprite* olc_Sprite_Create(int32_t w, int32_t h);
olc_Sprite* olc_Sprite_Load(const char* sImageFile);
void        olc_Sprite_Destroy(olc_Sprite* sprite);

olc_Sprite* olc_Sprite_LoadFromFile(const char* sImageFile);
olc_Sprite* olc_Sprite_LoadFromPGESprFile(const char* sImageFile);
int32_t   olc_Sprite_SaveToPGESprFile(olc_Sprite* sprite, const char* sImageFile);

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
    olc_Decal* decal;
} olc_Renderable;

olc_Renderable* olc_Renderable_Create(uint32_t width, uint32_t height);
olc_Renderable* olc_Renderable_Load(const char* sFile);
olc_Sprite* olc_Renderable_GetSprite(olc_Renderable* renderable);
olc_Decal* olc_Renderable_GetDecal(olc_Renderable* renderable);

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

// O------------------------------------------------------------------------------O
// | Renderer Forward Declarations                                                |
// O------------------------------------------------------------------------------O
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

// O------------------------------------------------------------------------------O
// | Platform Forward Declarations                                                |
// O------------------------------------------------------------------------------O
int32_t olc_Platform_ApplicationStartUp();
int32_t olc_Platform_ApplicationCleanUp();
int32_t olc_Platform_ThreadStartUp();
int32_t olc_Platform_ThreadCleanUp();
int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize);
int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen);
int32_t olc_Platform_SetWindowTitle(const char* s);
int32_t olc_Platform_StartSystemEventLoop();
int32_t olc_Platform_HandleSystemEvent();

// Input Mappings
static inputdata mapKeys[256];

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - The main state data structure                         |
// O------------------------------------------------------------------------------O
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
    olc_Decal* fontDecal;
    olc_Sprite* pDefaultDrawTarget;
    olc_LayerDesc* vLayers;
    uint8_t		nTargetLayer;
    uint32_t	nLastFPS;
    olc_Pixel(*funcPixelMode)(int x, int y, olc_Pixel p1, olc_Pixel p2);
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

olc_PixelGameEngine PGE;

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Initialization Routines                               |
// O------------------------------------------------------------------------------O
void olc_PGE_DefaultState();

int32_t PGE_Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
    bool full_screen, bool vsync);
int32_t PGE_Start(bool (*create)(), bool (*update)(float), bool (*destroy)());

bool PGE_DefaultOnUserCreate();
bool PGE_DefaultOnUserUpdate(float);
bool PGE_DefaultOnUserDestroy();

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Hardware Interfaces                                   |
// O------------------------------------------------------------------------------O

// Returns true if window is currently in focus
bool PGE_IsFocused();
// Get the state of a specific keyboard button
olc_HWButton PGE_GetKey(uint8_t k);
// Get the state of a specific mouse button
olc_HWButton PGE_GetMouse(uint32_t b);
// Get Mouse X coordinate in "xel" space
int32_t PGE_GetMouseX();
// Get Mouse Y coordinate in "pixel" space
int32_t PGE_GetMouseY();
// Get Mouse Wheel Delta
int32_t PGE_GetMouseWheel();
// Get the ouse in window space
olc_vi2d PGE_GetWindowMouse();

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Utility                                               |
// O------------------------------------------------------------------------------O

// Returns the width of the screen in "pixels"
int32_t PGE_ScreenWidth();
// Returns the height of the screen in "pixels"
int32_t PGE_ScreenHeight();
// Returns the width of the currently selected drawing target in "pixels"
int32_t PGE_GetDrawTargetWidth();
// Returns the height of the currently selected drawing target in "pixels"
int32_t PGE_GetDrawTargetHeight();
// Returns the currently active draw target
olc_Sprite* PGE_GetDrawTarget();
// Resize the primary screen sprite
void PGE_SetScreenSize(int w, int h);
// Specify which Sprite should be the target of drawing functions, use NULL
// to specify the primary screen
void PGE_SetDrawTarget(olc_Sprite* target);
// Gets the current Frames Per Second
uint32_t PGE_GetFPS();
// Gets last update of elapsed time
const float PGE_GetElapsedTime();
// Gets Actual Window size
const olc_vi2d PGE_GetWindowSize();
// Is system mouse cursor currently visible?
bool PGE_IsMouseCursorVisible();
// show the system mouse cursor (true: visible, false: invisible)
void PGE_ShowSystemMouseCursor(bool state);

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Configuration Routines                                |
// O------------------------------------------------------------------------------O
void PGE_SetAppName(const char* title);

// Layer targeting functions
void PGE_SetLayerTarget(uint8_t layer);
void PGE_EnableLayer(uint8_t layer, bool b);
void PGE_SetLayerOffset(uint8_t layer, float x, float y);
void PGE_SetLayerScale(uint8_t layer, float x, float y);
void PGE_SetLayerTint(uint8_t layer, const olc_Pixel tint);
void PGE_SetLayerCustomRenderFunction(uint8_t layer, void (*f)());

olc_LayerDesc* PGE_GetLayers();
uint32_t PGE_CreateLayer();

// Change the pixel mode for different optimisations
// olc_PIXELMODE_NORMAL = No transparency
// olc_PIXELMODE_MASK   = Transparent if alpha is < 255
// olc_PIXELMODE_ALPHA  = Full transparency
void PGE_SetPixelMode(int32_t m);
int32_t PGE_GetPixelMode();
// Use a custom blend function
void PGE_SetCustomPixelMode(olc_Pixel(*f)(int x, int y, olc_Pixel p1, olc_Pixel p2));
// Change the blend factor form between 0.0f to 1.0f;
void PGE_SetPixelBlend(float fBlend);
// Offset texels by sub-pixel amount (advanced, do not use)
void PGE_SetSubPixelOffset(float ox, float oy);

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Drawing Routines                                      |
// O------------------------------------------------------------------------------O

// Draws a single Pixel
bool PGE_Draw(int32_t x, int32_t y, olc_Pixel p);
// Draws a line from (x1,y1) to (x2,y2)
void PGE_DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, olc_Pixel p, uint32_t pattern);
// Draws a circle located at (x,y) with radius
void PGE_DrawCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p, uint8_t mask);
// Fills a circle located at (x,y) with radius
void PGE_FillCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p);
// Draws a rectangle at (x,y) to (x+w,y+h)
void PGE_DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p);
// Fills a rectangle at (x,y) to (x+w,y+h)
void PGE_FillRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p);
// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void PGE_DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p);
// Flat fills a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void PGE_FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p);
// Draws an entire sprite at well in my defencelocation (x,y)
void PGE_DrawSprite(int32_t x, int32_t y, olc_Sprite* sprite, uint32_t scale, uint8_t flip);
// Draws an area of a sprite at location (x,y), where the
// selected area is (ox,oy) to (ox+w,oy+h)
void PGE_DrawPartialSprite(int32_t x, int32_t y, olc_Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip);

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Decal Quad Functions                                  |
// O------------------------------------------------------------------------------O

// Draws a whole decal, with optional scale and tinting
void PGE_DrawDecal(olc_vf2d pos, olc_Decal* decal, olc_vf2d scale, const olc_Pixel tint);
// Draws a region of a decal, with optional scale and tinting
void PGE_DrawPartialDecal(olc_vf2d pos, olc_Decal* decal, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint);
// Draws fully user controlled 4 vertices, pos(pixels), uv(pixels), colours
void PGE_DrawExplicitDecal(olc_Decal* decal, olc_vf2d* pos, olc_vf2d* uv, const olc_Pixel* col);
// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
void PGE_DrawWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], const olc_Pixel tint);
// As above, but you can specify a region of a decal source sprite
void PGE_DrawPartialWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], olc_vf2d source_pos, olc_vf2d source_size, const olc_Pixel tint);
// Draws a decal rotated to specified angle, wit point of rotation offset
void PGE_DrawRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d scale, const olc_Pixel tint);
void PGE_DrawPartialRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint);
// Draws a multiline string as a decal, with tiniting and scaling
void PGE_DrawStringDecal(olc_vf2d pos, const char* sText, const olc_Pixel col, olc_vf2d scale);
// Draws a single shaded filled rectangle as a decal
void PGE_FillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel col);
// Draws a corner shaded rectangle as a decal
void PGE_GradientFillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel colTL, const olc_Pixel colBL, const olc_Pixel colBR, const olc_Pixel colTR);


// Draws a single line of text
void PGE_DrawString(int32_t x, int32_t y, const char* sText, olc_Pixel col, uint32_t scale);
olc_vi2d PGE_GetTextSize(const char* s);
// Clears entire draw target to Pixel
void PGE_Clear(olc_Pixel p);
void PGE_ClearBuffer(olc_Pixel p, bool depth);

// The main engine thread
olc_CrossPlatform_Thread PGE_EngineThread();

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - "Break In" Functions                                  |
// O------------------------------------------------------------------------------O
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

// NOTE: Items Here are to be deprecated, I have left them in for now
// in case you are using them, but they will be removed.
// olc::vf2d	vSubPixelOffset = { 0.0f, 0.0f };

#endif // OLC_PGE_DEF


// O------------------------------------------------------------------------------O
// | START OF OLC_PGE_APPLICATION                                                 |
// O------------------------------------------------------------------------------O
#ifdef OLC_PGE_APPLICATION
#undef OLC_PGE_APPLICATION

// local utility functions
static void drawline(int sx, int ex, int ny, olc_Pixel p) { for (int i = sx; i <= ex; i++) PGE_Draw(i, ny, p); }
static void swap_int(int* a, int* b) { int temp = *a; *a = *b; *b = temp; }
static bool rol(uint32_t* pattern) { *pattern = (*pattern << 1) | (*pattern >> 31); return (*pattern & 1) ? true : false; }

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine C VECTOR ( Thanks for the inspiration MaGetzUb )          |
// O------------------------------------------------------------------------------O
void* _vector_init(size_t elementSize)
{
    cvector* cvect = calloc(1, sizeof(cvector) + elementSize);
    
    cvect->capacity    = 1;
    cvect->elementSize = elementSize;
    cvect->size        = 0;
    cvect->begin       = (uint8_t*)cvect + sizeof(cvector);
    cvect->end         = (uint8_t*)cvect + sizeof(cvector);

    return cvect->begin;
}

void _vector_destroy(void** vect)
{
    vector_header(*vect);
    free(cvect);
    cvect = NULL;
    *vect = NULL;
}

cvector* _vector_reserve(void** vect, size_t capacity)
{
    vector_header(*vect);

    void *allocation = realloc(cvect, (stubSize + (cvect->elementSize * capacity)));
    if(allocation)
    {
        // update? allocation
        cvect = (cvector*)allocation;
        
        // update capacity
        cvect->capacity = capacity;
        
        // ensure valid iterator pointers
        cvect->begin = (uint8_t*)cvect + stubSize;
        cvect->end = (uint8_t*)cvect + stubSize + (cvect->elementSize * cvect->size);
        *vect = cvect->begin;

        // zero out all new memory
        size_t newAllocationSize = (cvect->capacity - cvect->size) * cvect->elementSize;
        memset(cvect->end, 0, newAllocationSize);
    }
    return cvect;
}

void* _vector_push(void** vect, void* item)
{
    vector_header(*vect);

    if(cvect->size + 1 > cvect->capacity)
        cvect = _vector_reserve(vect, cvect->capacity * 2);
    
    // insert the item's data
    if(item != NULL)
        memcpy(cvect->end, item, cvect->elementSize);
    else
        memset(cvect->end, 0, cvect->elementSize);

    cvect->size++;
    cvect->end = (uint8_t*)cvect->begin + (cvect->elementSize * cvect->size);

    return ((uint8_t*)cvect->end - cvect->elementSize);
}

void vector_clear(void* vect)
{
    vector_header(vect);
    memset(cvect->begin, 0, cvect->capacity * cvect->elementSize);
    cvect->size = 0;
    cvect->end = cvect->begin;
}

size_t vector_capacity(void* vect)
{
    vector_header(vect);
    return cvect->capacity;
}

size_t vector_size(void* vect)
{
    vector_header(vect);
    return cvect->size;
}

void* vector_begin(void* vect)
{
    vector_header(vect);
    return cvect->begin;
}

void* vector_end(void* vect)
{
    vector_header(vect);
    return cvect->end;
}

bool vector_empty(void* vect)
{
    vector_header(vect);
    return ((uint8_t*)cvect->begin == (uint8_t*)cvect->end) ? true : false;
}

// O------------------------------------------------------------------------------O
// | olcPixelGameEngine INPUT MAPPING                                             |
// O------------------------------------------------------------------------------O
void inputmap_init()
{
    for (int i = 0; i < 256; i++)
    {
        mapKeys[i].key = -1;
        mapKeys[i].val = 0;
    }
}

uint8_t inputmap_get(size_t key)
{
    for (int i = 0; i < 256; i++)
    {
        if (mapKeys[i].key == key)
            return mapKeys[i].val;
    }

    return 0;
}

void inputmap_set(size_t key, uint8_t val)
{
    for (int i = 0; i < 256; i++)
    {
        if (mapKeys[i].key == key)
        {
            mapKeys[i].val = val;
            return;
        }
    }

    // if we made it here, we have to create a new inputdata
    for (int i = 0; i < 256; i++)
    {
        if (mapKeys[i].key == -1 && mapKeys[i].val == 0)
        {
            mapKeys[i].key = key;
            mapKeys[i].val = val;
            return;
        }
    }

}

// O------------------------------------------------------------------------------O
// | olc::Pixel IMPLEMENTATION                                                    |
// O------------------------------------------------------------------------------O
olc_Pixel olc_PixelDefault()
{
    return olc_PixelRAW(olc_nDefaultPixel);
}

olc_Pixel olc_PixelRAW(uint32_t p)
{
    olc_Pixel a; a.n = p; return a;
}

olc_Pixel olc_PixelRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    olc_Pixel a; a.r = red; a.g = green; a.b = blue; a.a = 255; return a;
}

olc_Pixel olc_PixelRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    olc_Pixel a; a.r = red; a.g = green; a.b = blue; a.a = alpha; return a;
}

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
{
    return (a.n == b.n) ? true : false;
}

void olc_PixelColourInit()
{
    olc_GREY = olc_PixelRGB(192, 192, 192);  olc_DARK_GREY = olc_PixelRGB(128, 128, 128);  olc_VERY_DARK_GREY = olc_PixelRGB(64, 64, 64);
    olc_RED = olc_PixelRGB(255, 0, 0);       olc_DARK_RED = olc_PixelRGB(128, 0, 0);       olc_VERY_DARK_RED = olc_PixelRGB(64, 0, 0);
    olc_YELLOW = olc_PixelRGB(255, 255, 0);  olc_DARK_YELLOW = olc_PixelRGB(128, 128, 0);  olc_VERY_DARK_YELLOW = olc_PixelRGB(64, 64, 0);
    olc_GREEN = olc_PixelRGB(0, 255, 0);     olc_DARK_GREEN = olc_PixelRGB(0, 128, 0);     olc_VERY_DARK_GREEN = olc_PixelRGB(0, 64, 0);
    olc_CYAN = olc_PixelRGB(0, 255, 255);    olc_DARK_CYAN = olc_PixelRGB(0, 128, 128);    olc_VERY_DARK_CYAN = olc_PixelRGB(0, 64, 64);
    olc_BLUE = olc_PixelRGB(0, 0, 255);      olc_DARK_BLUE = olc_PixelRGB(0, 0, 128);      olc_VERY_DARK_BLUE = olc_PixelRGB(0, 0, 64);
    olc_MAGENTA = olc_PixelRGB(255, 0, 255); olc_DARK_MAGENTA = olc_PixelRGB(128, 0, 128); olc_VERY_DARK_MAGENTA = olc_PixelRGB(64, 0, 64);
    olc_WHITE = olc_PixelRGB(255, 255, 255); olc_BLACK = olc_PixelRGB(0, 0, 0);            olc_BLANK = olc_PixelRGBA(0, 0, 0, 0);
}

// O------------------------------------------------------------------------------O
// | olc_vX2d - constructor utilities                                             |
// O------------------------------------------------------------------------------O
olc_vi2d olc_VI2D(int x, int y) { olc_vi2d ret; ret.x = x; ret.y = y; return ret; }
olc_vf2d olc_VF2D(float x, float y) { olc_vf2d ret; ret.x = x; ret.y = y; return ret; }
olc_vd2d olc_VD2D(double x, double y) { olc_vd2d ret; ret.x = x; ret.y = y; return ret; }

// O------------------------------------------------------------------------------O
// | olc_Sprite - An image represented by a 2D array of olc_Pixel               |
// O------------------------------------------------------------------------------O

olc_Sprite* olc_Sprite_Create(int32_t w, int32_t h)
{
    olc_Sprite* sprite;

    sprite = (olc_Sprite*)malloc(sizeof(olc_Sprite));
    if (sprite == NULL)
    {
        fprintf(stderr, "Failed to allcoate ram for sprite.\n");
        exit(EXIT_FAILURE);
    }

    sprite->width = w;
    sprite->height = h;
    sprite->pixels = (uint32_t*)calloc(sizeof(uint32_t), w * h);
    sprite->modeSample = olc_SPRITE_SAMPLEMODE_NORMAL; // Good Catch! Thanks Tarry

    if (sprite->pixels == NULL)
    {
        fprintf(stderr, "Failed to allocate ram for sprite pixel data.\n"); // Gusgo Spellcheck PRO+, coming to Google soon!
        exit(EXIT_FAILURE);
    }

    return sprite;
}

olc_Sprite* olc_Sprite_Load(const char* sImageFile)
{
    return olc_Sprite_LoadFromFile(sImageFile);
}

void olc_Sprite_Destroy(olc_Sprite* sprite)
{
    if(sprite == NULL) return;

    free(sprite->pixels);
    sprite->pixels = NULL;

    free(sprite);
    sprite = NULL;
}

olc_Sprite* olc_Sprite_LoadFromPGESprFile(const char* sImageFile)
{
    int32_t width;
    int32_t height;
    uint32_t* pixels;

    FILE* fp = fopen(sImageFile, "r");
    if (fp)
    {
        if(fread(&width, sizeof(int32_t), 1, fp) != sizeof(int32_t))
        {
            fprintf(stderr, "ERROR: PGESprite Loader failed to get width from header.\n");
            exit(EXIT_FAILURE);
        }
        
        if(fread(&height, sizeof(int32_t), 1, fp) != sizeof(int32_t))
        {
            fprintf(stderr, "ERROR: PGESprite Loader failed to get height from header.\n");
            exit(EXIT_FAILURE);
        }

        pixels = (uint32_t*)malloc(width * height * sizeof(uint32_t));
        if (pixels == NULL)
        {
            fprintf(stderr, "ERROR: PGESprite Loader failed to allocate memory for pixels.\n");
            exit(EXIT_FAILURE);
        }

        if(fread(pixels, sizeof(uint32_t), width * height, fp) != (width * height))
        {
            fprintf(stderr, "ERROR: PGESprite Loader failed to load pixel data.\n");
            exit(EXIT_FAILURE);
        }

        olc_Sprite* sprite = olc_Sprite_Create(width, height);

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                olc_Pixel p = olc_PixelRAW(pixels[y * width + x]);

                if (p.a == 0)
                    p = olc_BLANK;

                olc_Sprite_SetPixel(sprite, x, y, p);
            }
        }

        fclose(fp);
        free(pixels);

        return sprite;
    }

    fprintf(stderr, "Error loading PGESprite: %s\n", sImageFile);
    exit(EXIT_FAILURE);

    return NULL;
}

int32_t olc_Sprite_SaveToPGESprFile(olc_Sprite* sprite, const char* sImageFile)
{
    if (sprite == NULL)
        return olc_RCODE_FAIL;

    uint32_t* pixels = olc_Sprite_GetData(sprite);

    if (pixels == NULL) return olc_RCODE_FAIL;

    FILE* fp = fopen(sImageFile, "w");
    if (fp)
    {
        fwrite(&sprite->width, sizeof(uint32_t), 1, fp);
        fwrite(&sprite->height, sizeof(uint32_t), 1, fp);
        fwrite(pixels, sizeof(uint32_t), sprite->width * sprite->height, fp);

        fclose(fp);
        return olc_RCODE_OK;
    }

    fclose(fp);

    return olc_RCODE_FAIL;
}

void olc_Sprite_SetSampleMode(olc_Sprite* sprite, uint32_t mode)
{
    sprite->modeSample = mode;
}

olc_Pixel olc_Sprite_GetPixel(olc_Sprite* sprite, int32_t x, int32_t y)
{
    if (x >= 0 && y >= 0 && x < sprite->width && y < sprite->height)
    {
        return olc_PixelRAW(sprite->pixels[y * sprite->width + x]);
    }

    return olc_PixelDefault();
}

bool olc_Sprite_SetPixel(olc_Sprite* sprite, int32_t x, int32_t y, olc_Pixel p)
{
    if (x >= 0 && y >= 0 && x < sprite->width && y < sprite->height)
    {
        sprite->pixels[y * sprite->width + x] = p.n;
        return true;
    }

    return false;
}

olc_Pixel olc_Sprite_Sample(olc_Sprite* sprite, float x, float y)
{
    int32_t a, b;

    a = (int32_t)((x * (float)sprite->width));
    b = sprite->width - 1;
    int32_t sx = (a < b) ? a : b;

    a = (int32_t)((y * (float)sprite->height));
    b = sprite->height - 1;
    int32_t sy = (a < b) ? a : b;

    return olc_Sprite_GetPixel(sprite, sx, sy);
}

olc_Pixel olc_Sprite_SampleBL(olc_Sprite* sprite, float u, float v)
{
    u = u * sprite->width - 0.5f;
    v = v * sprite->height - 0.5f;

    int x = (int)floor(u); // cast to int rounds toward zero, not downward
    int y = (int)floor(v); // Thanks @joshinils
    float u_ratio = u - x;
    float v_ratio = v - y;
    float u_opposite = 1 - u_ratio;
    float v_opposite = 1 - v_ratio;

    olc_Pixel p1 = olc_Sprite_GetPixel(sprite, olc_MAX(x, 0), olc_MAX(y, 0));
    olc_Pixel p2 = olc_Sprite_GetPixel(sprite, olc_MIN(x + 1, (int)sprite->width - 1), olc_MAX(y, 0));
    olc_Pixel p3 = olc_Sprite_GetPixel(sprite, olc_MAX(x, 0), olc_MIN(y + 1, (int)sprite->height - 1));
    olc_Pixel p4 = olc_Sprite_GetPixel(sprite, olc_MIN(x + 1, (int)sprite->width - 1), olc_MIN(y + 1, (int)sprite->height - 1));

    return olc_PixelRGB(
        (uint8_t)((p1.r * u_opposite + p2.r * u_ratio) * v_opposite + (p3.r * u_opposite + p4.r * u_ratio) * v_ratio),
        (uint8_t)((p1.g * u_opposite + p2.g * u_ratio) * v_opposite + (p3.g * u_opposite + p4.g * u_ratio) * v_ratio),
        (uint8_t)((p1.b * u_opposite + p2.b * u_ratio) * v_opposite + (p3.b * u_opposite + p4.b * u_ratio) * v_ratio));
}

uint32_t* olc_Sprite_GetData(olc_Sprite* sprite)
{
    return sprite->pixels;
}

// O------------------------------------------------------------------------------O
// | olc_Decal - A GPU resident storage of an olc_Sprite                        |
// O------------------------------------------------------------------------------O
olc_Decal* olc_Decal_Create(olc_Sprite* sprite)
{
    if (sprite == NULL) return NULL;

    olc_Decal* decal = (olc_Decal*)malloc(sizeof(olc_Decal));
    if (decal == NULL)
    {
        fprintf(stderr, "Error creating decal.\n");
        exit(EXIT_FAILURE);
    }

    decal->id = -1;
    decal->sprite = sprite;
    decal->vUVScale = olc_VF2D(1.0f, 1.0f);
    decal->id = olc_Renderer_CreateTexture(decal->sprite->width, decal->sprite->height);
    olc_Decal_Update(decal);

    return decal;
}

void olc_Decal_Destroy(olc_Decal* decal)
{
    if(decal == NULL) return;

    if (decal->id != -1)
    {
        olc_Renderer_DeleteTexture(decal->id);
        decal->id = -1;
        free(decal);
    }
}

void olc_Decal_Update(olc_Decal* decal)
{
    if (decal->sprite == NULL) return;
    decal->vUVScale = olc_VF2D(1.0f / (float)(decal->sprite->width), 1.0f / (float)(decal->sprite->height));
    olc_Renderer_ApplyTexture(decal->id);
    olc_Renderer_UpdateTexture(decal->id, decal->sprite);
}

// O------------------------------------------------------------------------------O
// | olc_Renderable - Convenience class to keep a sprite and decal together      |
// O------------------------------------------------------------------------------O
olc_Renderable* olc_Renderable_Create(uint32_t width, uint32_t height)
{
    olc_Renderable* renderable = (olc_Renderable*)malloc(sizeof(olc_Renderable));
    if (renderable == NULL)
    {
        fprintf(stderr, "Error creating olc_Renderable\n");
        exit(EXIT_FAILURE);
    }

    renderable->sprite = olc_Sprite_Create(width, height);
    renderable->decal = olc_Decal_Create(renderable->sprite);

    return renderable;
}

olc_Renderable* olc_Renderable_Load(const char* sFile)
{
    olc_Renderable* renderable = (olc_Renderable*)malloc(sizeof(olc_Renderable));
    if (renderable == NULL)
    {
        fprintf(stderr, "Error creating olc_Renderable\n");
        exit(EXIT_FAILURE);
    }

    renderable->sprite = olc_Sprite_Load(sFile);
    renderable->decal = olc_Decal_Create(renderable->sprite);

    return renderable;
}

olc_Sprite* olc_Renderable_GetSprite(olc_Renderable* renderable)
{
    return renderable->sprite;
}

olc_Decal* olc_Renderable_GetDecal(olc_Renderable* renderable)
{
    return renderable->decal;
}

// O------------------------------------------------------------------------------O
// | olc_DecalInstance Constructor                                                |
// O------------------------------------------------------------------------------O
void olc_DecalInstance_Create(olc_DecalInstance* di)
{
    di->decal = NULL;

    di->pos[0] = olc_VF2D(0.0f, 0.0f); di->pos[1] = olc_VF2D(0.0f, 0.0f);
    di->pos[2] = olc_VF2D(0.0f, 0.0f); di->pos[3] = olc_VF2D(0.0f, 0.0f);

    di->uv[0] = olc_VF2D(0.0f, 0.0f); di->uv[1] = olc_VF2D(0.0f, 1.0f);
    di->uv[2] = olc_VF2D(1.0f, 1.0f); di->uv[3] = olc_VF2D(1.0f, 0.0f);

    di->w[0] = di->w[1] = di->w[2] = di->w[3] = 1.0f;
    di->tint[0] = di->tint[1] = di->tint[2] = di->tint[3] = olc_WHITE;
}

// O------------------------------------------------------------------------------O
// | olc::ResourcePack IMPLEMENTATION                                             |
// O------------------------------------------------------------------------------O

// TODO


// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Initialization Routines                               |
// O------------------------------------------------------------------------------O
void olc_PGE_DefaultState()
{
    PGE.nPixelMode = olc_PIXELMODE_NORMAL;
    PGE.fBlendFactor = 1.0f;
    PGE.bHasInputFocus = true;
    PGE.bHasMouseFocus = true;
    PGE.fFrameTimer = 0.0f;
    PGE.fLastElapsed = 0.0f;
    PGE.nFrameCount = 0;
    PGE.nTargetLayer = 0;
    PGE.nLastFPS = 0;
    PGE.bMouseIsVisible = true;

    if (PGE.sAppName == NULL)
        PGE_SetAppName("");

    sprintf(PGE.sTitle, "OneLoneCoder.com - Pixel Game Engine - %s - FPS: %d", PGE.sAppName, PGE.nFrameCount);
}

int32_t PGE_Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h, bool full_screen, bool vsync)
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

    if (PGE.vPixelSize.x <= 0 || PGE.vPixelSize.y <= 0 || PGE.vScreenSize.x <= 0 || PGE.vScreenSize.y <= 0)
        return olc_RCODE_FAIL;

    olc_PixelColourInit();
    olc_PGE_DefaultState();

    return olc_RCODE_OK;
}

#if !defined(PGE_USE_CUSTOM_START)
int32_t PGE_Start(bool (*create)(), bool (*update)(float), bool (*destroy)())
{
    PGE.OnUserCreate = (create == NULL) ? &PGE_DefaultOnUserCreate : create;
    PGE.OnUserUpdate = (update == NULL) ? &PGE_DefaultOnUserUpdate : update;
    PGE.OnUserDestroy = (destroy == NULL) ? &PGE_DefaultOnUserDestroy : destroy;

    if (olc_Platform_ApplicationStartUp() != olc_RCODE_OK) return olc_RCODE_FAIL;

    olc_vi2d vWinPos;

    vWinPos.x = 30;
    vWinPos.y = 30;

    // Construct the window
    if (olc_Platform_CreateWindowPane(vWinPos, PGE.vWindowSize, PGE.bFullScreen) != olc_RCODE_OK) return olc_RCODE_FAIL;
    olc_PGE_UpdateWindowSize(PGE.vWindowSize.x, PGE.vWindowSize.y);

    PGE.bActive = true;

    olc_CrossPlatform_Thread_Start();

    // Some implementations may form an event loop here
    olc_Platform_StartSystemEventLoop();

    olc_CrossPlatform_Thread_Join();

    if (olc_Platform_ApplicationCleanUp() != olc_RCODE_OK) return olc_RCODE_FAIL;

    return olc_RCODE_OK;
}
#endif

bool PGE_DefaultOnUserCreate() { return true; }
bool PGE_DefaultOnUserUpdate(float fElapsedTime) { UNUSED(fElapsedTime); return true; }
bool PGE_DefaultOnUserDestroy() { return true; }

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Hardware Interfaces                                   |
// O------------------------------------------------------------------------------O

// Returns true if window is currently in focus
bool PGE_IsFocused()
{
    return PGE.bHasInputFocus;
}

// Get the state of a specific keyboard button

olc_HWButton PGE_GetKey(uint8_t k)
{
    return PGE.pKeyboardState[k];
}

// Get the state of a specific mouse button
olc_HWButton PGE_GetMouse(uint32_t b)
{
    return PGE.pMouseState[b];
}

// Get Mouse X coordinate in "xel" space
int32_t PGE_GetMouseX()
{
    return PGE.vMousePos.x;
}

// Get Mouse Y coordinate in "pixel" space
int32_t PGE_GetMouseY()
{
    return PGE.vMousePos.y;
}

// Get Mouse Wheel Delta
int32_t PGE_GetMouseWheel()
{
    return PGE.nMouseWheelDelta;
}

// Get the ouse in window space
olc_vi2d PGE_GetWindowMouse()
{
    return PGE.vMouseWindowPos;
}

// Is system mouse cursor currently visible?
bool PGE_IsMouseCursorVisible()
{
    return PGE.bMouseIsVisible;
}

// show the system mouse cursor (true: visible, false: invisible)
void PGE_ShowSystemMouseCursor(bool state)
{
    PGE.bMouseIsVisible = state;
}


// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Utility                                               |
// O------------------------------------------------------------------------------O

// Returns the width of the screen in "pixels"
int32_t PGE_ScreenWidth()
{
    return PGE.vScreenSize.x;
}

// Returns the height of the screen in "pixels"
int32_t PGE_ScreenHeight()
{
    return PGE.vScreenSize.y;
}

// Returns the width of the currently selected drawing target in "pixels"
int32_t PGE_GetDrawTargetWidth()
{
    return PGE.pDrawTarget->width;
}

// Returns the height of the currently selected drawing target in "pixels"
int32_t PGE_GetDrawTargetHeight()
{
    return PGE.pDrawTarget->height;
}

// Returns the currently active draw target
olc_Sprite* PGE_GetDrawTarget()
{
    return PGE.pDrawTarget;
}

// Resize the primary screen sprite
void PGE_SetScreenSize(int w, int h)
{
    PGE.vScreenSize.x = w;
    PGE.vScreenSize.y = h;

    for (size_t i = 0; i < vector_size(PGE.vLayers); i++)
    {
        olc_Sprite_Destroy(PGE.vLayers[i].pDrawTarget);
        PGE.vLayers[i].pDrawTarget = olc_Sprite_Create(PGE.vScreenSize.x, PGE.vScreenSize.y);
        PGE.vLayers[i].bUpdate = true;
    }

    PGE_SetDrawTarget(NULL);

    PGE_ClearBuffer(olc_BLACK, true);
    olc_Renderer_DisplayFrame();

    PGE_ClearBuffer(olc_BLACK, true);
    olc_Renderer_UpdateViewport(PGE.vViewPos, PGE.vViewSize);
}

// Specify which Sprite should be the target of drawing functions, use NULL
// to specify the primary screen
void PGE_SetDrawTarget(olc_Sprite* target)
{
    if (target == NULL)
    {
        PGE.pDrawTarget = PGE.vLayers[0].pDrawTarget;
        PGE.nTargetLayer = 0;
    }
    else
    {
        PGE.pDrawTarget = target;
    }
}

// Gets the current Frames Per Second
uint32_t PGE_GetFPS()
{
    return PGE.nLastFPS;
}

// Gets last update of elapsed time
const float PGE_GetElapsedTime()
{
    return PGE.fLastElapsed;
}

// Gets Actual Window size
const olc_vi2d PGE_GetWindowSize()
{
    return PGE.vWindowSize;
}


// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Configuration Routines                                |
// O------------------------------------------------------------------------------O

// Set the Applications Name (For the Title Bar)
void PGE_SetAppName(const char* title)
{
    if (PGE.sAppName != NULL)
        free(PGE.sAppName);

    PGE.sAppName = (char*)calloc(sizeof(char), strlen(title) + 1);

    if (PGE.sAppName == NULL)
    {
        fprintf(stderr, "Failed to set sAppName.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(PGE.sAppName, title);
}

// Layer targeting functions
void PGE_SetLayerTarget(uint8_t layer)
{
    PGE.pDrawTarget = PGE.vLayers[layer].pDrawTarget;
    PGE.vLayers[layer].bUpdate = true;
    PGE.nTargetLayer = layer;
}

void PGE_EnableLayer(uint8_t layer, bool b)
{
    if (layer < vector_size(PGE.vLayers))
        PGE.vLayers[layer].bShow = b;
}

void PGE_SetLayerOffset(uint8_t layer, float x, float y)
{
    if (layer < vector_size(PGE.vLayers))
    {
        PGE.vLayers[layer].vOffset.x = x;
        PGE.vLayers[layer].vOffset.y = y;
    }

}

void PGE_SetLayerScale(uint8_t layer, float x, float y)
{
    if (layer < vector_size(PGE.vLayers))
    {
        PGE.vLayers[layer].vScale.x = x;
        PGE.vLayers[layer].vScale.y = y;
    }
}

void PGE_SetLayerTint(uint8_t layer, const olc_Pixel tint)
{
    if (layer < vector_size(PGE.vLayers))
        PGE.vLayers[layer].tint = tint;
}

void PGE_SetLayerCustomRenderFunction(uint8_t layer, void (*f)())
{
    if (layer < vector_size(PGE.vLayers))
        PGE.vLayers[layer].funcHook = f;
}

olc_LayerDesc* PGE_GetLayers()
{
    return PGE.vLayers;
}

uint32_t PGE_CreateLayer()
{
    olc_LayerDesc* ld = (olc_LayerDesc*)vector_push(PGE.vLayers, NULL);

    ld->vOffset = olc_VF2D(0, 0);
    ld->vScale = olc_VF2D(1, 1);
    ld->bShow = false;
    ld->bUpdate = false;
    ld->pDrawTarget = olc_Sprite_Create(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->nResID = olc_Renderer_CreateTexture(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->vecDecalInstance = vector_init(olc_DecalInstance);
    ld->tint = olc_WHITE;
    ld->funcHook = NULL;

    olc_Renderer_UpdateTexture(ld->nResID, ld->pDrawTarget);
    return (uint32_t)(vector_size(PGE.vLayers) - 1);
}

// Change the pixel mode for different optimisations
// olc_PIXELMODE_NORMAL = No transparency
// olc_PIXELMODE_MASK   = Transparent if alpha is < 255
// olc_PIXELMODE_ALPHA  = Full transparency
void PGE_SetPixelMode(int32_t m)
{
    PGE.nPixelMode = m;
}

int32_t PGE_GetPixelMode()
{
    return PGE.nPixelMode;
}

// Use a custom blend function
void PGE_SetCustomPixelMode(olc_Pixel(*f)(int x, int y, olc_Pixel p1, olc_Pixel p2))
{
    PGE.funcPixelMode = f;
    PGE.nPixelMode = olc_PIXELMODE_CUSTOM;
}

// Change the blend factor form between 0.0f to 1.0f;
void PGE_SetPixelBlend(float fBlend)
{
    PGE.fFrameTimer = fBlend;
    if (PGE.fBlendFactor < 0.0f) PGE.fBlendFactor = 0.0f;
    if (PGE.fBlendFactor > 1.0f) PGE.fBlendFactor = 1.0f;
}

// Offset texels by sub-pixel amount (advanced, do not use)
void PGE_SetSubPixelOffset(float ox, float oy)
{
    //vSubPixelOffset.x = ox * vPixel.x;
    //vSubPixelOffset.y = oy * vPixel.y;
}



// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Drawing Routines                                      |
// O------------------------------------------------------------------------------O

// Draws a single Pixel
bool PGE_Draw(int32_t x, int32_t y, olc_Pixel p)
{
    if (!PGE.pDrawTarget) return false;

    if (PGE.nPixelMode == olc_PIXELMODE_NORMAL)
    {
        return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, p);
    }

    if (PGE.nPixelMode == olc_PIXELMODE_MASK)
    {
        if (p.a == 255)
            return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, p);
    }

    if (PGE.nPixelMode == olc_PIXELMODE_ALPHA)
    {
        olc_Pixel d = olc_Sprite_GetPixel(PGE.pDrawTarget, x, y);
        float a = (float)(p.a / 255.0f) * PGE.fBlendFactor;
        float c = 1.0f - a;
        float r = a * (float)p.r + c * (float)d.r;
        float g = a * (float)p.g + c * (float)d.g;
        float b = a * (float)p.b + c * (float)d.b;
        return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, olc_PixelRGB((uint8_t)r, (uint8_t)g, (uint8_t)b));
    }

    if (PGE.nPixelMode == olc_PIXELMODE_CUSTOM)
    {
        return olc_Sprite_SetPixel(PGE.pDrawTarget, x, y, PGE.funcPixelMode(x, y, p, olc_Sprite_GetPixel(PGE.pDrawTarget, x, y)));
    }

    return false;
}

// Draws a line from (x1,y1) to (x2,y2)
void PGE_DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, olc_Pixel p, uint32_t pattern)
{
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i, temp;
    dx = x2 - x1; dy = y2 - y1;

    // straight lines idea by gurkanctn
    if (dx == 0) // Line is vertical
    {
        if (y2 < y1)
        {
            temp = y1;
            y1 = y2;
            y2 = temp;
        }
        for (y = y1; y <= y2; y++) if (rol(&pattern)) PGE_Draw(x1, y, p);
        return;
    }

    if (dy == 0) // Line is horizontal
    {
        if (x2 < x1)
        {
            temp = x1;
            x1 = x2;
            x2 = temp;
        }
        for (x = x1; x <= x2; x++) if (rol(&pattern)) PGE_Draw(x, y1, p);
        return;
    }

    // Line is Funk-aye
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        {
            x = x1; y = y1; xe = x2;
        }
        else
        {
            x = x2; y = y2; xe = x1;
        }

        if (rol(&pattern)) PGE_Draw(x, y, p);

        for (i = 0; x < xe; i++)
        {
            x = x + 1;
            if (px < 0)
                px = px + 2 * dy1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            if (rol(&pattern)) PGE_Draw(x, y, p);
        }
    }
    else
    {
        if (dy >= 0)
        {
            x = x1; y = y1; ye = y2;
        }
        else
        {
            x = x2; y = y2; ye = y1;
        }

        if (rol(&pattern)) PGE_Draw(x, y, p);

        for (i = 0; y < ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            if (rol(&pattern)) PGE_Draw(x, y, p);
        }
    }
}

// Draws a circle located at (x,y) with radius
void PGE_DrawCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p, uint8_t mask)
{ // Thanks to IanM-Matrix1 #PR121
    if (radius < 0 || x < -radius || y < -radius || x - PGE_GetDrawTargetWidth() > radius || y - PGE_GetDrawTargetHeight() > radius)
        return;

    if (radius > 0)
    {
        int x0 = 0;
        int y0 = radius;
        int d = 3 - 2 * radius;

        while (y0 >= x0) // only formulate 1/8 of circle
        {
            // Draw even octants
            if (mask & 0x01) PGE_Draw(x + x0, y - y0, p);// Q6 - upper right right
            if (mask & 0x04) PGE_Draw(x + y0, y + x0, p);// Q4 - lower lower right
            if (mask & 0x10) PGE_Draw(x - x0, y + y0, p);// Q2 - lower left left
            if (mask & 0x40) PGE_Draw(x - y0, y - x0, p);// Q0 - upper upper left
            if (x0 != 0 && x0 != y0)
            {
                if (mask & 0x02) PGE_Draw(x + y0, y - x0, p);// Q7 - upper upper right
                if (mask & 0x08) PGE_Draw(x + x0, y + y0, p);// Q5 - lower right right
                if (mask & 0x20) PGE_Draw(x - y0, y + x0, p);// Q3 - lower lower left
                if (mask & 0x80) PGE_Draw(x - x0, y - y0, p);// Q1 - upper left left
            }

            if (d < 0)
                d += 4 * x0++ + 6;
            else
                d += 4 * (x0++ - y0--) + 10;
        }
    }
    else
        PGE_Draw(x, y, p);
}

// Fills a circle located at (x,y) with radius
void PGE_FillCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p)
{ // Thanks to IanM-Matrix1 #PR121
    if (radius < 0 || x < -radius || y < -radius || x - PGE_GetDrawTargetWidth() > radius || y - PGE_GetDrawTargetHeight() > radius)
        return;

    if (radius > 0)
    {
        int x0 = 0;
        int y0 = radius;
        int d = 3 - 2 * radius;

        while (y0 >= x0)
        {
            drawline(x - y0, x + y0, y - x0, p);
            if (x0 > 0)	drawline(x - y0, x + y0, y + x0, p);

            if (d < 0)
                d += 4 * x0++ + 6;
            else
            {
                if (x0 != y0)
                {
                    drawline(x - x0, x + x0, y - y0, p);
                    drawline(x - x0, x + x0, y + y0, p);
                }
                d += 4 * (x0++ - y0--) + 10;
            }
        }
    }
    else
        PGE_Draw(x, y, p);
}

// Draws a rectangle at (x,y) to (x+w,y+h)
void PGE_DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p)
{
    PGE_DrawLine(x, y, x + w, y, p, olc_SOLID);
    PGE_DrawLine(x + w, y, x + w, y + h, p, olc_SOLID);
    PGE_DrawLine(x + w, y + h, x, y + h, p, olc_SOLID);
    PGE_DrawLine(x, y + h, x, y, p, olc_SOLID);
}

// Fills a rectangle at (x,y) to (x+w,y+h)
void PGE_FillRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p)
{
    int32_t x2 = x + w;
    int32_t y2 = y + h;

    if (x < 0) x = 0;
    if (x >= (int32_t)PGE_GetDrawTargetWidth()) x = (int32_t)PGE_GetDrawTargetWidth();
    if (y < 0) y = 0;
    if (y >= (int32_t)PGE_GetDrawTargetHeight()) y = (int32_t)PGE_GetDrawTargetHeight();

    if (x2 < 0) x2 = 0;
    if (x2 >= (int32_t)PGE_GetDrawTargetWidth()) x2 = (int32_t)PGE_GetDrawTargetWidth();
    if (y2 < 0) y2 = 0;
    if (y2 >= (int32_t)PGE_GetDrawTargetHeight()) y2 = (int32_t)PGE_GetDrawTargetHeight();

    for (int i = x; i < x2; i++)
        for (int j = y; j < y2; j++)
            PGE_Draw(i, j, p);
}

// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void PGE_DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p)
{
    PGE_DrawLine(x1, y1, x2, y2, p, olc_SOLID);
    PGE_DrawLine(x2, y2, x3, y3, p, olc_SOLID);
    PGE_DrawLine(x3, y3, x1, y1, p, olc_SOLID);
}

// https://www.avrfreaks.net/sites/default/files/triangles.c
void PGE_FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p)
{
    int t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int signx1, signx2, dx1, dy1, dx2, dy2;
    int e1, e2;
    // Sort vertices
    if (y1 > y2) { swap_int(&y1, &y2); swap_int(&x1, &x2); }
    if (y1 > y3) { swap_int(&y1, &y3); swap_int(&x1, &x3); }
    if (y2 > y3) { swap_int(&y2, &y3); swap_int(&x2, &x3); }

    t1x = t2x = x1; y = y1;   // Starting points
    dx1 = (int)(x2 - x1);
    if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
    else signx1 = 1;
    dy1 = (int)(y2 - y1);

    dx2 = (int)(x3 - x1);
    if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
    else signx2 = 1;
    dy2 = (int)(y3 - y1);

    if (dy1 > dx1) { swap_int(&dx1, &dy1); changed1 = true; }
    if (dy2 > dx2) { swap_int(&dy2, &dx2); changed2 = true; }

    e2 = (int)(dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2) goto next;
    e1 = (int)(dx1 >> 1);

    for (int i = 0; i < dx1;) {
        t1xp = 0; t2xp = 0;
        if (t1x < t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }
        // process first line until y value is about to change
        while (i < dx1) {
            i++;
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) t1xp = signx1;//t1x += signx1;
                else          goto next1;
            }
            if (changed1) break;
            else t1x += signx1;
        }
        // Move line
    next1:
        // process second line until y value is about to change
        while (1) {
            e2 += dy2;
            while (e2 >= dx2) {
                e2 -= dx2;
                if (changed2) t2xp = signx2;//t2x += signx2;
                else          goto next2;
            }
            if (changed2)     break;
            else              t2x += signx2;
        }
    next2:
        if (minx > t1x) minx = t1x;
        if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x;
        if (maxx < t2x) maxx = t2x;
        drawline(minx, maxx, y, p);    // Draw line from min to max points found on the y
                                    // Now increase y
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y == y2) break;

    }
next:
    // Second half
    dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
    else signx1 = 1;
    dy1 = (int)(y3 - y2);
    t1x = x2;

    if (dy1 > dx1) {   // swap values
        swap_int(&dy1, &dx1);
        changed1 = true;
    }
    else changed1 = false;

    e1 = (int)(dx1 >> 1);

    for (int i = 0; i <= dx1; i++) {
        t1xp = 0; t2xp = 0;
        if (t1x < t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }
        // process first line until y value is about to change
        while (i < dx1) {
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) { t1xp = signx1; break; }//t1x += signx1;
                else          goto next3;
            }
            if (changed1) break;
            else   	   	  t1x += signx1;
            if (i < dx1) i++;
        }
    next3:
        // process second line until y value is about to change
        while (t2x != x3) {
            e2 += dy2;
            while (e2 >= dx2) {
                e2 -= dx2;
                if (changed2) t2xp = signx2;
                else          goto next4;
            }
            if (changed2)     break;
            else              t2x += signx2;
        }
    next4:

        if (minx > t1x) minx = t1x;
        if (minx > t2x) minx = t2x;
        if (maxx < t1x) maxx = t1x;
        if (maxx < t2x) maxx = t2x;
        drawline(minx, maxx, y, p);
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y > y3) return;
    }

}

// Draws an entire sprite at well in my defencelocation (x,y)
void PGE_DrawSprite(int32_t x, int32_t y, olc_Sprite* sprite, uint32_t scale, uint8_t flip)
{
    if (sprite == NULL)
        return;

    int32_t fxs = 0, fxm = 1, fx = 0;
    int32_t fys = 0, fym = 1, fy = 0;

    if (flip & olc_SPRITE_FLIP_HORIZ) { fxs = sprite->width - 1; fxm = -1; }
    if (flip & olc_SPRITE_FLIP_VERT) { fys = sprite->height - 1; fym = -1; }

    if (scale > 1)
    {
        fx = fxs;
        for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < sprite->height; j++, fy += fym)
                for (uint32_t is = 0; is < scale; is++)
                    for (uint32_t js = 0; js < scale; js++)
                        PGE_Draw(x + (i * scale) + is, y + (j * scale) + js, olc_Sprite_GetPixel(sprite, fx, fy));
        }
    }
    else
    {
        fx = fxs;
        for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < sprite->height; j++, fy += fym)
                PGE_Draw(x + i, y + j, olc_Sprite_GetPixel(sprite, fx, fy));
        }
    }

}

// Draws an area of a sprite at location (x,y), where the
// selected area is (ox,oy) to (ox+w,oy+h)
void PGE_DrawPartialSprite(int32_t x, int32_t y, olc_Sprite* sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip)
{
    if (sprite == NULL)
        return;

    int32_t fxs = 0, fxm = 1, fx = 0;
    int32_t fys = 0, fym = 1, fy = 0;
    if (flip & olc_SPRITE_FLIP_HORIZ) { fxs = w - 1; fxm = -1; }
    if (flip & olc_SPRITE_FLIP_VERT) { fys = h - 1; fym = -1; }

    if (scale > 1)
    {
        fx = fxs;
        for (int32_t i = 0; i < w; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < h; j++, fy += fym)
                for (uint32_t is = 0; is < scale; is++)
                    for (uint32_t js = 0; js < scale; js++)
                        PGE_Draw(x + (i * scale) + is, y + (j * scale) + js, olc_Sprite_GetPixel(sprite, fx + ox, fy + oy));
        }
    }
    else
    {
        fx = fxs;
        for (int32_t i = 0; i < w; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < h; j++, fy += fym)
                PGE_Draw(x + i, y + j, olc_Sprite_GetPixel(sprite, fx + ox, fy + oy));
        }
    }

}

// O------------------------------------------------------------------------------O
// | olc::PixelGameEngine - Decal Quad Functions                                  |
// O------------------------------------------------------------------------------O

// Draws a whole decal, with optional scale and tinting
void PGE_DrawDecal(olc_vf2d pos, olc_Decal* decal, olc_vf2d scale, const olc_Pixel tint)
{
    olc_vf2d vScreenSpacePos;
    vScreenSpacePos.x = (pos.x * PGE.vInvScreenSize.x) * 2.0f - 1.0f;
    vScreenSpacePos.y = ((pos.y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f;

    olc_vf2d vScreenSpaceDim;
    vScreenSpaceDim.x = vScreenSpacePos.x + (2.0f * ((float)(decal->sprite->width) * PGE.vInvScreenSize.x)) * scale.x;
    vScreenSpaceDim.y = vScreenSpacePos.y - (2.0f * ((float)(decal->sprite->height) * PGE.vInvScreenSize.y)) * scale.y;

    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    di->decal = decal;

    di->tint[0] = tint;

    di->pos[0] = olc_VF2D(vScreenSpacePos.x, vScreenSpacePos.y);
    di->pos[1] = olc_VF2D(vScreenSpacePos.x, vScreenSpaceDim.y);
    di->pos[2] = olc_VF2D(vScreenSpaceDim.x, vScreenSpaceDim.y);
    di->pos[3] = olc_VF2D(vScreenSpaceDim.x, vScreenSpacePos.y);
}

// Draws a region of a decal, with optional scale and tinting
void PGE_DrawPartialDecal(olc_vf2d pos, olc_Decal* decal, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint)
{
    olc_vf2d vScreenSpacePos = olc_VF2D(
        (pos.x * PGE.vInvScreenSize.x) * 2.0f - 1.0f,
        ((pos.y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
    );

    olc_vf2d vScreenSpaceDim = olc_VF2D(
        vScreenSpacePos.x + (2.0f * source_size.x * PGE.vInvScreenSize.x) * scale.x,
        vScreenSpacePos.y - (2.0f * source_size.y * PGE.vInvScreenSize.y) * scale.y
    );

    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    di->decal = decal; di->tint[0] = tint;

    di->pos[0] = olc_VF2D(vScreenSpacePos.x, vScreenSpacePos.y);
    di->pos[1] = olc_VF2D(vScreenSpacePos.x, vScreenSpaceDim.y);
    di->pos[2] = olc_VF2D(vScreenSpaceDim.x, vScreenSpaceDim.y);
    di->pos[3] = olc_VF2D(vScreenSpaceDim.x, vScreenSpacePos.y);

    olc_vf2d uvtl = olc_VF2D(source_pos.x * decal->vUVScale.x, source_pos.y * decal->vUVScale.y);
    olc_vf2d uvbr = olc_VF2D(uvtl.x + (source_size.x * decal->vUVScale.x), uvtl.y + (source_size.y * decal->vUVScale.y));

    di->uv[0] = olc_VF2D(uvtl.x, uvtl.y); di->uv[1] = olc_VF2D(uvtl.x, uvbr.y);
    di->uv[2] = olc_VF2D(uvbr.x, uvbr.y); di->uv[3] = olc_VF2D(uvbr.x, uvtl.y);

}

// Draws fully user controlled 4 vertices, pos(pixels), uv(pixels), colours
void PGE_DrawExplicitDecal(olc_Decal* decal, olc_vf2d* pos, olc_vf2d* uv, const olc_Pixel* col)
{
    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    for (int i = 0; i < 4; i++)
    {
        di->pos[i] = olc_VF2D((pos[i].x * PGE.vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f);
        di->uv[i] = uv[i];
        di->tint[i] = col[i];
    }

}

// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
void PGE_DrawWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], const olc_Pixel tint)
{
    // Thanks Nathan Reed, a brilliant article explaining whats going on here
    // http://www.reedbeta.com/blog/quadrilateral-interpolation-part-1/
    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    di->decal = decal;
    di->tint[0] = tint;
    olc_vf2d center = olc_VF2D(0,0);
    float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
    if (rd != 0)
    {
        rd = 1.0f / rd;
        float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
        float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;

        if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f))
        {
            center.x = pos[0].x + rn * (pos[2].x - pos[0].x);
            center.y = pos[0].y + rn * (pos[2].y - pos[0].y);
        }

        float d[4];
        for (int i = 0; i < 4; i++)
        {
            olc_vf2d t = olc_VF2D(pos[i].x - center.x, pos[i].y - center.y);
            d[i] = sqrtf(t.x * t.x + t.y * t.y);
        }

        for (int i = 0; i < 4; i++)
        {
            float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
            di->uv[i].x *= q;
            di->uv[i].y *= q;
            di->w[i] *= q;

            di->pos[i] = olc_VF2D((pos[i].x * PGE.vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f);
        }
    }

}

// As above, but you can specify a region of a decal source sprite
void PGE_DrawPartialWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], olc_vf2d source_pos, olc_vf2d source_size, const olc_Pixel tint)
{
    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    di->decal = decal;
    di->tint[0] = tint;
    olc_vf2d center = olc_VF2D(0,0);
    float rd = ((pos[2].x - pos[0].x) * (pos[3].y - pos[1].y) - (pos[3].x - pos[1].x) * (pos[2].y - pos[0].y));
    if (rd != 0)
    {
        olc_vf2d uvtl = olc_VF2D(source_pos.x * decal->vUVScale.x, source_pos.y * decal->vUVScale.y);
        olc_vf2d uvbr = olc_VF2D(uvtl.x + (source_size.x * decal->vUVScale.x), uvtl.y + (source_size.y * decal->vUVScale.y));

        di->uv[0] = olc_VF2D(uvtl.x, uvtl.y); di->uv[1] = olc_VF2D(uvtl.x, uvbr.y);
        di->uv[2] = olc_VF2D(uvbr.x, uvbr.y); di->uv[3] = olc_VF2D(uvbr.x, uvtl.y);

        rd = 1.0f / rd;
        float rn = ((pos[3].x - pos[1].x) * (pos[0].y - pos[1].y) - (pos[3].y - pos[1].y) * (pos[0].x - pos[1].x)) * rd;
        float sn = ((pos[2].x - pos[0].x) * (pos[0].y - pos[1].y) - (pos[2].y - pos[0].y) * (pos[0].x - pos[1].x)) * rd;

        if (!(rn < 0.f || rn > 1.f || sn < 0.f || sn > 1.f))
            center = olc_VF2D(pos[0].x + rn * (pos[2].x - pos[0].x), pos[0].y + rn * (pos[2].y - pos[0].y));

        float d[4];
        for (int i = 0; i < 4; i++)
        {
            olc_vf2d t = olc_VF2D(pos[i].x - center.x, pos[i].y - center.y);
            d[i] = sqrtf(t.x * t.x + t.y * t.y);
        }

        for (int i = 0; i < 4; i++)
        {
            float q = d[i] == 0.0f ? 1.0f : (d[i] + d[(i + 2) & 3]) / d[(i + 2) & 3];
            di->uv[i].x *= q;
            di->uv[i].y *= q;
            di->w[i] *= q;

            di->pos[i] = olc_VF2D((pos[i].x * PGE.vInvScreenSize.x) * 2.0f - 1.0f, ((pos[i].y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f);
        }
    }

}

// Draws a decal rotated to specified angle, wit point of rotation offset
void PGE_DrawRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d scale, const olc_Pixel tint)
{
    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    di->decal = decal; di->tint[0] = tint;

    di->pos[0] = olc_VF2D((0.0f - center.x) * scale.x, (0.0f - center.y) * scale.y);
    di->pos[1] = olc_VF2D((0.0f - center.x) * scale.x, ((float)decal->sprite->height - center.y) * scale.y);
    di->pos[2] = olc_VF2D(((float)decal->sprite->width - center.x) * scale.x, ((float)decal->sprite->height - center.y) * scale.y);
    di->pos[3] = olc_VF2D(((float)decal->sprite->width - center.x) * scale.x, (0.0f - center.y) * scale.y);

    float c = (float)cos(fAngle), s = (float)sin(fAngle);

    for (int i = 0; i < 4; i++)
    {
        di->pos[i] = olc_VF2D(pos.x + (di->pos[i].x * c - di->pos[i].y * s), pos.y + (di->pos[i].x * s + di->pos[i].y * c));
        di->pos[i] = olc_VF2D(di->pos[i].x * PGE.vInvScreenSize.x * 2.0f - 1.0f, di->pos[i].y * PGE.vInvScreenSize.y * 2.0f - 1.0f);
        di->pos[i].y *= -1.0f;
    }
}

void PGE_DrawPartialRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint)
{
    olc_DecalInstance* di = (olc_DecalInstance*)vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance, NULL);
    olc_DecalInstance_Create(di);

    di->decal = decal; di->tint[0] = tint;

    di->pos[0] = olc_VF2D((0.0f - center.x) * scale.x, (0.0f - center.y) * scale.y);
    di->pos[1] = olc_VF2D((0.0f - center.x) * scale.x, (source_size.x - center.y) * scale.y);
    di->pos[2] = olc_VF2D((source_size.x - center.x) * scale.x, (source_size.y - center.y) * scale.y);
    di->pos[3] = olc_VF2D((source_size.x - center.x) * scale.x, (0.0f - center.y) * scale.y);

    float c = (float)cos(fAngle), s = (float)sin(fAngle);
    for (int i = 0; i < 4; i++)
    {
        di->pos[i] = olc_VF2D(pos.x + (di->pos[i].x * c - di->pos[i].y * s), pos.y + (di->pos[i].x * s + di->pos[i].y * c));
        di->pos[i] = olc_VF2D(di->pos[i].x * PGE.vInvScreenSize.x * 2.0f - 1.0f, di->pos[i].y * PGE.vInvScreenSize.y * 2.0f - 1.0f);
        di->pos[i].y *= -1.0f;
    }

    olc_vf2d uvtl = olc_VF2D(source_pos.x * decal->vUVScale.x, source_pos.y * decal->vUVScale.y);
    olc_vf2d uvbr = olc_VF2D(uvtl.x + (source_size.x * decal->vUVScale.x), uvtl.y + (source_size.y * decal->vUVScale.y));

    di->uv[0] = olc_VF2D(uvtl.x, uvtl.y); di->uv[1] = olc_VF2D(uvtl.x, uvbr.y);
    di->uv[2] = olc_VF2D(uvbr.x, uvbr.y); di->uv[3] = olc_VF2D(uvbr.x, uvtl.y);
}

// Draws a multiline string as a decal, with tiniting and scaling
void PGE_DrawStringDecal(olc_vf2d pos, const char* sText, const olc_Pixel col, olc_vf2d scale)
{
    olc_vf2d spos;

    spos.x = 0.0f;
    spos.y = 0.0f;

    for (size_t i = 0; i < strlen(sText); i++)
    {
        char c = sText[i];
        if (c == '\n')
        {
            spos.x = 0; spos.y += 8.0f * scale.y;
        }
        else
        {
            int32_t ox = (c - 32) % 16;
            int32_t oy = (c - 32) / 16;

            olc_vf2d p, src, src_size;

            p.x = pos.x + spos.x;
            p.y = pos.y + spos.y;

            src.x = (float)ox * 8.0f;
            src.y = (float)oy * 8.0f;

            src_size.x = 8.0f;
            src_size.y = 8.0f;

            PGE_DrawPartialDecal(p, PGE.fontDecal, src, src_size, scale, col);
            spos.x += 8.0f * scale.x;
        }
    }
}

// Draws a single shaded filled rectangle as a decal
void PGE_FillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel col)
{
    olc_vf2d  points[4];
    olc_vf2d  uvs[4];
    olc_Pixel cols[4];

    points[0] = pos;
    points[1] = olc_VF2D(pos.x, pos.y + size.y);
    points[2] = olc_VF2D(pos.x + size.x, pos.y + size.y);
    points[3] = olc_VF2D(pos.x + size.x, pos.y);

    for (int i = 0; i < 4; i++)
    {
        uvs[i] = olc_VF2D(0, 0);
        cols[i] = col;
    }

    PGE_DrawExplicitDecal(NULL, points, uvs, cols);
}

// Draws a corner shaded rectangle as a decal
void PGE_GradientFillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel colTL, const olc_Pixel colBL, const olc_Pixel colBR, const olc_Pixel colTR)
{
    olc_vf2d  points[4];
    olc_vf2d  uvs[4];
    olc_Pixel cols[4];

    points[0] = pos;
    points[1] = olc_VF2D(pos.x, pos.y + size.y);
    points[2] = olc_VF2D(pos.x + size.x, pos.y + size.y);
    points[3] = olc_VF2D(pos.x + size.x, pos.y);

    uvs[0] = uvs[1] = uvs[2] = uvs[3] = olc_VF2D(0, 0);

    cols[0] = colTL; cols[1] = colBL;
    cols[2] = colBR; cols[3] = colTR;

    PGE_DrawExplicitDecal(NULL, points, uvs, cols);
}



// Draws a single line of text
void PGE_DrawString(int32_t x, int32_t y, const char* sText, olc_Pixel col, uint32_t scale)
{
    int32_t sx = 0;
    int32_t sy = 0;
    int32_t m = PGE.nPixelMode;
    // Thanks @tucna, spotted bug with col.ALPHA :P
    if (col.a != 255)		PGE_SetPixelMode(olc_PIXELMODE_ALPHA);
    else					PGE_SetPixelMode(olc_PIXELMODE_MASK);
    for (size_t i = 0; i < strlen(sText); i++)
    {
        char c = sText[i];
        if (c == '\n')
        {
            sx = 0; sy += 8 * scale;
        }
        else
        {
            int32_t ox = (c - 32) % 16;
            int32_t oy = (c - 32) / 16;

            if (scale > 1)
            {
                for (uint32_t i = 0; i < 8; i++)
                    for (uint32_t j = 0; j < 8; j++)
                        if (olc_Sprite_GetPixel(PGE.fontSprite, i + ox * 8, j + oy * 8).r > 0)
                            for (uint32_t is = 0; is < scale; is++)
                                for (uint32_t js = 0; js < scale; js++)
                                    PGE_Draw(x + sx + (i * scale) + is, y + sy + (j * scale) + js, col);
            }
            else
            {
                for (uint32_t i = 0; i < 8; i++)
                    for (uint32_t j = 0; j < 8; j++)
                        if (olc_Sprite_GetPixel(PGE.fontSprite, i + ox * 8, j + oy * 8).r > 0)
                            PGE_Draw(x + sx + i, y + sy + j, col);
            }
            sx += 8 * scale;
        }
    }
    PGE_SetPixelMode(m);
}

olc_vi2d PGE_GetTextSize(const char* s)
{
    olc_vi2d size = { 0,1 };
    olc_vi2d pos = { 0,1 };

    for (size_t i = 0; i < strlen(s); i++)
    {
        if (s[i] == '\n') { pos.y++;  pos.x = 0; }
        else pos.x++;
        size.x = (size.x > pos.x) ? size.x : pos.x;
        size.y = (size.y > pos.y) ? size.y : pos.y;
    }

    size.x = size.x * 8;
    size.y = size.y * 8;

    return size;
}

// Clears entire draw target to Pixel
void PGE_Clear(olc_Pixel p)
{
    int pixels = PGE_GetDrawTargetWidth() * PGE_GetDrawTargetHeight();
    uint32_t* m = olc_Sprite_GetData(PGE_GetDrawTarget());
    for (int i = 0; i < pixels; i++) m[i] = p.n;
}

void PGE_ClearBuffer(olc_Pixel p, bool bDepth)
{
    olc_Renderer_ClearBuffer(p, bDepth);
}

olc_CrossPlatform_Thread PGE_EngineThread()
{
    // Allow platform to do stuff here if needed, since its now in the
    // context of this thread
    if (olc_Platform_ThreadStartUp() == olc_RCODE_FAIL)	return olc_CrossPlatform_Thread_Return;

    // Do engine context specific initialisation
    olc_PGE_PrepareEngine();

    // Create user resources as part of this thread
    if (!PGE.OnUserCreate()) PGE.bActive = false;

    while (PGE.bActive)
    {
        // Run as fast as possible
        while (PGE.bActive) { olc_PGE_CoreUpdate(); }

        // Allow the user to free resources if they have overrided the destroy function
        if (!PGE.OnUserDestroy())
        {
            // User denied destroy for some reason, so continue running
            PGE.bActive = true;
        }
    }

    olc_Platform_ThreadCleanUp();
    return olc_CrossPlatform_Thread_Return;
}

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
    if (PGE.vMousePosCache.x >= (int32_t)PGE.vScreenSize.x)	PGE.vMousePosCache.x = PGE.vScreenSize.x - 1;
    if (PGE.vMousePosCache.y >= (int32_t)PGE.vScreenSize.y)	PGE.vMousePosCache.y = PGE.vScreenSize.y - 1;
    if (PGE.vMousePosCache.x < 0) PGE.vMousePosCache.x = 0;
    if (PGE.vMousePosCache.y < 0) PGE.vMousePosCache.y = 0;

}

void olc_PGE_UpdateMouseWheel(int32_t delta)
{
    PGE.nMouseWheelDeltaCache += delta;
}

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

    if (PGE.vViewSize.y > PGE.vWindowSize.y)
    {
        PGE.vViewSize.y = PGE.vWindowSize.y;
        PGE.vViewSize.x = (int32_t)((float)PGE.vViewSize.y * wasp);
    }

    PGE.vViewPos.x = (PGE.vWindowSize.x - PGE.vViewSize.x) / 2;
    PGE.vViewPos.y = (PGE.vWindowSize.y - PGE.vViewSize.y) / 2;
}

void olc_PGE_ConstructFontSheet()
{
    // Thanks for the tip, MaGetzUb
    char* data = ""
        "?Q`0001oOch0o01o@F40o0<AGD4090LAGD<090@A7ch0?00O7Q`0600>00000000"
        "O000000nOT0063Qo4d8>?7a14Gno94AA4gno94AaOT0>o3`oO400o7QN00000400"
        "Of80001oOg<7O7moBGT7O7lABET024@aBEd714AiOdl717a_=TH013Q>00000000"
        "720D000V?V5oB3Q_HdUoE7a9@DdDE4A9@DmoE4A;Hg]oM4Aj8S4D84@`00000000"
        "OaPT1000Oa`^13P1@AI[?g`1@A=[OdAoHgljA4Ao?WlBA7l1710007l100000000"
        "ObM6000oOfMV?3QoBDD`O7a0BDDH@5A0BDD<@5A0BGeVO5ao@CQR?5Po00000000"
        "Oc``000?Ogij70PO2D]??0Ph2DUM@7i`2DTg@7lh2GUj?0TO0C1870T?00000000"
        "70<4001o?P<7?1QoHg43O;`h@GT0@:@LB@d0>:@hN@L0@?aoN@<0O7ao0000?000"
        "OcH0001SOglLA7mg24TnK7ln24US>0PL24U140PnOgl0>7QgOcH0K71S0000A000"
        "00H00000@Dm1S007@DUSg00?OdTnH7YhOfTL<7Yh@Cl0700?@Ah0300700000000"
        "<008001QL00ZA41a@6HnI<1i@FHLM81M@@0LG81?O`0nC?Y7?`0ZA7Y300080000"
        "O`082000Oh0827mo6>Hn?Wmo?6HnMb11MP08@C11H`08@FP0@@0004@000000000"
        "00P00001Oab00003OcKP0006@6=PMgl<@440MglH@000000`@000001P00000000"
        "Ob@8@@00Ob@8@Ga13R@8Mga172@8?PAo3R@827QoOb@820@0O`0007`0000007P0"
        "O`000P08Od400g`<3V=P0G`673IP0`@3>1`00P@6O`P00g`<O`000GP800000000"
        "?P9PL020O`<`N3R0@E4HC7b0@ET<ATB0@@l6C4B0O`H3N7b0?P01L3R000000020";

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

void olc_PGE_DestroyFontSheet()
{
    olc_Decal_Destroy(PGE.fontDecal);
    olc_Sprite_Destroy(PGE.fontSprite);
}

void olc_PGE_CoreUpdate()
{
    olc_CrossPlatform_GetTime(PGE.tp2);
    double duration = 1000.0 * PGE.tp2.tv_sec + 1e-6 * PGE.tp2.tv_nsec - (1000.0 * PGE.tp1.tv_sec + 1e-6 * PGE.tp1.tv_nsec);
    PGE.tp1 = PGE.tp2;


    float fElapsedTime = (float)(duration / 1000);
    PGE.fLastElapsed = fElapsedTime;

    olc_Platform_HandleSystemEvent();

    // INPUT WRANGLING
    for (int i = 0; i < 256; i++)
    {
        PGE.pKeyboardState[i].bPressed = false;
        PGE.pKeyboardState[i].bReleased = false;

        if (PGE.pKeyNewState[i] != !PGE.pKeyOldState[i])
        {
            if (PGE.pKeyNewState[i])
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

        if (i < olc_nMouseButtons)
        {
            PGE.pMouseState[i].bPressed = false;
            PGE.pMouseState[i].bReleased = false;

            if (PGE.pMouseNewState[i] != !PGE.pMouseOldState[i])
            {
                if (PGE.pMouseNewState[i])
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
    if (!PGE.OnUserUpdate(fElapsedTime))
        PGE.bActive = false;


    // Display Frame
    olc_Renderer_UpdateViewport(PGE.vViewPos, PGE.vViewSize);
    olc_Renderer_ClearBuffer(olc_BLACK, true);

    // Layer 0
    PGE.vLayers[0].bUpdate = true;
    PGE.vLayers[0].bShow = true;
    olc_Renderer_PrepareDrawing();

    for (int i = vector_size(PGE.vLayers) - 1; i >= 0; i--)
    {
        olc_LayerDesc* layer = &PGE.vLayers[i];
        if (layer->bShow)
        {
            if (layer->funcHook == NULL)
            {
                olc_Renderer_ApplyTexture(layer->nResID);
                if (layer->bUpdate)
                {
                    olc_Renderer_UpdateTexture(layer->nResID, layer->pDrawTarget);
                    layer->bUpdate = false;
                }

                olc_Renderer_DrawLayerQuad(layer->vOffset, layer->vScale, layer->tint);

                // Display Decals in order for this layer
                for (size_t j = 0; j < vector_size(layer->vecDecalInstance); j++)
                {
                    olc_Renderer_DrawDecalQuad(&layer->vecDecalInstance[j]);
                }

                // clear the instances
                vector_clear(layer->vecDecalInstance);
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
    if (PGE.fFrameTimer >= 1.0f)
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
    if (olc_Platform_CreateGraphics(PGE.bFullScreen, PGE.bEnableVSYNC, PGE.vViewPos, PGE.vViewSize) == olc_RCODE_FAIL) return;

    // Initialize Layer Vector
    PGE.vLayers = vector_init(olc_LayerDesc);

    // Create Primary Layer "0"
    PGE_CreateLayer();

    PGE.vLayers[0].bUpdate = true;
    PGE.vLayers[0].bShow = true;
    PGE_SetDrawTarget(NULL);

    // Construct default font sheet
    olc_PGE_ConstructFontSheet();
    olc_CrossPlatform_GetTime(PGE.tp1);
    olc_CrossPlatform_GetTime(PGE.tp2);
}

void olc_PGE_UpdateMouseState(int32_t button, bool state)
{
    PGE.pMouseNewState[button] = state;
}

void olc_PGE_UpdateKeyState(int32_t key, bool state)
{
    PGE.pKeyNewState[key] = state;
}

void olc_PGE_UpdateMouseFocus(bool state)
{
    PGE.bHasMouseFocus = state;
}

void olc_PGE_UpdateKeyFocus(bool state)
{
    PGE.bHasInputFocus = state;
}

void olc_PGE_Terminate()
{
    PGE.bActive = false;
}

// O------------------------------------------------------------------------------O
// | START RENDERER: OpenGL 1.0 (the original, the best...)                       |
// O------------------------------------------------------------------------------O
#if defined(OLC_GFX_OPENGL10)
glDeviceContext_t glDeviceContext = 0;
glRenderContext_t glRenderContext = 0;

void olc_Renderer_PrepareDevice()
{ }

int32_t olc_Renderer_CreateDevice(bool bFullScreen, bool bVSYNC)
{
#if defined(_WIN32)
    // Create Device Context
    glDeviceContext = GetDC(olc_hWnd);
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR), 1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        PFD_MAIN_PLANE, 0, 0, 0, 0
    };

    int pf = 0;
    if (!(pf = ChoosePixelFormat(glDeviceContext, &pfd))) return olc_RCODE_FAIL;
    SetPixelFormat(glDeviceContext, pf, &pfd);

    if (!(glRenderContext = wglCreateContext(glDeviceContext))) return olc_RCODE_FAIL;
    wglMakeCurrent(glDeviceContext, glRenderContext);

    // Remove Frame cap
    wglSwapInterval = (wglSwapInterval_t*)wglGetProcAddress("wglSwapIntervalEXT");
    if (wglSwapInterval && !bVSYNC) wglSwapInterval(0);
#endif

#if defined(__linux__) || defined(__FreeBSD__)
    glDeviceContext = glXCreateContext(olc_Display, olc_VisualInfo, NULL, GL_TRUE);
    glXMakeCurrent(olc_Display, olc_Window, glDeviceContext);

    XWindowAttributes gwa;
    XGetWindowAttributes(olc_Display, olc_Window, &gwa);
    glViewport(0, 0, gwa.width, gwa.height);

    glSwapIntervalEXT = NULL;
    glSwapIntervalEXT = (glSwapInterval_t*)glXGetProcAddress((unsigned char*)"glXSwapIntervalEXT");

    if (glSwapIntervalEXT == NULL && !bVSYNC)
    {
        printf("NOTE: Could not disable VSYNC, glXSwapIntervalEXT() was not found!\n");
        printf("      Don't worry though, things will still work, it's just the\n");
        printf("      frame rate will be capped to your monitors refresh rate - javidx9\n");
    }

    if (glSwapIntervalEXT != NULL && !bVSYNC)
        glSwapIntervalEXT(olc_Display, olc_Window, 0);
#endif		

    glEnable(GL_TEXTURE_2D); // Turn on texturing
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    return olc_RCODE_OK;
}

int32_t olc_Renderer_DestroyDevice()
{
#if defined(_WIN32)
    wglDeleteContext(glRenderContext);
#endif

#if defined(__linux__) || defined(__FreeBSD__)
    glXMakeCurrent(olc_Display, None, NULL);
    glXDestroyContext(olc_Display, glDeviceContext);
#endif
    return olc_RCODE_OK;
}

void olc_Renderer_DisplayFrame()
{
#if defined(_WIN32)
    SwapBuffers(glDeviceContext);
#endif	

#if defined(__linux__) || defined(__FreeBSD__)
    glXSwapBuffers(olc_Display, olc_Window);
#endif		
}

void olc_Renderer_PrepareDrawing()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void olc_Renderer_DrawLayerQuad(olc_vf2d offset, olc_vf2d scale, const olc_Pixel tint)
{
    glBegin(GL_QUADS);
    glColor4ub(tint.r, tint.g, tint.b, tint.a);
    glTexCoord2f(0.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
    glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
    glTexCoord2f(0.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
    glVertex3f(-1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
    glTexCoord2f(1.0f * scale.x + offset.x, 0.0f * scale.y + offset.y);
    glVertex3f(1.0f /*+ vSubPixelOffset.x*/, 1.0f /*+ vSubPixelOffset.y*/, 0.0f);
    glTexCoord2f(1.0f * scale.x + offset.x, 1.0f * scale.y + offset.y);
    glVertex3f(1.0f /*+ vSubPixelOffset.x*/, -1.0f /*+ vSubPixelOffset.y*/, 0.0f);
    glEnd();
}

void olc_Renderer_DrawDecalQuad(olc_DecalInstance* decal)
{
    if (decal->decal == NULL)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glBegin(GL_QUADS);
        glColor4ub(decal->tint[0].r, decal->tint[0].g, decal->tint[0].b, decal->tint[0].a);
        glTexCoord4f(decal->uv[0].x, decal->uv[0].y, 0.0f, decal->w[0]); glVertex2f(decal->pos[0].x, decal->pos[0].y);
        glColor4ub(decal->tint[1].r, decal->tint[1].g, decal->tint[1].b, decal->tint[1].a);
        glTexCoord4f(decal->uv[1].x, decal->uv[1].y, 0.0f, decal->w[1]); glVertex2f(decal->pos[1].x, decal->pos[1].y);
        glColor4ub(decal->tint[2].r, decal->tint[2].g, decal->tint[2].b, decal->tint[2].a);
        glTexCoord4f(decal->uv[2].x, decal->uv[2].y, 0.0f, decal->w[2]); glVertex2f(decal->pos[2].x, decal->pos[2].y);
        glColor4ub(decal->tint[3].r, decal->tint[3].g, decal->tint[3].b, decal->tint[3].a);
        glTexCoord4f(decal->uv[3].x, decal->uv[3].y, 0.0f, decal->w[3]); glVertex2f(decal->pos[3].x, decal->pos[3].y);
        glEnd();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, decal->decal->id);
        glBegin(GL_QUADS);
        glColor4ub(decal->tint[0].r, decal->tint[0].g, decal->tint[0].b, decal->tint[0].a);
        glTexCoord4f(decal->uv[0].x, decal->uv[0].y, 0.0f, decal->w[0]); glVertex2f(decal->pos[0].x, decal->pos[0].y);
        glTexCoord4f(decal->uv[1].x, decal->uv[1].y, 0.0f, decal->w[1]); glVertex2f(decal->pos[1].x, decal->pos[1].y);
        glTexCoord4f(decal->uv[2].x, decal->uv[2].y, 0.0f, decal->w[2]); glVertex2f(decal->pos[2].x, decal->pos[2].y);
        glTexCoord4f(decal->uv[3].x, decal->uv[3].y, 0.0f, decal->w[3]); glVertex2f(decal->pos[3].x, decal->pos[3].y);
        glEnd();
    }
}

uint32_t olc_Renderer_CreateTexture(const uint32_t width, const uint32_t height)
{
    uint32_t id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    return id;
}

void olc_Renderer_UpdateTexture(uint32_t id, olc_Sprite* spr)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spr->width, spr->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, olc_Sprite_GetData(spr));
}

uint32_t olc_Renderer_DeleteTexture(const uint32_t id)
{
    glDeleteTextures(1, &id);
    return id;
}

void olc_Renderer_ApplyTexture(uint32_t id)
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void olc_Renderer_UpdateViewport(const olc_vi2d pos, const olc_vi2d size)
{
    glViewport(pos.x, pos.y, size.x, size.y);
}

void olc_Renderer_ClearBuffer(olc_Pixel p, bool bDepth)
{
    glClearColor((float)p.r / 255.0f, (float)p.g / 255.0f, (float)p.b / 255.0f, (float)p.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (bDepth) glClear(GL_DEPTH_BUFFER_BIT);
}
#endif
// O------------------------------------------------------------------------------O
// | END RENDERER: OpenGL 1.0 (the original, the best...)                         |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                        |
// O------------------------------------------------------------------------------O
#if defined(_WIN32)
#if !defined(__MINGW32__)
#pragma comment(lib, "user32.lib")		// Visual Studio Only
#pragma comment(lib, "gdi32.lib")		// For other Windows Compilers please add
#pragma comment(lib, "opengl32.lib")	// these libs to your linker input
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Shlwapi.lib")
#else
    // In Code::Blocks
#if !defined(_WIN32_WINNT)
#ifdef HAVE_MSMF
#define _WIN32_WINNT 0x0600 // Windows Vista
#else
#define _WIN32_WINNT 0x0500 // Windows 2000
#endif
#endif
#endif

// Little utility function to convert from char to wchar in Windows environments
// depending upon how the compiler is configured. This should not be necessary
// on linux platforms
wchar_t* ConvertS2W(const char* s)
{
#ifdef __MINGW32__
    wchar_t *buffer = (wchar_t*)calloc(sizeof(wchar_t), strlen(s) + 1);
    mbstowcs(buffer, s, strlen(s));
    buffer[strlen(s)] = L'\0';
#else
    int count = MultiByteToWideChar(CP_UTF8, 0, s, -1, NULL, 0);
    wchar_t* buffer = (wchar_t*)calloc(sizeof(wchar_t), strlen(s) + 1);
    MultiByteToWideChar(CP_UTF8, 0, s, -1, buffer, count);
#endif
    return buffer;
}

int32_t olc_Platform_ApplicationStartUp()
{

    GDI_INPUT.GdiplusVersion = 1;
    GDI_INPUT.DebugEventCallback = NULL;
    GDI_INPUT.SuppressBackgroundThread = false;
    GDI_INPUT.SuppressExternalCodecs = false;

    int32_t status = GdiplusStartup(&GDI_TOKEN, &GDI_INPUT, NULL);
    if (status == 0)
        return olc_RCODE_OK;

    return olc_RCODE_FAIL;
}

int32_t olc_Platform_ApplicationCleanUp()
{
    GdiplusShutdown(GDI_TOKEN);
    return olc_RCODE_OK;
}

int32_t olc_Platform_ThreadStartUp()
{
    return olc_RCODE_OK;
}

int32_t olc_Platform_ThreadCleanUp()
{
    olc_Renderer_DestroyDevice();
    DestroyCursor(olc_InvisibleCursor);
    PostMessage(olc_hWnd, WM_DESTROY, 0, 0);
    return olc_RCODE_OK;
}

int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize)
{
    if (olc_Renderer_CreateDevice(bFullScreen, bEnableVSYNC) == olc_RCODE_OK)
    {
        olc_Renderer_UpdateViewport(vViewPos, vViewSize);
        return olc_RCODE_OK;
    }
    else
        return olc_RCODE_FAIL;
}

// Windows Event Handler - this is statically connected to the windows event system
LRESULT CALLBACK olc_Platform_WindowEvent(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_MOUSEMOVE:
    {
        // Thanks @ForAbby (Discord)
        uint16_t x = lParam & 0xFFFF; uint16_t y = (lParam >> 16) & 0xFFFF;
        int16_t ix = *(int16_t*)&x;   int16_t iy = *(int16_t*)&y;
        olc_PGE_UpdateMouse(ix, iy);
        return 0;
    }
    case WM_SIZE:       olc_PGE_UpdateWindowSize(lParam & 0xFFFF, (lParam >> 16) & 0xFFFF);	                return 0;
    case WM_MOUSEWHEEL:	olc_PGE_UpdateMouseWheel(GET_WHEEL_DELTA_WPARAM(wParam));                           return 0;
    case WM_MOUSELEAVE: olc_PGE_UpdateMouseFocus(false);                                                    return 0;
    case WM_SETFOCUS:	olc_PGE_UpdateKeyFocus(true);                                                       return 0;
    case WM_KILLFOCUS:	olc_PGE_UpdateKeyFocus(false);                                                      return 0;
    case WM_KEYDOWN:	olc_PGE_UpdateKeyState(inputmap_get(wParam), true);                                 return 0;
    case WM_KEYUP:		olc_PGE_UpdateKeyState(inputmap_get(wParam), false);                                return 0;
    case WM_LBUTTONDOWN:olc_PGE_UpdateMouseState(0, true);                                                  return 0;
    case WM_LBUTTONUP:	olc_PGE_UpdateMouseState(0, false);                                                 return 0;
    case WM_RBUTTONDOWN:olc_PGE_UpdateMouseState(1, true);                                                  return 0;
    case WM_RBUTTONUP:	olc_PGE_UpdateMouseState(1, false);                                                 return 0;
    case WM_MBUTTONDOWN:olc_PGE_UpdateMouseState(2, true);                                                  return 0;
    case WM_MBUTTONUP:	olc_PGE_UpdateMouseState(2, false);                                                 return 0;
    case WM_CLOSE:		olc_PGE_Terminate();                                                                return 0;
    case WM_DESTROY:	PostQuitMessage(0);                                                                 return 0;
    case WM_SETCURSOR:  SetCursor(PGE_IsMouseCursorVisible() ? olc_ArrowCursor : olc_InvisibleCursor); return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen)
{
    WNDCLASS wc;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpfnWndProc = olc_Platform_WindowEvent;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.lpszMenuName = NULL;
    wc.hbrBackground = NULL;
    wc.lpszClassName = olcT("OLC_PIXEL_GAME_ENGINE");
    RegisterClass(&wc);

    // Define window furniture
    DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

    olc_vi2d vTopLeft = vWindowPos;

    // Handle Fullscreen
    if (bFullScreen)
    {
        dwExStyle = 0;
        dwStyle = WS_VISIBLE | WS_POPUP;
        HMONITOR hmon = MonitorFromWindow(olc_hWnd, MONITOR_DEFAULTTONEAREST);
        MONITORINFO mi = { sizeof(mi) };
        if (!GetMonitorInfo(hmon, &mi)) return olc_RCODE_FAIL;
        vWindowSize = olc_VI2D(mi.rcMonitor.right, mi.rcMonitor.bottom);
        vTopLeft.x = 0;
        vTopLeft.y = 0;
    }

    // Keep client size as requested
    RECT rWndRect = { 0, 0, vWindowSize.x, vWindowSize.y };
    AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
    int width = rWndRect.right - rWndRect.left;
    int height = rWndRect.bottom - rWndRect.top;

    olc_hWnd = CreateWindowEx(dwExStyle, olcT("OLC_PIXEL_GAME_ENGINE"), olcT(""), dwStyle,
        vTopLeft.x, vTopLeft.y, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);

    // Create Keyboard Mapping
    inputmap_init();

    inputmap_set(0x00, olc_NONE); inputmap_set(0x41, olc_A); inputmap_set(0x42, olc_B);
    inputmap_set(0x43, olc_C); inputmap_set(0x44, olc_D); inputmap_set(0x45, olc_E);
    inputmap_set(0x46, olc_F); inputmap_set(0x47, olc_G); inputmap_set(0x48, olc_H);
    inputmap_set(0x49, olc_I); inputmap_set(0x4A, olc_J); inputmap_set(0x4B, olc_K);
    inputmap_set(0x4C, olc_L); inputmap_set(0x4D, olc_M); inputmap_set(0x4E, olc_N);
    inputmap_set(0x4F, olc_O); inputmap_set(0x50, olc_P); inputmap_set(0x51, olc_Q);
    inputmap_set(0x52, olc_R); inputmap_set(0x53, olc_S); inputmap_set(0x54, olc_T);
    inputmap_set(0x55, olc_U); inputmap_set(0x56, olc_V); inputmap_set(0x57, olc_W);
    inputmap_set(0x58, olc_X); inputmap_set(0x59, olc_Y); inputmap_set(0x5A, olc_Z);

    inputmap_set(VK_F1, olc_F1); inputmap_set(VK_F2, olc_F2); inputmap_set(VK_F3, olc_F3); inputmap_set(VK_F4, olc_F4);
    inputmap_set(VK_F5, olc_F5); inputmap_set(VK_F6, olc_F6); inputmap_set(VK_F7, olc_F7); inputmap_set(VK_F8, olc_F8);
    inputmap_set(VK_F9, olc_F9); inputmap_set(VK_F10, olc_F10); inputmap_set(VK_F11, olc_F11); inputmap_set(VK_F12, olc_F12);

    inputmap_set(VK_DOWN, olc_DOWN); inputmap_set(VK_LEFT, olc_LEFT); inputmap_set(VK_RIGHT, olc_RIGHT); inputmap_set(VK_UP, olc_UP);
    inputmap_set(VK_RETURN, olc_ENTER); //inputmap_set(VK_RETURN, olc_RETURN);

    inputmap_set(VK_BACK, olc_BACK); inputmap_set(VK_ESCAPE, olc_ESCAPE); inputmap_set(VK_RETURN, olc_ENTER); inputmap_set(VK_PAUSE, olc_PAUSE);
    inputmap_set(VK_SCROLL, olc_SCROLL); inputmap_set(VK_TAB, olc_TAB); inputmap_set(VK_DELETE, olc_DEL); inputmap_set(VK_HOME, olc_HOME);
    inputmap_set(VK_END, olc_END); inputmap_set(VK_PRIOR, olc_PGUP); inputmap_set(VK_NEXT, olc_PGDN); inputmap_set(VK_INSERT, olc_INS);
    inputmap_set(VK_SHIFT, olc_SHIFT); inputmap_set(VK_CONTROL, olc_CTRL);
    inputmap_set(VK_SPACE, olc_SPACE);

    inputmap_set(0x30, olc_K0); inputmap_set(0x31, olc_K1); inputmap_set(0x32, olc_K2); inputmap_set(0x33, olc_K3); inputmap_set(0x34, olc_K4);
    inputmap_set(0x35, olc_K5); inputmap_set(0x36, olc_K6); inputmap_set(0x37, olc_K7); inputmap_set(0x38, olc_K8); inputmap_set(0x39, olc_K9);

    inputmap_set(VK_NUMPAD0, olc_NP0); inputmap_set(VK_NUMPAD1, olc_NP1); inputmap_set(VK_NUMPAD2, olc_NP2); inputmap_set(VK_NUMPAD3, olc_NP3); inputmap_set(VK_NUMPAD4, olc_NP4);
    inputmap_set(VK_NUMPAD5, olc_NP5); inputmap_set(VK_NUMPAD6, olc_NP6); inputmap_set(VK_NUMPAD7, olc_NP7); inputmap_set(VK_NUMPAD8, olc_NP8); inputmap_set(VK_NUMPAD9, olc_NP9);
    inputmap_set(VK_MULTIPLY, olc_NP_MUL); inputmap_set(VK_ADD, olc_NP_ADD); inputmap_set(VK_DIVIDE, olc_NP_DIV); inputmap_set(VK_SUBTRACT, olc_NP_SUB); inputmap_set(VK_DECIMAL, olc_NP_DECIMAL);

    BYTE cursorAndMask[128];
    BYTE cursorXorMask[128];
    for (int i = 0; i < 128; i++)
    {
        cursorAndMask[i] = 0xff;
        cursorXorMask[i] = 0x00;
    }

    // create Arrow Mouse Cursor
    olc_ArrowCursor = LoadCursor(NULL, IDC_ARROW);

    // create Invisible Mouse Cursor
    olc_InvisibleCursor = CreateCursor(wc.hInstance, 0 /* hotspot x */, 0 /* hostpot y */,
        32 /* width */, 32 /* height */, cursorAndMask, cursorXorMask);

    return olc_RCODE_OK;
}

int32_t olc_Platform_SetWindowTitle(const char* s)
{
    #ifdef UNICODE
        wchar_t* w = ConvertS2W(s);
        SetWindowText(olc_hWnd, w);
        free(w);
    #else
        SetWindowText(olc_hWnd, s);
    #endif

    return olc_RCODE_OK;
}

int32_t olc_Platform_StartSystemEventLoop()
{
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return olc_RCODE_OK;
}

int32_t olc_Platform_HandleSystemEvent()
{
    return olc_RCODE_FAIL;
}

// On Windows load images using GDI+ library
olc_Sprite* olc_Sprite_LoadFromFile(const char* sImageFile)
{
    void* bmp = NULL;

    wchar_t* wc = ConvertS2W(sImageFile);

    // Load sprite from file
    if(GdipLoadImageFromFile(wc, &bmp) != 0)
    {
        printf("Error loading sprite: %s\n", sImageFile);
        exit(EXIT_FAILURE);
    }
    
    // we're done with the wchar
    free(wc);
    
    float width = 0;
    float height = 0;

    // get the width/height of the sprite
    GdipGetImageDimension(bmp, &width, &height);

    // create a blank sprite
    olc_Sprite* sprite = olc_Sprite_Create((int)width, (int)height);

    for (int y = 0; y < (int)height; y++)
        for (int x = 0; x < (int)width; x++)
        {
            olc_Pixel p;
            uint32_t gPixel = 0;

            GdipBitmapGetPixel(bmp, x, y, &gPixel);

            // red
            p.r = (gPixel & 0x00ff0000) >> 16;

            // green
            p.g = (gPixel & 0x0000ff00) >> 8;

            // blue
            p.b = (gPixel & 0x000000ff);

            // alpha
            p.a = (gPixel & 0xff000000) >> 24;

            if (p.a == 0)
                p = olc_BLANK;

            olc_Sprite_SetPixel(sprite, x, y, p);
        }

    GdipDisposeImage(bmp);

    return sprite;
}

#endif
// O------------------------------------------------------------------------------O
// | END PLATFORM: MICROSOFT WINDOWS XP, VISTA, 7, 8, 10                          |
// O------------------------------------------------------------------------------O

// O------------------------------------------------------------------------------O
// | START PLATFORM: LINUX Implemenations                                         |
// O------------------------------------------------------------------------------O
#if defined(__linux__) || defined(__FreeBSD__) 

int32_t olc_Platform_ApplicationStartUp()
{
    return olc_RCODE_OK;
}

int32_t olc_Platform_ApplicationCleanUp()
{
    for (size_t i = 0; i < vector_size(PGE.vLayers); i++)
        vector_destroy(PGE.vLayers[i].vecDecalInstance);

    vector_destroy(PGE.vLayers);

    olc_PGE_DestroyFontSheet();
    olc_Sprite_Destroy(PGE.pDrawTarget);
    free(PGE.sAppName);

    XFreeCursor(olc_Display, olc_ArrowCursor);
    XFreeCursor(olc_Display, olc_InvisibleCursor);
    XFreePixmap(olc_Display, olc_BitmapNoData);

    XDestroyWindow(olc_Display, olc_Window);
    XCloseDisplay(olc_Display);
    return olc_RCODE_OK;
}

int32_t olc_Platform_ThreadStartUp()
{
    return olc_RCODE_OK;
}

int32_t olc_Platform_ThreadCleanUp()
{
    olc_Renderer_DestroyDevice();
    return olc_RCODE_OK;
}

int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize)
{

    if (olc_Renderer_CreateDevice(bFullScreen, bEnableVSYNC) == olc_RCODE_OK)
    {
        olc_Renderer_UpdateViewport(vViewPos, vViewSize);
        return olc_RCODE_OK;
    }
    else
        return olc_RCODE_FAIL;
}

int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen)
{
    XInitThreads();

    olc_Display = XOpenDisplay(NULL);
    olc_WindowRoot = DefaultRootWindow(olc_Display);

    // Based on the display capabilities, configure the appearance of the window
    GLint olc_GLAttribs[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    olc_VisualInfo = glXChooseVisual(olc_Display, 0, olc_GLAttribs);
    olc_ColourMap = XCreateColormap(olc_Display, olc_WindowRoot, olc_VisualInfo->visual, AllocNone);
    olc_SetWindowAttribs.colormap = olc_ColourMap;

    // Register which events we are interested in receiving
    olc_SetWindowAttribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
        ButtonPressMask | ButtonReleaseMask | PointerMotionMask | FocusChangeMask | StructureNotifyMask;

    // Create the window
    olc_Window = XCreateWindow(olc_Display, olc_WindowRoot, vWindowPos.x, vWindowPos.y,
        vWindowSize.x, vWindowSize.y,
        0, olc_VisualInfo->depth, InputOutput, olc_VisualInfo->visual,
        CWColormap | CWEventMask, &olc_SetWindowAttribs);

    Atom wmDelete = XInternAtom(olc_Display, "WM_DELETE_WINDOW", true);
    XSetWMProtocols(olc_Display, olc_Window, &wmDelete, 1);

    XMapWindow(olc_Display, olc_Window);
    XStoreName(olc_Display, olc_Window, "OneLoneCoder.com - Pixel Game Engine");

    // create mouse cursors
    char noData[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

    olc_BlackColor.red = 0;
    olc_BlackColor.green = 0;
    olc_BlackColor.blue = 0;

    olc_BitmapNoData = XCreateBitmapFromData(olc_Display, olc_Window,
        noData, 8, 8);

    olc_ArrowCursor = XCreateFontCursor(olc_Display, XC_left_ptr);
    olc_InvisibleCursor = XCreatePixmapCursor(olc_Display, olc_BitmapNoData,
        olc_BitmapNoData, &olc_BlackColor, &olc_BlackColor, 0, 0);

    if (bFullScreen) // Thanks DragonEye, again :D
    {
        Atom wm_state;
        Atom fullscreen;
        wm_state = XInternAtom(olc_Display, "_NET_WM_STATE", False);
        fullscreen = XInternAtom(olc_Display, "_NET_WM_STATE_FULLSCREEN", False);
        // maybe a problem0
        XEvent xev = { 0 };
        xev.type = ClientMessage;
        xev.xclient.window = olc_Window;
        xev.xclient.message_type = wm_state;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = (bFullScreen ? 1 : 0);   // the action (0: off, 1: on, 2: toggle)
        xev.xclient.data.l[1] = fullscreen;             // first property to alter
        xev.xclient.data.l[2] = 0;                      // second property to alter
        xev.xclient.data.l[3] = 0;                      // source indication
        XMapWindow(olc_Display, olc_Window);
        XSendEvent(olc_Display, DefaultRootWindow(olc_Display), False,
            SubstructureRedirectMask | SubstructureNotifyMask, &xev);
        XFlush(olc_Display);
        XWindowAttributes gwa;
        XGetWindowAttributes(olc_Display, olc_Window, &gwa);
        vWindowSize.x = gwa.width;
        vWindowSize.y = gwa.height;
    }

    inputmap_init();

    inputmap_set(0x00, olc_NONE); inputmap_set(0x61, olc_A); inputmap_set(0x62, olc_B);
    inputmap_set(0x63, olc_C); inputmap_set(0x64, olc_D); inputmap_set(0x65, olc_E);
    inputmap_set(0x66, olc_F); inputmap_set(0x67, olc_G); inputmap_set(0x68, olc_H);
    inputmap_set(0x69, olc_I); inputmap_set(0x6A, olc_J); inputmap_set(0x6B, olc_K);
    inputmap_set(0x6C, olc_L); inputmap_set(0x6D, olc_M); inputmap_set(0x6E, olc_N);
    inputmap_set(0x6F, olc_O); inputmap_set(0x70, olc_P); inputmap_set(0x71, olc_Q);
    inputmap_set(0x72, olc_R); inputmap_set(0x73, olc_S); inputmap_set(0x74, olc_T);
    inputmap_set(0x75, olc_U); inputmap_set(0x76, olc_V); inputmap_set(0x77, olc_W);
    inputmap_set(0x78, olc_X); inputmap_set(0x79, olc_Y); inputmap_set(0x7A, olc_Z);

    inputmap_set(XK_F1, olc_F1); inputmap_set(XK_F2, olc_F2); inputmap_set(XK_F3, olc_F3);
    inputmap_set(XK_F4, olc_F4); inputmap_set(XK_F5, olc_F5); inputmap_set(XK_F6, olc_F6);
    inputmap_set(XK_F7, olc_F7); inputmap_set(XK_F8, olc_F8); inputmap_set(XK_F9, olc_F9);
    inputmap_set(XK_F10, olc_F10); inputmap_set(XK_F11, olc_F11); inputmap_set(XK_F12, olc_F12);

    inputmap_set(XK_Down, olc_DOWN); inputmap_set(XK_Left, olc_LEFT); inputmap_set(XK_Right, olc_RIGHT);
    inputmap_set(XK_Up, olc_UP); inputmap_set(XK_KP_Enter, olc_ENTER); inputmap_set(XK_Return, olc_ENTER);

    inputmap_set(XK_BackSpace, olc_BACK); inputmap_set(XK_Escape, olc_ESCAPE); inputmap_set(XK_Linefeed, olc_ENTER);
    inputmap_set(XK_Pause, olc_PAUSE); inputmap_set(XK_Scroll_Lock, olc_SCROLL); inputmap_set(XK_Tab, olc_TAB);
    inputmap_set(XK_Delete, olc_DEL); inputmap_set(XK_Home, olc_HOME); inputmap_set(XK_End, olc_END);
    inputmap_set(XK_Page_Up, olc_PGUP); inputmap_set(XK_Page_Down, olc_PGDN); inputmap_set(XK_Insert, olc_INS);
    inputmap_set(XK_Shift_L, olc_SHIFT); inputmap_set(XK_Shift_R, olc_SHIFT); inputmap_set(XK_Control_L, olc_CTRL);
    inputmap_set(XK_Control_R, olc_CTRL); inputmap_set(XK_space, olc_SPACE); inputmap_set(XK_period, olc_PERIOD);

    inputmap_set(XK_0, olc_K0); inputmap_set(XK_1, olc_K1); inputmap_set(XK_2, olc_K2);
    inputmap_set(XK_3, olc_K3); inputmap_set(XK_4, olc_K4); inputmap_set(XK_5, olc_K5);
    inputmap_set(XK_6, olc_K6); inputmap_set(XK_7, olc_K7); inputmap_set(XK_8, olc_K8);
    inputmap_set(XK_9, olc_K9);

    inputmap_set(XK_KP_0, olc_NP0); inputmap_set(XK_KP_1, olc_NP1); inputmap_set(XK_KP_2, olc_NP2);
    inputmap_set(XK_KP_3, olc_NP3); inputmap_set(XK_KP_4, olc_NP4); inputmap_set(XK_KP_5, olc_NP5);
    inputmap_set(XK_KP_6, olc_NP6); inputmap_set(XK_KP_7, olc_NP7); inputmap_set(XK_KP_8, olc_NP8);
    inputmap_set(XK_KP_9, olc_NP9);

    inputmap_set(XK_KP_Multiply, olc_NP_MUL); inputmap_set(XK_KP_Add, olc_NP_ADD);
    inputmap_set(XK_KP_Divide, olc_NP_DIV); inputmap_set(XK_KP_Subtract, olc_NP_SUB);
    inputmap_set(XK_KP_Decimal, olc_NP_DECIMAL);

    return olc_RCODE_OK;
}

int32_t olc_Platform_SetWindowTitle(const char* s)
{
    XStoreName(olc_Display, olc_Window, s);
    return olc_RCODE_OK;
}

int32_t olc_Platform_StartSystemEventLoop()
{
    return olc_RCODE_OK;
}


int32_t olc_Platform_HandleSystemEvent()
{
    if (PGE_IsMouseCursorVisible())
        XDefineCursor(olc_Display, olc_Window, olc_ArrowCursor);
    else
        XDefineCursor(olc_Display, olc_Window, olc_InvisibleCursor);

    XEvent xev;
    while (XPending(olc_Display))
    {
        XNextEvent(olc_Display, &xev);
        if (xev.type == Expose)
        {
            XWindowAttributes gwa;
            XGetWindowAttributes(olc_Display, olc_Window, &gwa);
            olc_PGE_UpdateWindowSize(gwa.width, gwa.height);
        }
        else if (xev.type == ConfigureNotify)
        {
            XConfigureEvent xce = xev.xconfigure;
            olc_PGE_UpdateWindowSize(xce.width, xce.height);
        }
        else if (xev.type == KeyPress)
        {
            KeySym sym = XLookupKeysym(&xev.xkey, 0);
            olc_PGE_UpdateKeyState(inputmap_get(sym), true);
            XKeyEvent* e = (XKeyEvent*)&xev; // Because DragonEye loves numpads
            XLookupString(e, NULL, 0, &sym, NULL);
            olc_PGE_UpdateKeyState(inputmap_get(sym), true);
        }
        else if (xev.type == KeyRelease)
        {
            KeySym sym = XLookupKeysym(&xev.xkey, 0);
            olc_PGE_UpdateKeyState(inputmap_get(sym), false);
            XKeyEvent* e = (XKeyEvent*)&xev;
            XLookupString(e, NULL, 0, &sym, NULL);
            olc_PGE_UpdateKeyState(inputmap_get(sym), false);
        }
        else if (xev.type == ButtonPress)
        {
            switch (xev.xbutton.button)
            {
            case 1:	olc_PGE_UpdateMouseState(0, true); break;
            case 2:	olc_PGE_UpdateMouseState(2, true); break;
            case 3:	olc_PGE_UpdateMouseState(1, true); break;
            case 4:	olc_PGE_UpdateMouseWheel(120); break;
            case 5:	olc_PGE_UpdateMouseWheel(-120); break;
            default: break;
            }
        }
        else if (xev.type == ButtonRelease)
        {
            switch (xev.xbutton.button)
            {
            case 1:	olc_PGE_UpdateMouseState(0, false); break;
            case 2:	olc_PGE_UpdateMouseState(2, false); break;
            case 3:	olc_PGE_UpdateMouseState(1, false); break;
            default: break;
            }
        }
        else if (xev.type == MotionNotify)
        {
            olc_PGE_UpdateMouse(xev.xmotion.x, xev.xmotion.y);
        }
        else if (xev.type == FocusIn)
        {
            olc_PGE_UpdateKeyFocus(true);
        }
        else if (xev.type == FocusOut)
        {
            olc_PGE_UpdateKeyFocus(false);
        }
        else if (xev.type == ClientMessage)
        {
            olc_PGE_Terminate();
        }
    }

    return olc_RCODE_OK;
}

#define PNG_FAIL { fprintf(stderr, "Error loading png: %s\n", sFilename); exit(EXIT_FAILURE); return NULL; }

olc_Sprite* olc_Sprite_LoadFromFile(const char* sFilename)
{
    ////////////////////////////////////////////////////////////////////////////
    // Use libpng, Thanks to Guillaume Cottenceau
    // https://gist.github.com/niw/5963798

    // Also reading png from streams
    // http://www.piko3d.net/tutorials/libpng-tutorial-loading-png-files-from-streams/

    FILE* f = fopen(sFilename, "rb");
    if (f == NULL)
    {
        fprintf(stderr, "Error loading png: %s\n", sFilename);
        exit(EXIT_FAILURE);
    }

    png_structp png;
    png_infop info;

    png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) PNG_FAIL

        info = png_create_info_struct(png);
    if (!info) PNG_FAIL

        if (setjmp(png_jmpbuf(png))) PNG_FAIL

            png_init_io(png, f);
    png_read_info(png, info);
    png_byte color_type;
    png_byte bit_depth;
    png_bytep* row_pointers;

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth = png_get_bit_depth(png, info);
    if (bit_depth == 16) png_set_strip_16(png);
    if (color_type == PNG_COLOR_TYPE_PALETTE) png_set_palette_to_rgb(png);
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)	png_set_expand_gray_1_2_4_to_8(png);
    if (png_get_valid(png, info, PNG_INFO_tRNS)) png_set_tRNS_to_alpha(png);
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);
    png_read_update_info(png, info);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
    }
    png_read_image(png, row_pointers);
    ////////////////////////////////////////////////////////////////////////////
    // Create sprite array
    olc_Sprite* sprite = olc_Sprite_Create(width, height);

    // Iterate through image rows, converting into sprite format
    for (int y = 0; y < height; y++)
    {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++)
        {
            png_bytep px = &(row[x * 4]);
            olc_Pixel p = olc_PixelRGBA(px[0], px[1], px[2], px[3]);

            if (p.a == 0)
                p = olc_BLANK;

            olc_Sprite_SetPixel(sprite, x, y, p);
        }
    }

    for (int y = 0; y < height; y++) // Thanks maksym33
        free(row_pointers[y]);
    free(row_pointers);
    png_destroy_read_struct(&png, &info, NULL);

    fclose(f);

    return sprite;
}

#endif 
// O------------------------------------------------------------------------------O
// | END PLATFORM: LINUX                                                          |
// O------------------------------------------------------------------------------O

#endif // End OLC_PGE_APPLICATION

// O------------------------------------------------------------------------------O
// | END OF OLC_PGE_APPLICATION                                                   |
// O------------------------------------------------------------------------------O
