/* Native Classic Mac OS OpenGL backend using AGL and OpenGLLibrary. */
#include "../../SDL_internal.h"
#include "sdl_mac.h"

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC
#ifdef SDL_VIDEO_OPENGL
#ifdef SDL_MACOSCLASSIC_OSGL

#include "SDL_agl.h"
#ifdef TARGET_OS_OSX
#else
#include <CodeFragments.h>
#endif

#include <SDL_render.h>

#ifdef SDL_MACOSCLASSIC_TINYGL
#include "GL/ostinygl.h"
#else
#include <GL/osmesa.h>
#endif


/* This supports both real Apple dynamic OpenGL, and static Mesa */

#ifdef __POWERPC__
//#define OPENGL_IS_DYNAMIC 1
#endif

#ifdef OPENGL_IS_DYNAMIC
#define NEED_EXT_FUNC
#endif


// TODO: This is a TEMPORARY hack!
// NOTE: Should be static
SDL_Window *theOnlyLonelyWindow;


#ifdef NEED_EXT_FUNCS
/* These are GL extensions and the names are "mangled"... */
/* This is NOT the right way...but works for now if they aren't called */
void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
  fprintf(stderr,"glBlendFuncSeparate...not implemented\n"); fflush(stderr);
}
void glBlendEquation(GLenum mode)
{
  fprintf(stderr,"glBlendEquation...not implemented\n"); fflush(stderr);
}
#else
extern void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
extern void glBlendEquation(GLenum mode);
#endif


extern DECLSPEC void SDLCALL SDL_Quit(void);


typedef struct OSGLPixelFormatRec
{
  int fake;
} OSGLPixelFormatRec;

#ifdef SDL_MACOSCLASSIC_TINYGL
typedef ostgl_context_t * OSGLContext;
#else
typedef OSMesaContext OSGLContext;
#endif


typedef struct MacGLContext
{
    OSGLContext osgl;
    SDL_Window *window;
    int drawable_attached;
    int double_buffered;
    struct MacGLContext *next;
} MacGLContext;


static CFragConnectionID gl_library;
static SDL_bool gl_library_open;
static MacGLContext *mac_current_context;
static MacGLContext *mac_contexts;
static int Mac_OSGLError(const char *operation);

static struct OSGLPixelFormatRec osPixelFormat;
typedef void * OSGLPixelFormat;
static OSGLPixelFormat osPixelFormatPtr=(OSGLPixelFormat)&osPixelFormat;

static SDL_Texture *texture = NULL;
static SDL_Renderer *renderer = NULL;

// TODO: This is a TEMPORARY hack!
SDL_Window *theOnlyLonelyWindow;

static int osError=0;
char *osBuffer=NULL;
OSGLContext osContext=NULL;


