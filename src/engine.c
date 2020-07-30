#include "engine.h"

olc_Pixel olc_GREY, olc_DARK_GREY, olc_VERY_DARK_GREY,
    olc_RED,     olc_DARK_RED,     olc_VERY_DARK_RED,
    olc_YELLOW,  olc_DARK_YELLOW,  olc_VERY_DARK_YELLOW,
    olc_GREEN,   olc_DARK_GREEN,   olc_VERY_DARK_GREEN,
    olc_CYAN,    olc_DARK_CYAN,    olc_VERY_DARK_CYAN,
    olc_BLUE,    olc_DARK_BLUE,    olc_VERY_DARK_BLUE,
    olc_MAGENTA, olc_DARK_MAGENTA, olc_VERY_DARK_MAGENTA,
    olc_WHITE,   olc_BLACK, olc_BLANK;

olc_PixelGameEngine PGE;

// local utility functions
void drawline(int sx, int ex, int ny, olc_Pixel p) { for (int i = sx; i <= ex; i++) Draw(i, ny, p); };
void swap_int(int *a, int *b) { int temp = *a; *a = *b; *b = temp; }
bool rol(uint32_t* pattern) { *pattern = (*pattern << 1) | (*pattern >> 31); return (*pattern & 1) ? true : false; }

void* vector_alloc_initial_capacity_callbacks(size_t elementSize, size_t initialSize, AllocatorCallbacks* callbacks) {

	CVector* cvector = NULL;
	size_t headerSize = sizeof(CVector);

	//allocation
	cvector = (CVector*)callbacks->allocate(headerSize + elementSize * initialSize);
	memset(cvector, 0, headerSize + elementSize * initialSize);
	cvector->allocation = elementSize * initialSize;
	cvector->size = 0;
	cvector->elementSize = elementSize;
	cvector->staticSize = 0;
	
	cvector->callbacks.allocate = callbacks->allocate;
	cvector->callbacks.reallocate = callbacks->reallocate;
	cvector->callbacks.release = callbacks->release;

	return (void*)(((size_t)cvector) + headerSize);
}

void* vector_alloc_initial_capacity(size_t elementSize, size_t initialSize) {
	AllocatorCallbacks callbacks = {
		&malloc,
		&realloc,
		&free
	};
	return vector_alloc_initial_capacity_callbacks(elementSize, initialSize, &callbacks);
}


void* vector_alloc_static(size_t elementSize, size_t elements) {
	void* mem = vector_alloc_initial_capacity(elementSize, elements);

}
void* vector_alloc(size_t elementSize) {
	return vector_alloc_initial_capacity(elementSize, 1);
}

void vector_free(void* vect) {
	CVector* vector = (CVector*)((size_t)vect - sizeof(CVector));
	vector->callbacks.release((void*)vector);
}

void* _vector_push(void** vect) {
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)(((size_t)*vect) - headerSize);
	void* back = NULL;
	void* alloc = NULL;
	size_t newAlloc = 0;
	size_t allocated = vector->allocation / vector->elementSize;


	if(vector->size == allocated && (!vector->staticSize)) {
		// printf("Resize! (%li)\n", (vector->size*2));
		newAlloc = vector->elementSize * vector->size * 2;
		alloc = vector->callbacks.reallocate(vector, headerSize + newAlloc);
		if(alloc) {
			*vect = (void*)((size_t)alloc + headerSize);
			vector = alloc;
			vector->allocation = newAlloc;
		} else {
			assert("Couldn't resize the vector!" && 0);
			free(vector);
			return NULL;
		}
	}

	size_t backIdx = vector->size;
	vector->size++;

	return (void*)((size_t)*vect + vector->elementSize*backIdx);
}


void vector_pop(void* vect){
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)((size_t)vect - headerSize);

	if(vector->size) {
		vector->size--;
	}
}

size_t vector_size(void* vect)
{
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)((size_t)vect - headerSize);
	return vector->size;
}

//Just for the sake of formality
void* vector_front(void* vect)
{
	return vect;
}

void* vector_back(void* vect)
{
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)((size_t)vect - headerSize);
	return (void*)((size_t)vect + (vector->size-1) * vector->elementSize);
}

size_t vector_element_size(void* vect)
{
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)((size_t)vect - headerSize);
	return vector->elementSize;
}

void* vector_at(void* vect, size_t index)
{
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)((size_t)vect - headerSize);
	return (void*)((size_t)vect + (vector->size - 1) * index);
}

void vector_clear(void* vect)
{
	size_t headerSize = sizeof(CVector);
	CVector* vector = (CVector*)((size_t)vect - headerSize);
	vector->size = 0;
}

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
// | olc_vX2d - A generic 2D vector type                                          |
// O------------------------------------------------------------------------------O

