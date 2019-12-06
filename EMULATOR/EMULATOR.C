#include "EMULATOR.H"

#include "EMULATOR_VERSION.H"
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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

void Emulator_GenerateLineArray(Vertex* vertex, short* p0, short* p1, short* p2, short* p3)
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

void Emulator_GenerateVertexArrayQuad(Vertex* vertex, short* p0, short* p1, short* p2, short* p3, short w, short h)
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
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
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
		vertex[3].x = (float)p3[0];
		vertex[3].y = (float)p3[1];
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


void Emulator_GenerateTexcoordArrayQuad(Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short w, short h)
{
	//Copy over uvs
	if (uv0 != NULL)
	{
		vertex[0].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
		vertex[0].v0 = ((float)uv0[1]) / TPAGE_WIDTH;
	}

	if (uv1 != NULL)
	{
		vertex[1].u0 = ((float)uv1[0]) / TPAGE_WIDTH;
		vertex[1].v0 = ((float)uv1[1]) / TPAGE_WIDTH;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].u0 = ((float)uv0[0]) / TPAGE_WIDTH;
			vertex[1].v0 = ((float)uv0[1] + h) / TPAGE_WIDTH;
		}
	}

	if (uv2 != NULL)
	{
		vertex[2].u0 = ((float)uv2[0]) / TPAGE_WIDTH;
		vertex[2].v0 = ((float)uv2[1]) / TPAGE_WIDTH;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[2].v0 = ((float)uv0[1] + h) / TPAGE_WIDTH;
		}
	}

	if (uv3 != NULL)
	{
		vertex[3].u0 = ((float)uv3[0]) / TPAGE_WIDTH;
		vertex[3].v0 = ((float)uv3[1]) / TPAGE_WIDTH;
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].u0 = ((float)uv0[0] + w) / TPAGE_WIDTH;
			vertex[3].v0 = ((float)uv0[1]) / TPAGE_WIDTH;
		}
	}

	return;
}

