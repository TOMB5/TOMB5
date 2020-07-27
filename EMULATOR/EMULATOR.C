#include "EMULATOR.H"

#include "EMULATOR_VERSION.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"
#include "CRASHHANDLER.H"

#include "EMULATOR_PLATFORM_SETUP.H"

#include "LIBGPU.H"
#include "LIBETC.H"
#include "LIBPAD.H"
#if !defined(__ANDROID__)
//#include <thread>
#endif
#include <assert.h>

#define FIXED_TIME_STEP    33
#define SWAP_INTERVAL      1

#if defined(NTSC_VERSION)
#define COUNTER_UPDATE_INTERVAL (263)
#else
#define COUNTER_UPDATE_INTERVAL (313)
#endif

#include <stdio.h>
#include <string.h>

#if defined(SDL2) || (defined(OGLES) && defined(_WINDOWS))
#include <SDL.h>
SDL_Window* g_window = NULL;
#endif

#if defined(D3D11)
ID3D11Texture2D* vramBaseTexture;
#endif
TextureID vramTexture;
TextureID whiteTexture;

#if defined(OGLES) || defined(OGL)
	GLuint dynamic_vertex_buffer;
	GLuint dynamic_vertex_array;
#elif defined(D3D9) || defined(XED3D)
	IDirect3DVertexBuffer9 *dynamic_vertex_buffer = NULL;
	IDirect3D9             *d3d;
	IDirect3DDevice9       *d3ddev;
	D3DPRESENT_PARAMETERS  d3dpp;
#elif defined(D3D11)
	ID3D11Buffer			*dynamic_vertex_buffer = NULL;
	ID3D11Device			*d3ddev;
	ID3D11DeviceContext		*d3dcontext;
	IDXGISwapChain			*swapChain;
	ID3D11RenderTargetView  *renderTargetView;
	ID3D11Buffer			*projectionMatrixBuffer;
	ID3D11SamplerState		*samplerState;
	ID3D11BlendState		*blendState;
#endif

int windowWidth = 0;
int windowHeight = 0;
char* pVirtualMemory = NULL;
SysCounter counters[3] = { 0 };
#if !defined(__ANDROID__)
//std::thread counter_thread;
#endif
#if defined(__ANDROID__)
#define malloc SDL_malloc
#define free SDL_free
#endif

unsigned int g_swapTime;
int g_swapInterval = SWAP_INTERVAL;
int g_wireframeMode = 0;
int g_texturelessMode = 0;
int g_emulatorPaused = 0;
int g_polygonSelected = 0;
TextureID g_lastBoundTexture;
int vram_need_update = TRUE;

void Emulator_ResetDevice()
{
#if defined(OGLES) || defined(OGL)
	SDL_GL_SetSwapInterval(g_swapInterval);
#elif defined(D3D9) || defined(XED3D)
	if (dynamic_vertex_buffer) {
		dynamic_vertex_buffer->Release();
		dynamic_vertex_buffer = NULL;
	}

	d3dpp.PresentationInterval = g_swapInterval ? D3DPRESENT_INTERVAL_ONE : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.BackBufferWidth      = windowWidth;
	d3dpp.BackBufferHeight     = windowHeight;
	HRESULT hr = d3ddev->Reset(&d3dpp);
	assert(!FAILED(hr));
#if defined(D3D9)
	hr = d3ddev->CreateVertexBuffer(sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, &dynamic_vertex_buffer, NULL);
#elif defined(XED3D)
	hr = d3ddev->CreateVertexBuffer(sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, D3DUSAGE_WRITEONLY, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, &dynamic_vertex_buffer, NULL);
#endif
	assert(!FAILED(hr));

	d3ddev->SetRenderState(D3DRS_ZENABLE,  D3DZB_FALSE);
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
#elif defined(D3D11)
	if (dynamic_vertex_buffer) {
		dynamic_vertex_buffer->Release();
		dynamic_vertex_buffer = NULL;
	}

	Emulator_DestroyGlobalShaders();
	Emulator_DestroyConstantBuffers();
	swapChain->Release();
	d3ddev->Release();
	d3dcontext->Release();
	renderTargetView->Release();
	vramTexture->Release();
	vramBaseTexture->Release();
	whiteTexture->Release();

	swapChain = NULL;
	d3ddev = NULL;
	d3dcontext = NULL;
	renderTargetView = NULL;
	vramTexture = NULL;
	vramBaseTexture = NULL;

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);

	DXGI_MODE_DESC bd;
	ZeroMemory(&bd, sizeof(DXGI_MODE_DESC));

	bd.Width = windowWidth;
	bd.Height = windowHeight;
	bd.RefreshRate.Numerator = 60;
	bd.RefreshRate.Denominator = 1;
	bd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.Windowed = TRUE;
	sd.BufferDesc = bd;
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.OutputWindow = wmInfo.info.win.window;

#if defined(_DEBUG)
	unsigned int deviceCreationFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	unsigned int deviceCreationFlags = 0;
#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &sd, &swapChain, &d3ddev, NULL, &d3dcontext);
	assert(!FAILED(hr));

	ID3D11Texture2D* backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	assert(!FAILED(hr));

	hr = d3ddev->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	assert(!FAILED(hr));

	backBuffer->Release();

	D3D11_BUFFER_DESC vbd;
	ZeroMemory(&vbd, sizeof(vbd));
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.ByteWidth = sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;

	hr = d3ddev->CreateBuffer(&vbd, NULL, &dynamic_vertex_buffer);
	assert(!FAILED(hr));

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.ArraySize = 1;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	td.Format = DXGI_FORMAT_R8G8_UNORM;
	td.Width = VRAM_WIDTH;
	td.Height = VRAM_HEIGHT;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DYNAMIC;
	hr = d3ddev->CreateTexture2D(&td, NULL, &vramBaseTexture);
	assert(!FAILED(hr));
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;

	d3ddev->CreateShaderResourceView(vramBaseTexture, &srvd, &vramTexture);
	assert(!FAILED(hr));

	Emulator_CreateGlobalShaders();
	Emulator_CreateConstantBuffers();
	Emulator_GenerateCommonTextures();
	
	vram_need_update = TRUE;
	UINT offset = 0;
	UINT stride = sizeof(Vertex);
	d3dcontext->IASetVertexBuffers(0, 1, &dynamic_vertex_buffer, &stride, &offset);
	d3dcontext->OMSetRenderTargets(1, &renderTargetView, NULL);
	d3dcontext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#endif
}

#if defined(D3D9) || defined(XED3D)
static int Emulator_InitialiseD3D9Context(char* windowName)
{
#if defined(SDL2)
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return FALSE;
	}

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);
#endif
	memset(&d3dpp, 0, sizeof(d3dpp));
#if defined(D3D9)
	d3dpp.Windowed               = TRUE;
#elif defined(XED3D)
	d3dpp.Windowed               = FALSE;
#endif
	d3dpp.BackBufferCount        = 1;
	d3dpp.BackBufferFormat       = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth        = windowWidth;
	d3dpp.BackBufferHeight       = windowHeight;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
#if defined(D3D9)
	d3dpp.hDeviceWindow          = wmInfo.info.win.window;
#endif
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;

	d3d =  Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d) {
		eprinterr("Failed to initialise D3D\n");
		return FALSE;
	}

#if defined(D3D9)
	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.hDeviceWindow, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
#elif defined(XED3D)
	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
#endif
	
	if (FAILED(hr)) {
		eprinterr("Failed to obtain D3D9 device!\n");
		return FALSE;
	}

	return TRUE;
}
#endif

#if defined(D3D11)
static int Emulator_InitialiseD3D11Context(char* windowName)
{
#if defined(SDL2)
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window!\n");
		return FALSE;
	}
#endif
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(g_window, &wmInfo);

	DXGI_MODE_DESC bd;
	ZeroMemory(&bd, sizeof(DXGI_MODE_DESC));

	bd.Width = windowWidth;
	bd.Height = windowHeight;
	bd.RefreshRate.Numerator = 60;
	bd.RefreshRate.Denominator = 1;
	bd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bd.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bd.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.Windowed = TRUE;
	sd.BufferDesc = bd;
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.OutputWindow = wmInfo.info.win.window;

#if defined(_DEBUG)
	unsigned int deviceCreationFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	unsigned int deviceCreationFlags = 0;
#endif

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, deviceCreationFlags, NULL, 0, D3D11_SDK_VERSION, &sd, &swapChain, &d3ddev, NULL, &d3dcontext);
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to initialise D3D\n");
		return FALSE;
	}

	ID3D11Texture2D* backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to get back buffer!\n");
		return FALSE;
	}

	hr = d3ddev->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
	if (!SUCCEEDED(hr)) {
		eprinterr("Failed to create render target view!\n");
		return FALSE;
	}

	backBuffer->Release();

	return TRUE;
}
#endif