olc_vi2d olc_VI2D(int x, int y) { olc_vi2d ret; ret.x = x; ret.y = y; return ret; }
olc_vf2d olc_VF2D(float x, float y) { olc_vf2d ret; ret.x = x; ret.y = y; return ret; }
olc_vd2d olc_VD2D(double x, double y) { olc_vd2d ret; ret.x = x; ret.y = y; return ret; }


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
    sprite->pixels = (uint32_t*)calloc(sizeof(uint32_t), w * h);
    sprite->modeSample = olc_SPRITEMODE_NORMAL; // Good Catch! Thanks Tarry

    if(sprite->pixels == NULL)
    {
        fprintf(stderr, "Failed to allocate ram for sprite pixel data.\n"); // Gusgo Spellcheck PRO+, coming to Google soon!
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

olc_Sprite* olc_Sprite_LoadFromPGESprFile(const char *sImageFile)
{
    int32_t width;
    int32_t height;
    uint32_t* pixels;
    
    FILE* fp = fopen(sImageFile, "r");
    if(fp)
    {
        fread(&width, sizeof(int32_t), 1, fp);
        fread(&height, sizeof(int32_t), 1, fp);

        pixels = malloc(width*height*sizeof(uint32_t));
        if(pixels == NULL)
        {
            fprintf(stderr, "Error loading allocating pixel data in PGESprite Loader.\n");
            exit(EXIT_FAILURE);
        }

        fread(pixels, sizeof(uint32_t), width*height, fp);

        olc_Sprite* sprite = olc_Sprite_Create(width, height);

        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                olc_Pixel p = olc_PixelRAW(pixels[y * width + x]);
                
                if(p.a == 0)
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

int32_t olc_Sprite_SaveToPGESprFile(olc_Sprite* sprite, const char *sImageFile)
{
    if(sprite == NULL)
        return olc_RCODE_FAIL;

    uint32_t* pixels = olc_Sprite_GetData(sprite);

    if(pixels == NULL) return olc_RCODE_FAIL;

    FILE* fp = fopen(sImageFile, "w");
    if(fp)
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
// | olc::Decal - A GPU resident storage of an olc::Sprite                        |
// O------------------------------------------------------------------------------O
olc_Decal* olc_Decal_Create(olc_Sprite* sprite)
{
    if(sprite == NULL) return NULL;

    olc_Decal* decal = (olc_Decal*)malloc(sizeof(olc_Decal));
    if(decal == NULL)
    {
        fprintf(stderr, "Error creating decal.\n");
        exit(EXIT_FAILURE);
    }

    decal->id = -1;
    decal->sprite = sprite;
    decal->vUVScale = olc_VF2D( 1.0f, 1.0f );
    decal->id = olc_Renderer_CreateTexture(decal->sprite->width, decal->sprite->height);
    olc_Decal_Update(decal);
    
    return decal;
}

void olc_Decal_Destroy(olc_Decal* decal)
{
    if(decal->id != -1)
    {
        olc_Renderer_DeleteTexture(decal->id);
        decal->id = -1;
        free(decal);
    }
}

void olc_Decal_Update(olc_Decal* decal)
{
    if(decal->sprite == NULL) return;
    decal->vUVScale = olc_VF2D( 1.0f / (float)(decal->sprite->width), 1.0f / (float)(decal->sprite->height) );
    olc_Renderer_ApplyTexture(decal->id);
    olc_Renderer_UpdateTexture(decal->id, decal->sprite);
}

// O------------------------------------------------------------------------------O
// | olc::Renderable - Convenience class to keep a sprite and decal together      |
// O------------------------------------------------------------------------------O
olc_Renderable* olc_Renderable_Create(uint32_t width, uint32_t height)
{
    olc_Renderable* renderable = (olc_Renderable*)malloc(sizeof(olc_Renderable));
    if(renderable == NULL)
    {
        fprintf(stderr,"Error creating olc_Renderable\n");
        exit(EXIT_FAILURE);
    }

    renderable->sprite = olc_Sprite_Create(width, height);
    renderable->decal = olc_Decal_Create(renderable->sprite);
    
    return renderable;
}

olc_Renderable* olc_Renderable_Load(const char* sFile)
{
    olc_Renderable* renderable = (olc_Renderable*)malloc(sizeof(olc_Renderable));
    if(renderable == NULL)
    {
        fprintf(stderr,"Error creating olc_Renderable\n");
        exit(EXIT_FAILURE);
    }

    renderable->sprite = olc_Sprite_Load(sFile);
    renderable->decal = olc_Decal_Create(renderable->sprite);
    
    return renderable;
}

olc_Sprite* olc_Renderable_GetSprite(olc_Renderable* renderable)
{
#ifdef PUNISH_MODE
    for(volatile int i = 0; i < 1000; i++)
    { UNUSED(i); }
#endif
    return renderable->sprite;
}

olc_Decal* olc_Renderable_GetDecal(olc_Renderable* renderable)
{
#ifdef PUNISH_MODE
    for(volatile int i = 0; i < 1000; i++)
    { UNUSED(i); }
#endif
    return renderable->decal;
}
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

void olc_DefaultState()
{
    PGE.nPixelMode = olc_PIXELMODE_NORMAL;
    PGE.fBlendFactor = 1.0f;
    PGE.bHasInputFocus = true;
    PGE.bHasMouseFocus = true;
    PGE.fFrameTimer = 0.0f;
    PGE.fLastElapsed = 0.0f;
    PGE.nFrameCount = 0;
    PGE.nTargetLayer = 0;
    PGE.nLastFPS = 0.0f;
    PGE.bMouseIsVisible = true;

    if(PGE.sAppName == NULL)
        SetAppName("");
    
    sprintf(PGE.sTitle, "OneLoneCoder.com - Pixel Game Engine - %s - FPS: %d", PGE.sAppName, PGE.nFrameCount);
}

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
    
    PGE.OnUserCreate = (create == NULL) ? &DefaultOnUserCreate : create;
    PGE.OnUserUpdate = (update == NULL) ? &DefaultOnUserUpdate : update;
    PGE.OnUserDestroy = (destroy == NULL) ? &DefaultOnUserDestroy : destroy;
    
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

bool DefaultOnUserCreate() { return true; }
bool DefaultOnUserUpdate(float fElapsedTime) { UNUSED(fElapsedTime); return true; };
bool DefaultOnUserDestroy() { return true; }


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

    for(int i = 0; i < vector_size(PGE.vLayers); i++)
    {
        olc_Sprite_Destroy(PGE.vLayers[i].pDrawTarget);
        PGE.vLayers[i].pDrawTarget = olc_Sprite_Create(PGE.vScreenSize.x, PGE.vScreenSize.y);
        PGE.vLayers[i].bUpdate = true;
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
        PGE.pDrawTarget = PGE.vLayers[0].pDrawTarget;
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
        for (y = y1; y <= y2; y++) if (rol(&pattern)) Draw(x1, y, p);
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
        for (x = x1; x <= x2; x++) if (rol(&pattern)) Draw(x, y1, p);
        return;
    }

    // Line is Funk-aye
    dx1 = abs(dx); dy1 = abs(dy);
    px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
    if (dy1 <= dx1)
    {
        if (dx >= 0)
        { x = x1; y = y1; xe = x2; }
        else
        { x = x2; y = y2; xe = x1; }

        if (rol(&pattern)) Draw(x, y, p);

        for (i = 0; x<xe; i++)
        {
            x = x + 1;
            if (px<0)
                px = px + 2 * dy1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
                px = px + 2 * (dy1 - dx1);
            }
            if (rol(&pattern)) Draw(x, y, p);
        }
    }
    else
    {
        if (dy >= 0)
        { x = x1; y = y1; ye = y2; }
        else
        { x = x2; y = y2; ye = y1; }

        if (rol(&pattern)) Draw(x, y, p);

        for (i = 0; y<ye; i++)
        {
            y = y + 1;
            if (py <= 0)
                py = py + 2 * dx1;
            else
            {
                if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
                py = py + 2 * (dx1 - dy1);
            }
            if (rol(&pattern)) Draw(x, y, p);
        }
    }
}

// Draws a circle located at (x,y) with radius
void DrawCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p, uint8_t mask)
{ // Thanks to IanM-Matrix1 #PR121
    if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius)
        return;

    if (radius > 0)
    {
        int x0 = 0;
        int y0 = radius;
        int d = 3 - 2 * radius;

        while (y0 >= x0) // only formulate 1/8 of circle
        {
            // Draw even octants
            if (mask & 0x01) Draw(x + x0, y - y0, p);// Q6 - upper right right
            if (mask & 0x04) Draw(x + y0, y + x0, p);// Q4 - lower lower right
            if (mask & 0x10) Draw(x - x0, y + y0, p);// Q2 - lower left left
            if (mask & 0x40) Draw(x - y0, y - x0, p);// Q0 - upper upper left
            if (x0 != 0 && x0 != y0)
            {
                if (mask & 0x02) Draw(x + y0, y - x0, p);// Q7 - upper upper right
                if (mask & 0x08) Draw(x + x0, y + y0, p);// Q5 - lower right right
                if (mask & 0x20) Draw(x - y0, y + x0, p);// Q3 - lower lower left
                if (mask & 0x80) Draw(x - x0, y - y0, p);// Q1 - upper left left
            }

            if (d < 0)
                d += 4 * x0++ + 6;
            else
                d += 4 * (x0++ - y0--) + 10;
        }
    }
    else
        Draw(x, y, p);
}

