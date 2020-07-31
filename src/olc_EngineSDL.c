#include "olc_EngineSDL.h"

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