void Emulator_GenerateColourArrayQuad(Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3, bool bMultiplyColour)
{
	//Copy over rgb vertex colours
	if (col0 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[0].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertex[0].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertex[0].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertex[0].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[0].col[0] = (1.0f / 255) * col0[0];
			vertex[0].col[1] = (1.0f / 255) * col0[1];
			vertex[0].col[2] = (1.0f / 255) * col0[2];
			vertex[0].col[3] = (1.0f / 255) * 255;
		}
	}

	if (col1 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[1].col[0] = (1.0f / 255) * (col1[0] * VERTEX_COLOUR_MULT);
			vertex[1].col[1] = (1.0f / 255) * (col1[1] * VERTEX_COLOUR_MULT);
			vertex[1].col[2] = (1.0f / 255) * (col1[2] * VERTEX_COLOUR_MULT);
			vertex[1].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[1].col[0] = (1.0f / 255) * col1[0];
			vertex[1].col[1] = (1.0f / 255) * col1[1];
			vertex[1].col[2] = (1.0f / 255) * col1[2];
			vertex[1].col[3] = (1.0f / 255) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertex[1].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertex[1].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertex[1].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertex[1].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[1].col[0] = (1.0f / 255) * col0[0];
			vertex[1].col[1] = (1.0f / 255) * col0[1];
			vertex[1].col[2] = (1.0f / 255) * col0[2];
			vertex[1].col[3] = (1.0f / 255) * 255;
		}
	}

	if (col2 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[2].col[0] = (1.0f / 255) * (col2[0] * VERTEX_COLOUR_MULT);
			vertex[2].col[1] = (1.0f / 255) * (col2[1] * VERTEX_COLOUR_MULT);
			vertex[2].col[2] = (1.0f / 255) * (col2[2] * VERTEX_COLOUR_MULT);
			vertex[2].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[2].col[0] = (1.0f / 255) * col2[0];
			vertex[2].col[1] = (1.0f / 255) * col2[1];
			vertex[2].col[2] = (1.0f / 255) * col2[2];
			vertex[2].col[3] = (1.0f / 255) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertex[2].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertex[2].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertex[2].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertex[2].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[2].col[0] = (1.0f / 255) * col0[0];
			vertex[2].col[1] = (1.0f / 255) * col0[1];
			vertex[2].col[2] = (1.0f / 255) * col0[2];
			vertex[2].col[3] = (1.0f / 255) * 255;
		}
	}

	if (col3 != NULL)
	{
		if (bMultiplyColour)
		{
			vertex[3].col[0] = (1.0f / 255) * (col3[0] * VERTEX_COLOUR_MULT);
			vertex[3].col[1] = (1.0f / 255) * (col3[1] * VERTEX_COLOUR_MULT);
			vertex[3].col[2] = (1.0f / 255) * (col3[2] * VERTEX_COLOUR_MULT);
			vertex[3].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[3].col[0] = (1.0f / 255) * col3[0];
			vertex[3].col[1] = (1.0f / 255) * col3[1];
			vertex[3].col[2] = (1.0f / 255) * col3[2];
			vertex[3].col[3] = (1.0f / 255) * 255;
		}
	}
	else
	{
		if (bMultiplyColour)
		{
			vertex[3].col[0] = (1.0f / 255) * (col0[0] * VERTEX_COLOUR_MULT);
			vertex[3].col[1] = (1.0f / 255) * (col0[1] * VERTEX_COLOUR_MULT);
			vertex[3].col[2] = (1.0f / 255) * (col0[2] * VERTEX_COLOUR_MULT);
			vertex[3].col[3] = (1.0f / 255) * 255;
		}
		else
		{
			vertex[3].col[0] = (1.0f / 255) * col0[0];
			vertex[3].col[1] = (1.0f / 255) * col0[1];
			vertex[3].col[2] = (1.0f / 255) * col0[2];
			vertex[3].col[3] = (1.0f / 255) * 255;
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
	const char* vertexShaderSource = "#version 330 core\n in vec4 a_position; in vec2 a_texcoord; out vec2 v_texcoord; in vec4 a_colour; out vec4 v_colour; uniform mat4 Projection; void main() { v_texcoord = a_texcoord; v_colour = a_colour; gl_Position = Projection*a_position; }";
#endif
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
#if defined(ES2_SHADERS)
	const char* fragmentShaderSource = "precision mediump float; varying vec2 v_texcoord; varying vec4 v_colour; uniform sampler2D s_texture; void main() { gl_FragColor = texture2D(s_texture, v_texcoord) * v_colour; }";
#elif defined(ES3_SHADERS)
	const char* fragmentShaderSource = "#version 300 es\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord) * v_colour; }";
#elif defined(OGL)
	//const char* fragmentShaderSource = "#version 330 core\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord); if (fragColour.a == 0.0 && bDiscardBlack) { discard; } fragColour *= v_colour; }";
	const char* fragmentShaderSource = "#version 330 core\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; out vec4 fragColour; void main() { vec4 dither = vec4(texture(s_texture, gl_FragCoord.xy / 8.0).r / 32.0 - (1.0 / 128.0)); fragColour = texture(s_texture, v_texcoord); if (fragColour.a == 0.0 && bDiscardBlack) { discard; } fragColour *= v_colour; fragColour += dither; }";
	//const char* fragmentShaderSource = "#version 330 core\n precision mediump float; in vec2 v_texcoord; in vec4 v_colour; uniform bool bDiscardBlack; uniform sampler2D s_texture; out vec4 fragColour; void main() { fragColour = texture(s_texture, v_texcoord); if (fragColour.a == 0.0 && bDiscardBlack) { discard; } fragColour *= v_colour; }";
#endif

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

#if defined(_DEBUG)
	char buff[1024];
	int maxLength = 1024;
	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &buff[0]);

	maxLength = 1024;
	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &buff[0]);
#endif

	/* Default */
	g_defaultShaderProgram = glCreateProgram();
	glAttachShader(g_defaultShaderProgram, vertexShader);
	glAttachShader(g_defaultShaderProgram, fragmentShader);
	glLinkProgram(g_defaultShaderProgram);
	glUseProgram(g_defaultShaderProgram);
	GLint idx = glGetUniformLocation(g_defaultShaderProgram, "s_texture");
	GLint sampler;
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
	Emulator_GenerateAndBindNullWhite();///@TODO remove completely, no longer needed
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_SCISSOR_TEST);
	glShadeModel(GL_SMOOTH);
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
	/* Bind VRAM texture to vram framebuffer */
#if defined (OGLES)
	Emulator_BindTexture(0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, vramTexture, 0);
#elif defined(OGL)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, vramTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glGetError());
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

