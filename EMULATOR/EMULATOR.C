#include "EMULATOR.H"

#include "EMULATOR_GLOBALS.H"
#include "CRASHHANDLER.H"

#include <LIBGPU.H>
#include <LIBETC.H>
#include <LIBPAD.H>

#include <stdio.h>
#include <string.h>
#include <thread>
#include <assert.h>

#if defined(__linux__) || defined(__APPLE__)
#include <sys/mman.h>
#include <unistd.h>
#endif

#if defined(_WINDOWS)
#include <Windows.h>
#include <ddraw.h>
#endif

#define MAX_NUM_CACHED_TEXTURES (256)
#define BLEND_MODE (1)
#define VERTEX_COLOUR_MULT (2)


#if defined(NTSC_VERSION)
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#if defined(DX9)
#include <d3dx9.h>
#include <d3d9.h>

#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

SDL_Renderer* g_Renderer;
IDirect3DDevice9* g_Device;
#endif

#define MAX_NUM_VERTICES (4)
Vertex vertices[MAX_NUM_VERTICES];
int vertexCount = 0;

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
SysCounter counters[3] = {0};
std::thread counter_thread;
unsigned short GlobalTpageTexture = 0;

struct CachedTexture
{
	GLuint textureID;
	unsigned short tpage;
	unsigned short clut;
	unsigned int lastAccess;
};

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

EGLint majorVersion, minorVersion;
EGLContext eglContext = NULL;
EGLSurface eglSurface;
EGLConfig eglConfig;
EGLDisplay eglDisplay;
int numConfigs;
EGLNativeWindowType displayWindow;

const EGLint config16bpp[] =
{
	EGL_RED_SIZE,   8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE,  8,
	EGL_DEPTH_SIZE, 0,
	EGL_NONE
};

static int Emulator_InitialiseGLESContext(char* windowName)
{
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
	{
		eprinterr("eglInitialize failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	if (!eglChooseConfig(eglDisplay, config16bpp, &eglConfig, 1, &numConfigs))
	{
		printf("eglChooseConfig failed\n");
		if (eglContext == 0) {
			printf("Error code: %d\n", eglGetError());
		}
	}

	SDL_SysWMinfo systemInfo;
	SDL_VERSION(&systemInfo.version);
	SDL_GetWindowWMInfo(g_window, &systemInfo);
#if defined(__EMSCRIPTEN__)
	EGLNativeWindowType dummyWindow;
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)dummyWindow, NULL);
#else
	eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)systemInfo.info.win.window, NULL);
#endif
	if (eglSurface == EGL_NO_SURFACE)
	{
		eprinterr("eglSurface failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE, EGL_NONE };
	eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttribs);

	if (eglContext == EGL_NO_CONTEXT)
	{
		eprinterr("eglContext failure! Error: %x\n", eglGetError());
		return FALSE;
	}

	eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);
	eglSwapInterval(eglDisplay, 1);
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
#if defined(OGL)
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
#endif
#if !defined(RO_DOUBLE_BUFFERED)
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
#endif

#if defined(OGLES)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#elif defined(OGL)
#if defined(CORE_PROF_3_1)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#elif defined(CORE_PROF_3_2)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#elif defined(CORE_PROF_3_3)
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif
#endif
		
#if defined(OGL)
	}
	else
	{
		eprinterr("Error: Failed to initialise SDL\n");
		return FALSE;
	}
#endif

#if defined(OGL)
	Emulator_InitialiseGLContext(windowName);
#elif defined(OGLES)
	Emulator_InitialiseGLESContext(windowName);
#endif

	SDL_GL_SetSwapInterval(1);

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
	SDL_memset(&cachedTextures[0], 0, MAX_NUM_CACHED_TEXTURES * sizeof(CachedTexture));

	//Initial texture value is -1
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		cachedTextures[i].textureID = -1;
	}
}