static int Emulator_InitialiseGLContext(char* windowName)
{
#if defined(SDL2)
	g_window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
#endif

#if defined(OGL)
	SDL_GL_CreateContext(g_window);
#endif

#if defined(SDL2)
	if (g_window == NULL)
	{
		eprinterr("Failed to initialise SDL window or GL context!\n");
		return FALSE;
	}
#endif

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


static int Emulator_InitialiseSDL(char* windowName, int width, int height)
{
#if defined(XED3D)
	windowWidth = 1280;
	windowHeight = 720;
#else
	windowWidth  = width;
	windowHeight = height;
#endif

#if defined(SDL2)
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
            windowWidth = displayMode.w;
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
#endif

#if defined(OGL)
	if (Emulator_InitialiseGLContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GL Context!\n");
		return FALSE;
	}
#elif defined(OGLES)
	if (Emulator_InitialiseGLESContext(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise GLES Context!\n");
		return FALSE;
	}
#elif defined(D3D9) || defined(XED3D)
	if (Emulator_InitialiseD3D9Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D9 Context!\n");
		return FALSE;
	}
#elif defined(D3D11)
	if (Emulator_InitialiseD3D11Context(windowName) == FALSE)
	{
		eprinterr("Failed to Initialise D3D11 Context!\n");
		return FALSE;
	}
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

static int Emulator_InitialiseCore()
{
	return TRUE;
}

void Emulator_Initialise(char* windowName, int width, int height)
{
	eprintf("Initialising Emulator.\n");
	eprintf("VERSION: %d.%d\n", EMULATOR_MAJOR_VERSION, EMULATOR_MINOR_VERSION);
	eprintf("Compile Date: %s Time: %s\n", EMULATOR_COMPILE_DATE, EMULATOR_COMPILE_TIME);

	if (Emulator_InitialiseSDL(windowName, width, height) == FALSE)
	{
		eprinterr("Failed to Intialise SDL\n");
		Emulator_ShutDown();
	}

#if defined(GLEW)
	if (Emulator_InitialiseGLEW() == FALSE)
	{
		eprinterr("Failed to Intialise GLEW\n");
		Emulator_ShutDown();
	}
#endif

	if (Emulator_InitialiseCore() == FALSE)
	{
		eprinterr("Failed to Intialise Emulator Core.\n");
		Emulator_ShutDown();
	}

	if (Emulator_Initialise() == FALSE)
	{
		eprinterr("Failed to Intialise GL.\n");
		Emulator_ShutDown();
	}

#if defined(SDL2) || 1
	g_swapTime = SDL_GetTicks() - FIXED_TIME_STEP;
#endif

	//counter_thread = std::thread(Emulator_CounterLoop);
}

void Emulator_CounterLoop()
{
	static int numUpdates = 0;
	int last_time = 0;

	while (TRUE)
	{
#if defined(SDL2)
		int now = SDL_GetTicks();
#else
		int now = 0;
#endif
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

void Emulator_GenerateLineArray(struct Vertex* vertex, short* p0, short* p1)
{
	// swap line coordinates for left-to-right and up-to-bottom direction
	if (p0[0] > p1[0]) {
		short *tmp = p0;
		p0 = p1;
		p1 = tmp;
	} else if (p0[0] == p1[0]) {
		 if (p0[1] > p1[1]) {
			short *tmp = p0;
			p0 = p1;
			p1 = tmp;
		 }
	}

	int dx = p1[0] - p0[0];
	int dy = p1[1] - p0[1];

	if (dx > abs(dy)) { // horizontal
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];

		vertex[1].x = p1[0] + 1;
		vertex[1].y = p1[1];

		vertex[2].x = vertex[1].x;
		vertex[2].y = vertex[1].y + 1;

		vertex[3].x = vertex[0].x;
		vertex[3].y = vertex[0].y + 1;
	} else { // vertical
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];

		vertex[1].x = p1[0];
		vertex[1].y = p1[1] + 1;

		vertex[2].x = vertex[1].x + 1;
		vertex[2].y = vertex[1].y;

		vertex[3].x = vertex[0].x + 1;
		vertex[3].y = vertex[0].y;
	} // TODO diagonal line alignment
}

void Emulator_GenerateVertexArrayTriangle(struct Vertex* vertex, short* p0, short* p1, short* p2)
{
	assert(p0);
	assert(p1);
	assert(p2);

#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;
	PGXPVertex* pgxp_vertex_1 = NULL;
	PGXPVertex* pgxp_vertex_2 = NULL;

	//Locate each vertex based on SXY2 (very slow)
	for (int i = 0; i < pgxp_vertex_index; i++)
	{
		if (pgxp_vertex_0 && pgxp_vertex_1 && pgxp_vertex_2) {
			break;
		}

		if (pgxp_vertex_0 == NULL)
		{
			if (((unsigned int*)p0)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_0 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (pgxp_vertex_1 == NULL)
		{
			if (((unsigned int*)p1)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_1 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (pgxp_vertex_2 == NULL)
		{
			if (((unsigned int*)p2)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_2 = &pgxp_vertex_buffer[i];
				continue;
			}
		}
	}

	//Copy over position
	if (pgxp_vertex_0 != NULL)
	{
		vertex[0].x = pgxp_vertex_0->x;
		vertex[0].y = pgxp_vertex_0->y;
		vertex[0].z = 0.95f;
		vertex[0].w = pgxp_vertex_0->z;
	}
	else
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
	}

	if (pgxp_vertex_1 != NULL)
	{
		vertex[1].x = pgxp_vertex_1->x;
		vertex[1].y = pgxp_vertex_1->y;
		vertex[1].z = 0.95f;
		vertex[1].w = pgxp_vertex_1->z;
	}
	else
	{
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
	}

	if (pgxp_vertex_2 != NULL)
	{
		vertex[2].x = pgxp_vertex_2->x;
		vertex[2].y = pgxp_vertex_2->y;
		vertex[2].z = 0.95f;
		vertex[2].w = pgxp_vertex_2->z;
	}
	else
	{
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
	}
#else
	vertex[0].x = p0[0];
	vertex[0].y = p0[1];

	vertex[1].x = p1[0];
	vertex[1].y = p1[1];

	vertex[2].x = p2[0];
	vertex[2].y = p2[1];
#endif
}

void Emulator_GenerateVertexArrayQuad(struct Vertex* vertex, short* p0, short* p1, short* p2, short* p3)
{
	assert(p0);
	assert(p1);
	assert(p2);
	assert(p3);

#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;
	PGXPVertex* pgxp_vertex_1 = NULL;
	PGXPVertex* pgxp_vertex_2 = NULL;
	PGXPVertex* pgxp_vertex_3 = NULL;

	//Locate each vertex based on SXY2 (very slow)
	for (int i = 0; i < pgxp_vertex_index; i++)
	{
		if (pgxp_vertex_0 && pgxp_vertex_1 && pgxp_vertex_2 && pgxp_vertex_3) {
			break;
		}

		if (pgxp_vertex_0 == NULL)
		{
			if (((unsigned int*)p0)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_0 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (pgxp_vertex_1 == NULL)
		{
			if (((unsigned int*)p1)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_1 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (pgxp_vertex_2 == NULL)
		{
			if (((unsigned int*)p2)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_2 = &pgxp_vertex_buffer[i];
				continue;
			}
		}

		if (pgxp_vertex_3 == NULL)
		{
			if (((unsigned int*)p3)[0] == pgxp_vertex_buffer[i].originalSXY2)
			{
				pgxp_vertex_3 = &pgxp_vertex_buffer[i];
				continue;
			}
		}
	}

	//Copy over position
	if (pgxp_vertex_0 != NULL)
	{
		vertex[0].x = pgxp_vertex_0->x;
		vertex[0].y = pgxp_vertex_0->y;
		vertex[0].z = 0.95f;
		vertex[0].w = pgxp_vertex_0->z;
	}
	else
	{
		vertex[0].x = (float)p0[0];
		vertex[0].y = (float)p0[1];
#if defined(PGXP)
		vertex[0].z = 0.95f;
		vertex[0].w = 1.0f;
#endif
	}

	if (pgxp_vertex_1 != NULL)
	{
		vertex[1].x = pgxp_vertex_1->x;
		vertex[1].y = pgxp_vertex_1->y;
		vertex[1].z = 0.95f;
		vertex[1].w = pgxp_vertex_1->z;
	}
	else
	{
		vertex[1].x = (float)p1[0];
		vertex[1].y = (float)p1[1];
#if defined(PGXP)
		vertex[1].z = 0.95f;
		vertex[1].w = 1.0f;
#endif
	}

	if (pgxp_vertex_2 != NULL)
	{
		vertex[2].x = pgxp_vertex_2->x;
		vertex[2].y = pgxp_vertex_2->y;
		vertex[2].z = 0.95f;
		vertex[2].w = pgxp_vertex_2->z;
	}
	else
	{
		vertex[2].x = (float)p2[0];
		vertex[2].y = (float)p2[1];
#if defined(PGXP)
		vertex[2].z = 0.95f;
		vertex[2].w = 1.0f;
#endif
	}

	if (pgxp_vertex_3 != NULL)
	{
		vertex[3].x = pgxp_vertex_3->x;
		vertex[3].y = pgxp_vertex_3->y;
		vertex[3].z = 0.95f;
		vertex[3].w = pgxp_vertex_3->z;
	}
	else
	{
		vertex[3].x = (float)p3[0];
		vertex[3].y = (float)p3[1];
#if defined(PGXP)
		vertex[3].z = 0.95f;
		vertex[3].w = 1.0f;
#endif
	}
#else
	vertex[0].x = p0[0];
	vertex[0].y = p0[1];

	vertex[1].x = p1[0];
	vertex[1].y = p1[1];

	vertex[2].x = p2[0];
	vertex[2].y = p2[1];

	vertex[3].x = p3[0];
	vertex[3].y = p3[1];
#endif
}

void Emulator_GenerateVertexArrayRect(struct Vertex* vertex, short* p0, short w, short h)
{
	assert(p0);

#if defined(PGXP)
	PGXPVertex* pgxp_vertex_0 = NULL;

	//Locate each vertex based on SXY2 (very slow)
	for (int i = 0; i < pgxp_vertex_index; i++)
	{
		if (((unsigned int*)p0)[0] == pgxp_vertex_buffer[i].originalSXY2)
		{
			pgxp_vertex_0 = &pgxp_vertex_buffer[i];
			break;
		}
	}

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

	vertex[1].x = vertex[0].x;
	vertex[1].y = vertex[0].y + h;

	vertex[2].x = vertex[0].x + w;
	vertex[2].y = vertex[0].y + h;

	vertex[3].x = vertex[0].x + w;
	vertex[3].y = vertex[0].y;

#else
	vertex[0].x = p0[0];
	vertex[0].y = p0[1];

	vertex[1].x = vertex[0].x;
	vertex[1].y = vertex[0].y + h;

	vertex[2].x = vertex[0].x + w;
	vertex[2].y = vertex[0].y + h;

	vertex[3].x = vertex[0].x + w;
	vertex[3].y = vertex[0].y;
#endif
}

void Emulator_GenerateTexcoordArrayQuad(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, unsigned char* uv3, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);
	assert(uv3);

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
		vertex[0].x = p0[0];
		vertex[0].y = p0[1];
	}

	if (uv1 != NULL)
	{
		vertex[1].x = p1[0];
		vertex[1].y = p1[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[1].x = p0[0];
			vertex[1].y = p0[1] + h;
		}
	}

	if (uv2 != NULL)
	{
		vertex[2].x = p2[0];
		vertex[2].y = p2[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[2].x = p0[0] + w;
			vertex[2].y = p0[1] + h;
		}
	}

	if (uv3 != NULL)
	{
		vertex[3].x = p3[0];
		vertex[3].y = p3[1];
	}
	else
	{
		if (w != -1 && h != -1)
		{
			vertex[3].x = p0[0] + w;
			vertex[3].y = p0[1];
		}
	}
#else
	const unsigned char bright = 2;

	vertex[0].u      = uv0[0];
	vertex[0].v      = uv0[1];

	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv1[0];
	vertex[1].v      = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv2[0];
	vertex[2].v      = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;

	vertex[3].u      = uv3[0];
	vertex[3].v      = uv3[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = page;
	vertex[3].clut   = clut;
#endif
}

void Emulator_GenerateTexcoordArrayTriangle(struct Vertex* vertex, unsigned char* uv0, unsigned char* uv1, unsigned char* uv2, short page, short clut, unsigned char dither)
{
	assert(uv0);
	assert(uv1);
	assert(uv2);

#if defined(PGXP) && 0
	#error COPY IMPLEMENTATION FROM Emulator_GenerateTexcoordArrayQuad
#else
	const unsigned char bright = 2;

	vertex[0].u      = uv0[0];
	vertex[0].v      = uv0[1];

	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv1[0];
	vertex[1].v      = uv1[1];
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv2[0];
	vertex[2].v      = uv2[1];
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;
#endif
}

void Emulator_GenerateTexcoordArrayRect(struct Vertex* vertex, unsigned char* uv, short page, short clut, short w, short h)
{
	assert(uv);
	//assert(int(uv[0]) + w <= 255);
	//assert(int(uv[1]) + h <= 255);
	// TODO
	if (int(uv[0]) + w > 255) w = 255 - uv[0];
	if (int(uv[1]) + h > 255) h = 255 - uv[1];

	const unsigned char bright = 2;
	const unsigned char dither = 0;

	vertex[0].u      = uv[0];
	vertex[0].v      = uv[1];

	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = page;
	vertex[0].clut   = clut;

	vertex[1].u      = uv[0];
	vertex[1].v      = uv[1] + h;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = page;
	vertex[1].clut   = clut;

	vertex[2].u      = uv[0] + w;
	vertex[2].v      = uv[1] + h;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = page;
	vertex[2].clut   = clut;

	vertex[3].u      = uv[0] + w;
	vertex[3].v      = uv[1];
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = page;
	vertex[3].clut   = clut;
}

void Emulator_GenerateTexcoordArrayLineZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

	vertex[3].u      = 0;
	vertex[3].v      = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = 0;
	vertex[3].clut   = 0;
}

void Emulator_GenerateTexcoordArrayTriangleZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;
}

void Emulator_GenerateTexcoordArrayQuadZero(struct Vertex* vertex, unsigned char dither)
{
	const unsigned char bright = 1;

	vertex[0].u      = 0;
	vertex[0].v      = 0;
	vertex[0].bright = bright;
	vertex[0].dither = dither;
	vertex[0].page   = 0;
	vertex[0].clut   = 0;

	vertex[1].u      = 0;
	vertex[1].v      = 0;
	vertex[1].bright = bright;
	vertex[1].dither = dither;
	vertex[1].page   = 0;
	vertex[1].clut   = 0;

	vertex[2].u      = 0;
	vertex[2].v      = 0;
	vertex[2].bright = bright;
	vertex[2].dither = dither;
	vertex[2].page   = 0;
	vertex[2].clut   = 0;

	vertex[3].u      = 0;
	vertex[3].v      = 0;
	vertex[3].bright = bright;
	vertex[3].dither = dither;
	vertex[3].page   = 0;
	vertex[3].clut   = 0;
}

void Emulator_GenerateColourArrayLine(struct Vertex* vertex, unsigned char* col0, unsigned char* col1)
{
	assert(col0);
	assert(col1);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col1[0];
	vertex[2].g = col1[1];
	vertex[2].b = col1[2];
	vertex[2].a = 255;

	vertex[3].r = col0[0];
	vertex[3].g = col0[1];
	vertex[3].b = col0[2];
	vertex[3].a = 255;
}

void Emulator_GenerateColourArrayTriangle(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2)
{
	assert(col0);
	assert(col1);
	assert(col2);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col2[0];
	vertex[2].g = col2[1];
	vertex[2].b = col2[2];
	vertex[2].a = 255;
}

void Emulator_GenerateColourArrayQuad(struct Vertex* vertex, unsigned char* col0, unsigned char* col1, unsigned char* col2, unsigned char* col3)
{
	assert(col0);
	assert(col1);
	assert(col2);
	assert(col3);

	vertex[0].r = col0[0];
	vertex[0].g = col0[1];
	vertex[0].b = col0[2];
	vertex[0].a = 255;

	vertex[1].r = col1[0];
	vertex[1].g = col1[1];
	vertex[1].b = col1[2];
	vertex[1].a = 255;

	vertex[2].r = col2[0];
	vertex[2].g = col2[1];
	vertex[2].b = col2[2];
	vertex[2].a = 255;

	vertex[3].r = col3[0];
	vertex[3].g = col3[1];
	vertex[3].b = col3[2];
	vertex[3].a = 255;
}

ShaderID g_gte_shader_4;
ShaderID g_gte_shader_8;
ShaderID g_gte_shader_16;
ShaderID g_blit_shader;

#if defined(OGLES) || defined(OGL)
GLint u_Projection;


#define GTE_PACK_RG\
	"		float color_16 = (color_rg.y * 256.0 + color_rg.x) * 255.0;\n"

#define GTE_DISCARD\
	"		if (color_16 == 0.0) { discard; }\n"

#define GTE_DECODE_RG\
	"		fragColor = fract(floor(color_16 / vec4(1.0, 32.0, 1024.0, 32768.0)) / 32.0);\n"

#define GTE_DITHERING\
	"		fragColor *= v_color;\n"\
	"		mat4 dither = mat4(\n"\
	"			-4.0,  +0.0,  -3.0,  +1.0,\n"\
	"			+2.0,  -2.0,  +3.0,  -1.0,\n"\
	"			-3.0,  +1.0,  -4.0,  +0.0,\n"\
	"			+3.0,  -1.0,  +2.0,  -2.0) / 255.0;\n"\
	"		ivec2 dc = ivec2(fract(gl_FragCoord.xy / 4.0) * 4.0);\n"\
	"		fragColor.xyz += vec3(dither[dc.x][dc.y] * v_texcoord.w);\n"


#if (VRAM_FORMAT == GL_LUMINANCE_ALPHA)
	#define GTE_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).ra; }\n"
#else
	#define GTE_FETCH_VRAM_FUNC\
		"	uniform sampler2D s_texture;\n"\
		"	vec2 VRAM(vec2 uv) { return texture2D(s_texture, uv).rg; }\n"
#endif

#if defined(PGXP)
	#define GTE_PERSPECTIVE_CORRECTION \
		"		gl_Position.z = a_z;\n" \
		"		gl_Position *= a_w;\n"
#else
	#define GTE_PERSPECTIVE_CORRECTION
#endif

const char* gte_shader_4 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	attribute float a_z;\n"
	"	attribute float a_w;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
	"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
	GTE_PERSPECTIVE_CORRECTION
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 uv = (v_texcoord.xy * vec2(0.25, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		vec2 comp = VRAM(uv);\n"
	"		int index = int(fract(v_texcoord.x / 4.0 + 0.0001) * 4.0);\n"
	"\n"
	"		float v = comp[index / 2] * (255.0 / 16.0);\n"
	"		float f = floor(v);\n"
	"\n"
	"		vec2 c = vec2( (v - f) * 16.0, f );\n"
	"\n"
	"		vec2 clut_pos = v_page_clut.zw;\n"
	"		clut_pos.x += mix(c[0], c[1], fract(float(index) / 2.0) * 2.0) / 1024.0;\n"
	"		vec2 color_rg = VRAM(clut_pos);\n"
	GTE_PACK_RG
	GTE_DISCARD
	GTE_DECODE_RG
	GTE_DITHERING
	"	}\n"
	"#endif\n";

const char* gte_shader_8 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"varying vec4 v_page_clut;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	attribute float a_z;\n"
	"	attribute float a_w;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord;\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	"		v_page_clut.x = fract(a_position.z / 16.0) * 1024.0;\n"
	"		v_page_clut.y = floor(a_position.z / 16.0) * 256.0;\n"
	"		v_page_clut.z = fract(a_position.w / 64.0);\n"
	"		v_page_clut.w = floor(a_position.w / 64.0) / 512.0;\n"
	"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
	GTE_PERSPECTIVE_CORRECTION
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 uv = (v_texcoord.xy * vec2(0.5, 1.0) + v_page_clut.xy) * vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		vec2 comp = VRAM(uv);\n"
	"\n"
	"		vec2 clut_pos = v_page_clut.zw;\n"
	"		clut_pos.x += comp[int(mod(v_texcoord.x, 2.0))] * 255.0 / 1024.0;\n"
	"		vec2 color_rg = VRAM(clut_pos);\n"
	GTE_PACK_RG
	GTE_DISCARD
	GTE_DECODE_RG
	GTE_DITHERING
	"	}\n"
	"#endif\n";

const char* gte_shader_16 =
	"varying vec4 v_texcoord;\n"
	"varying vec4 v_color;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord; // uv, color multiplier, dither\n"
	"	attribute vec4 a_color;\n"
	"	attribute float a_z;\n"
	"	attribute float a_w;\n"
	"	uniform mat4 Projection;\n"
	"	void main() {\n"
	"		vec2 page\n;"
	"		page.x = fract(a_position.z / 16.0) * 1024.0\n;"
	"		page.y = floor(a_position.z / 16.0) * 256.0;\n;"
	"		v_texcoord = a_texcoord;\n"
	"		v_texcoord.xy += page;\n"
	"		v_texcoord.xy *= vec2(1.0 / 1024.0, 1.0 / 512.0);\n"
	"		v_color = a_color;\n"
	"		v_color.xyz *= a_texcoord.z;\n"
	"		gl_Position = Projection * vec4(a_position.xy, 0.0, 1.0);\n"
	GTE_PERSPECTIVE_CORRECTION
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
	GTE_PACK_RG
	GTE_DISCARD
	GTE_DECODE_RG
	GTE_DITHERING
	"	}\n"
	"#endif\n";

const char* blit_shader =
	"varying vec4 v_texcoord;\n"
	"#ifdef VERTEX\n"
	"	attribute vec4 a_position;\n"
	"	attribute vec4 a_texcoord;\n"
	"	void main() {\n"
	"		v_texcoord = a_texcoord * vec4(8.0 / 1024.0, 8.0 / 512.0, 0.0, 0.0);\n"
	"		gl_Position = vec4(a_position.xy, 0.0, 1.0);\n"
	"	}\n"
	"#else\n"
	GTE_FETCH_VRAM_FUNC
	"	void main() {\n"
	"		vec2 color_rg = VRAM(v_texcoord.xy);\n"
	GTE_PACK_RG
	GTE_DECODE_RG
	"	}\n"
	"#endif\n";

void Shader_CheckShaderStatus(GLuint shader)
{
    char info[1024];
    glGetShaderInfoLog(shader, sizeof(info), NULL, info);
    if (info[0] && strlen(info) > 8)
    {
        eprinterr("%s\n", info);
        assert(FALSE);
    }
}

void Shader_CheckProgramStatus(GLuint program)
{
    char info[1024];
    glGetProgramInfoLog(program, sizeof(info), NULL, info);
    if (info[0] && strlen(info) > 8)
    {
        eprinterr("%s\n", info);
        //assert(FALSE);
    }
}

ShaderID Shader_Compile(const char *source)
{
#if defined(ES2_SHADERS)
    const char *GLSL_HEADER_VERT =
        "#version 100\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define VERTEX\n";

    const char *GLSL_HEADER_FRAG =
        "#version 100\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define fragColor gl_FragColor\n";
#elif defined(ES3_SHADERS)
    const char *GLSL_HEADER_VERT =
        "#version 300 es\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define VERTEX\n"
        "#define varying   out\n"
        "#define attribute in\n"
        "#define texture2D texture\n";

    const char *GLSL_HEADER_FRAG =
        "#version 300 es\n"
        "precision lowp  int;\n"
        "precision highp float;\n"
        "#define varying     in\n"
        "#define texture2D   texture\n"
        "out vec4 fragColor;\n";
#else
    const char *GLSL_HEADER_VERT =
        "#version 330\n"
        "#define VERTEX\n"
        "#define varying   out\n"
        "#define attribute in\n"
        "#define texture2D texture\n";

    const char *GLSL_HEADER_FRAG =
        "#version 330\n"
        "#define varying     in\n"
        "#define texture2D   texture\n"
        "out vec4 fragColor;\n";
#endif

    const char *vs_list[] = { GLSL_HEADER_VERT, source };
    const char *fs_list[] = { GLSL_HEADER_FRAG, source };

    GLuint program = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 2, vs_list, NULL);
    glCompileShader(vertexShader);
    Shader_CheckShaderStatus(vertexShader);
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 2, fs_list, NULL);
    glCompileShader(fragmentShader);
    Shader_CheckShaderStatus(fragmentShader);
    glAttachShader(program, fragmentShader);
    glDeleteShader(fragmentShader);

    glBindAttribLocation(program, a_position, "a_position");
    glBindAttribLocation(program, a_texcoord, "a_texcoord");
    glBindAttribLocation(program, a_color,    "a_color");

#if defined(PGXP)
	glBindAttribLocation(program, a_z, "a_z");
	glBindAttribLocation(program, a_w, "a_w");
#endif

    glLinkProgram(program);
    Shader_CheckProgramStatus(program);

    GLint sampler = 0;
    glUseProgram(program);
    glUniform1iv(glGetUniformLocation(program, "s_texture"), 1, &sampler);
    glUseProgram(0);

    return program;
}
#elif defined(D3D9) || defined(XED3D)

#include "shaders/gte_shader_4_vs.h"
#include "shaders/gte_shader_4_ps.h"
#include "shaders/gte_shader_8_vs.h"
#include "shaders/gte_shader_8_ps.h"
#include "shaders/gte_shader_16_vs.h"
#include "shaders/gte_shader_16_ps.h"
#include "shaders/blit_shader_vs.h"
#include "shaders/blit_shader_ps.h"

// shader registers
const int u_Projection = 0;

LPDIRECT3DVERTEXDECLARATION9 vertexDecl;

#define Shader_Compile(name) Shader_Compile_Internal((DWORD*)name##_vs, (DWORD*)name##_ps)

ShaderID Shader_Compile_Internal(const DWORD *vs_data, const DWORD *ps_data)
{
	ShaderID shader;
	HRESULT hr;
	hr = d3ddev->CreateVertexShader(vs_data, &shader.VS);
	assert(!FAILED(hr));
	hr = d3ddev->CreatePixelShader(ps_data, &shader.PS);
	assert(!FAILED(hr));
	return shader;
}

#elif defined(D3D11)

#include "shaders/gte_shader_4_vs.h"
#include "shaders/gte_shader_4_ps.h"
#include "shaders/gte_shader_8_vs.h"
#include "shaders/gte_shader_8_ps.h"
#include "shaders/gte_shader_16_vs.h"
#include "shaders/gte_shader_16_ps.h"
#include "shaders/blit_shader_vs.h"
#include "shaders/blit_shader_ps.h"


#define Shader_Compile(name) Shader_Compile_Internal((DWORD*)name##_vs, (DWORD*)name##_ps, sizeof(name##_vs), sizeof(name##_ps))

ShaderID Shader_Compile_Internal(const DWORD* vs_data, const DWORD* ps_data, const unsigned int vs_size, const unsigned int ps_size)
{
	ShaderID shader;
	HRESULT hr;
	int test = sizeof(gte_shader_4_vs);
	hr = d3ddev->CreateVertexShader(vs_data, vs_size, NULL, &shader.VS);
	assert(!FAILED(hr));
	hr = d3ddev->CreatePixelShader(ps_data, ps_size, NULL, &shader.PS);
	assert(!FAILED(hr));
#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3D11_INPUT_ELEMENT_DESC INPUT_LAYOUT[] =
	{
#if defined(PGXP)
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, OFFSETOF(Vertex, x), D3D11_INPUT_PER_VERTEX_DATA, 0 },
#else	
		{ "POSITION", 0, DXGI_FORMAT_R16G16B16A16_SINT, 0, OFFSETOF(Vertex, x), D3D11_INPUT_PER_VERTEX_DATA, 0 },
#endif
		{ "TEXCOORD", 0, DXGI_FORMAT_R8G8B8A8_UINT,		0, OFFSETOF(Vertex, u), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R8G8B8A8_UNORM,	0, OFFSETOF(Vertex, r), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

	hr = d3ddev->CreateInputLayout(INPUT_LAYOUT, sizeof(INPUT_LAYOUT) / sizeof(D3D11_INPUT_ELEMENT_DESC), vs_data, vs_size, &shader.IL);
	assert(!FAILED(hr));

	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampDesc.MinLOD = -D3D11_FLOAT32_MAX;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
	sampDesc.MaxAnisotropy = 1;
	d3ddev->CreateSamplerState(&sampDesc, &samplerState);

#undef OFFSETOF

	return shader;
}
#else
    #error
#endif

void Emulator_CreateGlobalShaders()
{
	g_gte_shader_4  = Shader_Compile(gte_shader_4);
	g_gte_shader_8  = Shader_Compile(gte_shader_8);
	g_gte_shader_16 = Shader_Compile(gte_shader_16);
	g_blit_shader   = Shader_Compile(blit_shader);

#if defined(OGL) || defined(OGLES)
	u_Projection = glGetUniformLocation(g_gte_shader_4, "Projection");
#endif
}

void Emulator_DestroyGlobalShaders()
{
	g_gte_shader_4.VS->Release();
	g_gte_shader_4.PS->Release();
	g_gte_shader_4.IL->Release();
	g_gte_shader_8.VS->Release();
	g_gte_shader_8.PS->Release();
	g_gte_shader_8.IL->Release();
	g_gte_shader_16.VS->Release();
	g_gte_shader_16.PS->Release();
	g_gte_shader_16.IL->Release();
	g_blit_shader.VS->Release();
	g_blit_shader.PS->Release();
	g_blit_shader.IL->Release();
}

unsigned short vram[VRAM_WIDTH * VRAM_HEIGHT];

void Emulator_GenerateCommonTextures()
{
	unsigned int pixelData = 0xFFFFFFFF;
#if defined(OGL) || defined(OGLES)
	glGenTextures(1, &whiteTexture);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixelData);
	glBindTexture(GL_TEXTURE_2D, 0);
#elif defined(D3D9) || defined(XED3D)
	HRESULT hr = d3ddev->CreateTexture(1, 1, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &whiteTexture, NULL);
	assert(!FAILED(hr));
	D3DLOCKED_RECT rect;
	hr = whiteTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, &pixelData, sizeof(pixelData));
	whiteTexture->UnlockRect(0);
#elif defined(D3D11)
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = 1;
	td.Height = 1;
	td.MipLevels = td.ArraySize = 1;
	td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;
	ID3D11Texture2D* t = NULL;

	D3D11_SUBRESOURCE_DATA srd;
	ZeroMemory(&srd, sizeof(srd));
	srd.pSysMem = (void*)&pixelData;
	srd.SysMemPitch = td.Width * sizeof(unsigned int);
	srd.SysMemSlicePitch = 0;

	HRESULT hr = d3ddev->CreateTexture2D(&td, &srd, &t);
	assert(!FAILED(hr));
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MipLevels = td.MipLevels;
	srvd.Texture2D.MostDetailedMip = 0;
	hr = d3ddev->CreateShaderResourceView(t, &srvd, &whiteTexture);
	assert(!FAILED(hr));
	t->Release();

#endif
}

int Emulator_Initialise()
{
	memset(vram, 0, VRAM_WIDTH * VRAM_HEIGHT * sizeof(unsigned short));
	Emulator_GenerateCommonTextures();
	Emulator_CreateGlobalShaders();

#if defined(D3D11)
	Emulator_CreateConstantBuffers();
#endif

#if defined(OGL) || defined(OGLES)
	glDisable(GL_DEPTH_TEST);
	glBlendColor(0.5f, 0.5f, 0.5f, 0.25f);

	glGenTextures(1, &vramTexture);
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, VRAM_INTERNAL_FORMAT, VRAM_WIDTH, VRAM_HEIGHT, 0, VRAM_FORMAT, GL_UNSIGNED_BYTE, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &dynamic_vertex_buffer);
	glGenVertexArrays(1, &dynamic_vertex_array);
	glBindVertexArray(dynamic_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, dynamic_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(a_position);
	glEnableVertexAttribArray(a_texcoord);
	
    glEnableVertexAttribArray(a_color);
#if defined(PGXP)
	glVertexAttribPointer(a_position, 4, GL_FLOAT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
#else
	glVertexAttribPointer(a_position, 4, GL_SHORT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->x);
#endif
	glVertexAttribPointer(a_texcoord, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->u);
	glVertexAttribPointer(a_color,    4, GL_UNSIGNED_BYTE, GL_TRUE,  sizeof(Vertex), &((Vertex*)NULL)->r);
#if defined(PGXP)
	glVertexAttribPointer(a_z,        1, GL_FLOAT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->z);
	glVertexAttribPointer(a_w,        1, GL_FLOAT,         GL_FALSE, sizeof(Vertex), &((Vertex*)NULL)->w);

	glEnableVertexAttribArray(a_z);
	glEnableVertexAttribArray(a_w);
#endif
	glBindVertexArray(0);
#elif defined(D3D9) || defined(XED3D)
	if (FAILED(d3ddev->CreateTexture(VRAM_WIDTH, VRAM_HEIGHT, 1, 0, D3DFMT_A8L8, D3DPOOL_MANAGED, &vramTexture, NULL)))
	{
		eprinterr("Failed to create render target texture!\n");
		return FALSE;
	}

	#define OFFSETOF(T, E)     ((size_t)&(((T*)0)->E))

	const D3DVERTEXELEMENT9 VERTEX_DECL[] = {
#if defined(PGXP)
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_FLOAT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
#else
		{0, OFFSETOF(Vertex, x), D3DDECLTYPE_SHORT4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, // a_position
#endif
		{0, OFFSETOF(Vertex, u), D3DDECLTYPE_UBYTE4,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0}, // a_texcoord
		{0, OFFSETOF(Vertex, r), D3DDECLTYPE_UBYTE4N,  D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0}, // a_color
		D3DDECL_END()
	};

	d3ddev->CreateVertexDeclaration(VERTEX_DECL, &vertexDecl);

	#undef OFFSETOF
#elif defined(D3D11)

	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.ArraySize = 1;
	td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	td.Format = DXGI_FORMAT_R8G8_UNORM;
	td.Width = VRAM_WIDTH;
	td.Height = VRAM_HEIGHT;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DYNAMIC;
	if (FAILED(d3ddev->CreateTexture2D(&td, NULL, &vramBaseTexture)))
	{
		eprinterr("Failed to create render target texture!\n");
		return FALSE;
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
	srvd.Format = td.Format;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = 1;

	if (FAILED(d3ddev->CreateShaderResourceView(vramBaseTexture, &srvd, &vramTexture)))
	{
		eprinterr("Failed to create shader resource view!\n");
		return FALSE;
	}
#else
	#error
#endif

	Emulator_ResetDevice();

    return TRUE;
}

void Emulator_Ortho2D(float left, float right, float bottom, float top, float znear, float zfar)
{
	float a = 2.0f / (right - left);
	float b = 2.0f / (top - bottom);
	float c = 2.0f / (znear - zfar);

	float x = (left + right) / (left - right);
	float y = (bottom + top) / (bottom - top);

#if defined(OGL) || defined(OGLES) // -1..1
	float z = (znear + zfar) / (znear - zfar);
#elif defined(D3D9) || defined (XED3D) || defined(D3D11)// 0..1
	float z = znear / (znear - zfar);
#endif

	DirectX::XMMATRIX mat;

	float ortho[16] = {
		a, 0, 0, 0,
		0, b, 0, 0,
		0, 0, c, 0,
		x, y, z, 1
	};

	memcpy(&mat, &ortho[0], sizeof(DirectX::XMMATRIX));
	mat = DirectX::XMMatrixTranspose(mat);

#if defined(OGL) || defined(OGLES)
	glUniformMatrix4fv(u_Projection, 1, GL_FALSE, ortho);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->SetVertexShaderConstantF(u_Projection, ortho, 4);
#elif defined(D3D11)
	Emulator_UpdateProjectionConstantBuffer(&ortho[0]);
	Emulator_SetConstantBuffers();
#else
	#error
#endif
}

void Emulator_SetShader(const ShaderID &shader)
{
#if defined(OGL) || defined(OGLES)
	glUseProgram(shader);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->SetVertexShader(shader.VS);
	d3ddev->SetPixelShader(shader.PS);
#elif defined(D3D11)
	d3dcontext->VSSetShader(shader.VS, NULL, 0);
	d3dcontext->PSSetShader(shader.PS, NULL, 0);
	d3dcontext->IASetInputLayout(shader.IL);
#else
	#error
#endif

	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);
}

void Emulator_SetTexture(TextureID texture, TexFormat texFormat)
{
	switch (texFormat)
	{
		case TF_4_BIT :
			Emulator_SetShader(g_gte_shader_4);
			break;
		case TF_8_BIT :
			Emulator_SetShader(g_gte_shader_8);
			break;
		case TF_16_BIT :
			Emulator_SetShader(g_gte_shader_16);
			break;
	}

	if (g_texturelessMode) {
		texture = whiteTexture;
	}

	if (g_lastBoundTexture == texture) {
		return;
	}

#if defined(OGL) || defined(OGLES)
	glBindTexture(GL_TEXTURE_2D, texture);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->SetTexture(0, texture);
#elif defined(D3D11)
	d3dcontext->PSSetShaderResources(0, 1, &texture);
	d3dcontext->PSSetSamplers(0, 1, &samplerState);
#else
	#error
#endif

	g_lastBoundTexture = texture;
}

void Emulator_DestroyTexture(TextureID texture)
{
#if defined(OGL) || defined(OGLES)
    glDeleteTextures(1, &texture);
#elif defined(D3D9) || defined(XED3D) || defined(D3D11)
    texture->Release();
#else
    #error
#endif
}

extern void Emulator_Clear(int x, int y, int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
// TODO clear rect if it's necessary
///@FIXME set scissor!
#if defined(OGL) || defined(OGLES)
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF000000 | (r << 16) | (g << 8) | (b), 1.0f, 0);
#elif defined(D3D11)
	FLOAT clearColor[4]{ r / 255.0f, g / 255.0f, b / 255.0f, 1.0f };
	d3dcontext->ClearRenderTargetView(renderTargetView, clearColor);
#else
	#error
#endif
}

#define NOFILE 0

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)

void Emulator_SaveVRAM(const char* outputFileName, int x, int y, int width, int height, int bReadFromFrameBuffer)
{
#if NOFILE
	return;
#endif

#if defined(OGL) || defined(OGLES) || 1
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

	fwrite(TGAheader, sizeof(unsigned char), 12, f);
	fwrite(header, sizeof(unsigned char), 6, f);

	//512 const is hdd sector size
	int numSectorsToWrite = (width * height * sizeof(unsigned short)) / 512;
	int numRemainingSectorsToWrite = (width * height * sizeof(unsigned short)) % 512;

	for (int i = 0; i < numSectorsToWrite; i++)
	{
		fwrite(&vram[i * 512 / sizeof(unsigned short)], 512, 1, f);
	}

	for (int i = 0; i < numRemainingSectorsToWrite; i++)
	{
		fwrite(&vram[numSectorsToWrite * 512 / sizeof(unsigned short)], numRemainingSectorsToWrite, 1, f);
	}

	fclose(f);

#elif defined(D3D9)
	//D3DXSaveSurfaceToFile(outputFileName, D3DXIFF_TGA, vramFrameBuffer, NULL, NULL);
#elif defined(D3D11)
	
#endif
}
#endif

void Emulator_StoreFrameBuffer(int x, int y, int w, int h)
{
	short *fb = (short*)malloc(windowWidth * windowHeight * sizeof(short));

#if defined(OGL) || defined(OGLES)
	int *data = (int*)malloc(windowWidth * windowHeight * sizeof(int));
	glReadPixels(0, 0, windowWidth, windowHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);

	#define FLIP_Y (h - fy - 1)
#elif defined(D3D9) || defined (XED3D)
	IDirect3DSurface9 *srcSurface, *dstSurface;
	HRESULT hr;
	D3DLOCKED_RECT rect;
	hr = d3ddev->GetRenderTarget(0, &srcSurface);
	assert(!FAILED(hr));
#if !defined(XED3D)
	hr = d3ddev->CreateOffscreenPlainSurface(windowWidth, windowHeight, D3DFMT_A8R8G8B8, D3DPOOL_SYSTEMMEM, &dstSurface, NULL);
	assert(!FAILED(hr));
	hr = d3ddev->GetRenderTargetData(srcSurface, dstSurface);
	assert(!FAILED(hr));
#endif
	hr = dstSurface->LockRect(&rect, NULL, D3DLOCK_READONLY);
	assert(!FAILED(hr));
	assert(windowWidth * 4 == rect.Pitch);

	int *data = (int*)rect.pBits;

	#define FLIP_Y (fy)
#elif defined(D3D11)
	ID3D11Texture2D* backBuffer;
	HRESULT hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	assert(!FAILED(hr));
	ID3D11Texture2D* newBackBuffer = NULL;
	D3D11_TEXTURE2D_DESC description;
	backBuffer->GetDesc(&description);
	description.BindFlags = 0;
	description.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	description.Usage = D3D11_USAGE_STAGING;
	hr = d3ddev->CreateTexture2D(&description, NULL, &newBackBuffer);
	assert(!FAILED(hr));
	d3dcontext->CopyResource(newBackBuffer, backBuffer);
	D3D11_MAPPED_SUBRESOURCE resource;
	unsigned int subResource = D3D11CalcSubresource(0, 0, 0);
	hr = d3dcontext->Map(newBackBuffer, subResource, D3D11_MAP_READ_WRITE, 0, &resource);
	assert(!FAILED(hr));
	
	int* data = (int*)resource.pData;

#define FLIP_Y (fy)

#endif

	unsigned int   *data_src = (unsigned int*)data;
	unsigned short *data_dst = (unsigned short*)fb;

	for (int i = 0; i < windowHeight; i++) {
		for (int j = 0; j < windowWidth; j++) {
			unsigned int  c = *data_src++;
			unsigned char b = ((c >>  3) & 0x1F);
			unsigned char g = ((c >> 11) & 0x1F);
			unsigned char r = ((c >> 19) & 0x1F);
			*data_dst++ = r | (g << 5) | (b << 10) | 0x8000;
		}
	}

#if defined(OGL) || defined(OGLES)
	free(data);
#elif defined(D3D9) || defined(XED3D)
	dstSurface->UnlockRect();

	dstSurface->Release();
	srcSurface->Release();
#elif defined(D3D11)
	d3dcontext->Unmap(newBackBuffer, subResource);
#endif

	short *ptr = (short*)vram + VRAM_WIDTH * y + x;

	for (int fy = 0; fy < h; fy++) {
		short *fb_ptr = fb + (windowHeight * FLIP_Y / h) * windowWidth;

		for (int fx = 0; fx < w; fx++) {
			ptr[fx] = fb_ptr[windowWidth * fx / w];
		}

		ptr += VRAM_WIDTH;
	}

	#undef FLIP_Y

	free(fb);

	vram_need_update = TRUE;
}

void Emulator_CopyVRAM(unsigned short *src, int x, int y, int w, int h, int dst_x, int dst_y)
{
	vram_need_update = TRUE;

    int stride = w;

    if (!src) {
        src    = vram;
        stride = VRAM_WIDTH;
    }

    src += x + y * stride;

    unsigned short *dst = vram + dst_x + dst_y * VRAM_WIDTH;

    for (int i = 0; i < h; i++) {
        memcpy(dst, src, w * sizeof(short));
        dst += VRAM_WIDTH;
        src += stride;
    }
}

void Emulator_ReadVRAM(unsigned short *dst, int x, int y, int dst_w, int dst_h)
{
	unsigned short *src = vram + x + VRAM_WIDTH * y;

	for (int i = 0; i < dst_h; i++) {
		memcpy(dst, src, dst_w * sizeof(short));
		dst += dst_w;
		src += VRAM_WIDTH;
	}
}

void Emulator_UpdateVRAM()
{
	if (!vram_need_update) {
		return;
	}
	vram_need_update = FALSE;

#if defined(OGL) || defined(OGLES)
	glBindTexture(GL_TEXTURE_2D, vramTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, VRAM_WIDTH, VRAM_HEIGHT, VRAM_FORMAT, GL_UNSIGNED_BYTE, vram);
#elif defined(D3D9) || defined(XED3D)
	D3DLOCKED_RECT rect;
	HRESULT hr = vramTexture->LockRect(0, &rect, NULL, 0);
	assert(!FAILED(hr));
	memcpy(rect.pBits, vram, VRAM_WIDTH * VRAM_HEIGHT * sizeof(short));
	vramTexture->UnlockRect(0);
#elif defined(D3D11)
	D3D11_MAPPED_SUBRESOURCE sr;
	HRESULT hr = d3dcontext->Map(vramBaseTexture, 0, D3D11_MAP_WRITE_DISCARD, 0, &sr);
	assert(!FAILED(hr));
	memcpy(sr.pData, vram, VRAM_WIDTH * VRAM_HEIGHT * sizeof(short));
	d3dcontext->Unmap(vramBaseTexture, 0);
#endif
}

void Emulator_BlitVRAM()
{
	if (activeDispEnv.isinter)
	{
		//Emulator_StoreFrameBuffer(activeDispEnv.disp.x, activeDispEnv.disp.y, activeDispEnv.disp.w, activeDispEnv.disp.h);
		return;
	}

	Emulator_SetTexture(vramTexture, TF_16_BIT);
	Emulator_SetShader(g_blit_shader);

	u_char l = activeDispEnv.disp.x / 8;
	u_char t = activeDispEnv.disp.y / 8;
	u_char r = activeDispEnv.disp.w / 8 + l;
	u_char b = activeDispEnv.disp.h / 8 + t;

	Vertex blit_vertices[] =
	{
		{ +1, +1,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
		{ -1, -1,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ -1, +1,    0, 0,    l, t,    0, 0,    0, 0, 0, 0 },

		{ +1, -1,    0, 0,    r, b,    0, 0,    0, 0, 0, 0 },
		{ -1, -1,    0, 0,    l, b,    0, 0,    0, 0, 0, 0 },
		{ +1, +1,    0, 0,    r, t,    0, 0,    0, 0, 0, 0 },
	};

	Emulator_UpdateVertexBuffer(blit_vertices, 6);
	Emulator_SetBlendMode(BM_NONE);
	Emulator_DrawTriangles(0, 2);
}

void Emulator_DoDebugKeys(int nKey, bool down); // forward decl

void Emulator_DoPollEvent()
{
#if defined(SDL2)
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_CONTROLLERDEVICEADDED:
				padHandle[event.jbutton.which] = SDL_GameControllerOpen(event.cdevice.which);
				break;
			case SDL_CONTROLLERDEVICEREMOVED:
				SDL_GameControllerClose(padHandle[event.cdevice.which]);
				break;
			case SDL_QUIT:
				Emulator_ShutDown();
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					windowWidth = event.window.data1;
					windowHeight = event.window.data2;
					Emulator_ResetDevice();
					break;
				case SDL_WINDOWEVENT_CLOSE:
					Emulator_ShutDown();
					break;
				}
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				int nKey = event.key.keysym.scancode;

				// lshift/right shift
				if (nKey == SDL_SCANCODE_RSHIFT)
					nKey = SDL_SCANCODE_LSHIFT;
				else if (nKey == SDL_SCANCODE_RCTRL)
					nKey = SDL_SCANCODE_LCTRL;
				else if (nKey == SDL_SCANCODE_RALT)
					nKey = SDL_SCANCODE_LALT;

				Emulator_DoDebugKeys(nKey, (event.type == SDL_KEYUP) ? FALSE : TRUE);
				break;
			}
		}
	}
#endif
}

bool begin_scene_flag = FALSE;
bool vbo_was_dirty_flag = FALSE;

int Emulator_BeginScene()
{
	Emulator_DoPollEvent();

	if (begin_scene_flag)
		return FALSE;

	assert(!begin_scene_flag);

	g_lastBoundTexture = NULL;

#if defined(OGL) || defined(OGLES)
	glBindVertexArray(dynamic_vertex_array);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->BeginScene();
	d3ddev->SetVertexDeclaration(vertexDecl);
	d3ddev->SetStreamSource(0, dynamic_vertex_buffer, 0, sizeof(Vertex));
#elif defined(D3D11)
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3dcontext->IASetVertexBuffers(0, 1, &dynamic_vertex_buffer, &stride, &offset);
#endif

	Emulator_UpdateVRAM();
	Emulator_SetViewPort(0, 0, windowWidth, windowHeight);

	Emulator_SetShader(g_gte_shader_4);
	Emulator_Ortho2D(0.0f, activeDispEnv.disp.w, activeDispEnv.disp.h, 0.0f, 0.0f, 1.0f);

	begin_scene_flag = TRUE;

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(TRUE);
	}

	return TRUE;
}

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
void Emulator_TakeScreenshot()
{
	unsigned char* pixels = new unsigned char[windowWidth * windowHeight * 4];
#if defined(OGL) || defined(OGLES)
#define GL_BGRA GL_RGBA
	glReadPixels(0, 0, windowWidth, windowHeight, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
#endif

#if defined(SDL2)
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, windowWidth, windowHeight, 8 * 4, windowWidth * 4, 0, 0, 0, 0);
	SDL_SaveBMP(surface, "SCREENSHOT.BMP");
	SDL_FreeSurface(surface);
#endif

	delete[] pixels;
}
#endif

void Emulator_DoDebugKeys(int nKey, bool down)
{
#if defined(SDL2)
	if (nKey == SDL_SCANCODE_BACKSPACE)
	{
		if(down)
		{
			if (g_swapInterval != 0)
			{
				g_swapInterval = 0;
				Emulator_ResetDevice();
			}
		}
		else
		{
			if (g_swapInterval != SWAP_INTERVAL)
			{
				g_swapInterval = SWAP_INTERVAL;
				Emulator_ResetDevice();
			}
		}
	}

	if (!down)
	{
		switch (nKey)
		{
			case SDL_SCANCODE_1:
				g_wireframeMode ^= 1;
				eprintf("wireframe mode: %d\n", g_wireframeMode);
				break;

			case SDL_SCANCODE_2:
				g_texturelessMode ^= 1;
				eprintf("textureless mode: %d\n", g_texturelessMode);
				break;

			case SDL_SCANCODE_3:
				g_emulatorPaused ^= 1;
				break;

			case SDL_SCANCODE_UP:
			case SDL_SCANCODE_DOWN:
				if (g_emulatorPaused)
					g_polygonSelected += (nKey == SDL_SCANCODE_UP) ? 3 : -3;
				break;

#if !defined(__EMSCRIPTEN__) && !defined(__ANDROID__)
			case SDL_SCANCODE_4:
				eprintf("saving screenshot\n");
				Emulator_TakeScreenshot();
				break;
			case SDL_SCANCODE_5:
				eprintf("saving VRAM.TGA\n");
				Emulator_SaveVRAM("VRAM.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
				break;
#endif
		}
	}
#endif
}

void Emulator_UpdateInput()
{
	// also poll events here
	Emulator_DoPollEvent();

#if defined(SDL2)
	unsigned short kbInputs = UpdateKeyboardInput();

	//Update pad
	if (SDL_NumJoysticks() > 0)
	{
		for (int i = 0; i < MAX_CONTROLLERS; i++)
		{
			if (padHandle[i] != NULL)
			{
				unsigned short controllerInputs = UpdateGameControllerInput(padHandle[i]);

				padData[i][0] = 0;
				padData[i][1] = 0x41;//?
				((unsigned short*)padData[i])[1] = kbInputs & controllerInputs;
			}
		}
	}
	else
	{
		//Update keyboard
		if (padData[0] != NULL)
		{
			padData[0][0] = 0;
			padData[0][1] = 0x41;//?
			((unsigned short*)padData[0])[1] = kbInputs;
		}
	}
#endif

#if defined(__ANDROID__)
    ///@TODO SDL_NumJoysticks always reports > 0 for some reason on Android.
    ((unsigned short*)padData[0])[1] = UpdateKeyboardInput();
#endif
}

unsigned int Emulator_GetFPS()
{
#if defined(SDL2)
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
#else
	return 0;
#endif
	
}

void Emulator_SwapWindow()
{
	Emulator_WaitForTimestep(1);

#if defined(RO_DOUBLE_BUFFERED)
#if defined(OGL)
	SDL_GL_SwapWindow(g_window);
#elif defined(OGLES)
	eglSwapBuffers(eglDisplay, eglSurface);
#elif defined(D3D9) || defined(XED3D)
	if (d3ddev->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST) {
		Emulator_ResetDevice();
	}
#elif defined(D3D11)
	HRESULT hr = swapChain->Present(1, 0);
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
		Emulator_ResetDevice();
	}
#endif
#else
	glFinish();
#endif
}

void Emulator_WaitForTimestep(int count)
{
#if defined(SDL2)
	if (g_swapInterval > 0) 
	{
		int delta = g_swapTime + FIXED_TIME_STEP*count - SDL_GetTicks();

		if (delta > 0) {
			SDL_Delay(delta);
		}
	}

	g_swapTime = SDL_GetTicks();
#elif defined(XED3D)
	///@TODO
#endif
}

void Emulator_EndScene()
{
	if (!begin_scene_flag)
		return;

	if (!vbo_was_dirty_flag)
		return;

	assert(begin_scene_flag);

	if (g_wireframeMode)
	{
		Emulator_SetWireframe(FALSE);
	}

#if defined(OGL) || defined(OGLES)
	glBindVertexArray(0);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->EndScene();
#endif

	begin_scene_flag = FALSE;
	vbo_was_dirty_flag = FALSE;

	Emulator_SwapWindow();
}

void Emulator_ShutDown()
{
#if defined(OGL) || defined(OGLES)
	Emulator_DestroyTexture(vramTexture);
	Emulator_DestroyTexture(whiteTexture);
#endif

#if defined(SDL2)
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
#endif

#if defined(D3D9) || defined(XED3D)
	d3ddev->Release();
	d3d->Release();
	///@TODO release shaders.
#elif defined(D3D11)
	d3ddev->Release();
	d3dcontext->Release();
	vramBaseTexture->Release();
	///@TODO release shaders.
#endif

#if defined(SDL2)
	SDL_DestroyWindow(g_window);
	SDL_Quit();
#endif

	exit(0);
}

int g_PreviousBlendMode = BM_NONE;

void Emulator_SetBlendMode(BlendMode blendMode)
{
	if (g_PreviousBlendMode == blendMode)
	{
		return;
	}

#if defined(OGL) || defined(OGLES)
	if (g_PreviousBlendMode == BM_NONE)
	{
		glEnable(GL_BLEND);
	}

	switch (blendMode)
	{
	case BM_NONE:
		glDisable(GL_BLEND);
		break;
	case BM_AVERAGE:
		glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_COLOR);
		glBlendEquation(GL_FUNC_ADD);
		break;
	case BM_ADD:
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		break;
	case BM_SUBTRACT:
		glBlendFunc(GL_ONE, GL_ONE);
		glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
		break;
	case BM_ADD_QUATER_SOURCE:
		glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE);
		glBlendEquation(GL_FUNC_ADD);
		break;
	}
#elif defined(D3D9) || defined(XED3D)
	if (g_PreviousBlendMode == BM_NONE)
	{
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	}

	switch (blendMode)
	{
	case BM_NONE:
		d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		break;
	case BM_AVERAGE:
		d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(128, 128, 128, 128));
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_BLENDFACTOR);
		break;
	case BM_ADD:
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case BM_SUBTRACT:
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case BM_ADD_QUATER_SOURCE:
		d3ddev->SetRenderState(D3DRS_BLENDFACTOR, D3DCOLOR_RGBA(64, 64, 64, 64));
		d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_BLENDFACTOR);
		d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	}
