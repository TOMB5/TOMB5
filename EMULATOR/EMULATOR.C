#include "EMULATOR.H"

#include "EMULATOR_VERSION.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"
#include "CRASHHANDLER.H"

#include "EMULATOR_PLATFORM_SETUP.H"

#include "LIBGPU.H"
#include "LIBETC.H"
#include "LIBPAD.H"

//#include <stdio.h>
//#include <string.h>
#if !defined(__ANDROID__)
//#include <thread>
#endif
#include <assert.h>

#define VERTEX_COLOUR_MULT (2)

#if defined(NTSC_VERSION)
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <SDL_syswm.h>

SDL_Window* g_window = NULL;
GLuint vramTexture;
GLuint vramFrameBuffer = 0;
GLuint vramRenderBuffer = 0;
GLuint nullWhiteTexture;
GLint g_defaultFBO;
int screenWidth = 0;
int screenHeight = 0;
int windowWidth = 0;
int windowHeight = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = { 0 };
#if !defined(__ANDROID__)
//std::thread counter_thread;
#endif
int g_hasHintedTextureAtlas = 0;
struct CachedTexture cachedTextures[MAX_NUM_CACHED_TEXTURES];

static int Emulator_InitialiseGLContext(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);

#if defined(OGL)
	SDL_GL_CreateContext(g_window);
#endif

	if (g_window == NULL)
	{
		eprinterr("Failed to initialise GL context!\n");
		return FALSE;
	}

	return TRUE;
}

#if defined(OGLES)
EGLint majorVersion = 0, minorVersion = 0;
EGLContext eglContext = NULL;
EGLSurface eglSurface = NULL;
EGLConfig eglConfig = NULL;
EGLDisplay eglDisplay = NULL;
int numConfigs = 0;

const EGLint config16bpp[] =
{
#if OGLES_VERSION == 2
        EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
#elif OGLES_VERSION == 3
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES3_BIT,
#endif
		EGL_BUFFER_SIZE,24,
		EGL_RED_SIZE,8,
		EGL_GREEN_SIZE,8,
		EGL_BLUE_SIZE,8,
		EGL_ALPHA_SIZE,0,
		EGL_DEPTH_SIZE,24,
		EGL_STENCIL_SIZE,0,
		EGL_SAMPLE_BUFFERS,1,
		EGL_SAMPLES,4,
		EGL_NONE
};

static int Emulator_InitialiseGLESContext(char* windowName)
{
	unsigned int windowFlags = SDL_WINDOW_OPENGL;

#if defined(__ANDROID__)
	windowFlags |= SDL_WINDOW_FULLSCREEN;
#endif

    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, windowFlags);

	if(g_window == NULL)
    {
	    eprinterr("Failed to create SDL window!\n");
    }

	if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
	{
		eprinterr("eglInitialize failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	eglBindAPI(EGL_OPENGL_ES_API);

	if (!eglChooseConfig(eglDisplay, config16bpp, &eglConfig, 1, &numConfigs))
	{
		printf("eglChooseConfig failed\n");
		if (eglContext == 0)
		{
			printf("Error code: %d\n", eglGetError());
		}
	}

	SDL_SysWMinfo systemInfo;
	SDL_VERSION(&systemInfo.version);
	SDL_GetWindowWMInfo(g_window, &systemInfo);
#if defined(__EMSCRIPTEN__)
	EGLNativeWindowType dummyWindow;
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)dummyWindow, NULL);
#elif defined(__ANDROID__)
	eglSurface = systemInfo.info.android.surface;
#else
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)systemInfo.info.win.window, NULL);
#endif
	if (eglSurface == EGL_NO_SURFACE)
	{
		eprinterr("eglSurface failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, OGLES_VERSION, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);

	if (eglContext == EGL_NO_CONTEXT) {
        eprinterr("eglContext failure! Error: %x\n", eglGetError());
        return FALSE;
    }

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

	return TRUE;
}

#endif

static int Emulator_InitialiseSDL(char* windowName, int screenWidth, int screenHeight)
{
	screenWidth = screenWidth;
	screenHeight = screenHeight;
	windowWidth = screenWidth;
	windowHeight = screenHeight;

	//Initialise SDL2
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
#if !defined(RO_DOUBLE_BUFFERED)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
#endif

#if defined(OGLES)

#if defined(__ANDROID__)
        //Override to full screen.
        SDL_DisplayMode displayMode;
        if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
        {
            screenWidth = displayMode.w;
            windowWidth = displayMode.w;
            screenHeight = displayMode.h;
            windowHeight = displayMode.h;
        }
#endif
        //SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OGLES_VERSION);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#elif defined(OGL)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
		return FALSE;
	}

#if defined(OGL)
	Emulator_InitialiseGLContext(windowName);
#elif defined(OGLES)
	Emulator_InitialiseGLESContext(windowName);
#endif

#if defined(OGL)
	SDL_GL_SetSwapInterval(1);
#elif defined(OGLES)
	eglSwapInterval(eglDisplay, 1);
#endif

	return TRUE;
}

static int Emulator_InitialiseGLEW()
{
#if defined(GLEW)
	glewExperimental = GL_TRUE;

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		return FALSE;
	}
#endif
	return TRUE;
}

static void Emulator_InitialiseCore()
{
	//Initialise texture cache
	SDL_memset(&cachedTextures[0], -1, MAX_NUM_CACHED_TEXTURES * sizeof(struct CachedTexture));
}

void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight)
{
	eprintf("Initialising Emulator.\n");
	eprintf("VERSION: %d.%d\n", EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION);
	eprintf("Compile Date: %s Time: %s\n", EMULATOR_COMPILE_DATE, EMULATOR_COMPILE_TIME);

	Emulator_InitialiseSDL(windowName, screenWidth, screenHeight);

#if defined(GLEW)
	Emulator_InitialiseGLEW();
#endif

	Emulator_InitialiseCore();

#if defined(OGL) || defined(OGLES)
	Emulator_InitialiseGL();
#endif

	//counter_thread = std::thread(Emulator_CounterLoop);
}