// Fills a circle located at (x,y) with radius
void FillCircle(int32_t x, int32_t y, int32_t radius, olc_Pixel p)
{ // Thanks to IanM-Matrix1 #PR121
    if (radius < 0 || x < -radius || y < -radius || x - GetDrawTargetWidth() > radius || y - GetDrawTargetHeight() > radius)
        return;

    if (radius > 0)
    {
        int x0 = 0;
        int y0 = radius;
        int d = 3 - 2 * radius;

        while (y0 >= x0)
        {
            drawline(x - y0, x + y0,y - x0, p);
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
        Draw(x, y, p);
}

// Draws a rectangle at (x,y) to (x+w,y+h)
void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p)
{
    DrawLine(x, y, x+w, y, p, olc_SOLID);
    DrawLine(x+w, y, x+w, y+h, p, olc_SOLID);
    DrawLine(x+w, y+h, x, y+h, p, olc_SOLID);
    DrawLine(x, y+h, x, y, p, olc_SOLID);
}

// Fills a rectangle at (x,y) to (x+w,y+h)
void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, olc_Pixel p)
{
    int32_t x2 = x + w;
    int32_t y2 = y + h;

    if (x < 0) x = 0;
    if (x >= (int32_t)GetDrawTargetWidth()) x = (int32_t)GetDrawTargetWidth();
    if (y < 0) y = 0;
    if (y >= (int32_t)GetDrawTargetHeight()) y = (int32_t)GetDrawTargetHeight();

    if (x2 < 0) x2 = 0;
    if (x2 >= (int32_t)GetDrawTargetWidth()) x2 = (int32_t)GetDrawTargetWidth();
    if (y2 < 0) y2 = 0;
    if (y2 >= (int32_t)GetDrawTargetHeight()) y2 = (int32_t)GetDrawTargetHeight();

    for (int i = x; i < x2; i++)
        for (int j = y; j < y2; j++)
            Draw(i, j, p);
}

// Draws a triangle between points (x1,y1), (x2,y2) and (x3,y3)
void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p)
{
    DrawLine(x1, y1, x2, y2, p, olc_SOLID);
    DrawLine(x2, y2, x3, y3, p, olc_SOLID);
    DrawLine(x3, y3, x1, y1, p, olc_SOLID);
}

// https://www.avrfreaks.net/sites/default/files/triangles.c
void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, olc_Pixel p)
{
    int t1x, t2x, y, minx, maxx, t1xp, t2xp;
    bool changed1 = false;
    bool changed2 = false;
    int signx1, signx2, dx1, dy1, dx2, dy2;
    int e1, e2;
    // Sort vertices
    if (y1>y2) {swap_int(&y1, &y2); swap_int(&x1, &x2); }
    if (y1>y3) {swap_int(&y1, &y3); swap_int(&x1, &x3); }
    if (y2>y3) {swap_int(&y2, &y3); swap_int(&x2, &x3); }

    t1x = t2x = x1; y = y1;   // Starting points
    dx1 = (int)(x2 - x1);
    if (dx1<0) { dx1 = -dx1; signx1 = -1; }	else signx1 = 1;
    dy1 = (int)(y2 - y1);

    dx2 = (int)(x3 - x1);
    if (dx2<0) { dx2 = -dx2; signx2 = -1; } else signx2 = 1;
    dy2 = (int)(y3 - y1);

    if (dy1 > dx1) { swap_int(&dx1, &dy1); changed1 = true; }
    if (dy2 > dx2) { swap_int(&dy2, &dx2); changed2 = true; }

    e2 = (int)(dx2 >> 1);
    // Flat top, just process the second half
    if (y1 == y2) goto next;
    e1 = (int)(dx1 >> 1);

    for (int i = 0; i < dx1;) {
        t1xp = 0; t2xp = 0;
        if (t1x<t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }
        // process first line until y value is about to change
        while (i<dx1) {
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
        if (minx>t1x) minx = t1x;
        if (minx>t2x) minx = t2x;
        if (maxx<t1x) maxx = t1x;
        if (maxx<t2x) maxx = t2x;
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
    dx1 = (int)(x3 - x2); if (dx1<0) { dx1 = -dx1; signx1 = -1; }
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
        if (t1x<t2x) { minx = t1x; maxx = t2x; }
        else { minx = t2x; maxx = t1x; }
        // process first line until y value is about to change
        while (i<dx1) {
            e1 += dy1;
            while (e1 >= dx1) {
                e1 -= dx1;
                if (changed1) { t1xp = signx1; break; }//t1x += signx1;
                else          goto next3;
            }
            if (changed1) break;
            else   	   	  t1x += signx1;
            if (i<dx1) i++;
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

        if (minx>t1x) minx = t1x;
        if (minx>t2x) minx = t2x;
        if (maxx<t1x) maxx = t1x;
        if (maxx<t2x) maxx = t2x;
        drawline(minx, maxx, y, p);
        if (!changed1) t1x += signx1;
        t1x += t1xp;
        if (!changed2) t2x += signx2;
        t2x += t2xp;
        y += 1;
        if (y>y3) return;
    }

}

// Draws an entire sprite at well in my defencelocation (x,y)
void DrawSprite(int32_t x, int32_t y, olc_Sprite *sprite, uint32_t scale, uint8_t flip)
{
    if (sprite == NULL)
        return;

    int32_t fxs = 0, fxm = 1, fx = 0;
    int32_t fys = 0, fym = 1, fy = 0;
    
    if (flip & olc_SPRITEFLIP_HORIZ) { fxs = sprite->width - 1; fxm = -1; }
    if (flip & olc_SPRITEFLIP_VERT) { fys = sprite->height - 1; fym = -1; }

    if (scale > 1)
    {
        fx = fxs;
        for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < sprite->height; j++, fy += fym)
                for (uint32_t is = 0; is < scale; is++)
                    for (uint32_t js = 0; js < scale; js++)
                        Draw(x + (i*scale) + is, y + (j*scale) + js, olc_Sprite_GetPixel(sprite, fx, fy));
        }
    }
    else
    {
        fx = fxs;
        for (int32_t i = 0; i < sprite->width; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < sprite->height; j++, fy += fym)
                Draw(x + i, y + j, olc_Sprite_GetPixel(sprite, fx, fy));
        }
    }

}