OSGLContext osglCreateContext(OSGLPixelFormat pix, OSGLContext share)
{
    //fprintf(stderr,"aglCreateContext....\n"); fflush(stderr); aglTheError=1;
    //fprintf(stderr,"aglTheScreenDepth is %d\n",aglTheScreenDepth); fflush(stderr);
    int winSizeX,winSizeY;
    SDL_GetWindowSize(theOnlyLonelyWindow,&winSizeX,&winSizeY);
#ifdef USING_SDL2
    if(!theOnlyLonelyWindow) {
      fprintf(stderr,"theOnlyLonelyWindow failed!\n"); fflush(stderr); aglTheError=1;
      return NULL;
    }  
    SDL_GetWindowSize(theOnlyLonelyWindow,&aglWinSizeX,&aglWinSizeY);
#endif
#ifdef SDL_MACOSCLASSIC_TINYGL
    fprintf(stderr,"osglCreateContext using TinyGL...\n"); fflush(stderr);
    int tDepth=myDepth;
    if(myDepth==32) {
      fprintf(stderr,"NOTE: Requested 32 bit, switching to 16!\n"); fflush(stderr);
      tDepth=16;
    }
  	osContext = ostgl_create_context(winSizeX,winSizeY,tDepth);
	  ostgl_make_current(osContext);
	  osBuffer=osContext->pixels;
#else
    fprintf(stderr,"osglCreateContext using Mesa...\n"); fflush(stderr);
    int format=OSMESA_RGB;
    if(myDepth==32) format=OSMESA_ARGB;  // Not sure this is right...
    int factor=2;
    if(myDepth==32) factor=4;
    fprintf(stderr,"myDepth is %d\n",myDepth); fflush(stderr);
    // TODO: The context is obviously not QUITE right...
  	osContext=OSMesaCreateContext(format,NULL);
  	osBuffer=(char *)malloc(winSizeX*winSizeY*factor);
    if(!osBuffer) {
      fprintf(stderr,"osBuffer failed!\n"); fflush(stderr); osError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got osBuffer\n"); fflush(stderr); } 
    GLboolean res=OSMesaMakeCurrent(osContext,osBuffer,GL_UNSIGNED_BYTE,winSizeX,winSizeY);
    if(!res) {
      fprintf(stderr,"OSMesaMakeCurrent failed!\n"); fflush(stderr); osError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got OSMesaMakeCurrent\n"); fflush(stderr); } 
#endif
    if(!osContext) {
      fprintf(stderr,"osContext failed!\n"); fflush(stderr); osError=1;
      return NULL;
    }
    else { fprintf(stderr,"got osContext\n"); fflush(stderr); }
//#ifdef USING_SDL2
    renderer = SDL_CreateRenderer(theOnlyLonelyWindow, -1, SDL_RENDERER_PRESENTVSYNC);	
    if(!renderer) {
      fprintf(stderr,"SDL_CreateRenderer failed!\n"); fflush(stderr); osError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got renderer\n"); fflush(stderr); } 
    texture = SDL_CreateTexture(renderer, SDL_GetWindowPixelFormat(theOnlyLonelyWindow), SDL_TEXTUREACCESS_STREAMING, winSizeX,winSizeY);
    if(!texture) {
      fprintf(stderr,"SDL_CreateTexture failed!\n"); fflush(stderr); osError=1;
      return NULL;
    }  
    else { fprintf(stderr,"got texture\n"); fflush(stderr); } 
//#endif
    fprintf(stderr,"osglCreateContext done\n"); fflush(stderr);
    return (OSGLContext)osContext;
}


void osglSwapBuffers(OSGLContext ctx)
{
//#ifdef USING_SDL2
    SDL_Surface *src=NULL;
    SDL_Surface *dst=NULL;
    int tFormat=SDL_PIXELFORMAT_RGB565;
    if(myDepth==32) tFormat=SDL_PIXELFORMAT_ARGB8888;
//#endif
    int winSizeX=640,winSizeY=480;
    int tDepth=myDepth;
#ifdef SDL_MACOSCLASSIC_TINYGL
    // Note: If doesn't match actual win size, we're wrong for win, right for buffer...
    winSizeX=((ostgl_context_t *)ctx)->width;
    winSizeY=((ostgl_context_t *)ctx)->height;
    // Same here...
    tDepth=((ostgl_context_t *)ctx)->depth;
    if(((ostgl_context_t *)ctx)->depth!=myDepth) {
      fprintf(stderr,"ostgl_context_t depth mismatch!\n"); fflush(stderr);
    }
#else
    // Mesa only?
    SDL_GetWindowSize(theOnlyLonelyWindow,&winSizeX,&winSizeY);
#endif
//#ifdef USING_SDL2
    // Would error checking here slow things down?
  	src = SDL_CreateRGBSurfaceWithFormatFrom(osBuffer, winSizeX, winSizeY, tDepth, ((winSizeX * tDepth) / 8), tFormat);
  	dst = SDL_CreateRGBSurfaceWithFormatFrom(NULL, winSizeX, winSizeY, 0, 0, SDL_GetWindowPixelFormat(theOnlyLonelyWindow));
	  if (SDL_LockTexture(texture, NULL, &dst->pixels, &dst->pitch) == 0)
	  {
		  if (SDL_BlitSurface(src, NULL, dst, NULL) != 0)
		  { SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "surface blit failed: %s", SDL_GetError()); }
		  SDL_UnlockTexture(texture);
	  }
	  else
	  { SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "texture lock failed: %s", SDL_GetError()); }
	  if(dst) SDL_FreeSurface(dst);
	  if(src) SDL_FreeSurface(src);
	  SDL_RenderClear(renderer);
	  SDL_RenderCopy(renderer, texture, NULL, NULL);
	  SDL_RenderPresent(renderer);
//#endif
}


GLenum osglGetError()
{
  return osError;
}


struct OSGLpixelfmtRec *osglChoosePixelFormat(void *gdevs, GLint ndev,  GLint *v)
{
  // We don't choose anything, there's only a single static one
  return (struct OSGLpixelfmtRec *)osPixelFormatPtr;
}


void osglDestroyPixelFormat(OSGLPixelFormat pix)
{
  // We don't destroy anything, there's only a single static one
}


GLboolean osglSetDrawable(OSGLContext ctx, AGLDrawable draw)
{
  //fprintf(stderr,"fake osglSetDrawable!\n"); fflush(stderr);
  return true;
}


GLboolean osglSetCurrentContext(OSGLContext ctx)
{
  //fprintf(stderr,"fake osglSetCurrentContext!\n"); fflush(stderr);
  return true;
}


GLboolean osglDestroyContext(OSGLContext ctx)
{
#ifdef SDL_MACOSCLASSIC_TINYGL
  ostgl_delete_context((ostgl_context_t *)ctx);
#else
#endif
  return true;
}


OSGLContext osglGetCurrentContext(void)
{
  return osContext;
}


GLboolean osglUpdateContext(OSGLContext ctx)
{
  //fprintf(stderr,"fake osglUpdateContext!\n"); fflush(stderr);
  return true;
}


GLboolean osglSetInteger(OSGLContext ctx, GLenum pname,const GLint *params)
{
  fprintf(stderr,"fake osglSetInteger %d %d!\n",pname,*params); fflush(stderr);
  switch(pname) {
    case AGL_SWAP_INTERVAL:
      fprintf(stderr,"osglSetInteger AGL_SWAP_INTERVAL not implemented\n"); fflush(stderr);
      break;
    default:
      fprintf(stderr,"osglSetInteger...pname %d to %d not implemented\n",pname,*params); fflush(stderr);
      break;
  }
    
  return true;
}


const GLubyte * osglErrorString(GLenum code)
{
  if(osError==1) return (GLubyte *)"Problem getting something!";
  else return (GLubyte *)"Who knows";
}


GLboolean osglDescribePixelFormat(OSGLPixelFormatRec *fmt,GLint what,GLint *value)
{
  // This is all fake, but plausible
  switch(what) {
    case AGL_RGBA:
      *value=1;
      return true;
      break;
    case AGL_ACCELERATED:
      *value=true;
      return true;
      break;
    case AGL_RENDERER_ID:
      *value=1;
      return true;
      break;
    case AGL_DEPTH_SIZE:
      *value=20;  // Random
      return true;
      break;
    case AGL_STENCIL_SIZE:
      *value=20;  // Random
      return true;
      break;
    case AGL_DOUBLEBUFFER:
      *value=true;
      return true;
      break;
    case AGL_PIXEL_SIZE:
      *value=myDepth;
      return true;
      break;
    default:
      fprintf(stderr,"osglDescribePixelFormat...what=%d not implemented\n",what); fflush(stderr);
      return false;
      break;
  }
  return false;
}


int Mac_GL_SetDrawableActive(int active)
{
    MacGLContext *context;
    int result = 0;

    active = active ? 1 : 0;
    for (context = mac_contexts; context; context = context->next) {
        if (context->drawable_attached == active)
            continue;

        if (active) {
            if (!macport || !osglSetDrawable(context->osgl, macport)) {
                Mac_OSGLError("osglSetDrawable(window)");
                result = -1;
                continue;
            }
        } else if (!osglSetDrawable(context->osgl, NULL)) {
            Mac_OSGLError("osglSetDrawable(NULL)");
            result = -1;
            continue;
        }

        context->drawable_attached = active;
    }
    return result;
}

void Mac_GL_Update(void)
{
    MacGLContext *context;

    if (!mac_window_active)
        return;
    for (context = mac_contexts; context; context = context->next) {
        if (context->drawable_attached && !osglUpdateContext(context->osgl)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "macosclassic: osglUpdateContext failed (AGL %u)",
                        (unsigned)osglGetError());
        }
    }
}