void Emulator_CounterLoop()
{
	static int numUpdates = 0;
	int last_time = 0;

	while (TRUE)
	{
		int now = SDL_GetTicks();

		if (now > last_time + 1000)
		{
			numUpdates = 0;
			last_time = now;
		}

		if (numUpdates++ <= 60)
		{
			for (int i = 0; i < 3; i++)
			{
				//if (!counters[i].IsStopped)
				{
					counters[i].cycle += COUNTER_UPDATE_INTERVAL;
					if (counters[i].target > 0)
					{
						counters[i].cycle %= counters[i].target;
					}
				}
			}
		}
	}
}

void Emulator_GenerateLineArray(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3)
{
	//Copy over position
	if (p0 != NULL)
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
	}

	if (p1 != NULL)
	{
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
	}
}

void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3, short w, short h)
{
#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;
	PGXPVertex* pgxp_vertex_1 = NULL;
	PGXPVertex* pgxp_vertex_2 = NULL;
	PGXPVertex* pgxp_vertex_3 = NULL;

	//Locate each vertex based on SXY2 (very slow)
	for (int i = 0; i < pgxp_vertex_index; i++)
	{
		if (p0 != NULL)
		{
			if (((unsigned int*)p0)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_0 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (p1 != NULL)
		{
			if (((unsigned int*)p1)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_1 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (p2 != NULL)
		{
			if (((unsigned int*)p2)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_2 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (p3 != NULL)
		{
			if (((unsigned int*)p3)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_3 = &pgxp_vertex_buffer[i];
				continue;
			}
		}
	}
#endif

	//Copy over position
	if (p0 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_0 != NULL)
		{
			vertex[0].x = pgxp_vertex_0->x;
			vertex[0].y = pgxp_vertex_0->y;
		}
		else
		{
			vertex[0].x = (float)p0[0];
			vertex[0].y = (float)p0[1];
		}
#else
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
#endif
	}

	if (p1 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_1 != NULL)
		{
			vertex[1].x = pgxp_vertex_1->x;
			vertex[1].y = pgxp_vertex_1->y;
		}
		else
		{
			vertex[1].x = (float)p1[0];
			vertex[1].y = (float)p1[1];
		}
#else
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
#endif
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].x = (float)p0[0];
			vertex[1].y = (float)p0[1] + h;
		}
	}

	if (p2 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_2 != NULL)
		{
			vertex[2].x = pgxp_vertex_2->x;
			vertex[2].y = pgxp_vertex_2->y;
		}
		else
		{
			vertex[2].x = (float)p2[0];
			vertex[2].y = (float)p2[1];
		}
#else
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
#endif
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].x = (float)p0[0] + w;
			vertex[2].y = (float)p0[1] + h;
		}
	}

	if (p3 != NULL)
	{
#if defined(PGXP)
		if (pgxp_vertex_3 != NULL)
		{
			vertex[3].x = pgxp_vertex_3->x;
			vertex[3].y = pgxp_vertex_3->y;
		}
		else
		{
			vertex[3].x = (float)p3[0];
			vertex[3].y = (float)p3[1];
		}
#else
		vertex[3].x = (float)p3[0];
		vertex[3].y = (float)p3[1];
#endif
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].x = (float)p0[0] + w;
			vertex[3].y = (float)p0[1];
		}
	}
	return;
}


void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short w, short h)
{
#if defined(PGXP) && 0
	/*
	Locate polygon in ztable
	*/

	PGXPPolygon* z0 = NULL;
	PGXPPolygon* z1 = NULL;
	PGXPPolygon* z2 = NULL;
	PGXPPolygon* z3 = NULL;

	//Can speed this up by storing last index found and using as start iter
	for (int i = pgxp_polgon_table_index; i > -1; i--)
	{
		if (uv0 != NULL)
		{
			if (((unsigned int*)uv0)[0] == pgxp_polygons[i].originalSXY)
			{
				z0 = &pgxp_polygons[i];
				//z0->bUsed = TRUE;
			}
		}

		if (uv1 != NULL)
		{
			if (((unsigned int*)uv1)[0] == pgxp_polygons[i].originalSXY)
			{
				z1 = &pgxp_polygons[i];
				//z1->bUsed = TRUE;
			}
		}

		if (uv2 != NULL)
		{
			if (((unsigned int*)uv2)[0] == pgxp_polygons[i].originalSXY)
			{
				z2 = &pgxp_polygons[i];
				//z2->bUsed = TRUE;
			}
		}

		if (uv3 != NULL)
		{
			if (((unsigned int*)uv3)[0] == pgxp_polygons[i].originalSXY)
			{
				z3 = &pgxp_polygons[i];
				//z3->bUsed = TRUE;
			}
		}

		if ((z0 != NULL || uv0 == NULL) && (z1 != NULL || uv1 == NULL) && (z2 != NULL || uv2 == NULL) && (z3 != NULL || uv3 == NULL))
			break;
	}

	//Copy over uvs
	if (uv0 != NULL)
	{
		if (z0 != NULL)
		{
			vertex[0].u0 = z0->x;
			vertex[0].v0 = z0->y;
		}
		else
		{
			vertex[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[0].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
		}
	}

	if (uv1 != NULL)
	{
		if (z1 != NULL)
		{
			vertex[1].u0 = z1->x;
			vertex[1].v0 = z1->y;
		}
		else
		{
			vertex[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv1[1]) / TPAGE_HEIGHT;
		}
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv2 != NULL)
	{
		if (z2 != NULL)
		{
			vertex[2].u0 = z2->x;
			vertex[2].v0 = z2->y;
		}
		else
		{
			vertex[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv2[1]) / TPAGE_HEIGHT;
		}
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv3 != NULL)
	{
		if (z3 != NULL)
		{
			vertex[3].u0 = z3->x;
			vertex[3].v0 = z3->y;
		}
		else
		{
			vertex[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv3[1]) / TPAGE_HEIGHT;
		}
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
		}
	}

#else
	//Copy over uvs
	if (uv0 != NULL)
	{
		vertex[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
		vertex[0].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
	}

	if (uv1 != NULL)
	{
		vertex[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
		vertex[1].v0 = ((float)uv1[1]) / TPAGE_HEIGHT;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv2 != NULL)
	{
		vertex[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
		vertex[2].v0 = ((float)uv2[1]) / TPAGE_HEIGHT;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv0[1] + h) / TPAGE_HEIGHT;
		}
	}

	if (uv3 != NULL)
	{
		vertex[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
		vertex[3].v0 = ((float)uv3[1]) / TPAGE_HEIGHT;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv0[1]) / TPAGE_HEIGHT;
		}
	}
#endif
	return;
}