// Draws an area of a sprite at location (x,y), where the
// selected area is (ox,oy) to (ox+w,oy+h)
void DrawPartialSprite(int32_t x, int32_t y, olc_Sprite *sprite, int32_t ox, int32_t oy, int32_t w, int32_t h, uint32_t scale, uint8_t flip)
{
    if (sprite == NULL)
        return;

    int32_t fxs = 0, fxm = 1, fx = 0;
    int32_t fys = 0, fym = 1, fy = 0;
    if (flip & olc_SPRITEFLIP_HORIZ) { fxs = w - 1; fxm = -1; }
    if (flip & olc_SPRITEFLIP_VERT) { fys = h - 1; fym = -1; }

    if (scale > 1)
    {
        fx = fxs;
        for (int32_t i = 0; i < w; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < h; j++, fy += fym)
                for (uint32_t is = 0; is < scale; is++)
                    for (uint32_t js = 0; js < scale; js++)
                        Draw(x + (i*scale) + is, y + (j*scale) + js, olc_Sprite_GetPixel(sprite, fx + ox, fy + oy));
        }
    }
    else
    {
        fx = fxs;
        for (int32_t i = 0; i < w; i++, fx += fxm)
        {
            fy = fys;
            for (int32_t j = 0; j < h; j++, fy += fym)
                Draw(x + i, y + j, olc_Sprite_GetPixel(sprite, fx + ox, fy + oy));
        }
    }

}

// Decal Quad functions

// Draws a whole decal, with optional scale and tinting
void DrawDecal(olc_vf2d pos, olc_Decal *decal, olc_vf2d scale, const olc_Pixel tint)
{
    olc_vf2d vScreenSpacePos;
    vScreenSpacePos.x = (pos.x * PGE.vInvScreenSize.x) * 2.0f - 1.0f;
    vScreenSpacePos.y = ((pos.y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f;
    
    olc_vf2d vScreenSpaceDim;
    vScreenSpaceDim.x = vScreenSpacePos.x + (2.0f * ((float)(decal->sprite->width) * PGE.vInvScreenSize.x)) * scale.x;
    vScreenSpaceDim.y = vScreenSpacePos.y - (2.0f * ((float)(decal->sprite->height) * PGE.vInvScreenSize.y)) * scale.y;
    
    olc_DecalInstance* di = vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance);
    olc_DecalInstance_Create(di);
    
    di->decal = decal;
    
    di->tint[0] = tint;
    
    di->pos[0] = olc_VF2D( vScreenSpacePos.x, vScreenSpacePos.y );
    di->pos[1] = olc_VF2D( vScreenSpacePos.x, vScreenSpaceDim.y );
    di->pos[2] = olc_VF2D( vScreenSpaceDim.x, vScreenSpaceDim.y );
    di->pos[3] = olc_VF2D( vScreenSpaceDim.x, vScreenSpacePos.y );
}

// Draws a region of a decal, with optional scale and tinting
void DrawPartialDecal(olc_vf2d pos, olc_Decal* decal, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint)
{
    olc_vf2d vScreenSpacePos = olc_VF2D(
        (pos.x * PGE.vInvScreenSize.x) * 2.0f - 1.0f,
        ((pos.y * PGE.vInvScreenSize.y) * 2.0f - 1.0f) * -1.0f
    );
    
    olc_vf2d vScreenSpaceDim = olc_VF2D(
        vScreenSpacePos.x + (2.0f * source_size.x * PGE.vInvScreenSize.x) * scale.x,
        vScreenSpacePos.y - (2.0f * source_size.y * PGE.vInvScreenSize.y) * scale.y
    );

    olc_DecalInstance* di = vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance);
    olc_DecalInstance_Create(di);

    di->decal = decal; di->tint[0] = tint;

    di->pos[0] = olc_VF2D( vScreenSpacePos.x, vScreenSpacePos.y );
    di->pos[1] = olc_VF2D( vScreenSpacePos.x, vScreenSpaceDim.y );
    di->pos[2] = olc_VF2D( vScreenSpaceDim.x, vScreenSpaceDim.y );
    di->pos[3] = olc_VF2D( vScreenSpaceDim.x, vScreenSpacePos.y );
    
    olc_vf2d uvtl = olc_VF2D(source_pos.x * decal->vUVScale.x, source_pos.y * decal->vUVScale.y);
    olc_vf2d uvbr = olc_VF2D(uvtl.x + (source_size.x * decal->vUVScale.x), uvtl.y + (source_size.y * decal->vUVScale.y));
    
    di->uv[0] = olc_VF2D( uvtl.x, uvtl.y ); di->uv[1] = olc_VF2D( uvtl.x, uvbr.y );
    di->uv[2] = olc_VF2D( uvbr.x, uvbr.y ); di->uv[3] = olc_VF2D( uvbr.x, uvtl.y );	

}