#elif defined(D3D11)
	if (blendState != NULL)
	{
		blendState->Release();
		blendState = NULL;
	}

	if (g_PreviousBlendMode == BM_NONE)
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = FALSE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		assert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
	}

	switch (blendMode)
	{
	case BM_NONE:
	{
		d3dcontext->OMSetBlendState(NULL, 0, -1);
		break;
	}
	case BM_AVERAGE:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		assert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 128.0f * (1.0f / 255.0f), 128.0f * (1.0f / 255.0f), 128.0f * (1.0f / 255.0f), 128.0f * (1.0f / 255.0f) };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	case BM_ADD:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		assert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	case BM_SUBTRACT:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_REV_SUBTRACT;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		assert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	case BM_ADD_QUATER_SOURCE:
	{
		D3D11_BLEND_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.AlphaToCoverageEnable = FALSE;
		bd.IndependentBlendEnable = TRUE;
		bd.RenderTarget[0].BlendEnable = TRUE;
		bd.RenderTarget[0].SrcBlend = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_BLEND_FACTOR;
		bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
		bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		HRESULT hr = d3ddev->CreateBlendState(&bd, &blendState);
		assert(SUCCEEDED(hr));
		FLOAT blendFactor[4] = { 64.0f * (1.0f / 255.0f), 64.0f * (1.0f / 255.0f), 64.0f * (1.0f / 255.0f), 64.0f * (1.0f / 255.0f) };
		d3dcontext->OMSetBlendState(blendState, blendFactor, -1);
		break;
	}
	}
