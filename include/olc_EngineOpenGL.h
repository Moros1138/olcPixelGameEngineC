#ifndef OLC_ENGINEOPENGL_H
#define OLC_ENGINEOPENGL_H
#include "olc_Engine.h"

// RENDERER

#if (defined(__linux__) || defined(__FreeBSD__))
    #include <GL/gl.h>
    #include <GL/glx.h>
    #include <X11/cursorfont.h>
    #include <X11/X.h>
    #include <X11/Xlib.h>
    #include <png.h>

    typedef int(glSwapInterval_t)(Display* dpy, GLXDrawable drawable, int interval);
    static glSwapInterval_t* glSwapIntervalEXT;
    typedef GLXContext glDeviceContext_t;
    typedef GLXContext glRenderContext_t;
#endif

glDeviceContext_t glDeviceContext = 0;
glRenderContext_t glRenderContext = 0;

// PLATFORM

#if defined(__linux__) || defined(__FreeBSD__)
    Display*                olc_Display;
    Window                  olc_WindowRoot;
    Window                  olc_Window;
    XVisualInfo*            olc_VisualInfo;
    Colormap                olc_ColourMap;
    XSetWindowAttributes    olc_SetWindowAttribs;
    
    Cursor                  olc_ArrowCursor;
    Cursor                  olc_InvisibleCursor;
    Pixmap                  olc_BitmapNoData;
    XColor                  olc_BlackColor;
#endif



#endif