// Draws fully user controlled 4 vertices, pos(pixels), uv(pixels), colours
void DrawExplicitDecal(olc_Decal* decal, olc_vf2d *pos, olc_vf2d *uv, const olc_Pixel *col)
{
    // IMPOSSIBLE WITH SDL (AT LEAST HOW I'M USING IT), HERE FOR, REASONS
}

// Draws a decal with 4 arbitrary points, warping the texture to look "correct"
void DrawWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], const olc_Pixel tint)
{
    // IMPOSSIBLE WITH SDL (AT LEAST HOW I'M USING IT), HERE FOR, REASONS
}

// As above, but you can specify a region of a decal source sprite
void DrawPartialWarpedDecal(olc_Decal* decal, olc_vf2d pos[4], olc_vf2d source_pos, olc_vf2d source_size, const olc_Pixel tint)
{
    // IMPOSSIBLE WITH SDL (AT LEAST HOW I'M USING IT), HERE FOR, REASONS
}

// Draws a decal rotated to specified angle, wit point of rotation offset
void DrawRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d scale, const olc_Pixel tint)
{
    olc_DecalInstance* di = vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance);
    olc_DecalInstance_Create(di);

    di->decal = decal; di->tint[0] = tint;

    di->pos[0] = olc_VF2D((0.0f - center.x) * scale.x,(0.0f - center.y) * scale.y);
    di->pos[1] = olc_VF2D((0.0f - center.x) * scale.x, ((float)decal->sprite->height - center.y) * scale.y);
    di->pos[2] = olc_VF2D(((float)decal->sprite->width - center.x) * scale.x, ((float)decal->sprite->height - center.y) * scale.y);
    di->pos[3] = olc_VF2D(((float)decal->sprite->width - center.x) * scale.x, (0.0f - center.y) * scale.y);
    
    float c = cos(fAngle), s = sin(fAngle);

    for (int i = 0; i < 4; i++)
    {
        di->pos[i] = olc_VF2D(pos.x + (di->pos[i].x * c - di->pos[i].y * s), pos.y + (di->pos[i].x * s + di->pos[i].y * c));
        di->pos[i] = olc_VF2D(di->pos[i].x * PGE.vInvScreenSize.x * 2.0f - 1.0f, di->pos[i].y * PGE.vInvScreenSize.y * 2.0f - 1.0f);
        di->pos[i].y *= -1.0f;
    }
}

void DrawPartialRotatedDecal(olc_vf2d pos, olc_Decal* decal, const float fAngle, olc_vf2d center, olc_vf2d source_pos, olc_vf2d source_size, olc_vf2d scale, const olc_Pixel tint)
{
    olc_DecalInstance* di = vector_push(PGE.vLayers[PGE.nTargetLayer].vecDecalInstance);
    olc_DecalInstance_Create(di);

    di->decal = decal; di->tint[0] = tint;

    di->pos[0] = olc_VF2D((0.0f - center.x) * scale.x, (0.0f - center.y) * scale.y);
    di->pos[1] = olc_VF2D((0.0f - center .x) * scale.x, (source_size.x - center.y) * scale.y);
    di->pos[2] = olc_VF2D((source_size.x - center.x) * scale.x, (source_size.y - center.y) * scale.y);
    di->pos[3] = olc_VF2D((source_size.x - center.x) * scale.x, (0.0f - center.y) * scale.y);

    float c = cos(fAngle), s = sin(fAngle);
    for (int i = 0; i < 4; i++)
    {
        di->pos[i] = olc_VF2D(pos.x + (di->pos[i].x * c - di->pos[i].y * s), pos.y + (di->pos[i].x * s + di->pos[i].y * c));
        di->pos[i] = olc_VF2D(di->pos[i].x * PGE.vInvScreenSize.x * 2.0f - 1.0f, di->pos[i].y * PGE.vInvScreenSize.y * 2.0f - 1.0f);
        di->pos[i].y *= -1.0f;
    }

    olc_vf2d uvtl = olc_VF2D(source_pos.x * decal->vUVScale.x, source_pos.y * decal->vUVScale.y);
    olc_vf2d uvbr = olc_VF2D(uvtl.x + (source_size.x * decal->vUVScale.x), uvtl.y + (source_size.y * decal->vUVScale.y));
    
    di->uv[0] = olc_VF2D( uvtl.x, uvtl.y ); di->uv[1] = olc_VF2D( uvtl.x, uvbr.y );
    di->uv[2] = olc_VF2D( uvbr.x, uvbr.y ); di->uv[3] = olc_VF2D( uvbr.x, uvtl.y );	
}

// Draws a multiline string as a decal, with tiniting and scaling
void DrawStringDecal(olc_vf2d pos, const char* sText, const olc_Pixel col, olc_vf2d scale)
{
    olc_vf2d spos;
    
    spos.x = 0.0f;
    spos.y = 0.0f;
    
    for(int i = 0; i < strlen(sText); i++)
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

            DrawPartialDecal(p, PGE.fontDecal, src, src_size, scale, col);
            spos.x += 8.0f * scale.x;
        }
    }
}

// Draws a single shaded filled rectangle as a decal
void FillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel col)
{
    // IMPOSSIBLE WITH SDL (AT LEAST HOW I'M USING IT), HERE FOR, REASONS
}

// Draws a corner shaded rectangle as a decal
void GradientFillRectDecal(olc_vf2d pos, olc_vf2d size, const olc_Pixel colTL, const olc_Pixel colBL, const olc_Pixel colBR, const olc_Pixel colTR)
{
    // IMPOSSIBLE WITH SDL (AT LEAST HOW I'M USING IT), HERE FOR, REASONS
}