void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, int bMultiplyColour)
{
	//Copy over rgb vertex colours
	if (col0 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[0].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[0].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[0].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[0].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[0].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[0].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[0].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[0].col[3] = (1.0f / 255.0f) * 255;
		}
	}

	if (col1 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[1].col[0] = ((1.0f / 255.0f) * col1[0]) * VERTEX_COLOUR_MULT;
			vertex[1].col[1] = ((1.0f / 255.0f) * col1[1]) * VERTEX_COLOUR_MULT;
			vertex[1].col[2] = ((1.0f / 255.0f) * col1[2]) * VERTEX_COLOUR_MULT;
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[1].col[0] = (1.0f / 255.0f) * col1[0];
			vertex[1].col[1] = (1.0f / 255.0f) * col1[1];
			vertex[1].col[2] = (1.0f / 255.0f) * col1[2];
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertex[1].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[1].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[1].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[1].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[1].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[1].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[1].col[3] = (1.0f / 255.0f) * 255;
		}
	}

	if (col2 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[2].col[0] = ((1.0f / 255.0f) * col2[0]) * VERTEX_COLOUR_MULT;
			vertex[2].col[1] = ((1.0f / 255.0f) * col2[1]) * VERTEX_COLOUR_MULT;
			vertex[2].col[2] = ((1.0f / 255.0f) * col2[2]) * VERTEX_COLOUR_MULT;
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[2].col[0] = (1.0f / 255.0f) * col2[0];
			vertex[2].col[1] = (1.0f / 255.0f) * col2[1];
			vertex[2].col[2] = (1.0f / 255.0f) * col2[2];
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertex[2].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[2].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[2].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[2].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[2].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[2].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[2].col[3] = (1.0f / 255.0f) * 255;
		}
	}

	if (col3 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[3].col[0] = ((1.0f / 255.0f) * col3[0]) * VERTEX_COLOUR_MULT;
			vertex[3].col[1] = ((1.0f / 255.0f) * col3[1]) * VERTEX_COLOUR_MULT;
			vertex[3].col[2] = ((1.0f / 255.0f) * col3[2]) * VERTEX_COLOUR_MULT;
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[3].col[0] = (1.0f / 255.0f) * col3[0];
			vertex[3].col[1] = (1.0f / 255.0f) * col3[1];
			vertex[3].col[2] = (1.0f / 255.0f) * col3[2];
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertex[3].col[0] = ((1.0f / 255.0f) * col0[0]) * VERTEX_COLOUR_MULT;
			vertex[3].col[1] = ((1.0f / 255.0f) * col0[1]) * VERTEX_COLOUR_MULT;
			vertex[3].col[2] = ((1.0f / 255.0f) * col0[2]) * VERTEX_COLOUR_MULT;
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
		}
		else
		{
			vertex[3].col[0] = (1.0f / 255.0f) * col0[0];
			vertex[3].col[1] = (1.0f / 255.0f) * col0[1];
			vertex[3].col[2] = (1.0f / 255.0f) * col0[2];
			vertex[3].col[3] = (1.0f / 255.0f) * 255;
		}
	}

	return;
}

#if defined(OGLES) || defined(OGL)
GLuint g_defaultShaderProgram;

void Emulator_CreateGlobalShaders()
{
#if defined(ES2_SHADERS)
	const char* vertexShaderSource = "attribute vec4 a_position; attribute vec2 a_texcoord; varying vec2 v_texcoord; attribute vec4 a_colour; varying vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#elif defined(ES3_SHADERS)
	const char* vertexShaderSource = "#version 300 es\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#elif defined(OGL)
	const char* vertexShaderSource = "#version 330 core\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; uniform mat4 Scale; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*(a_position*Scale);  }";
#endif
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
#if defined(ES2_SHADERS)
	const char* fragmentShaderSource = "precision mediump float; varying vec2 v_texcoord; varying vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; void main() { gl_FragColor = texture2D(s_texture, v_texcoord); if (gl_FragColor.a == 0.0 && bDiscardBlack) { discard; } gl_FragColor *= v_colour; }";
#elif defined(ES3_SHADERS)
	const char* fragmentShaderSource = "#version 300 es\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord) * v_colour; }";
#elif defined(OGL)
	const char* fragmentShaderSource = "#version 330 core\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord); if (fragColour.a == 0.0 && bDiscardBlack) { discard; } fragColour *= v_colour; }";
#endif

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

#if defined(_DEBUG)
	char buff[1024];
	int maxLength = 1024;
	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &buff[0]);

	printf("%s", &buff[0]);

	maxLength = 1024;
	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &buff[0]);

	printf("%s", &buff[0]);