static int Mac_OSGLError(const char *operation)
{
    GLenum code = osglGetError();
    const GLubyte *description = osglErrorString(code);
    return SDL_SetError("%s failed (AGL %u: %s)", operation, (unsigned)code,
                        description ? (const char *)description : "unknown error");
}

/*static void Mac_CToPascal(const char *source, Str255 destination)
{
    size_t length = SDL_strlen(source);
    if (length > 255) length = 255;
    destination[0] = (unsigned char)length;
    SDL_memcpy(destination + 1, source, length);
}*/

int glLoadLibrary(_THIS, const char *name)
{
    Str255 library_name;
    Str255 error_name;
    Ptr main_address = NULL;
    OSErr error;

    if (gl_library_open) return 0;
#ifdef OPENGL_IS_DYNAMIC
    if (name && *name && SDL_strcmp(name, "OpenGLLibrary") != 0) {
        return SDL_SetError("Classic Mac OS supports only OpenGLLibrary");
    }

    Mac_CToPascal("OpenGLLibrary", library_name);
    error = GetSharedLibrary(library_name, kPowerPCCFragArch, kLoadCFrag,
                             &gl_library, &main_address, error_name);
    if (error != noErr) {
        return SDL_SetError("Unable to load OpenGLLibrary (CFM error %d)", (int)error);
    }
#else
#ifdef MAC_DEBUG
        fprintf(stderr,"macosclassic using static opengl...\n"); fflush(stderr);
#endif
#endif

    gl_library_open = SDL_TRUE;
    _this->gl_config.driver_loaded = 1;
    SDL_strlcpy(_this->gl_config.driver_path, "OpenGLLibrary",
                sizeof(_this->gl_config.driver_path));
    _this->gl_config.dll_handle = (void *)gl_library;
    return 0;
}