// Draws a single line of text
void DrawString(int32_t x, int32_t y, const char* sText, olc_Pixel col, uint32_t scale)
{
    int32_t sx = 0;
    int32_t sy = 0;
    int32_t m = PGE.nPixelMode;
    // Thanks @tucna, spotted bug with col.ALPHA :P
    if(col.a != 255)		SetPixelMode(olc_PIXELMODE_ALPHA);
    else					SetPixelMode(olc_PIXELMODE_MASK);
    for(int i = 0; i < strlen(sText); i++)
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
                        if(olc_Sprite_GetPixel(PGE.fontSprite,i + ox * 8, j + oy * 8).r > 0)
                            for (uint32_t is = 0; is < scale; is++)
                                for (uint32_t js = 0; js < scale; js++)
                                    Draw(x + sx + (i*scale) + is, y + sy + (j*scale) + js, col);
            }
            else
            {
                for (uint32_t i = 0; i < 8; i++)
                    for (uint32_t j = 0; j < 8; j++)
                        if(olc_Sprite_GetPixel(PGE.fontSprite,i + ox * 8, j + oy * 8).r > 0)
                            Draw(x + sx + i, y + sy + j, col);
            }
            sx += 8 * scale;
        }
    }
    SetPixelMode(m);
}

olc_vi2d GetTextSize(const char* s)
{
    olc_vi2d size = { 0,1 };
    olc_vi2d pos = { 0,1 };

    for(int i = 0; i < strlen(s); i++)
    {
        if(s[i] == '\n') { pos.y++;  pos.x = 0; }
        else pos.x++;
        size.x = (size.x > pos.x) ? size.x : pos.x;
        size.y = (size.y > pos.y) ? size.y : pos.y;
    }
    
    size.x = size.x * 8;
    size.y = size.y * 8;

    return size;
}

// Clears entire draw target to Pixel
void Clear(olc_Pixel p)
{
    int pixels = GetDrawTargetWidth() * GetDrawTargetHeight();
    uint32_t* m = olc_Sprite_GetData(GetDrawTarget());
    for(int i = 0; i < pixels; i++) m[i] = p.n;    
}

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
    PGE.pDrawTarget = PGE.vLayers[layer].pDrawTarget;
    PGE.vLayers[layer].bUpdate = true;
    PGE.nTargetLayer = layer;
}

void EnableLayer(uint8_t layer, bool b)
{
    if(layer < vector_size(PGE.vLayers))
        PGE.vLayers[layer].bShow = b;
}

void SetLayerOffset(uint8_t layer, float x, float y)
{
    if(layer < vector_size(PGE.vLayers))
    {
        PGE.vLayers[layer].vOffset.x = x;
        PGE.vLayers[layer].vOffset.y = y;
    }

}

void SetLayerScale(uint8_t layer, float x, float y)
{
    if(layer < vector_size(PGE.vLayers))
    {
        PGE.vLayers[layer].vScale.x = x;
        PGE.vLayers[layer].vScale.y = y;
    }
}

void SetLayerTint(uint8_t layer, const olc_Pixel tint)
{
    if(layer < vector_size(PGE.vLayers))
        PGE.vLayers[layer].tint = tint;
}

void SetLayerCustomRenderFunction(uint8_t layer, void (*f)())
{
    if(layer < vector_size(PGE.vLayers))
        PGE.vLayers[layer].funcHook = f;
}

olc_LayerDesc* GetLayers()
{ return PGE.vLayers; }