#endif

	/* Default */
	g_defaultShaderProgram = glCreateProgram();
	glAttachShader(g_defaultShaderProgram, vertexShader);
	glAttachShader(g_defaultShaderProgram, fragmentShader);
	glLinkProgram(g_defaultShaderProgram);
	glUseProgram(g_defaultShaderProgram);
	GLint idx = glGetUniformLocation(g_defaultShaderProgram, "s_texture");
	GLint sampler = 0;
	glUniform1iv(idx, 1, &sampler);
	glActiveTexture(GL_TEXTURE0 + sampler);
}
#endif

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

void Emulator_InitialiseGL()
{
	glEnable(GL_BLEND);

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &g_defaultFBO);

	/* Initialise VRAM */
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

	/* Generate NULL white texture */
	Emulator_GenerateAndBindNullWhite();
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_SCISSOR_TEST);
	glBlendColor(0.25f, 0.25f, 0.25f, 0.5f);
	glGenTextures(1, &vramTexture);
	Emulator_BindTexture(vramTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if defined(OGLES)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &vram[0]);
#elif defined(OGL)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
#endif
	/* Generate VRAM Frame Buffer */
	glGenFramebuffers(1, &vramFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);

	eprintf("FrameBufferId: %d\n", vramFrameBuffer);

	/* Bind VRAM texture to vram framebuffer */
#if defined (OGLES)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vramTexture, 0);
#elif defined(OGL)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glGetError());
		eprinterr("Frame buffer status : %d\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
		exit(0);
	}
#endif

	glLineWidth(RESOLUTION_SCALE);

#if defined(OGL)
	glEnable(GL_DEPTH_TEST);
#endif

#if defined(OGLES) || defined(OGL)
	Emulator_CreateGlobalShaders();
#endif

	Emulator_BindTexture(0);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
}

GLuint g_lastBoundTexture = -1;

void Emulator_BindTexture(GLuint textureId)
{
#if !defined(__EMSCRIPTEN__)
	//assert(textureId < 1000);
#endif
	if (g_lastBoundTexture != textureId)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		g_lastBoundTexture = textureId;
	}
}

void Emulator_DestroyTextures(int numTextures, GLuint* textures)
{
	for (int i = 0; i < numTextures; i++)
	{
		if (textures[i] == g_lastBoundTexture)
		{
			g_lastBoundTexture = -1;
		}
	}

	glDeleteTextures(numTextures, textures);
}

void Emulator_GenerateAndBindNullWhite()
{
	unsigned char pixelData[4];
	((int*)&pixelData[0])[0] = 0x80808080;
	glGenTextures(1, &nullWhiteTexture);
	Emulator_BindTexture(nullWhiteTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData[0]);
}

void Emulator_CheckTextureIntersection(RECT16* rect)///@TODO internal upres
{
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		//Unused texture
		if (cachedTextures[i].textureID == 0xFFFFFFFF)
			continue;

		unsigned short tpage = cachedTextures[i].tpage;
		unsigned int tpageX = ((tpage << 6) & 0x7C0) % VRAM_WIDTH;///@TODO macro
		unsigned int tpageY = (((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200)) % VRAM_HEIGHT;///@TODO macro

		if (rect->x < tpageX + TPAGE_WIDTH && rect->x + rect->w > tpageX&&
			rect->y > tpageY + TPAGE_WIDTH && rect->y + rect->h < tpageY)
		{
			Emulator_DestroyTextures(1, &cachedTextures[i].textureID);
			SDL_memset(&cachedTextures[i], -1, sizeof(struct CachedTexture));
		}
	}
}
#define NOFILE 0

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

	FILE* f = fopen(outputFileName, "wb");
	if (f == NULL)
	{
		return;
	}
	unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
	unsigned char header[6];
	header[0] = (width % 256);
	header[1] = (width / 256);
	header[2] = (height % 256);
	header[3] = (height / 256);
	header[4] = 16;
	header[5] = 0;
	unsigned short* pixelData = new unsigned short[width * height];

	if (bReadFromFrameBuffer)
	{
		glReadPixels(x, y, width, height, GL_BGRA, TEXTURE_FORMAT, &pixelData[0]);
	}
	else
	{
		glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, TEXTURE_FORMAT, pixelData);
	}

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&pixelData[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&pixelData[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);
	delete[] pixelData;
}
#endif

void Emulator_BeginScene()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_JOYDEVICEADDED:
			if (SDL_IsGameController(event.jbutton.which))
			{
				padHandle[event.jbutton.which] = SDL_GameControllerOpen(event.jbutton.which);
			}
			break;
		case SDL_JOYDEVICEREMOVED:
			SDL_GameControllerClose(padHandle[event.jbutton.which]);
			break;
		case SDL_QUIT:
			Emulator_ShutDown();
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				Emulator_ShutDown();
				break;
			}
			break;
		}
	}
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void Emulator_TakeScreenshot()
{
	unsigned char* pixels = new unsigned char[512 * RESOLUTION_SCALE * 240 * RESOLUTION_SCALE * 4];
	glReadPixels(0, 0, 512 * RESOLUTION_SCALE, 240 * RESOLUTION_SCALE, GL_BGRA, GL_UNSIGNED_BYTE, pixels);

	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, 512 * RESOLUTION_SCALE, 240 * RESOLUTION_SCALE, 8 * 4, 512 * RESOLUTION_SCALE * 4, 0, 0, 0, 0);
	SDL_SaveBMP(surface, "SCREENSHOT.BMP");
	SDL_FreeSurface(surface);

	delete[] pixels;
}
#endif

