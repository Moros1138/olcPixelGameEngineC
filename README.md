# olcPixelGameEngine (For C)

This is an **"IN PROGRESS"** repository that exists for the sole purpose of tracking my progress as time goes on.
### Current Status (NOT WORKING)

Anything in here that is not commented out has been implemented. 
```c
// Pixels

olc_Pixel olc_PixelDefault();
olc_Pixel olc_PixelRAW(uint32_t p);
olc_Pixel olc_PixelRGB(uint8_t red, uint8_t green, uint8_t blue);
olc_Pixel olc_PixelRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
olc_Pixel olc_PixelF(float red, float green, float blue, float alpha);
bool      olc_PixelCompare(olc_Pixel a, olc_Pixel b);
void olc_PixelColourInit();


typedef struct Sprite
{
    int32_t width;
    int32_t height;
    uint32_t* pixels;
    uint32_t modeSample;
} olc_Sprite;

olc_Sprite* olc_SpriteCreate(int32_t w, int32_t h);
olc_Sprite* olc_SpriteLoad(const char *sImageFile);
void        olc_SpriteDestroy(olc_Sprite* sprite);

// TODO
// olc_Sprite* olc_SpriteLoadFromFile(const char *sImageFile);
// olc_Sprite* olc_SpriteLoadFromPGESprFile(const char *sImageFile);
// int32_t   olc_SpriteSaveToPGESprFile(olc_Sprite* sprite, const char *sImageFile);

void      olc_Sprite_SetSampleMode(olc_Sprite* sprite, uint32_t mode);
olc_Pixel olc_Sprite_GetPixel(olc_Sprite* sprite, int32_t x, int32_t y);
bool      olc_Sprite_SetPixel(olc_Sprite* sprite, int32_t x, int32_t y, olc_Pixel p);
olc_Pixel olc_Sprite_Sample(olc_Sprite* sprite, float x, float y);
olc_Pixel olc_Sprite_SampleBL(olc_Sprite* sprite, float u, float v);
uint32_t* olc_Sprite_GetData(olc_Sprite* sprite);

olc_Decal* olc_DecalCreate(olc_Sprite* sprite);
void       olc_DecalDestroy(olc_Decal* decal);
void       olc_DecalUpdate(olc_Decal* decal);

// TODO
// olc_Renderable* olc_RenderableCreate(uint32_t width, uint32_t height);
// olc_Renderable* olc_RenderableLoad(const char* sFile);
// olc_Sprite*     olc_RenderableGetSprite(olc_Renderable* renderable);
// olc_Decal*      olc_RenderableGetDecal(olc_Renderable* renderable);


// TODO
// int32_t Construct(int32_t screen_w, int32_t screen_h, int32_t pixel_w, int32_t pixel_h,
//     bool full_screen, bool vsync);
// int32_t Start(bool (*create)(), bool (*update)(float), bool (*destroy)());


// Hardware Interfaces
bool IsFocused();
olc_HWButton GetKey(uint8_t k);
olc_HWButton GetMouse(uint32_t b);
int32_t GetMouseX();
int32_t GetMouseY();
int32_t GetMouseWheel();
olc_vi2d GetWindowMouse();


// Utility
int32_t ScreenWidth();
int32_t ScreenHeight();
int32_t GetDrawTargetWidth();
int32_t GetDrawTargetHeight();
olc_Sprite* GetDrawTarget();
void SetScreenSize(int w, int h);
void SetDrawTarget(olc_Sprite *target);
uint32_t GetFPS();
const float GetElapsedTime();
const olc_vi2d GetWindowSize();
bool IsMouseCursorVisible();


// CONFIGURATION ROUTINES


// Layer targeting functions
void SetLayerDrawTarget(uint8_t layer);
void EnableLayer(uint8_t layer, bool b);
void SetLayerOffset(uint8_t layer, float x, float y);
void SetLayerScale(uint8_t layer, float x, float y);
void SetLayerTint(uint8_t layer, const olc_Pixel tint);
void SetLayerCustomRenderFunction(uint8_t layer, void (*f)());

vector GetLayers();
uint32_t CreateLayer();

void SetPixelMode(int32_t m);
int32_t GetPixelMode();
void SetCustomPixelMode(olc_Pixel (*funcPixelMode)(int x, int y, olc_Pixel p1, olc_Pixel p2));
void SetPixelBlend(float fBlend);
void SetSubPixelOffset(float ox, float oy);
void ShowSystemMouseCursor(bool state);


// DRAWING ROUTINES

// TODO


// "Break In" Functions
void olc_PGE_UpdateMouse(int32_t x, int32_t y);
void olc_PGE_UpdateMouseWheel(int32_t delta);
void olc_PGE_UpdateWindowSize(int32_t x, int32_t y);
void olc_PGE_UpdateViewport();
void olc_PGE_ConstructFontSheet();
void olc_PGE_CoreUpdate();
void olc_PGE_PrepareEngine();
void olc_PGE_UpdateMouseState(int32_t button, bool state);
void olc_PGE_UpdateKeyState(int32_t key, bool state);
void olc_PGE_UpdateMouseFocus(bool state);
void olc_PGE_UpdateKeyFocus(bool state);
void olc_PGE_Terminate();

// RENDERER
void       olc_Renderer_PrepareDevice();
int32_t    olc_Renderer_CreateDevice(vector params, bool bFullScreen, bool bVSYNC);
int32_t    olc_Renderer_DestroyDevice();
void       olc_Renderer_DisplayFrame();
void       olc_Renderer_PrepareDrawing();
void       olc_Renderer_DrawLayerQuad(const olc_vf2d offset, const olc_vf2d scale, const olc_Pixel tint);
void       olc_Renderer_DrawDecalQuad(olc_DecalInstance* decal);
uint32_t   olc_Renderer_CreateTexture(const uint32_t width, const uint32_t height);
void       olc_Renderer_UpdateTexture(uint32_t id, olc_Sprite* spr);
uint32_t   olc_Renderer_DeleteTexture(const uint32_t id);
void       olc_Renderer_ApplyTexture(uint32_t id);
void       olc_Renderer_UpdateViewport(const olc_vi2d pos, const olc_vi2d size);
void       olc_Renderer_ClearBuffer(olc_Pixel p, bool bDepth);


// PLATFORM

// TODO
// int32_t olc_Platform_ApplicationStartUp();
// int32_t olc_Platform_ApplicationCleanUp();
// int32_t olc_Platform_ThreadStartUp();
// int32_t olc_Platform_ThreadCleanUp();
// int32_t olc_Platform_CreateGraphics(bool bFullScreen, bool bEnableVSYNC, const olc_vi2d vViewPos, const olc_vi2d vViewSize);
// int32_t olc_Platform_CreateWindowPane(const olc_vi2d vWindowPos, olc_vi2d vWindowSize, bool bFullScreen);
// int32_t olc_Platform_SetWindowTitle(const char* s);
// int32_t olc_Platform_StartSystemEventLoop();
// int32_t olc_Platform_HandleSystemEvent();
```