#endif

	g_PreviousBlendMode = blendMode;
}

void Emulator_SetPGXPVertexCount(int vertexCount)
{
#if defined(PGXP)
	pgxp_vertex_count = vertexCount;
#endif
}

void Emulator_SetViewPort(int x, int y, int width, int height)
{
#if defined(OGL) || defined(OGLES)
	glViewport(x, y, width, height);
#elif defined(D3D9) || defined(XED3D)
	D3DVIEWPORT9 viewport;
	viewport.X      = x;
	viewport.Y      = y;
	viewport.Width  = width;
	viewport.Height = height;
	viewport.MinZ   = 0.0f;
	viewport.MaxZ   = 1.0f;
	d3ddev->SetViewport(&viewport);
#elif defined(D3D11)
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX	= (float)x;
	viewport.TopLeftY	= (float)y;
	viewport.Width		= (float)width;
	viewport.Height		= (float)height;
	viewport.MinDepth	= 0.0f;
	viewport.MaxDepth	= 1.0f;
	d3dcontext->RSSetViewports(1, &viewport);
#endif
}

void Emulator_SetRenderTarget(const RenderTargetID &frameBufferObject)
{
#if defined(OGL) || defined(OGLES)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->SetRenderTarget(0, frameBufferObject);
#elif defined(D3D11)
	d3dcontext->OMSetRenderTargets(1, &frameBufferObject, NULL);
#else
    #error
#endif
}