///@FIXME keyboardState only accessible if padInitDirect called! Let the emulator manage input not the sub library!
void Emulator_DoDebugKeys()
{
	static unsigned int currentTime;
	static unsigned int lastTime;

	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 60)
	{
		if (keyboardState[SDL_SCANCODE_BACKSPACE])
		{
			if (g_swapInterval != 0)
			{
				SDL_GL_SetSwapInterval(0);
			}
			g_swapInterval = 0;
		}
		else
		{
			if (g_swapInterval != 1)
			{
				SDL_GL_SetSwapInterval(1);
			}
			g_swapInterval = 1;
		}

		if (keyboardState[SDL_SCANCODE_1])
		{
			g_wireframeMode ^= 1;
		}

		if (keyboardState[SDL_SCANCODE_2])
		{
			g_texturelessMode ^= 1;
		}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
		if (keyboardState[SDL_SCANCODE_3])
		{
			Emulator_TakeScreenshot();
		}
#endif

		lastTime = currentTime;
	}
}

void Emulator_UpdateInput()
{
	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				padData[i][0] = 0;
				padData[i][1] = 0x41;//?
				((unsigned short*)padData[i])[1] = UpdateGameControllerInput(padHandle[i]);
			}
		}
	}
	else
	{
		//Update keyboard
		if (padData[0] != NULL)
		{
			((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
		}
	}

#if defined(__ANDROID__)
    ///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
    ((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif

	Emulator_DoDebugKeys();
}

unsigned int Emulator_GetFPS()
{
#define FPS_INTERVAL 1.0

	static unsigned int lastTime = SDL_GetTicks();
	static unsigned int currentFps = 0;
	static unsigned int passedFrames = 0;

	passedFrames++;
	if (lastTime < SDL_GetTicks() - FPS_INTERVAL * 1000)
	{
		lastTime = SDL_GetTicks();
		currentFps = passedFrames;
		passedFrames = 0;
	}

	return currentFps;
}

void Emulator_SwapWindow()
{
#if defined(RO_DOUBLE_BUFFERED)
#if defined(OGL)
	SDL_GL_SwapWindow(g_window);
#elif defined(OGLES)
	eglSwapBuffers(eglDisplay, eglSurface);
#endif
#else
	glFinish();
#endif
}

void Emulator_EndScene()
{
	glDisable(GL_BLEND);

	glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "bDiscardBlack"), FALSE);
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);

	glScissor(0, 0, windowWidth * RESOLUTION_SCALE, windowHeight * RESOLUTION_SCALE);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);

	float x = 1.0f / (VRAM_WIDTH / (float)(word_33BC.disp.x * RESOLUTION_SCALE));
	float y = 1.0f / (VRAM_HEIGHT / (float)(word_33BC.disp.y * RESOLUTION_SCALE));
	float h = 1.0f / (VRAM_HEIGHT / (float)(word_33BC.disp.h * RESOLUTION_SCALE));
	float w = 1.0f / (VRAM_WIDTH / (float)(word_33BC.disp.w * RESOLUTION_SCALE));

	float vertexBuffer[] =
	{
		0.0f, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x, y, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, x, y + h, 1.0f, 1.0f, 1.0f, 1.0f,
		(float)word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, 0.0f, x + w, y + h, 1.0f, 1.0f, 1.0f, 1.0f,
		(float)word_33BC.disp.w * RESOLUTION_SCALE, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x + w, y, 1.0f, 1.0f, 1.0f, 1.0f,
		(float)word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, 0.0f, x + w, y + h, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, (float)word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, x, y, 1.0f, 1.0f, 1.0f, 1.0f,
	};

#if defined(OGLES) || defined (OGL)
	GLuint vbo, ibo, vao;
	GLuint indexBuffer[] = { 0,1,2,0,2,3 };

#if (defined OGL) || (defined(OGLES) && OGLES_VERSION == 3)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
#else
	glGenVertexArraysOES(1, &vao);
	glBindVertexArrayOES(vao);
#endif

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indexBuffer, GL_STATIC_DRAW);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), &vertexBuffer[0], GL_STATIC_DRAW);

	GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
	GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
	GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
	glEnableVertexAttribArray(posAttrib);
	glEnableVertexAttribArray(colAttrib);
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 9, 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)20);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 9, (GLvoid*)12);
	Emulator_Ortho2D(0.0f, word_33BC.disp.w * RESOLUTION_SCALE, 0.0f, word_33BC.disp.h * RESOLUTION_SCALE, 0.0f, 1.0f);
	Emulator_Scalef(1.0f, 1.0f, 1.0f);
	Emulator_BindTexture(vramTexture);

	//Delete buffers
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(colAttrib);
	glDisableVertexAttribArray(texAttrib);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
#if (defined OGL) || (defined(OGLES) && OGLES_VERSION == 3)
    glDeleteVertexArrays(1, &vao);
#else
    glDeleteVertexArraysOES(1, &vao);
#endif
#endif

#if _DEBUG && 1
	glBindFramebuffer(GL_READ_FRAMEBUFFER, vramFrameBuffer);
	Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

	Emulator_SwapWindow();
	glUseProgram(g_defaultShaderProgram);

	//glEnable(GL_BLEND);
}

void Emulator_ShutDown()
{
	Emulator_DestroyFrameBuffer(&vramFrameBuffer);
	Emulator_DestroyTextures(1, &vramTexture);
	Emulator_DestroyTextures(1, &nullWhiteTexture);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		if (cachedTextures[i].textureID != 0xFFFFFFFF)
		{
			Emulator_DestroyTextures(1, &cachedTextures[i].textureID);
		}
	}

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