uint32_t CreateLayer()
{
    olc_LayerDesc* ld = vector_push(PGE.vLayers);
    
    ld->pDrawTarget = olc_Sprite_Create(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->nResID = olc_Renderer_CreateTexture(PGE.vScreenSize.x, PGE.vScreenSize.y);
    ld->tint = olc_WHITE;
    ld->funcHook = NULL;

    ld->vecDecalInstance = vector_type_alloc(olc_DecalInstance);

    olc_Renderer_UpdateTexture(ld->nResID, ld->pDrawTarget);
    
    return (uint32_t)(vector_size(PGE.vLayers) - 1);
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
    PGE.tp2 = SDL_GetPerformanceCounter();
    double duration = (double)((PGE.tp2 - PGE.tp1)*1000) / SDL_GetPerformanceFrequency();
    PGE.tp1 = PGE.tp2;


    float fElapsedTime = (float)(duration/1000);
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
    PGE.vLayers[0].bUpdate = true;
    PGE.vLayers[0].bShow = true;

    olc_Renderer_PrepareDrawing();

    for(int i = vector_size(PGE.vLayers)-1; i >= 0; i--)
    {
        olc_LayerDesc* layer = &PGE.vLayers[i];
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
                for(int j = 0; j < vector_size(layer->vecDecalInstance); j++)
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
    PGE.vLayers = vector_type_alloc(olc_LayerDesc);

    // Create Primary Layer "0"
    CreateLayer();

    PGE.vLayers[0].bUpdate = true;
    PGE.vLayers[0].bShow = true;
    SetDrawTarget(NULL);

    // Construct default font sheet
    olc_PGE_ConstructFontSheet();

    PGE.tp1 = SDL_GetPerformanceCounter();
    PGE.tp2 = SDL_GetPerformanceCounter();
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


void olc_Renderer_PrepareDevice()
{}

int32_t olc_Renderer_CreateDevice(bool bFullScreen, bool bVSYNC)
{
    vTextures = vector_type_alloc(SDL_Texture*);
    return olc_RCODE_OK;
}

int32_t olc_Renderer_DestroyDevice()
{
    for(size_t i = 0; i < vector_size(vTextures); i++)
    {
        SDL_DestroyTexture(vTextures[i]);
        vTextures[i] = NULL;
    }
    vector_free(vTextures);
    return olc_RCODE_OK;
}

void olc_Renderer_DisplayFrame()
{
    SDL_RenderPresent(olc_Renderer);
}

void olc_Renderer_PrepareDrawing()
{}

void olc_Renderer_DrawLayerQuad(olc_vf2d offset, olc_vf2d scale, const olc_Pixel tint)
{
    // Apply Tint
    SDL_SetTextureColorMod(vTextures[nActiveTexture], tint.r, tint.g, tint.b);
    SDL_SetTextureAlphaMod(vTextures[nActiveTexture], tint.a);

    // Draw Texture
    SDL_RenderCopy(olc_Renderer, vTextures[nActiveTexture], NULL, NULL);
}

// Locally used functions to convert OpenGL to Screen Coords
olc_vf2d PointToScreen(olc_vf2d point)
{
    olc_vf2d ret;

    ret.x = (point.x + 1.0f) * (float)rViewport.w * 0.5f;
    ret.y = (point.y - 1.0f) * (float)rViewport.h * 0.5f * -1.0f;
    
    return ret;
}

SDL_Rect GetSubTexture(olc_vf2d uv[4], olc_Decal *decal)
{
    // get the top left of the sub-texture
    olc_vf2d vPos = olc_VF2D(uv[0].x / decal->vUVScale.x, uv[0].y / decal->vUVScale.y);
    
    // get the size of the sub-texture
    olc_vf2d vSize = {
        (uv[3].x - uv[0].x) /  decal->vUVScale.x,
        (uv[1].y - uv[0].y) / decal->vUVScale.y
    };
    
    // generate rectangle for the sub-texture
    SDL_Rect rect;
    
    rect.x = vPos.x;
    rect.y = vPos.y;
    rect.w = vSize.x;
    rect.h = vSize.y;
    
    return rect;
}

SDL_Rect VecToRect(olc_vf2d pos, olc_vf2d size)
{
    SDL_Rect rect;

    rect.x = pos.x;
    rect.y = pos.y;
    rect.w = size.x;
    rect.h = size.y;

    return rect;
}

void olc_Renderer_DrawDecalQuad(olc_DecalInstance* decal)
{
    if(decal->decal == NULL)
        return;
    
    float fAngle;
    olc_vf2d vSize;

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
        vSize.x = pos[3].x - pos[0].x;
        vSize.y = pos[1].y - pos[0].y;
        fAngle = 0;
    }
    else
    {
        // width
        olc_vf2d a = { pos[3].x - pos[0].x, pos[3].y - pos[0].y };
        vSize.x = sqrt(a.x * a.x + a.y * a.y);
        
        // height
        olc_vf2d b = { pos[1].x - pos[0].x, pos[1].y - pos[0].y };
        vSize.y = sqrt(b.x * b.x + b.y * b.y);
        
        fAngle = (atan2(pos[1].y - pos[0].y, pos[1].x - pos[0].x) * 180 / 3.14159f) - 90;
    }
    
    SDL_Rect src  = GetSubTexture(decal->uv, decal->decal);
    SDL_Rect dest = VecToRect(pos[0], vSize);
    SDL_Point center; center.x = 0; center.y = 0;

    // Apply Tint
    SDL_SetTextureColorMod(vTextures[decal->decal->id], decal->tint[0].r, decal->tint[0].g, decal->tint[0].b);
    SDL_SetTextureAlphaMod(vTextures[decal->decal->id], decal->tint[0].a);
    
    // Draw Texture
    SDL_RenderCopyEx(olc_Renderer, vTextures[decal->decal->id], &src, &dest, fAngle, &center, SDL_FLIP_NONE);
}

uint32_t olc_Renderer_CreateTexture(const uint32_t width, const uint32_t height)
{
    // reuse empty slots from deleted textures
    if(nOpenSlot > 0)
    {
        for(size_t i = 0; i < vector_size(vTextures); i++)
        {
            if(vTextures[i] == NULL)
            {
                nOpenSlot--;
                vTextures[i] = SDL_CreateTexture(olc_Renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
                if(vTextures[i] == NULL)
                {
                    fprintf(stderr, "Failed to create texture.\n");
                    exit(EXIT_FAILURE);
                }
                SDL_SetTextureBlendMode(vTextures[i], SDL_BLENDMODE_BLEND);
                return i;
            }
        }
    }

    int id = nTextureID++;
    SDL_Texture** texture = vector_push(vTextures);
    *texture = SDL_CreateTexture(olc_Renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if(*texture == NULL)
    {
        fprintf(stderr, "Failed to create texture.\n");
        exit(EXIT_FAILURE);
    }
    SDL_SetTextureBlendMode(*texture, SDL_BLENDMODE_BLEND);
    
    return id;
}

void olc_Renderer_UpdateTexture(uint32_t id, olc_Sprite* spr)
{
    SDL_UpdateTexture(vTextures[id], NULL, (void*)olc_Sprite_GetData(spr), spr->width * 4);
}

uint32_t olc_Renderer_DeleteTexture(const uint32_t id)
{
    if(vTextures[id] != NULL)
    {
        SDL_DestroyTexture(vTextures[id]);
        vTextures[id] = NULL;
        nOpenSlot++;
    }
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


void inputmap_init()
{
    for(int i = 0; i < 256; i++)
    {
        mapKeys[i].key = -1;
        mapKeys[i].val = 0;
    }
}

uint8_t inputmap_get(size_t key)
{
    for(int i = 0; i < 256; i++)
    {
        if(mapKeys[i].key == key)
            return mapKeys[i].val;
    }
   
    return 0;
}

void inputmap_set(size_t key, uint8_t val)
{
    for(int i = 0; i < 256; i++)
    {
        if(mapKeys[i].key == key)
        {
            mapKeys[i].val = val;
            return;
        }
    }

    // if we made it here, we have to create a new inputdata
    for(int i = 0; i < 256; i++)
    {
        if(mapKeys[i].key == -1 && mapKeys[i].val == 0)
        {
            mapKeys[i].key = key;
            mapKeys[i].val = val;
            return;
        }
    }

}

int32_t olc_Platform_ApplicationStartUp()
{ return olc_RCODE_OK; }

int32_t olc_Platform_ApplicationCleanUp()
{
    for(size_t i = 0; i < vector_size(PGE.vLayers); i++)
    {
        vector_clear(PGE.vLayers[i].vecDecalInstance);
        vector_free(PGE.vLayers[i].vecDecalInstance);
    }
    vector_clear(PGE.vLayers);
    vector_free(PGE.vLayers);

    olc_PGE_DestroyFontSheet();
    olc_Sprite_Destroy(PGE.pDrawTarget);
    free(PGE.sAppName);
    
    SDL_DestroyRenderer(olc_Renderer);
    SDL_DestroyWindow(olc_Window);
    SDL_Quit();
    return olc_RCODE_OK;
}

int32_t olc_Platform_ThreadStartUp()
{ return olc_RCODE_OK; }

int32_t olc_Platform_ThreadCleanUp()
{
    olc_Renderer_DestroyDevice();
    return olc_RCODE_OK;
}

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
    olc_Window = SDL_CreateWindow(PGE.sTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, vWindowSize.x, vWindowSize.y, SDL_WINDOW_SHOWN);
    SDL_SetWindowResizable(olc_Window, SDL_TRUE);
    SDL_SetWindowFullscreen(olc_Window, (bFullScreen) ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0 );

    inputmap_init();
    
    inputmap_set(SDLK_UNKNOWN, olc_NONE);
    inputmap_set(SDLK_a, olc_A); inputmap_set(SDLK_b, olc_B);
    inputmap_set(SDLK_c, olc_C); inputmap_set(SDLK_d, olc_D);
    inputmap_set(SDLK_e, olc_E); inputmap_set(SDLK_f, olc_F);
    inputmap_set(SDLK_g, olc_G); inputmap_set(SDLK_h, olc_H);
    inputmap_set(SDLK_i, olc_I); inputmap_set(SDLK_j, olc_J);
    inputmap_set(SDLK_k, olc_K); inputmap_set(SDLK_l, olc_L);
    inputmap_set(SDLK_m, olc_M); inputmap_set(SDLK_n, olc_N);
    inputmap_set(SDLK_o, olc_O); inputmap_set(SDLK_p, olc_P);
    inputmap_set(SDLK_q, olc_Q); inputmap_set(SDLK_r, olc_R);
    inputmap_set(SDLK_s, olc_S); inputmap_set(SDLK_t, olc_T);
    inputmap_set(SDLK_u, olc_U); inputmap_set(SDLK_v, olc_V);
    inputmap_set(SDLK_w, olc_W); inputmap_set(SDLK_x, olc_X);
    inputmap_set(SDLK_y, olc_Y); inputmap_set(SDLK_z, olc_Z);
    
    inputmap_set(SDLK_0, olc_K0); inputmap_set(SDLK_1, olc_K1); 
    inputmap_set(SDLK_2, olc_K2); inputmap_set(SDLK_3, olc_K3);
    inputmap_set(SDLK_4, olc_K4); inputmap_set(SDLK_5, olc_K5); 
    inputmap_set(SDLK_6, olc_K6); inputmap_set(SDLK_7, olc_K7);
    inputmap_set(SDLK_8, olc_K8); inputmap_set(SDLK_9, olc_K9);

    inputmap_set(SDLK_F1,  olc_F1);  inputmap_set(SDLK_F2,  olc_F2);
    inputmap_set(SDLK_F3,  olc_F3);  inputmap_set(SDLK_F4,  olc_F4);
    inputmap_set(SDLK_F5,  olc_F5);  inputmap_set(SDLK_F6,  olc_F6);
    inputmap_set(SDLK_F7,  olc_F7);  inputmap_set(SDLK_F8,  olc_F8);
    inputmap_set(SDLK_F9,  olc_F9);  inputmap_set(SDLK_F10, olc_F10);
    inputmap_set(SDLK_F11, olc_F11); inputmap_set(SDLK_F12, olc_F12);

    inputmap_set(SDLK_DOWN,       olc_DOWN);   inputmap_set(SDLK_LEFT,   olc_LEFT);
    inputmap_set(SDLK_RIGHT,      olc_RIGHT);  inputmap_set(SDLK_UP,     olc_UP);
    inputmap_set(SDLK_KP_ENTER,   olc_ENTER);  inputmap_set(SDLK_RETURN, olc_ENTER);
    inputmap_set(SDLK_BACKSPACE,  olc_BACK);   inputmap_set(SDLK_ESCAPE, olc_ESCAPE);
    inputmap_set(SDLK_RETURN,     olc_ENTER);  inputmap_set(SDLK_PAUSE,  olc_PAUSE);
    inputmap_set(SDLK_SCROLLLOCK, olc_SCROLL); inputmap_set(SDLK_TAB,    olc_TAB);
    inputmap_set(SDLK_DELETE,     olc_DEL);    inputmap_set(SDLK_HOME,   olc_HOME);
    inputmap_set(SDLK_END,        olc_END);    inputmap_set(SDLK_PAGEUP, olc_PGUP);
    inputmap_set(SDLK_PAGEDOWN,   olc_PGDN);   inputmap_set(SDLK_INSERT, olc_INS);
    inputmap_set(SDLK_LSHIFT,     olc_SHIFT);  inputmap_set(SDLK_RSHIFT, olc_SHIFT);
    inputmap_set(SDLK_LCTRL,      olc_CTRL);   inputmap_set(SDLK_RCTRL,  olc_CTRL);
    inputmap_set(SDLK_SPACE,      olc_SPACE);

    inputmap_set(SDLK_KP_0, olc_NP0); inputmap_set(SDLK_KP_1, olc_NP1);
    inputmap_set(SDLK_KP_2, olc_NP2); inputmap_set(SDLK_KP_3, olc_NP3);
    inputmap_set(SDLK_KP_4, olc_NP4); inputmap_set(SDLK_KP_5, olc_NP5);
    inputmap_set(SDLK_KP_6, olc_NP6); inputmap_set(SDLK_KP_7, olc_NP7);
    inputmap_set(SDLK_KP_8, olc_NP8); inputmap_set(SDLK_KP_9, olc_NP9);

    inputmap_set(SDLK_KP_MULTIPLY, olc_NP_MUL); inputmap_set(SDLK_KP_DIVIDE, olc_NP_DIV);
    inputmap_set(SDLK_KP_PLUS, olc_NP_ADD); inputmap_set(SDLK_KP_MINUS, olc_NP_SUB);
    inputmap_set(SDLK_KP_PERIOD, olc_NP_DECIMAL); inputmap_set(SDLK_PERIOD, olc_PERIOD);

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
            olc_PGE_UpdateKeyState(inputmap_get(event.key.keysym.sym), true);
        }
        else if(event.type == SDL_KEYUP)
        {
            olc_PGE_UpdateKeyState(inputmap_get(event.key.keysym.sym), false);
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