void *glGetProcAddress(_THIS, const char *proc)
{
    Str255 symbol_name;
    Ptr symbol = NULL;
    CFragSymbolClass symbol_class;
    OSErr error;
    (void)_this;

    if (!proc || !*proc) return NULL;
#ifdef MAC_DEBUG
        fprintf(stderr,"glGetProcAddress %s\n",proc); fflush(stderr);
#endif
    if (!gl_library_open && glLoadLibrary(_this, NULL) < 0) return NULL;
#ifdef OPENGL_IS_DYNAMIC

/* These are GL extensions and the names are "mangled"... */
/* This is NOT the right way...but works for now if they aren't called */
    if(!strcmp("glBlendEquation",proc)) return (void *)glBlendEquation;
    if(!strcmp("glBlendFuncSeparate",proc)) return (void *)glBlendFuncSeparate;
    
    Mac_CToPascal(proc, symbol_name);
    error = FindSymbol(gl_library, symbol_name, &symbol, &symbol_class);
    if (error != noErr ||
        (symbol_class != kCodeCFragSymbol &&
         symbol_class != kTVectorCFragSymbol &&
         symbol_class != kGlueCFragSymbol)) {
        return NULL;
    }
#ifdef MAC_DEBUG
        fprintf(stderr,"Got it.\n"); fflush(stderr);
#endif
#else
    /* There's a better way to do this...but this works for now... */
    if(!strcmp("glBegin",proc)) symbol=(void *)glBegin;
    if(!strcmp("glBindTexture",proc)) symbol=(void *)glBindTexture;
    if(!strcmp("glClear",proc)) symbol=(void *)glClear;
    if(!strcmp("glClearColor",proc)) symbol=(void *)glClear;
    if(!strcmp("glColor3fv",proc)) symbol=(void *)glColor3fv;
    if(!strcmp("glColor4f",proc)) symbol=(void *)glColor4f;
    if(!strcmp("glColorPointer",proc)) symbol=(void *)glColorPointer;
    if(!strcmp("glDeleteTextures",proc)) symbol=(void *)glDeleteTextures;
    if(!strcmp("glDisable",proc)) symbol=(void *)glDisable;
    if(!strcmp("glDisableClientState",proc)) symbol=(void *)glDisableClientState;
    if(!strcmp("glDrawArrays",proc)) symbol=(void *)glDrawArrays;
    if(!strcmp("glDrawPixels",proc)) symbol=(void *)glDrawPixels;
    if(!strcmp("glEnable",proc)) symbol=(void *)glEnable;
    if(!strcmp("glEnableClientState",proc)) symbol=(void *)glEnableClientState;
    if(!strcmp("glEnd",proc)) symbol=(void *)glEnd;
    if(!strcmp("glGenTextures",proc)) symbol=(void *)glGenTextures;
    if(!strcmp("glGetError",proc)) symbol=(void *)glGetError;
    if(!strcmp("glGetFloatv",proc)) symbol=(void *)glGetFloatv;
    if(!strcmp("glGetIntegerv",proc)) symbol=(void *)glGetIntegerv;
    if(!strcmp("glGetString",proc)) symbol=(void *)glGetString;
    if(!strcmp("glLoadIdentity",proc)) symbol=(void *)glLoadIdentity;
    if(!strcmp("glMatrixMode",proc)) symbol=(void *)glMatrixMode;
    if(!strcmp("glPointSize",proc)) symbol=(void *)glPointSize;
    if(!strcmp("glReadBuffer",proc)) symbol=(void *)glReadBuffer;
    if(!strcmp("glReadPixels",proc)) symbol=(void *)glReadPixels;
    if(!strcmp("glRectf",proc)) symbol=(void *)glRectf;
    if(!strcmp("glRotatef",proc)) symbol=(void *)glRotatef;
    if(!strcmp("glShadeModel",proc)) symbol=(void *)glShadeModel;
    if(!strcmp("glTexCoord2f",proc)) symbol=(void *)glTexCoord2f;
    if(!strcmp("glTexCoordPointer",proc)) symbol=(void *)glTexCoordPointer;
    if(!strcmp("glTexParameteri",proc)) symbol=(void *)glTexParameteri;
    if(!strcmp("glVertex2f",proc)) symbol=(void *)glVertex2f;
    if(!strcmp("glVertex3fv",proc)) symbol=(void *)glVertex3fv;
    if(!strcmp("glVertexPointer",proc)) symbol=(void *)glVertexPointer;
    if(!strcmp("glViewport",proc)) symbol=(void *)glViewport;
    //
    if(!strcmp("glBlendFuncSeparate",proc)) symbol=(void *)glBlendFuncSeparate;
    if(!strcmp("glBlendEquation",proc)) symbol=(void *)glBlendEquation;
    //
    if(!strcmp("glOrtho",proc)) symbol=(void *)glOrtho;
    if(!strcmp("glTexEnvf",proc)) symbol=(void *)glTexEnvf;
    if(!strcmp("glDepthFunc",proc)) symbol=(void *)glDepthFunc;
    if(!strcmp("glScissor",proc)) symbol=(void *)glScissor;
    if(!strcmp("glTexSubImage2D",proc)) symbol=(void *)glTexSubImage2D;
    if(!strcmp("glGetPointerv",proc)) symbol=(void *)glGetPointerv;
    if(!strcmp("glLineWidth",proc)) symbol=(void *)glLineWidth;
    if(!strcmp("glTexImage2D",proc)) symbol=(void *)glTexImage2D;
    if(!strcmp("glRasterPos2i",proc)) symbol=(void *)glRasterPos2i;
    if(!strcmp("glPixelStorei",proc)) symbol=(void *)glPixelStorei;
    if(!strcmp("glColor4ub",proc)) symbol=(void *)glColor4ub;
    //
    if(!symbol) {
    /*
#ifdef MAC_DEBUG
      fprintf(stderr,"Returning fake pointer for %s...this will cause a crash when called!\n",proc); fflush(stderr);
#endif
      symbol=(void *)0x8000;
      */
      fprintf(stderr,"Func for %s...does not exist\n",proc); fflush(stderr);
      SDL_Quit();
      exit(5);
    }
#ifdef MAC_DEBUG
      fprintf(stderr,"Returning 0x%x\n",(int)symbol); fflush(stderr);
#endif

#endif
    return (void *)symbol;
}