void Emulator_AllocateVirtualMemory(unsigned int baseAddress, unsigned int size)
{
	do
	{
#if __linux__ || __APPLE__
		pVirtualMemory = (char*)mmap((void*)baseAddress, size, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_SHARED, 0, 0);
#endif

#ifdef _WINDOWS
		size = size + (4096 - 1) & ~(4096 - 1);
		baseAddress = baseAddress + (4096 - 1) & ~(4096 - 1);
		MEMORY_BASIC_INFORMATION memInfo;
		VirtualQuery((void*)baseAddress, &memInfo, size);
#if _DEBUG
		printf("VQ: %d\n", GetLastError());
#endif
		if (!(memInfo.State & MEM_FREE))
		{
			if (memInfo.Type & MEM_MAPPED)
			{
#if _DEBUG
				printf("Mapped\n");
#endif
			}
			else
			{
#if _DEBUG
				printf("Not Mapped\n");
#endif
				VirtualUnlock((void*)baseAddress, memInfo.RegionSize);
				VirtualFree((void*)baseAddress, NULL, MEM_RELEASE);
			}
		}
		else
		{
			
			pVirtualMemory = (char*)VirtualAlloc((void*)memInfo.BaseAddress, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

#if _DEBUG
			printf("VA: %d\n", GetLastError());
#endif
		}
#endif

		if (pVirtualMemory)
		{
			printf("%x\n", (unsigned int)baseAddress);
			//VirtualLock((void*)baseAddress, size);
			break;
		}

	} while (baseAddress += size);

	if (pVirtualMemory == NULL)
	{
		printf("Failed to map virtual memory!\n");
	}

	return;
}

int Emulator_InitialiseGameVariables()
{
#if defined(__linux__) || defined(__APPLE__)
	extern unsigned long* GadwOrderingTables;
	extern unsigned long* GadwPolygonBuffers;
	extern unsigned long* GadwOrderingTables_V2;
	extern unsigned long* terminator;

#if defined(_WINDOWS)
	SYSTEM_INFO info;
	GetSystemInfo(&info);
	Emulator_AllocateVirtualMemory((unsigned int)info.lpMinimumApplicationAddress, (5128 * 4) + (52260 * 4) + (512 * 4) + 4);
#else
	Emulator_AllocateVirtualMemory(0x400000, (5128 * 4) + (52260 * 4) + (512 * 4) + 4);
#endif
	
	if (pVirtualMemory == NULL)
	{
		return 0;
	}
	if ((uintptr_t)pVirtualMemory & 0xFF000000)
	{
		printf("*********************************************************************** And an error occured!\n");
		return 0;
	}

	GadwOrderingTables = (unsigned long*)&pVirtualMemory[0];
	GadwPolygonBuffers = (unsigned long*)&pVirtualMemory[(5128 * 4)];
	GadwOrderingTables_V2 = (unsigned long*)&pVirtualMemory[(5128 * 4) + (52260 * 4)];
	terminator = (unsigned long*)&pVirtualMemory[(5128 * 4) + (52260 * 4) + (512 * 4)];
	*terminator = -1;
#endif
	return 1;
}

void Emulator_Initialise(char* windowName, int screenWidth, int screenHeight)
{
	Emulator_InitialiseSDL(windowName, screenWidth, screenHeight);
#if defined(GLEW)
	Emulator_InitialiseGLEW();
#endif
	Emulator_InitialiseCore();

#if defined(OGL) || defined(OGLES)
	Emulator_InitialiseGL();
#endif

#if defined(__linux__) || defined(__APPLE__)
	if (!Emulator_InitialiseGameVariables())
	{
		exit(0);
	}
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

		if(numUpdates++ <= 60)
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

char* Emulator_GenerateVertexArrayQuad(short* p0, short* p1, short* p2, short* p3, short w, short h)
{
	//Copy over position
	if (p0 != NULL)
	{
		vertices[0].x = (float)p0[0];
		vertices[0].y = (float)p0[1];
	}

	if (p1 != NULL)
	{
		vertices[1].x = (float)p1[0];
		vertices[1].y = (float)p1[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertices[1].x = (float)p0[0];
			vertices[1].y = (float)p0[1] + h;
		}
	}

	if (p2 != NULL)
	{
		vertices[2].x = (float)p2[0];
		vertices[2].y = (float)p2[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertices[2].x = (float)p0[0] + w;
			vertices[2].y = (float)p0[1] + h;
		}
	}

	if (p3 != NULL)
	{
		vertices[3].x = (float)p3[0];
		vertices[3].y = (float)p3[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertices[3].x = (float)p0[0] + w;
			vertices[3].y = (float)p0[1];
		}
	}

	return (char*)& vertices[0].x;
}


char* Emulator_GenerateTexcoordArrayQuad(unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short w, short h)
{
	//Copy over uvs
	if (uv0 != NULL)
	{
		vertices[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
		vertices[0].v0 = ((float)uv0[1]) / TPAGE_WIDTH;
	}

	if (uv1 != NULL)
	{
		vertices[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
		vertices[1].v0 = ((float)uv1[1]) / TPAGE_WIDTH;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertices[1].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertices[1].v0 = ((float)uv0[1] + h) / TPAGE_WIDTH;
		}
	}

	if (uv2 != NULL)
	{
		vertices[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
		vertices[2].v0 = ((float)uv2[1]) / TPAGE_WIDTH;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertices[2].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertices[2].v0 = ((float)uv0[1] + h) / TPAGE_WIDTH;
		}
	}

	if (uv3 != NULL)
	{
		vertices[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
		vertices[3].v0 = ((float)uv3[1]) / TPAGE_WIDTH;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertices[3].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertices[3].v0 = ((float)uv0[1]) / TPAGE_WIDTH;
		}
	}

	return (char*)& vertices[0].u0;
}

char* Emulator_GenerateColourArrayQuad(unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, bool bMultiplyColour)
{
	//Copy over rgb vertex colours
	if (col0 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[0].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertices[0].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertices[0].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertices[0].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[0].col[0] = (1.0f / 255) * col0[0];
			vertices[0].col[1] = (1.0f / 255) * col0[1];
			vertices[0].col[2] = (1.0f / 255) * col0[2];
			vertices[0].col[3] = (1.0f / 255) * 255;
		}
	}

	if (col1 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[1].col[0] = (1.0f / 255) * (col1[0] * VERTEX_COLOUR_MULT);
			vertices[1].col[1] = (1.0f / 255) * (col1[1] * VERTEX_COLOUR_MULT);
			vertices[1].col[2] = (1.0f / 255) * (col1[2] * VERTEX_COLOUR_MULT);
			vertices[1].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[1].col[0] = (1.0f / 255) * col1[0];
			vertices[1].col[1] = (1.0f / 255) * col1[1];
			vertices[1].col[2] = (1.0f / 255) * col1[2];
			vertices[1].col[3] = (1.0f / 255) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[1].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertices[1].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertices[1].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertices[1].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[1].col[0] = (1.0f / 255) * col0[0];
			vertices[1].col[1] = (1.0f / 255) * col0[1];
			vertices[1].col[2] = (1.0f / 255) * col0[2];
			vertices[1].col[3] = (1.0f / 255) * 255;
		}
	}

	if (col2 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[2].col[0] = (1.0f / 255) * (col2[0] * VERTEX_COLOUR_MULT);
			vertices[2].col[1] = (1.0f / 255) * (col2[1] * VERTEX_COLOUR_MULT);
			vertices[2].col[2] = (1.0f / 255) * (col2[2] * VERTEX_COLOUR_MULT);
			vertices[2].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[2].col[0] = (1.0f / 255) * col2[0];
			vertices[2].col[1] = (1.0f / 255) * col2[1];
			vertices[2].col[2] = (1.0f / 255) * col2[2];
			vertices[2].col[3] = (1.0f / 255) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[2].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertices[2].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertices[2].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertices[2].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[2].col[0] = (1.0f / 255) * col0[0];
			vertices[2].col[1] = (1.0f / 255) * col0[1];
			vertices[2].col[2] = (1.0f / 255) * col0[2];
			vertices[2].col[3] = (1.0f / 255) * 255;
		}
	}

	if (col3 != NULL)
	{
		if (bMultiplyColour)
		{
			vertices[3].col[0] = (1.0f / 255) * (col3[0] * VERTEX_COLOUR_MULT);
			vertices[3].col[1] = (1.0f / 255) * (col3[1] * VERTEX_COLOUR_MULT);
			vertices[3].col[2] = (1.0f / 255) * (col3[2] * VERTEX_COLOUR_MULT);
			vertices[3].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[3].col[0] = (1.0f / 255) * col3[0];
			vertices[3].col[1] = (1.0f / 255) * col3[1];
			vertices[3].col[2] = (1.0f / 255) * col3[2];
			vertices[3].col[3] = (1.0f / 255) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertices[3].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertices[3].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertices[3].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertices[3].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertices[3].col[0] = (1.0f / 255) * col0[0];
			vertices[3].col[1] = (1.0f / 255) * col0[1];
			vertices[3].col[2] = (1.0f / 255) * col0[2];
			vertices[3].col[3] = (1.0f / 255) * 255;
		}
	}

	return (char*)& vertices[0].col[0];
}
#if defined(OGLES) || defined(CORE_PROF_3_3)
GLuint g_defaultShaderProgram;