void Emulator_BindTexture(GLuint textureId)
{
	static GLuint g_lastBoundTexture = -1;

	if (g_lastBoundTexture != textureId)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
	}
}

void Emulator_GenerateAndBindNullWhite()
{
	unsigned char pixelData[4];
	((int*)&pixelData[0])[0] = -1;
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

		if (rect->x < tpageX + TPAGE_WIDTH && rect->x + rect->w > tpageX &&
			rect->y > tpageY + TPAGE_WIDTH && rect->y + rect->h < tpageY)
		{
			cachedTextures[i].lastAccess = 0;
			cachedTextures[i].tpage = 0;
			cachedTextures[i].clut = 0;
			glDeleteTextures(1, &cachedTextures[i].textureID);
			cachedTextures[i].textureID = -1;
		}
	}
}
#define NOFILE 0

#if !defined(__EMSCRIPTEN__)
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
		glReadPixels(x, y, width, height, GL_RGBA, TEXTURE_FORMAT, &pixelData[0]);
	}
	else
	{
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_FORMAT, pixelData);
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

///@FIXME keyboardState only accessible if padInitDirect called! Let the emulator manage input not the sub library!
void Emulator_DoDebugKeys()
{
	static unsigned int currentTime;
	static unsigned int lastTime;

	currentTime = SDL_GetTicks();

	if (currentTime > lastTime + 60)
	{
		if (keyboardState[SDL_SCANCODE_1])
		{
			g_wireframeMode ^= 1;
		}

		if (keyboardState[SDL_SCANCODE_2])
		{
			g_texturelessMode ^= 1;
		}

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

	Emulator_DoDebugKeys();
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
	glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "bDiscardBlack"), false);
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);

#if defined(OGLES)
	glReadPixels(0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, &pixels[0]);
#elif defined(OGL)
	glReadPixels(0, 0, VRAM_WIDTH, VRAM_HEIGHT, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &pixels[0]);
#endif

	Emulator_BindTexture(vramTexture);

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

#if defined(OGLES) || defined (OGL)
	GLuint vbo, ibo, vao;
	GLuint indexBuffer[] = { 0,1,2,0,2,3 };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
	glDisableVertexAttribArray(posAttrib);
	glDisableVertexAttribArray(colAttrib);
	glDisableVertexAttribArray(texAttrib);

	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
#endif

#if _DEBUG && 0
	glBindFramebuffer(GL_READ_FRAMEBUFFER, vramFrameBuffer);
	Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

	Emulator_SwapWindow();
	glUseProgram(g_defaultShaderProgram);
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

	CachedTexture* tpageTexture = Emulator_FindTextureInCache(tpage, clut);
	bool bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

	if (bMustAddTexture)
	{
		tpageTexture = Emulator_GetFreeCachedTexture();
		tpageTexture->tpage = tpage;
		tpageTexture->clut = clut;
		glGenTextures(1, &tpageTexture->textureID);
		Emulator_BindTexture(tpageTexture->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
		unsigned short* texturePage = new unsigned short[TPAGE_WIDTH * TPAGE_HEIGHT];

		glReadPixels(tpageX, tpageY, TPAGE_WIDTH, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &texturePage[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, TEXTURE_FORMAT, &texturePage[0]);

#if defined(_DEBUG) && 0
		char buff[64];
		sprintf(&buff[0], "TPAGE_%d_%d.TGA", tpage, clut);
		FILE* f = fopen(buff, "wb");
		unsigned char TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };
		unsigned char header[6] = { 256 % 256, 256 / 256, 256 % 256, 256 / 256,16,0 };
		fwrite(TGAheader, sizeof(unsigned char), 12, f);
		fwrite(header, sizeof(unsigned char), 6, f);
		fwrite(&texturePage[0], sizeof(char), 256 * 256 * 2, f);
		fclose(f);
#endif

		delete[] texturePage;
		break;
	}
	case TP_8BIT:
	{
		assert(0);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, &texturePage[0]);
		break;
	}
	case TP_4BIT:
	{
		unsigned short* texturePage = new unsigned short[TPAGE_WIDTH / 4 * TPAGE_HEIGHT];
		unsigned short* clut = new unsigned short[16];
		unsigned short* convertedTpage = new unsigned short[TPAGE_WIDTH * TPAGE_HEIGHT];

		//Read CLUT
		glReadPixels(clutX, clutY, CLUT_WIDTH, CLUT_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &clut[0]);

		//Read texture data
		glReadPixels(tpageX, tpageY, TPAGE_WIDTH / 4, TPAGE_HEIGHT, GL_RGBA, TEXTURE_FORMAT, &texturePage[0]);

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
			rgba5551* pixel = (rgba5551*)& convertedTpage[xy];
			abgr1555* pixel2 = (abgr1555*)& convertedTpage[xy];

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

#if _DEBUG && 1
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
		
		delete[] clut;
		delete[] texturePage;
		delete[] convertedTpage;
		break;
	}

	return tpageTexture->textureID;
	}
}