static void Mac_AddGLAttribute(GLint *attributes, int *count,
                               GLint attribute, GLint value)
{
    attributes[(*count)++] = attribute;
    if (value >= 0) attributes[(*count)++] = value;
}

SDL_GLContext glCreateContext(_THIS, SDL_Window *window)
{
    GLint attributes[48];
    int count = 0;
    int double_buffer_attribute = -1;
    int i;
    AGLDevice device;
    OSGLPixelFormat pixel_format;
    OSGLContext share = NULL;
    MacGLContext *context;
    GLint accelerated = 0;
    GLint renderer_id = 0;
    GLint pixel_size = 0;
    GLint depth_size = 0;
    GLint stencil_size = 0;
    GLint double_buffer = 0;

// TODO: This is a TEMPORARY hack!
theOnlyLonelyWindow=window;

    if (!window || !macwindow) {
        SDL_SetError("OpenGL context requires a native Classic window");
        return NULL;
    }
    if (_this->gl_config.profile_mask & (SDL_GL_CONTEXT_PROFILE_CORE |
                                         SDL_GL_CONTEXT_PROFILE_ES)) {
        SDL_SetError("Classic OpenGL supports only the compatibility profile");
        return NULL;
    }
    if (_this->gl_config.major_version > 1 ||
        (_this->gl_config.major_version == 1 && _this->gl_config.minor_version > 5)) {
#ifdef MAC_DEBUG
        fprintf(stderr,"Asked for OpenGL %d.%d\n",_this->gl_config.major_version,_this->gl_config.minor_version); fflush(stderr);
#endif
        SDL_SetError("Classic OpenGL runtime provides OpenGL 1.5");
        return NULL;
    }
    if (!gl_library_open && glLoadLibrary(_this, NULL) < 0) return NULL;

    device = GetMainDevice();
    Mac_AddGLAttribute(attributes, &count, AGL_RGBA, -1);
    Mac_AddGLAttribute(attributes, &count, AGL_PIXEL_SIZE, myDepth);
    Mac_AddGLAttribute(attributes, &count, AGL_CLOSEST_POLICY, -1);
    if (_this->gl_config.double_buffer) {
        double_buffer_attribute = count;
        Mac_AddGLAttribute(attributes, &count, AGL_DOUBLEBUFFER, -1);
    }
    if (_this->gl_config.stereo) Mac_AddGLAttribute(attributes, &count, AGL_STEREO, -1);
    if (_this->gl_config.accelerated > 0) {
        Mac_AddGLAttribute(attributes, &count, AGL_ACCELERATED, -1);
        Mac_AddGLAttribute(attributes, &count, AGL_NO_RECOVERY, -1);
    }
    if (_this->gl_config.red_size) Mac_AddGLAttribute(attributes, &count, AGL_RED_SIZE, _this->gl_config.red_size);
    if (_this->gl_config.green_size) Mac_AddGLAttribute(attributes, &count, AGL_GREEN_SIZE, _this->gl_config.green_size);
    if (_this->gl_config.blue_size) Mac_AddGLAttribute(attributes, &count, AGL_BLUE_SIZE, _this->gl_config.blue_size);
    if (_this->gl_config.alpha_size) Mac_AddGLAttribute(attributes, &count, AGL_ALPHA_SIZE, _this->gl_config.alpha_size);
    if (_this->gl_config.depth_size) Mac_AddGLAttribute(attributes, &count, AGL_DEPTH_SIZE, _this->gl_config.depth_size);
    if (_this->gl_config.stencil_size) Mac_AddGLAttribute(attributes, &count, AGL_STENCIL_SIZE, _this->gl_config.stencil_size);
    if (_this->gl_config.accum_red_size) Mac_AddGLAttribute(attributes, &count, AGL_ACCUM_RED_SIZE, _this->gl_config.accum_red_size);
    if (_this->gl_config.accum_green_size) Mac_AddGLAttribute(attributes, &count, AGL_ACCUM_GREEN_SIZE, _this->gl_config.accum_green_size);
    if (_this->gl_config.accum_blue_size) Mac_AddGLAttribute(attributes, &count, AGL_ACCUM_BLUE_SIZE, _this->gl_config.accum_blue_size);
    if (_this->gl_config.accum_alpha_size) Mac_AddGLAttribute(attributes, &count, AGL_ACCUM_ALPHA_SIZE, _this->gl_config.accum_alpha_size);
    if (_this->gl_config.multisamplebuffers) {
        Mac_AddGLAttribute(attributes, &count, AGL_SAMPLE_BUFFERS_ARB, _this->gl_config.multisamplebuffers);
        Mac_AddGLAttribute(attributes, &count, AGL_SAMPLES_ARB, _this->gl_config.multisamplesamples);
    }
    attributes[count++] = AGL_NONE;

    pixel_format = osglChoosePixelFormat((void *)&device, 1, attributes);
#ifdef MAC_DEBUG
  fprintf(stderr,"pixel_format=%x double_buffer_attribute=%d accerlated=%d\n",(unsigned int)pixel_format,double_buffer_attribute,_this->gl_config.accelerated); fflush(stderr);
#endif
    if (!pixel_format && double_buffer_attribute >= 0 &&
        _this->gl_config.accelerated > 0) {
        GLenum first_error = osglGetError();

        /* Retry without double buffering while preserving the requested
           acceleration attributes. */
        for (i = double_buffer_attribute; i < count - 1; ++i)
            attributes[i] = attributes[i + 1];
        --count;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                     "macosclassic: hardware double buffering unavailable "
                     "(0x%lx); retrying with a single buffer",
                     (unsigned long)first_error);
        pixel_format = osglChoosePixelFormat(&device, 1, attributes);
    }
    if (!pixel_format) {
        Mac_OSGLError("osglChoosePixelFormat");
        return NULL;
    }

    if (!osglDescribePixelFormat(pixel_format, AGL_PIXEL_SIZE, &pixel_size)) {
        Mac_OSGLError("osglDescribePixelFormat(AGL_PIXEL_SIZE)");
        osglDestroyPixelFormat(pixel_format);
        return NULL;
    }
    osglDescribePixelFormat(pixel_format, AGL_ACCELERATED, &accelerated);
    osglDescribePixelFormat(pixel_format, AGL_RENDERER_ID, &renderer_id);
    osglDescribePixelFormat(pixel_format, AGL_DEPTH_SIZE, &depth_size);
    osglDescribePixelFormat(pixel_format, AGL_STENCIL_SIZE, &stencil_size);
    osglDescribePixelFormat(pixel_format, AGL_DOUBLEBUFFER, &double_buffer);
    (void)osglGetError();
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                 "macosclassic: AGL format accelerated=%ld renderer=0x%lx "
                 "color=%ld depth=%ld stencil=%ld double=%ld",
                 (long)accelerated, (unsigned long)renderer_id,
                 (long)pixel_size, (long)depth_size, (long)stencil_size,
                 (long)double_buffer);

    if (_this->gl_config.accelerated > 0 && !accelerated) {
        osglDestroyPixelFormat(pixel_format);
        SDL_SetError("AGL returned a software format for a hardware-only request");
        return NULL;
    }
    if (pixel_size != myDepth) {
        /* A 32-bit display may have only a 16-bit accelerated AGL format. */
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: display is %d-bit but AGL will render to "
                    "a %ld-bit color buffer",
                    myDepth, (long)pixel_size);
    }

    if (_this->gl_config.share_with_current_context && _this->current_glctx) {
        share = ((MacGLContext *)_this->current_glctx)->osgl;
    }
    context = (MacGLContext *)SDL_calloc(1, sizeof(*context));
    if (!context) {
        osglDestroyPixelFormat(pixel_format);
        SDL_OutOfMemory();
        return NULL;
    }
    context->osgl = osglCreateContext(pixel_format, share);
    context->double_buffered = double_buffer ? 1 : 0;
    osglDestroyPixelFormat(pixel_format);
    if (!context->osgl) {
        SDL_free(context);
        Mac_OSGLError("osglCreateContext");
        return NULL;
    }
    context->window = window;
    if (!osglSetDrawable(context->osgl, macport) ||
        !osglSetCurrentContext(context->osgl)) {
        osglSetDrawable(context->osgl, NULL);
        osglDestroyContext(context->osgl);
        SDL_free(context);
        Mac_OSGLError("attaching the AGL drawable");
        return NULL;
    }
    context->drawable_attached = 1;
    context->next = mac_contexts;
    mac_contexts = context;
    mac_current_context = context;
    return (SDL_GLContext)context;
}

