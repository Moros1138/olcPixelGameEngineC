#include "olc_EngineOpenGL.h"

// RENDERER

void olc_Renderer_PrepareDevice()
{}

int32_t olc_Renderer_CreateDevice(bool bFullScreen, bool bVSYNC)
{

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

#if defined(__linux__) || defined(__FreeBSD__)
    glXMakeCurrent(olc_Display, None, NULL);
    glXDestroyContext(olc_Display, glDeviceContext);
#endif

    return olc_RCODE_OK;
}

void olc_Renderer_DisplayFrame()
{

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
    if(decal->decal == NULL)
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

// PLATFORM

#if defined(__linux__) || defined(__FreeBSD__) 

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
    
    XFreeCursor(olc_Display, olc_ArrowCursor);
    XFreeCursor(olc_Display, olc_InvisibleCursor);
    XFreePixmap(olc_Display, olc_BitmapNoData);
    
    XDestroyWindow(olc_Display, olc_Window);
    XCloseDisplay(olc_Display);			
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

    if(olc_Renderer_CreateDevice(bFullScreen, bEnableVSYNC) == olc_RCODE_OK)
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
        XEvent xev = {0};
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
{ return olc_RCODE_OK; }


int32_t olc_Platform_HandleSystemEvent()
{
    if(IsMouseCursorVisible())
        XDefineCursor(olc_Display, olc_Window, olc_ArrowCursor);
    else
        XDefineCursor(olc_Display, olc_Window, olc_InvisibleCursor);
    
    XEvent xev;
    while(XPending(olc_Display))
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



olc_Sprite* olc_Sprite_LoadFromFile(const char* filename)
{
    return NULL;
}

#endif // LINUX PLATFORM