void Emulator_CreateGlobalShaders()
{
#if defined(ES2_SHADERS)
	const char* vertexShaderSource = "attribute vec4 a_position; attribute vec2 a_texcoord; varying vec2 v_texcoord; attribute vec4 a_colour; varying vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#elif defined(ES3_SHADERS)
	const char* vertexShaderSource = "#version 300 es\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#elif defined(CORE_PROF_3_3)
	const char* vertexShaderSource = "#version 330 core\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#endif
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
#if defined(ES2_SHADERS)
	const char* fragmentShaderSource = "precision mediump float; varying vec2 v_texcoord; varying vec4 v_colour; uniform sampler2D s_texture; void main() { gl_FragColor = texture2D(s_texture, v_texcoord) * v_colour; }";
#elif defined(ES3_SHADERS)
	const char* fragmentShaderSource = "#version 300 es\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord) * v_colour; }";
#elif defined(CORE_PROF_3_3)
	const char* fragmentShaderSource = "#version 330 core\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord) * v_colour; }";
#endif
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

#if 1
	char buff[1024];
	int maxLength = 1024;
	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &buff[0]);

	maxLength = 1024;
	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &buff[0]);
#endif

	g_defaultShaderProgram = glCreateProgram();
	glAttachShader(g_defaultShaderProgram, vertexShader);
	glAttachShader(g_defaultShaderProgram, fragmentShader);
	glLinkProgram(g_defaultShaderProgram);
	glUseProgram(g_defaultShaderProgram);
}
#endif

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