int glSetSwapInterval(_THIS, int interval)
{
    MacGLContext *context = (MacGLContext *)_this->current_glctx;
    GLint value = interval;
    if (!context) return SDL_SetError("No current Classic OpenGL context");
    if (interval < 0) return SDL_SetError("Adaptive swap interval is unavailable on Classic OpenGL");
    /* There is no back-buffer presentation point to synchronize. Accept the
       application's preference while leaving front-buffer delivery alone. */
    if (!context->double_buffered) return 0;
    if (!osglSetInteger(context->osgl, AGL_SWAP_INTERVAL, &value)) {
        return Mac_OSGLError("osglSetInteger(AGL_SWAP_INTERVAL)");
    }
    return 0;
}

int glSwapWindow(_THIS, SDL_Window *window)
{
    MacGLContext *context = (MacGLContext *)_this->current_glctx;
    if (!context || context->window != window) {
        return SDL_SetError("The window does not own the current OpenGL context");
    }
    if (mac_window_active && context->drawable_attached) {
        if (context->double_buffered)
            osglSwapBuffers(context->osgl);
        else
            glFlush();
    }
    return 0;
}

int glMakeCurrent(_THIS, SDL_Window *window, SDL_GLContext sdl_context)
{
    MacGLContext *context = (MacGLContext *)sdl_context;
    (void)_this;
    if (!context) {
        if (!osglSetCurrentContext(NULL)) return Mac_OSGLError("osglSetCurrentContext(NULL)");
        mac_current_context = NULL;
        return 0;
    }
    if (window && context->window != window) {
        context->window = window;
    }
    if (!osglSetCurrentContext(context->osgl)) return Mac_OSGLError("osglSetCurrentContext");
    mac_current_context = context;
    return 0;
}