void Emulator_GenerateFrameBuffer(GLuint* fbo)
{
#if defined(OGL) || defined(OGLES)
	glGenFramebuffers(1, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
#endif
}

struct CachedTexture* Emulator_FindTextureInCache(unsigned short tpage, unsigned short clut)
{
	if (g_hasHintedTextureAtlas)
	{
		for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
		{
			if (cachedTextures[i].tpage == tpage)
			{
				cachedTextures[i].lastAccess = SDL_GetTicks();
				return &cachedTextures[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
		{
			if (cachedTextures[i].tpage == tpage && cachedTextures[i].clut == clut)
			{
				cachedTextures[i].lastAccess = SDL_GetTicks();
				return &cachedTextures[i];
			}
		}
	}

	return NULL;
}

struct CachedTexture* Emulator_GetFreeCachedTexture()
{
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		if (cachedTextures[i].textureID == 0xFFFFFFFF)
		{
			return &cachedTextures[i];
		}
	}

	//Cache is full, this should never happen
	assert(0);

	return NULL;
}

GLuint Emulator_GenerateTpage(unsigned short tpage, unsigned short clut)
{
	unsigned int textureType = GET_TPAGE_TYPE(tpage);
	unsigned int tpageX = GET_TPAGE_X(tpage);
	unsigned int tpageY = GET_TPAGE_Y(tpage)
	unsigned int clutX = GET_CLUT_X(clut);
	unsigned int clutY = GET_CLUT_Y(clut);

#if RESOLUTION_SCALE > 1
	if (tpageX >= 256)
	{
		tpageX += ((VRAM_WIDTH - (VRAM_WIDTH / RESOLUTION_SCALE)) / 2);
	}

	if (tpageY >= 256)
	{
		tpageY += ((VRAM_HEIGHT - (VRAM_HEIGHT / RESOLUTION_SCALE)) / 2);
	}
	if (clutX >= 256)
	{
		clutX += ((VRAM_WIDTH - (VRAM_WIDTH / RESOLUTION_SCALE)) / 2);
	}
	if (clutY >= 256)
	{
		clutY += ((VRAM_HEIGHT - (VRAM_HEIGHT / RESOLUTION_SCALE)) / 2);
	}
#endif

	struct CachedTexture* tpageTexture = Emulator_FindTextureInCache(tpage, clut);
	int bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

	if (bMustAddTexture)
	{
		tpageTexture = Emulator_GetFreeCachedTexture();
		tpageTexture->tpage = tpage;
		tpageTexture->clut = clut;
		glGenTextures(1, &tpageTexture->textureID);
#if !defined(__EMSCRIPTEN__)
		assert(tpageTexture->textureID < 1000);
#endif
		Emulator_BindTexture(tpageTexture->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else
	{
		return tpageTexture->textureID;
	}

	enum
	{
		TP_4BIT,
		TP_8BIT,
		TP_16BIT
	};

	switch (textureType)
	{
	case TP_16BIT:
	{
		unsigned short* tpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH * TPAGE_HEIGHT * sizeof(unsigned short));
		glReadPixels(tpageX, tpageY, TPAGE_WIDTH, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, tpage);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, TEXTURE_FORMAT, tpage);

#if defined(_DEBUG) && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(tpage, sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif

		SDL_free(tpage);
		break;
	}
	case TP_8BIT:
	{
		unsigned short* tpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH * TPAGE_HEIGHT * sizeof(unsigned short));
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &tpage[0]);
		SDL_free(tpage);
#if defined(_DEBUG) && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(&tpage[0], sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif
		break;
	}
	case TP_4BIT:
	{
		unsigned short clut[CLUT_WIDTH * CLUT_HEIGHT];

		//Read CLUT
		glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &clut[0]);

		unsigned short* tpage = (unsigned short*)SDL_malloc(TPAGE_WIDTH / 4 * TPAGE_HEIGHT * sizeof(unsigned short));

		//Read texture data
		glReadPixels(tpageX, tpageY, TPAGE_WIDTH / 4, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &tpage[0]);

		unsigned short convertedTpage[TPAGE_WIDTH * TPAGE_HEIGHT];
		unsigned short* convertPixel = &convertedTpage[0];

		for (int xy = 0; xy < TPAGE_WIDTH / 4 * TPAGE_HEIGHT; xy++)
		{
			*convertPixel++ = clut[(tpage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
			*convertPixel++ = clut[(tpage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
			*convertPixel++ = clut[(tpage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
			*convertPixel++ = clut[(tpage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
		}

#if defined(OGLES)
#define ARGB1555toRGBA1555(x) ((x & 0x8000) >> 15) | ((x & 0x7FFF) << 1)
#pragma pack(push,1)
		struct rgba5551
		{
			unsigned short r : 5;
			unsigned short g : 5;
			unsigned short b : 5;
			unsigned short a : 1;
		};

		struct abgr1555
		{
			unsigned short a : 1;
			unsigned short b : 5;
			unsigned short g : 5;
			unsigned short r : 5;
		};
#pragma pack(pop)

		for (int xy = 0; xy < TPAGE_WIDTH * TPAGE_HEIGHT; xy++)
		{
			struct rgba5551* pixel = (struct rgba5551*) & convertedTpage[xy];
			struct abgr1555* pixel2 = (struct abgr1555*) & convertedTpage[xy];

			unsigned short r = pixel->r;
			unsigned short g = pixel->g;
			unsigned short b = pixel->b;
			unsigned short a = pixel->a;
			pixel2->a = a;
			pixel2->r = r;
			pixel2->g = g;
			pixel2->b = b;
		}

#endif

#if _DEBUG && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(&convertedTpage[0], sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_RGBA, TEXTURE_FORMAT, &convertedTpage[0]);
		break;
	}
	}



	return tpageTexture->textureID;
}

void Emulator_DestroyFrameBuffer(GLuint* fbo)
{
	glDeleteFramebuffers(1, fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
}

static int g_PreviousBlendMode = -1;
static int g_PreviousSemiTrans = 0;

void Emulator_SetBlendMode(int mode, int semiTransparent)
{
	if (semiTransparent)
	{
		//If previous wasn't semi trans, enable blend
		if (g_PreviousSemiTrans == 0)
		{
			glEnable(GL_BLEND);
		}

		if (g_PreviousBlendMode != mode)
		{
			switch (mode)
			{
			case BM_AVERAGE:
				glBlendFuncSeparate(GL_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				break;
			case BM_ADD:
				glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				break;
			case BM_SUBTRACT:
				glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
				break;
			case BM_ADD_QUATER_SOURCE:
				glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				break;
			default:
				glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				break;
			}

			g_PreviousBlendMode = mode;
		}
	}
	else
	{
		//If previous was semi trans disable blend
		if (g_PreviousSemiTrans)
		{
			glDisable(GL_BLEND);
		}
	}

	g_PreviousSemiTrans = semiTransparent;
}

#if defined(OGLES) || defined(OGL)
void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = -2.0f / (zfar - znear);

	float tx = -(right + left) / (right - left);
	float ty = -(top + bottom) / (top - bottom);
	float tz = -(zfar + znear) / (zfar - znear);

	float ortho[16] =
	{
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		tx, ty, tz, 1
	};

	GLint projectionUniform = glGetUniformLocation(g_defaultShaderProgram, "Projection");
	glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, &ortho[0]);
}

void Emulator_Scalef(float sx, float sy, float sz)
{
	float scale[16] =
	{
		sx, 0, 0, 0,
		0, sy, 0, 0,
		0, 0, sz, 0,
		0, 0, 0, 1
	};

	GLint scaleUniform = glGetUniformLocation(g_defaultShaderProgram, "Scale");
	glUniformMatrix4fv(scaleUniform, 1, GL_FALSE, &scale[0]);
}

#endif

void Emulator_GetTopLeftAndBottomLeftTextureCoordinate(int* x, int* y, int* w, int* h, unsigned char* u, unsigned char* v)
{
	int topCoordX = -1;
	int topCoordY = -1;
	int bottomCoordX = -1;
	int bottomCoordY = -1;

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			//Skip same coordinate
			if (i == j)
			{
				continue;
			}

			//This is a left coord
			if (u[j] < u[i])
			{
				topCoordX = u[j];
			}

			//This is a top coord
			if (v[i] < v[j])
			{
				topCoordY = v[i];
			}
		}
	}

	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			//Skip same coordinate
			if (i == j)
			{
				continue;
			}

			//This is a right coord
			if (u[j] > u[i])
			{
				bottomCoordX = u[j];
			}

			//This is a bottom coord
			if (v[i] > v[j])
			{
				bottomCoordY = v[i];
			}
		}
	}

	*x = topCoordX;
	*y = topCoordY;
	*w = (bottomCoordX - topCoordX) + 1;
	*h = (bottomCoordY - topCoordY) + 1;

	//Round up next multiple of 2
	//*w = (*w + 1) & ~0x1;
	//*h = (*h + 1) & ~0x1;

	//Round down next multiple of 2
	//*w -= (*w % 2);
	//*h -= (*h % 2);
}

#define EXTERNAL_LOGO

void Emulator_HintTextureAtlas(unsigned short texTpage, unsigned short texClut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3, unsigned short bIsQuad)
{
	//Locate the 4-bit texture in vram, convert it and glTexSubImage to the atlas
	unsigned int tpageX = GET_TPAGE_X(texTpage);
	unsigned int tpageY = GET_TPAGE_Y(texTpage);
	unsigned int clutX = GET_CLUT_X(texClut);
	unsigned int clutY = GET_CLUT_Y(texClut);

	//Set this to true so the emulator uses atlas textures
	g_hasHintedTextureAtlas = 1;

	int x = 0, y = 0, w = 0, h = 0;
	unsigned char textureCoordsU[] = { u0, u1, u2, u3 };
	unsigned char textureCoordsV[] = { v0, v1, v2, v3 };

	/* Get the top left and bottom left coordinate for TOMB5, return them plus width height */
	Emulator_GetTopLeftAndBottomLeftTextureCoordinate(&x, &y, &w, &h, &textureCoordsU[0], &textureCoordsV[0]);

	//Check if this tpage is already in our cache!
	struct CachedTexture* tpageTexture = Emulator_FindTextureInCache(texTpage, texClut);
	int bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

	//If not in cache, generate new texture for this tpage!
	if (bMustAddTexture)
	{
		tpageTexture = Emulator_GetFreeCachedTexture();
		tpageTexture->tpage = texTpage;
		tpageTexture->clut = texClut;
		glGenTextures(1, &tpageTexture->textureID);
		Emulator_BindTexture(tpageTexture->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_RGBA, TEXTURE_FORMAT, NULL);
	}
	else
	{
		Emulator_BindTexture(tpageTexture->textureID);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
	unsigned short* texturePage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * w * h * 1024);
	unsigned short* clut = (unsigned short*)SDL_malloc(sizeof(unsigned short) * 16);
	unsigned short* convertedTpage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * w * h * 1024);

	//Read CLUT
	glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &clut[0]);

	//Read texture data
	glReadPixels(tpageX + (x / 4), tpageY + y, w / 4, h, GL_RGBA, TEXTURE_FORMAT, &texturePage[0]);

	unsigned short* convertPixel = &convertedTpage[0];

	for (int xy = 0; xy < (w / 4) * h; xy++)
	{
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
	}

#if defined(OGLES)
#define ARGB1555toRGBA1555(x) ((x & 0x8000) >> 15) | ((x & 0x7FFF) << 1)
#pragma pack(push,1)
	struct rgba5551
	{
		unsigned short r : 5;
		unsigned short g : 5;
		unsigned short b : 5;
		unsigned short a : 1;
	};

	struct abgr1555
	{
		unsigned short a : 1;
		unsigned short b : 5;
		unsigned short g : 5;
		unsigned short r : 5;
	};
#pragma pack(pop)

	for (int xy = 0; xy < w * h; xy++)
	{
		struct rgba5551* pixel = (struct rgba5551*) & convertedTpage[xy];
		struct abgr1555* pixel2 = (struct abgr1555*) & convertedTpage[xy];

		unsigned short r = pixel->r;
		unsigned short g = pixel->g;
		unsigned short b = pixel->b;
		unsigned short a = pixel->a;
		pixel2->a = a;
		pixel2->r = r;
		pixel2->g = g;
		pixel2->b = b;
	}

#endif

	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, TEXTURE_FORMAT, &convertedTpage[0]);

#if defined(_DEBUG) && 0
	char buf[32];
	sprintf(&buf[0], "TEX_%d.TGA", texTpage);
	Emulator_SaveVRAM(buf, 0, 0, TPAGE_WIDTH, TPAGE_HEIGHT, FALSE);
#endif

	SDL_free(clut);
	SDL_free(texturePage);
	SDL_free(convertedTpage);

	//Set this to false so the emulator can search up and add textures
	//That are not atlas hinted
	//g_hasHintedTextureAtlas = 0;
}


void Emulator_InjectTIM(char* fileName, unsigned short texTpage, unsigned short texClut, unsigned char u0, unsigned char v0, unsigned char u1, unsigned char v1, unsigned char u2, unsigned char v2, unsigned char u3, unsigned char v3)
{
	/* Take from atlas */
	g_hasHintedTextureAtlas = 1;

	int x = 0, y = 0, w = 0, h = 0;
	unsigned char textureCoordsU[] = { u0, u1, u2, u3 };
	unsigned char textureCoordsV[] = { v0, v1, v2, v3 };

	/* Get the top left and bottom left coordinate for TOMB5, return them plus width height */
	Emulator_GetTopLeftAndBottomLeftTextureCoordinate(&x, &y, &w, &h, &textureCoordsU[0], &textureCoordsV[0]);

	//Check if this tpage is already in our cache!
	struct CachedTexture* tpageTexture = Emulator_FindTextureInCache(texTpage, texClut);

	//Not in cache, why are we injecting? ; - )
	if (tpageTexture == NULL)
	{
		return;
	}

	Emulator_BindTexture(tpageTexture->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned short* texturePage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * ((w * h) / 2));
	unsigned short* clut = (unsigned short*)SDL_malloc(sizeof(unsigned short) * 16);
	unsigned short* convertedTpage = (unsigned short*)SDL_malloc(sizeof(unsigned short) * (w * h));

	FILE* f = fopen("LOGO.TIM", "rb");
	fseek(f, 20, SEEK_SET);
	fread(&clut[0], 16 * sizeof(short), 1, f);
	fseek(f, 64, SEEK_SET);
	fread(&texturePage[0], (w * h) / 2, 1, f);
	fclose(f);

	//For LOGO only, temporarily set injection x y position on 256x256 tpage
	x = 0;
	y = 68;

	unsigned short* convertPixel = &convertedTpage[0];

	for (int xy = 0; xy < (w / 4) * h; xy++)
	{
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 0 * 4)) >> (0 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 1 * 4)) >> (1 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 2 * 4)) >> (2 * 4)];
		*convertPixel++ = clut[(texturePage[xy] & (0xF << 3 * 4)) >> (3 * 4)];
	}