void Emulator_InitialiseGL()
{
	glEnable(GL_BLEND);

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &g_defaultFBO);

	/* Initialise VRAM */
	SDL_memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));

#if defined(OGL)
	glEnable(GL_TEXTURE_2D);
#endif
	/* Generate NULL white texture */
	Emulator_GenerateAndBindNullWhite();

	glEnable(GL_SCISSOR_TEST);

	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#if defined(OGLES)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &vram[0]);
#elif defined(OGL)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VRAM_WIDTH, VRAM_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &vram[0]);
#endif
	/* Generate VRAM Frame Buffer */
	glGenFramebuffers(1, &vramFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
	/* Bind VRAM texture to vram framebuffer */
#if defined(CORE_PROF_3_1) || defined (OGLES)
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vramTexture, 0);
#elif defined(CORE_PROF_3_2) || defined(CORE_PROF_3_3)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glGetError());
	}
#endif

	glLineWidth(RESOLUTION_SCALE);

#if BLEND_MODE
	glBlendColor(0.25, 0.25, 0.25, 0.5);
#endif

#if defined(OGL)
	glShadeModel(GL_SMOOTH);
	glDisable(GL_DEPTH_TEST);
#endif

#if defined(OGLES) || defined(CORE_PROF_3_3)
	Emulator_CreateGlobalShaders();
#endif

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
}

void Emulator_GenerateAndBindNullWhite()
{
	unsigned char pixelData[4];
	((int*)&pixelData[0])[0] = -1;
	glGenTextures(1, &nullWhiteTexture);
	glBindTexture(GL_TEXTURE_2D, nullWhiteTexture);
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
		unsigned int tpageX = ((tpage << 6) & 0x7C0) % VRAM_WIDTH;
		unsigned int tpageY = (((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200)) % VRAM_HEIGHT;

		if (!(rect->x > tpageX + TPAGE_WIDTH || rect->x + rect->w < tpageX || rect->y > tpageY + TPAGE_HEIGHT || rect->y + rect->h < tpageY))
		{
			cachedTextures[i].lastAccess = 0;
			cachedTextures[i].tpage = 0;
			cachedTextures[i].clut = 0;
			glDeleteTextures(1, &cachedTextures[i].textureID);
			cachedTextures[i].textureID = -1;
		}
	}
}
#define NOFILE 1

#if !__EMSCRIPTEN__
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
	unsigned char header[6] = { width % 256, width / 256, height % 256, height / 256,16,0 };
	unsigned short* pixelData = new unsigned short[width * height];
	if (bReadFromFrameBuffer)
	{
#if defined(OGLES)
		glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixelData[0]);