void glUpdateWindow(_THIS, SDL_Window *window)
{
    MacGLContext *context;
    (void)_this;

    if (!mac_window_active)
        return;
    for (context = mac_contexts; context; context = context->next) {
        if (context->window == window && context->drawable_attached &&
            !osglUpdateContext(context->osgl)) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "macosclassic: osglUpdateContext failed (AGL %u)",
                        (unsigned)osglGetError());
        }
    }
}

void glDeleteContext(_THIS, SDL_GLContext sdl_context)
{
    MacGLContext *context = (MacGLContext *)sdl_context;
    MacGLContext **link;
    (void)_this;
    if (!context) return;

    for (link = &mac_contexts; *link; link = &(*link)->next) {
        if (*link == context) {
            *link = context->next;
            break;
        }
    }
    if (osglGetCurrentContext() == context->osgl) osglSetCurrentContext(NULL);
    osglSetDrawable(context->osgl, NULL);
    if (mac_current_context == context) mac_current_context = NULL;
    osglDestroyContext(context->osgl);
    SDL_free(context);
}

void glUnloadLibrary(_THIS)
{
    if (gl_library_open) {
        CloseConnection(&gl_library);
        gl_library_open = SDL_FALSE;
    }
    mac_current_context = NULL;
    _this->gl_config.driver_loaded = 0;
    _this->gl_config.dll_handle = NULL;
    _this->gl_config.driver_path[0] = '\0';
}

#endif
#endif
#endif