#if defined(OGLES)
#define ARGB1555toRGBA1555(x) ((x & 0x8000) >> 15) | ((x & 0x7FFF) << 1)
#pragma pack(push,1)
	struct rgba5551
	{
		unsigned short r : 5;
		unsigned short g : 5;
		unsigned short b : 5;
		unsigned short a : 1;
	};

	struct abgr1555
	{
		unsigned short a : 1;
		unsigned short b : 5;
		unsigned short g : 5;
		unsigned short r : 5;
	};
#pragma pack(pop)

	for (int xy = 0; xy < w * h; xy++)
	{
		struct rgba5551* pixel = (struct rgba5551*) & convertedTpage[xy];
		struct abgr1555* pixel2 = (struct abgr1555*) & convertedTpage[xy];

		unsigned short r = pixel->r;
		unsigned short g = pixel->g;
		unsigned short b = pixel->b;
		unsigned short a = pixel->a;
		pixel2->a = a;
		pixel2->r = r;
		pixel2->g = g;
		pixel2->b = b;
	}

#endif

	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, TEXTURE_FORMAT, &convertedTpage[0]);

#if defined(_DEBUG) && 0
	char buf[32];
	sprintf(&buf[0], "TEX_%d.TGA", texTpage);
	Emulator_SaveVRAM(buf, 0, 0, TPAGE_WIDTH, TPAGE_HEIGHT, FALSE);
#endif

	SDL_free(clut);
	SDL_free(texturePage);
	SDL_free(convertedTpage);

	//Set this to false so the emulator can search up and add textures
	//That are not atlas hinted
	g_hasHintedTextureAtlas = 1;
}

void Emulator_DestroyAllTextures()
{
	//Initial texture id is -1
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		if (cachedTextures[i].textureID != 0xFFFFFFFF)
		{
			Emulator_DestroyTextures(1, &cachedTextures[i].textureID);
		}
	}

	//Initialise texture cache
	SDL_memset(&cachedTextures[0], -1, MAX_NUM_CACHED_TEXTURES * sizeof(struct CachedTexture));

	return;
}

void Emulator_SetPGXPVertexCount(int vertexCount)
{
#if defined(PGXP)
	pgxp_vertex_count = vertexCount;
#endif
}