void Emulator_SetWireframe(bool enable)
{
#if defined(OGL)
	glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->SetRenderState(D3DRS_FILLMODE, enable ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
#elif defined(D3D11)
	d3dcontext->IASetPrimitiveTopology(enable ? D3D_PRIMITIVE_TOPOLOGY_LINELIST : D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
#endif
}

void Emulator_UpdateVertexBuffer(const Vertex *vertices, int num_vertices)
{
	assert(num_vertices <= MAX_NUM_POLY_BUFFER_VERTICES);
#if defined(OGL) || defined(OGLES)
	glBufferSubData(GL_ARRAY_BUFFER, 0, num_vertices * sizeof(Vertex), vertices);
#elif defined(D3D9) || defined(XED3D)
	void *ptr;
#if defined(D3D9)
	dynamic_vertex_buffer->Lock(0, 0, &ptr, D3DLOCK_DISCARD);
#elif defined(XED3D)
	d3ddev->SetStreamSource(0, NULL, 0, 0);
	dynamic_vertex_buffer->Lock(0, 0, &ptr, 0);
#endif
	memcpy(ptr, vertices, num_vertices * sizeof(Vertex));
	dynamic_vertex_buffer->Unlock();

#if defined(XED3D)
	d3ddev->SetStreamSource(0, dynamic_vertex_buffer, 0, sizeof(Vertex));
#endif
#elif defined(D3D11)
	D3D11_MAPPED_SUBRESOURCE sr;
	d3dcontext->Map(dynamic_vertex_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sr);
	memcpy(sr.pData, vertices, num_vertices * sizeof(Vertex));
	d3dcontext->Unmap(dynamic_vertex_buffer, 0);
#else
	#error
#endif

	vbo_was_dirty_flag = TRUE;
}

void Emulator_DrawTriangles(int start_vertex, int triangles)
{
#if defined(OGL) || defined(OGLES)
	glDrawArrays(GL_TRIANGLES, start_vertex, triangles * 3);
#elif defined(D3D9) || defined(XED3D)
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, start_vertex, triangles);
#elif defined(D3D11)
	d3dcontext->Draw(triangles * 3, start_vertex);
#else
	#error
#endif
}

#if defined(D3D11)
void Emulator_CreateConstantBuffers()
{
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(D3D11_BUFFER_DESC));
	cbd.Usage = D3D11_USAGE_DEFAULT;
	cbd.ByteWidth = sizeof(float) * 16;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = 0;
	cbd.MiscFlags = 0;
	HRESULT hr = d3ddev->CreateBuffer(&cbd, NULL, &projectionMatrixBuffer);
	assert(SUCCEEDED(hr));
}

void Emulator_UpdateProjectionConstantBuffer(float* ortho)
{
	d3dcontext->UpdateSubresource(projectionMatrixBuffer, 0, NULL, ortho, 0, 0);
}

void Emulator_SetConstantBuffers()
{
	d3dcontext->VSSetConstantBuffers(0, 1, &projectionMatrixBuffer);
}

void Emulator_DestroyConstantBuffers()
{
	projectionMatrixBuffer->Release();
}

#endif