#elif defined(OGL)
		
		glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixelData[0]);
#endif
	}
	else
	{
#if defined(OGLES)
		//glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, pixelData);
#elif defined(OGL)
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, pixelData);
#endif
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

	//Update keyboard
	if (padData[0] != NULL)
	{
		((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
	}
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
unsigned short pixels[VRAM_WIDTH * VRAM_HEIGHT];
void Emulator_EndScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);

#if defined(OGLES)
	glReadPixels(0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixels[0]);
#elif defined(OGL)
	glReadPixels(0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
#endif

	glBindTexture(GL_TEXTURE_2D, vramTexture);
#if defined(OGLES)
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixels[0]);
#elif defined(OGL)
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
#endif
	glScissor(0, 0, windowWidth, windowHeight);
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

#if defined(OGL) && !defined(CORE_PROF_3_3)
	glVertexPointer(3, GL_FLOAT, 9 * sizeof(float), vertexBuffer);
	glTexCoordPointer(2, GL_FLOAT, 9 * sizeof(float), vertexBuffer + 3);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glLoadIdentity();
	glOrtho(0, word_33BC.disp.w * RESOLUTION_SCALE, 0, word_33BC.disp.h * RESOLUTION_SCALE, 0, 1);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#elif defined(OGLES) || defined (CORE_PROF_3_3)
	GLuint vbo, ibo, vao;
	GLubyte indexBuffer[] = { 0,1,2,0,2,3 };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, indexBuffer, GL_STATIC_DRAW);

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
	Emulator_Ortho2D(0, word_33BC.disp.w * RESOLUTION_SCALE, 0, word_33BC.disp.h * RESOLUTION_SCALE, 0, 1);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, NULL);
	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(colAttrib);
	glDisableVertexAttribArray(texAttrib);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
#endif

#if _DEBUG && 1
	glBindFramebuffer(GL_READ_FRAMEBUFFER, vramFrameBuffer);
	Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

	Emulator_SwapWindow();
}

void Emulator_ShutDown()
{
	Emulator_DestroyFrameBuffer(vramFrameBuffer);
	glDeleteTextures(1, &vramTexture);
	glDeleteTextures(1, &nullWhiteTexture);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		if (cachedTextures[i].textureID != 0xFFFFFFFF)
		{
			glDeleteTextures(1, &cachedTextures[i].textureID);
		}
	}
#ifdef _WINDOWS
	//VirtualFree(pVirtualMemory, 0, MEM_RELEASE);
#endif

#if D3D9
	SDL_DestroyRenderer(g_Renderer);
#endif

	SDL_DestroyWindow(g_window);
	SDL_Quit();
	exit(0);
}

void Emulator_GenerateFrameBuffer(GLuint& fbo)
{
#if defined(OGL) || defined(OGLES)
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
#endif
}

CachedTexture* Emulator_FindTextureInCache(unsigned short tpage, unsigned short clut)
{
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		if (cachedTextures[i].tpage == tpage && cachedTextures[i].clut == clut)
		{
			cachedTextures[i].lastAccess = SDL_GetTicks();
			return &cachedTextures[i];
		}
	}

	return NULL;
}

CachedTexture* Emulator_GetFreeCachedTexture()
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