void Emulator_DestroyFrameBuffer(GLuint& fbo)
{
	glDeleteFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, g_defaultFBO);
}

void Emulator_SetBlendMode(int mode, int semiTransparent)
{
	static int previousBlendMode = -1;

	if(semiTransparent)
	{
		glEnable(GL_BLEND);

		//if (previousBlendMode != mode)
		{
			switch (mode)
			{
			case 0://Average
				glBlendFuncSeparate(GL_CONSTANT_ALPHA, GL_CONSTANT_ALPHA, GL_ONE, GL_ZERO);
				glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
				break;
			case 1://Add
				glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_ZERO);
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
		}

		previousBlendMode = mode;
	}
	else
	{
		glDisable(GL_BLEND);
	}
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
#endif

void Emulator_GetTopLeftAndBottomLeftTextureCoordinate(int& x, int& y, int& w, int& h, unsigned char* u, unsigned char* v)
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

	x = topCoordX;
	y = topCoordY;
	w = (bottomCoordX - topCoordX) + 1;
	h = (bottomCoordY - topCoordY) + 1;

	//Round up next multiple of 2
	w = (w + 1) & ~0x1;
	h = (h + 1) & ~0x1;

	//Round down next multiple of 2
	//w -= (w % 2);
	//h -= (h % 2);
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
	Emulator_GetTopLeftAndBottomLeftTextureCoordinate(x, y, w, h, &textureCoordsU[0], &textureCoordsV[0]);

	//Check if this tpage is already in our cache!
	CachedTexture* tpageTexture = Emulator_FindTextureInCache(texTpage, texClut);
	bool bMustAddTexture = (tpageTexture == NULL) ? 1 : 0;

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
	unsigned short* texturePage = new unsigned short[w * h * 1024];
	unsigned short* clut = new unsigned short[16];
	unsigned short* convertedTpage = new unsigned short[w * h * 1024];

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
		rgba5551* pixel = (rgba5551*)& convertedTpage[xy];
		abgr1555* pixel2 = (abgr1555*)& convertedTpage[xy];

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

	delete[] clut;
	delete[] texturePage;
	delete[] convertedTpage;

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
	Emulator_GetTopLeftAndBottomLeftTextureCoordinate(x, y, w, h, &textureCoordsU[0], &textureCoordsV[0]);

	//Check if this tpage is already in our cache!
	CachedTexture* tpageTexture = Emulator_FindTextureInCache(texTpage, texClut);

	//Not in cache, why are we injecting? ; - )
	if (tpageTexture == NULL)
	{
		return;
	}

	Emulator_BindTexture(tpageTexture->textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned short* texturePage = new unsigned short[w * h / 2];
	unsigned short* clut = new unsigned short[16];
	unsigned short* convertedTpage = new unsigned short[w * h];

	FILE* f = fopen("LOGO.TIM", "rb");
	fseek(f, 20, SEEK_SET);
	fread(&clut[0], 16 * sizeof(short), 1, f);
	fseek(f, 64, SEEK_SET);
	fread(&texturePage[0], (w*h) / 2, 1, f);
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
		rgba5551* pixel = (rgba5551*)& convertedTpage[xy];
		abgr1555* pixel2 = (abgr1555*)& convertedTpage[xy];

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

	delete[] clut;
	delete[] texturePage;
	delete[] convertedTpage;

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
			glDeleteTextures(1, &cachedTextures[i].textureID);
		}
	}

	//Initialise texture cache
	SDL_memset(&cachedTextures[0], 0, MAX_NUM_CACHED_TEXTURES * sizeof(CachedTexture));
	
	//Initial texture id is -1
	for (int i = 0; i < MAX_NUM_CACHED_TEXTURES; i++)
	{
		cachedTextures[i].textureID = -1;
	}

	return;
}