void Emulator_GenerateAndBindTpage(unsigned short tpage, unsigned short clut, int semiTransparent)
{
	unsigned int bShouldUseGlobalTpageTexture = (tpage == 0xFFFF) ? 1 : 0;
	static GLuint lastTextureId = 0xFFFFFFFF;

	if (bShouldUseGlobalTpageTexture)
	{
		tpage = GlobalTpageTexture;
	}

	unsigned int textureType = (tpage >> 7) & 0x3;
	unsigned int tpageX = ((tpage << 6) & 0x7C0) % (VRAM_WIDTH / RESOLUTION_SCALE);
	unsigned int tpageY = ((((tpage << 4) & 0x100) + ((tpage >> 2) & 0x200))) % (VRAM_HEIGHT / RESOLUTION_SCALE);
	unsigned int clutX = ((clut & 0x3F) << 4);
	unsigned int clutY = (clut >> 6);
	unsigned int tpageAbr = (tpage >> 5) & 3;

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

	Emulator_SetBlendMode(tpageAbr);

	CachedTexture* tpageTexture = Emulator_FindTextureInCache(tpage, clut);
	bool bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

	if (bMustAddTexture)
	{
		tpageTexture = Emulator_GetFreeCachedTexture();
		tpageTexture->tpage = tpage;
		tpageTexture->clut = clut;
		glGenTextures(1, &tpageTexture->textureID);
	}

	if (tpageTexture->textureID != lastTextureId)
	{
		glBindTexture(GL_TEXTURE_2D, tpageTexture->textureID);
		lastTextureId = tpageTexture->textureID;
	}

	if (!bMustAddTexture)
	{
		return;
	}

	if (bMustAddTexture)
	{
		switch (textureType)
		{
		case 2:
		{
			//ARGB1555
			unsigned short* texturePage = new unsigned short[TPAGE_WIDTH * TPAGE_HEIGHT];
#if defined(OGL)
			glReadPixels(tpageX, tpageY, TPAGE_WIDTH, TPAGE_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);
#endif
			delete[] texturePage;
			break;
		}
		case 1:
		{
			//RGBA8888
			assert(0);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texturePage[0]);
			break;
		}
		case 0:
		{
			//RGBA4444
			unsigned short* texturePage = new unsigned short[TPAGE_WIDTH / 4 * TPAGE_HEIGHT];
			unsigned short* clut = new unsigned short[16];
			unsigned short* convertedTpage = new unsigned short[TPAGE_WIDTH * TPAGE_HEIGHT];
			
#if defined (OGLES)
			//Read CLUT
			glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &clut[0]);

			//Read texture data
			glReadPixels(tpageX, tpageY, TPAGE_WIDTH / 4, TPAGE_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &texturePage[0]);
#elif defined(OGL)
			//Read CLUT
			glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &clut[0]);

			//Read texture data
			glReadPixels(tpageX, tpageY, TPAGE_WIDTH / 4, TPAGE_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &texturePage[0]);
#endif
			unsigned short* convertPixel = &convertedTpage[0];

			for (int xy = 0; xy < TPAGE_WIDTH / 4 * TPAGE_HEIGHT; xy++)
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

			for (int xy = 0; xy < TPAGE_WIDTH * TPAGE_HEIGHT; xy++)
			{
				rgba5551* pixel = (rgba5551*)&convertedTpage[xy];
				abgr1555* pixel2 = (abgr1555*)&convertedTpage[xy];

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
			FILE* f = fopen("TPAGE.TGA", "wb");
			unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
			unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
			fwrite(TGAheader, sizeof(unsigned char), 12, f);
			fwrite(header, sizeof(unsigned char), 6, f);
			fwrite(&convertedTpage[0], sizeof(char), 256 * 256 * 2, f);
			fclose(f);
#endif
#if defined(OGLES) || defined(CORE_PROF_3_3)
			glActiveTexture(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "s_texture"), 0);
#endif
#if defined(OGL)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &convertedTpage[0]);
#elif defined(OGLES)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TPAGE_WIDTH, TPAGE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &convertedTpage[0]);
#endif
			delete[] clut;
			delete[] texturePage;
			delete[] convertedTpage;
			break;
		}
		}
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void Emulator_DestroyFrameBuffer(GLuint& fbo)
{
	glDeleteFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
}

void Emulator_SetBlendMode(int mode)
{
	static int lastBlendMode = -1;

#if !BLEND_MODE
	if (lastBlendMode != mode)
	{
		switch (mode)
		{
		case 0://Average
			glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
			break;
		case 1://Add
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case 2://Subtract
			glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
			break;
		case 3://Addquatersource
			glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE);
			break;
		default:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glDisable(GL_BLEND);
			break;
		}

		lastBladeMode = mode;
	}
#else
	if (lastBlendMode != mode)
	{
		switch (mode)
		{
		case 0://Average
			glBlendFuncSeparate(GL_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			break;
		case 1://Add
			glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			break;
		case 2://Subtract
			glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
			glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT, GL_FUNC_ADD);
			break;
		case 3://Addquatersource
			glBlendFuncSeparate(GL_CONSTANT_COLOR, GL_ONE, GL_ONE, GL_ZERO);
			glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
			break;
		}

		lastBlendMode = mode;
	}
#endif
}

#if defined(OGLES) || defined(CORE_PROF_3_3)
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
#endif