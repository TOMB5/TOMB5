#define _X86_
#define _USE_32BIT_TIME_T

#include <cstddef>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <debugapi.h>
#include "FILE.H"
#include "INCLUDE.H"
#include "SPECTYPES.H"
#include "SOUND.H"
#include "DS.H"
#include "GLOBAL.H"
#include "DIRECTX.H"
#include "PCTIME.H"
#include "DRAWPRIMITIVE.H"
#include "DEBUG.H"
#include "GAME.H"
#include "HWINSERT.H"
#include "TEXT.H"
#include "DISPLAY.H"
#include "GAMEFLOW.H"
#include "LARA.H"
#include "INPUT.H"
#include "TOMB4FX.H"
#include "WINMAIN.H"
#include "CAMERA.H"
#include "SPOTCAM.H"
#include "HEALTH.H"
#include "DELTAPAK.H"
#include "NEWINV2.H"
#include <ctime>
#include <zlib.h>
#include "CONTROL.H"
#include "EFFECTS.H"

#if DEBUG
#pragma comment(lib, "zlibstaticd.lib")
#else
#pragma comment(lib, "zlibstatic.lib")
#endif

bool loadBarShown;
int loadBarMax;
float loadBarPercent;
float loadBar2;


void DebugPrint(const char* message)// (F)
{
	static int logCount = 0;
	char buf[1024];
	time_t t = time(nullptr);
	tm tm = *localtime(&t);

	sprintf(buf, "[%02d:%02d:%02d] [%6d] ", tm.tm_hour, tm.tm_min, tm.tm_sec, logCount++);

	strcat(buf, message);

	int len = strlen(buf);

	if (buf[len - 1] != '\n')
	{
		buf[len] = '\n';
		buf[len + 1] = 0;
	}

	OutputDebugString(buf);
	printf(buf);
	fprintf(fplog, buf);
	fflush(fplog);
}


int GetCollisionInfo(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight)//7B210, 7D254
{
	UNIMPLEMENTED();
	return 0;
}


#ifdef __cplusplus
//extern "C" {
#endif

	

void S_Warn(const char* warning_message, ...)// (F)
{
	char buf[1024];
	time_t t = time(nullptr);
	tm tm = *localtime(&t);

	sprintf(buf, "[%02d:%02d:%02d] ", tm.tm_hour, tm.tm_min, tm.tm_sec);

	va_list argptr;
	va_start(argptr, warning_message);
	vsprintf(buf, warning_message, argptr);
	va_end(argptr);

	Log_backend(LT_Info, buf);

	DebugPrint(buf);
}

void S_CDPlay(sint16 track, int mode)
{
	Log(LT_Enter, "S_CDPlay: track=%d; mode=%d", track, mode);

	if (ACMInited)
	{
		dword_57A018 = 0;
		IsAtmospherePlaying = track == CurrentAtmosphere;
		S_CDStop();
		ACMEmulateCDPlay(track, mode);
	}
}

void S_CDStop(void)
{
	if (ACMInited && acm_file_stream)
	{
		memset(wave_file_buf, 0, 225280);
		ACMSoundBuffer->Stop();
		ACMSoundBuffer->SetCurrentPosition(0);
		while (byte_57A01C)
			;
		fclose(acm_file_stream);
		acm_file_stream = 0;
		dword_57A018 = 0;
		dword_510B18 = 7;
		XATrack = -1;
	}
}

void S_SoundStopSample(sint32 handle)// (F)
{
	if (!sound_active)
		return;

	DS_StopSample(handle);
}

void S_SoundStopAllSamples(void)// (F)
{
	if (!sound_active)
		return;

	DS_StopAllSamples();
}

int WeirdWaitThingy()// (F)
{
	Sleep1ms();
	return Sync();
}

void		S_DumpScreenFrame()// (F)
{
	int last = Sync();
	if (last < 1)
	{
		int rev = 1 - last;
		do
		{
			if (Sync() == 0)
				while (WeirdWaitThingy() == 0);
			rev--;
		} while (rev != 0);
	}
	GnFrameCounter++;

	EndScene();
	DXShowFrame();
	App.sceneDone = true;
}

long		S_DumpScreen()
{
	// todo
	int last = Sync();
	int off = last;
	if (last < 2)
	{
		int rev = 2 - last;
		off = 2;
		do
		{
			while (!Sync());
			rev--;
		} while (rev);
	}
	GnFrameCounter++;

	if (!keymap[DIK_D])
		DrawDebugPost();
	
	ShowDebugInfo();

	EndScene();
	DXShowFrame();
	App.sceneDone = true;

	return off;
}

void CalcColorSplit(uint32_t clr, uint32_t* out1, uint32_t* out2)// (F)
{
	uint8_t red1, green1, blue1;
	uint8_t red2 = 0, green2 = 0, blue2 = 0;

	if (RGBA_GETRED(clr) <= 128)
	{
		red1 = 2 * RGBA_GETRED(clr);
	}
	else
	{
		red1 = 255;
		red2 = (RGBA_GETRED(clr) - 128) / 2;
	}

	if (RGBA_GETGREEN(clr) <= 128)
	{
		green1 = 2 * RGBA_GETGREEN(clr);
	}
	else
	{
		green1 = 255;
		green2 = (RGBA_GETGREEN(clr) - 128) / 2;
	}

	if (RGBA_GETBLUE(clr) <= 128)
	{
		blue1 = 2 * RGBA_GETBLUE(clr);
	}
	else
	{
		blue1 = 255;
		blue2 = (RGBA_GETBLUE(clr) - 128) / 2;
	}

	red1 = CLAMP(red1, 0, 255);
	green1 = CLAMP(green1, 0, 255);
	blue1 = CLAMP(blue1, 0, 255);

	red2 = CLAMP(red2, 0, 255);
	green2 = CLAMP(green2, 0, 255);
	blue2 = CLAMP(blue2, 0, 255);

	*out1 = RGBONLY(red1, green1, blue1);
	*out2 = RGBONLY(red2, green2, blue2);
}

void UpdateLoadBar()// (F)
{
	loadBarPercent += 100.0 / loadBarMax;
}
void S_LoadBar()// (F)
{
	UpdateLoadBar();
}
void S_InitLoadBar(int size)// (F)
{
	loadBarPercent = 0.0;
	loadBarMax = size;
	loadBar2 = 0.0;
	loadBarShown = true;
}

void DoBar(int x, int y, int w, int h, float pc, D3DCOLOR color1, D3DCOLOR color2)// (F)
{
	D3DTLVERTEX tlvert[4];

	d9ab34[0] = 0;
	d9ab34[1] = 0;
	d9ab34[2] = 0;
	d9ab34[3] = 0;

	e4b100 = 4;

	OBJECT_TEXTURE tex;

	tex.attribute = OT_ALL_OPAQUE;
	tex.tile_and_flag = 0;

	float xfactor = phd_winxmax / 640.0;
	float yfactor = phd_winymax / 480.0;

	float real_x = x * xfactor;
	float real_y = y * yfactor;
	float real_w = w * xfactor;
	float real_h = h * yfactor;

	float real_y_middle = real_y + real_h / 2.0;
	float real_y_bottom = real_y + real_h;
	float real_x_right = real_x + real_w;

	float sznorm = pc / 100.0;
	float w_filled = real_w * sznorm;
	float real_x_right_fill = w_filled + real_x;

	float rhw = f_persp / f_znear * f_oneopersp;
	float rhw_2 = f_persp / (f_znear + 1.0) * f_oneopersp;

	BYTE red1 = RGBA_GETRED(color1);
	BYTE green1 = RGBA_GETGREEN(color1);
	BYTE blue1 = RGBA_GETBLUE(color1);

	int real_red1 = red1, real_green1 = green1, real_blue1 = blue1;
	D3DCOLOR real_color1 = RGBONLY(real_red1, real_green1, real_blue1);
	D3DCOLOR real_color1d = RGBONLY(real_red1 & ~1, real_green1 & ~1, real_blue1 & ~1);

	BYTE red2 = RGBA_GETRED(color2);
	BYTE green2 = RGBA_GETGREEN(color2);
	BYTE blue2 = RGBA_GETBLUE(color2);

	int real_red2 = SCALE_CLR(red1, red2, sznorm);
	int real_green2 = SCALE_CLR(green1, green2, sznorm);
	int real_blue2 = SCALE_CLR(blue1, blue2, sznorm);
	D3DCOLOR real_color2 = RGBONLY(real_red2, real_green2, real_blue2);
	D3DCOLOR real_color2d = RGBONLY(real_red2 & ~1, real_green2 & ~1, real_blue2 & ~1);

	tlvert[0].sx = real_x;
	tlvert[1].sx = real_x_right_fill;
	tlvert[2].sx = real_x;
	tlvert[3].sx = real_x_right_fill;

	tlvert[0].sy = real_y;
	tlvert[1].sy = real_y;
	tlvert[2].sy = real_y_middle;
	tlvert[3].sy = real_y_middle;
	
	tlvert[0].sz = f_znear; // todo, in the original they wrote that to sx which is wrong i guess
	tlvert[1].sz = f_znear;
	tlvert[2].sz = f_znear;
	tlvert[3].sz = f_znear;

	tlvert[0].specular = RGB_MAKE(0, 0, 0);
	tlvert[1].specular = RGB_MAKE(0, 0, 0);
	tlvert[2].specular = RGB_MAKE(0, 0, 0);
	tlvert[3].specular = RGB_MAKE(0, 0, 0);

	tlvert[0].rhw = rhw;	
	tlvert[1].rhw = rhw;
	tlvert[2].rhw = rhw;	
	tlvert[3].rhw = rhw;

	tlvert[0].color = real_color1d;
	tlvert[1].color = real_color2d;
	tlvert[2].color = real_color1;
	tlvert[3].color = real_color2;	

	AddQuad2(tlvert, 0, 1, 3, 2, &tex, 1);

	tlvert[0].sy = real_y_middle;
	tlvert[1].sy = real_y_middle;
	tlvert[2].sy = real_y_bottom;
	tlvert[3].sy = real_y_bottom;

	tlvert[0].color = real_color1;	
	tlvert[1].color = real_color2;
	tlvert[2].color = real_color1d;
	tlvert[3].color = real_color2d;

	AddQuad2(tlvert, 0, 1, 3, 2, &tex, 1);

	tlvert[0].sx = real_x; 
	tlvert[1].sx = real_x_right;
	tlvert[2].sx = real_x;
	tlvert[3].sx = real_x_right;

	tlvert[0].sy = real_y;
	tlvert[1].sy = real_y;
	tlvert[2].sy = real_y_bottom;
	tlvert[3].sy = real_y_bottom;

	tlvert[0].sz = f_znear + 1.0;
	tlvert[1].sz = f_znear + 1.0;
	tlvert[2].sz = f_znear + 1.0;
	tlvert[3].sz = f_znear + 1.0;

	tlvert[0].rhw = rhw_2;
	tlvert[1].rhw = rhw_2;
	tlvert[2].rhw = rhw_2;
	tlvert[3].rhw = rhw_2;

	tlvert[0].color = RGBA_MAKE(0, 0, 0, 0);
	tlvert[1].color = RGBA_MAKE(0, 0, 0, 0);
	tlvert[2].color = RGBA_MAKE(0, 0, 0, 0);
	tlvert[3].color = RGBA_MAKE(0, 0, 0, 0);

	AddQuad2(tlvert, 0, 1, 3, 2, &tex, 1);

	tlvert[0].sx = real_x - 1.0;	
	tlvert[1].sx = real_x_right + 1.0;
	tlvert[2].sx = real_x - 1.0;
	tlvert[3].sx = real_x_right + 1.0;
	
	tlvert[0].sy = real_y - 1.0;
	tlvert[1].sy = real_y - 1.0;
	tlvert[2].sy = real_y_bottom + 1.0;
	tlvert[3].sy = real_y_bottom + 1.0;
	
	tlvert[0].sz = f_znear + 2.0;
	tlvert[1].sz = f_znear + 2.0;
	tlvert[2].sz = f_znear + 2.0;
	tlvert[3].sz = f_znear + 2.0;

	tlvert[0].rhw = f_persp / (f_znear + 2.0) * f_oneopersp;
	tlvert[1].rhw = f_persp / (f_znear + 2.0) * f_oneopersp;
	tlvert[2].rhw = f_persp / (f_znear + 2.0) * f_oneopersp;
	tlvert[3].rhw = f_persp / (f_znear + 2.0) * f_oneopersp;

	tlvert[0].color = RGB_MAKE(255, 255, 255);
	tlvert[1].color = RGB_MAKE(255, 255, 255);
	tlvert[2].color = RGB_MAKE(255, 255, 255);
	tlvert[3].color = RGB_MAKE(255, 255, 255);

	AddQuad2(tlvert, 0, 1, 3, 2, &tex, 1);
}

void SuperShowLogo()// (F)
{
	D3DTLVERTEX tlvert[4];

	d9ab34[0] = 0;
	d9ab34[1] = 0;
	d9ab34[2] = 0;
	d9ab34[3] = 0;

	e4b100 = 4;

	tlvert[0].rhw = f_oneoznear;
	tlvert[1].rhw = f_oneoznear;
	tlvert[2].rhw = f_oneoznear;
	tlvert[3].rhw = f_oneoznear;

	float x = 64.0;
	float y = 0.0;
	float width = 256.0;
	float height = 256.0;

	float xfactor = phd_winxmax / 640.0;
	float yfactor = phd_winymax / 480.0;

	float real_width = width * xfactor;
	float real_height = height * yfactor;

	float real_x = phd_winxmin + x * xfactor;
	float real_x_right = real_x + real_width;

	float real_y = phd_winymin + y * yfactor;
	float real_y_bottom = real_y + real_height;

	tlvert[0].sx = real_x;
	tlvert[1].sx = real_x_right;
	tlvert[2].sx = real_x_right;
	tlvert[3].sx = real_x;

	tlvert[0].sy = real_y;
	tlvert[1].sy = real_y;
	tlvert[2].sy = real_y_bottom;
	tlvert[3].sy = real_y_bottom;

	tlvert[0].sz = 0.0;
	tlvert[1].sz = 0.0;
	tlvert[2].sz = 0.0;
	tlvert[3].sz = 0.0;

	tlvert[0].specular = RGB_MAKE(0, 0, 0);
	tlvert[1].specular = RGB_MAKE(0, 0, 0);
	tlvert[2].specular = RGB_MAKE(0, 0, 0);
	tlvert[3].specular = RGB_MAKE(0, 0, 0);

	tlvert[0].rhw = f_oneoznear;
	tlvert[1].rhw = f_oneoznear;
	tlvert[2].rhw = f_oneoznear;
	tlvert[3].rhw = f_oneoznear;

	tlvert[0].color = RGB_MAKE(255, 255, 255);
	tlvert[1].color = RGB_MAKE(255, 255, 255);
	tlvert[2].color = RGB_MAKE(255, 255, 255);
	tlvert[3].color = RGB_MAKE(255, 255, 255);

	OBJECT_TEXTURE tex;

	tex.attribute = OT_ALPHA_TESTING;
	tex.new_flags = 0;
	tex.tile_and_flag = num_pages - 5;

	tex.vertices[0].x = 1 / 256.0;
	tex.vertices[0].y = 1 / 256.0;

	tex.vertices[1].x = 1 - 1 / 256.0;
	tex.vertices[1].y = 1 / 256.0;

	tex.vertices[2].x = 1 - 1 / 256.0;
	tex.vertices[2].y = 1 - 1 / 256.0;

	tex.vertices[3].x = 1 / 256.0;
	tex.vertices[3].y = 1 - 1 / 256.0;

	AddQuad2(tlvert, 0, 1, 2, 3, &tex, 0);

	tlvert[0].sx = real_x_right;
	tlvert[1].sx = real_x_right + real_width;
	tlvert[2].sx = real_x_right + real_width;
	tlvert[3].sx = real_x_right;

	tlvert[0].sy = real_y;
	tlvert[1].sy = real_y;
	tlvert[2].sy = real_y_bottom;
	tlvert[3].sy = real_y_bottom;

	tlvert[0].sz = 0.0;
	tlvert[1].sz = 0.0;
	tlvert[2].sz = 0.0;
	tlvert[3].sz = 0.0;

	tlvert[0].specular = RGB_MAKE(0, 0, 0);
	tlvert[1].specular = RGB_MAKE(0, 0, 0);
	tlvert[2].specular = RGB_MAKE(0, 0, 0);
	tlvert[3].specular = RGB_MAKE(0, 0, 0);

	tlvert[0].rhw = f_oneoznear;
	tlvert[1].rhw = f_oneoznear;
	tlvert[2].rhw = f_oneoznear;
	tlvert[3].rhw = f_oneoznear;

	tlvert[0].color = RGB_MAKE(255, 255, 255);
	tlvert[1].color = RGB_MAKE(255, 255, 255);
	tlvert[2].color = RGB_MAKE(255, 255, 255);
	tlvert[3].color = RGB_MAKE(255, 255, 255);

	tex.attribute = OT_ALPHA_TESTING;
	tex.new_flags = 0;
	tex.tile_and_flag = num_pages - 4;

	tex.vertices[0].x = 1 / 256.0;
	tex.vertices[0].y = 1 / 256.0;

	tex.vertices[1].x = 1 - 1 / 256.0;
	tex.vertices[1].y = 1 / 256.0;

	tex.vertices[2].x = 1 - 1 / 256.0;
	tex.vertices[2].y = 1 - 1 / 256.0;

	tex.vertices[3].x = 1 / 256.0;
	tex.vertices[3].y = 1 - 1 / 256.0;

	AddQuad2(tlvert, 0, 1, 2, 3, &tex, 1);
}

bool S_DrawLoadBar()
{
	BeginScene();
	InitBuckets();
	InitialiseSortList();

	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);
	
	DoBar(170, 480 - font_height, 300, 10, loadBar2, RGB_MAKE(0, 0, 16), RGB_MAKE(0, 0, 240));

	SortPolyList(surfacenumbf, sort3d_bufferbf);
	//RestoreFPCW();
	DrawSortList();
	//MungeFPCW(..
	S_DumpScreenFrame();

	if (loadBar2 >= loadBarPercent)
	{
		if (loadBarMax > loadBarPercent)
			return false;

		return true;
	}

	loadBar2 += 2.0;

	return false;
}

bool Decompress(void* buf, void* compressed, int compSize, int uncompSize)// (F)
{
	Log(LT_Enter, "Decompress");

	z_stream strm;
	Zero(strm);
	strm.avail_in = compSize;
	strm.avail_out = uncompSize;
	strm.next_out = (BYTE *)buf;
	strm.next_in = (BYTE *)compressed;

	inflateInit(&strm);
	inflate(&strm, Z_FINISH);

	if (strm.total_out == uncompSize)
	{
		inflateEnd(&strm);

		Log(LT_Info, "Decompression OK");
		return true;
	}
	else
	{
		Log(LT_Error, "Error Decompressing Data");
		return false;
	}
}

unsigned short nAnimUVRanges; // offset 0xA4660

void SetFogColor(uint8_t r, uint8_t g, uint8_t b)// (F)
{
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_FOGCOLOR, GENRGB(r, g, b));
}

void ClearFXFogBulbs()// (F)
{
	
}

DWORD dword_C87BF0;
DWORD dword_C86BE8;
DWORD dword_C713D4;
DWORD dword_C713DC;
DWORD dword_C713E0;

void SetFade(int a1, int a2)
{
	dword_C87BF0 = 1;
	dword_C86BE8 = a1;
	dword_C713D4 = (a2 - a1) >> 3;
	dword_C713DC = 0;
	dword_C713E0 = a2;
}

void S_InitialiseScreen()// (F)
{

}

BYTE IsVolumetric()// (F)
{
	return App.tVolumetricShadows;
}

WORD AnimComp = 0;
short AnimatingTexturesVOffset = 0;
short AnimatingTexturesV[16][8][3];

void S_AnimateTextures(long nFrames)// to test
{
	AnimComp += nFrames;

	while (AnimComp > 5)
	{
		uint16_t* ptr = AnimTextureRanges;

		for (uint16_t i = *(ptr++); i > 0; i--, ptr++)
		{
			OBJECT_TEXTURE tmp = object_textures[*(ptr + 1)];

			for (uint16_t j = *ptr++; j > 0; j--, ptr++)
			{
				object_textures[*ptr] = object_textures[*(ptr + 1)];
			}

			object_textures[*ptr] = tmp;
		}

		AnimComp -= 5;
	}

	if (gfUVRotate) // 19d8
	{
		uint16_t* t3 = AnimTextureRanges;
		AnimatingTexturesVOffset = (AnimatingTexturesVOffset - gfUVRotate * (nFrames / 2)) & 0x1f;
		if (nAnimUVRanges > 0)
		{
			short(*t2)[8][3] = AnimatingTexturesV;

			for (int i = 0; i < nAnimUVRanges; i++, t2++)
			{
				unsigned short num = *t3++;
				if (num > 0)
				{
					short* t1 = t2[i][num];

					for (int j = 0; j <= num; j++, t1 -= 3, t3++)
					{

						OBJECT_TEXTURE* v18 = &object_textures[*t3];
						double v19 = AnimatingTexturesVOffset / 256.0;
						v18->vertices[0].y = v19 + t1[3];
						v18->vertices[1].y = v19 + t1[3];
						v18->vertices[2].y = v19 + t1[3] + 0.125;
						v18->vertices[3].y = v19 + t1[3] + 0.125;
					}
				}
			}
		}
	}
}

void DrawPsxTile(long a1, long a2, long a3)
{
	Log(LT_Enter, "DrawPsxTile %6d %6d %6d", a1, a2, a3);
	
	e4b100 = 6;
	
	uint16 blend; // si
	unsigned int color; // eax
	
	if ((a3 & 0xFF000000) == 0x62000000)
	{
		blend = OT_ALPHA_BLENDING_INV;
		color = a3 << 24;
	}
	else
	{
		blend = OT_ALPHA_BLENDING;
		color = a3 | 0xFF000000;
	}
	float rhw = f_oneoznear;
	double z = f_znear3;

	if (gfCurrentLevel == LVL5_TITLE)
	{
		z += 10.0;
		rhw += 50.0;
	}
	
	double v10 = a2 + 1.0 + (a1 >> 16);
	double v11 = (a2 >> 16) + 1.0 + a1;

	D3DTLVERTEX v[4]; // [esp+1Ch] [ebp-A8h]
	
	v[0].sx = a1 >> 16;
	v[1].sx = v10;
	v[2].sx = v10;
	v[3].sx = a1 >> 16;

	v[0].sy = a1;
	v[1].sy = a1;
	v[2].sy = v11;
	v[3].sy = v11;

	v[0].sz = z;
	v[1].sz = z;
	v[2].sz = z;
	v[3].sz = z;

	v[0].specular = ARGB(255, 0, 0, 0);;
	v[1].specular = ARGB(255, 0, 0, 0);
	v[2].specular = ARGB(255, 0, 0, 0);
	v[3].specular = ARGB(255, 0, 0, 0);
	
	v[0].rhw = rhw;
	v[1].rhw = rhw;
	v[2].rhw = rhw;
	v[3].rhw = rhw;
	
	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	OBJECT_TEXTURE tex; // [esp+9Ch] [ebp-28h]
	
	tex.attribute = blend;
	tex.new_flags = 0;
	
	tex.tile_and_flag = 0;

	d9ab34[0] = 0;
	d9ab34[1] = 0;
	d9ab34[2] = 0;
	d9ab34[3] = 0;

	AddQuad2(v, 0, 1, 2, 3, &tex, 0);
}

void DoScreenFade()
{
	dword_C86BE8 += dword_C713D4;
	if (dword_C713DC >= 8)
		dword_C87BF0 = 2;

	d9ab34[0] = 0;
	d9ab34[1] = 0;
	d9ab34[2] = 0;
	d9ab34[3] = 0;
}

void S_OutputPolyList()
{
	Log(LT_Info, "S_OutputPolyList - RENDER START");

	//RestoreFPCW();
	WinFrameRate();

	d9ab1c = 0;
	d9ab10 = 0;

	App.DrawPrimitiveCntBuk = 0;
	App.DrawPrimitiveCnt = 0;

	// todo (log)

	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_INVSRCALPHA);
	App.lpD3DDevice->SetRenderState(D3DRENDERSTATE_ALPHABLENDENABLE, FALSE);

	if (App.ResChangeTimer)
	{
		WinDisplayString(8, App.height - 8, "%dx%d", App.width, App.height);

		App.ResChangeTimer -= 30.0 / App.fps;

		if (App.ResChangeTimer < 0)
			App.ResChangeTimer = 0;
	}

	if (App.lpZBuffer != nullptr)
		DrawBuckets();

	if (gfCurrentLevel == LVL5_TITLE)
	{
		Fade();

		if (App.lpZBuffer != nullptr)
			DrawSortList();
	}

	SortPolyList(surfacenumbf, sort3d_bufferbf);
	DrawSortList();

	if (App.lpZBuffer != nullptr)
	{
		D3DRECT r;
		r.x1 = App.GnClientRect.left;
		r.y1 = App.GnClientRect.top;
		r.x2 = App.GnClientRect.left + App.GnClientRect.right;
		r.y2 = App.GnClientRect.top + App.GnClientRect.bottom;
		DX_TRY(App.lpViewPort->Clear2(1, &r, D3DCLEAR_ZBUFFER, RGBA_MAKE(0, 0, 0, 0), 1.0f, 0));
	}

	if ((BinocularRange || SCOverlay || SniperOverlay) && !in_loading_screen)
	{
		InitialiseSortList();
		DrawBinoculars();
		DrawSortList();
	}

	if (pickups[CurrentPickup].life != -1 && !in_loading_screen && !GLOBAL_playing_cutseq)
	{
		dword_7EE0D4 = 0;
		InitialiseSortList();
		S_DrawPickup(pickups[CurrentPickup].object_number);
		SortPolyList(surfacenumbf, sort3d_bufferbf);
		DrawSortList();
	}

	InitialiseSortList();

	if (FadeScreenHeight != 0)
	{
		int height = phd_winymax / 256.0 * FadeScreenHeight;
		DrawPsxTile(0, phd_winwidth | (height << 16), RGBA(255, 255, 255, 0x62));
		DrawPsxTile(phd_winheight - height, phd_winwidth | (height << 16), RGBA(255, 255, 255, 0x62));
	}

	if (gfCurrentLevel != LVL5_TITLE)
	{
		Fade();

		if (FlashFader != 0)
		{
			DrawFlash();

			if (FlashFader != 0)
				FlashFader -= 2;
		}

		DrawSortList();
	}

	if (dword_C87BF0 == 1)
	{
		InitialiseSortList();
		DoScreenFade();
		DrawSortList();
	}

	if (++dword_921684 == 2)
	{
		if (keymap[DIK_B])                         
			App.tBumpMap = App.tBumpMap != 1;
		dword_921684 = 0;
	}

	// MungeFPCW((int)&word_878654);

	Log(LT_Info, "S_OutputPolyList - RENDER END");
}

void S_CalculateStaticMeshLight(int x, int y, int z, int shade, room_info* room)
{
	Unimpl();
}

void S_CalculateLight(long x, long y, long z, short room, ITEM_LIGHT* light)// (F)
{
	
}

void S_CDLoop()// (F)
{
	
}

int S_LoadSave(int input, int in_inventory)
{
	Unimpl();
	return 0;
}

int S_DisplayPauseMenu(int a1)
{
	Unimpl(); 
	return 0;
}

	int S_PauseMenu()
{
	Unimpl();
	return 0;
}

void S_DrawAirBar(int size)// (F)
{
	if (gfCurrentLevel != LVL5_TITLE)
	{
		DoBar(490 - font_height / 4, font_height / 2 + font_height / 4 + 32, 150, 12, size, RGBONLY(0, 0, 160), RGBONLY(0, 80, 160));
	}
}

void S_DrawHealthBar(int size)// (F)
{
	if (gfCurrentLevel != LVL5_TITLE)
	{
		D3DCOLOR col = RGBONLY(0, 160, 0);

		if (lara.poisoned || lara.Gassed)
			col = RGBONLY(160, 160, 0);

		DoBar(font_height / 4, font_height / 4 + 32, 150, 12, size, RGBONLY(160, 0, 0), col);
	}
}

void S_DrawHealthBar2(int size)// (F)
{
	if (gfCurrentLevel != LVL5_TITLE)
	{
		D3DCOLOR col = RGBONLY(0, 160, 0);

		if (lara.poisoned || lara.Gassed)
			col = RGBONLY(160, 160, 0);

		DoBar(245, font_height / 4 + 32, 150, 12, size, RGBONLY(160, 0, 0), col);
	}
}

void S_CDFade(int a1)// (F)
{
	
}

int		S_StartSyncedAudio(int num)
{
		Unimpl();
		return 0;
}

LPDIRECTDRAWSURFACE4 CreateTexturePage(int width, int height, int mipmaps, int *buf, void(*a5)(uchar *, uchar *, uchar *, uchar *), int bpp)
{
	DDSURFACEDESC2 desc;
	DXInit(desc);

	desc.dwWidth = width;
	desc.dwHeight = height;

	if (width < 32 || height < 32)
		mipmaps = 0;

	desc.ddpfPixelFormat = CUR_TEX.ddpf;
	desc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH | DDSD_PIXELFORMAT;
	desc.ddsCaps.dwCaps = DDSCAPS_TEXTURE;

	if (App.Flags & WA_BACK_BUFFER)
		desc.ddsCaps.dwCaps2 = DDSCAPS2_TEXTUREMANAGE;
	else
		desc.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;

	if (mipmaps)
	{
		desc.dwFlags |= DDSD_MIPMAPCOUNT;
		desc.dwMipMapCount = mipmaps + 1;
		desc.ddsCaps.dwCaps |= DDSCAPS_MIPMAP | DDSCAPS_COMPLEX;
	}

	LPDIRECTDRAWSURFACE4 surf;

	DXCreateSurface(App.lpDD, &desc, &surf);

	DX_TRY(surf->Lock(nullptr, &desc, DDLOCK_NOSYSLOCK, nullptr));

	if (desc.dwHeight != 0 && desc.dwWidth != 0)
	{
		if (bpp == 0)
		{
			auto sptr = (BYTE*)desc.lpSurface;

			for (int y = 0; y < desc.dwHeight; y++)
			{
				for (int x = 0; x < desc.dwWidth; x++)
				{
					auto ptr = (BYTE*)buf;

					auto b = ptr[0];// todo inverted r&b in original
					auto g = ptr[1];
					auto r = ptr[2];
					auto a = ptr[3];

					if (a5)
					{
						a5(&r, &g, &b, &a);
					}

					DWORD color =
						r >> (8 - CUR_TEX.rbpp) << CUR_TEX.rshift |
						g >> (8 - CUR_TEX.gbpp) << CUR_TEX.gshift |
						b >> (8 - CUR_TEX.bbpp) << CUR_TEX.bshift |
						a >> (8 - CUR_TEX.abpp) << CUR_TEX.ashift;

					if (CUR_TEX.bpp > 0)
					{
						for(int i = 0; i < (CUR_TEX.bpp + 7) / 8; i++)
						{
							*sptr++ = color;
							color >>= 8;
						}
					}

					buf += 256 / width;
				}
			}
		}
		else
		{
			if (bpp == 2)
			{
				auto ptr = (WORD*)buf;
				auto sptr = (WORD*)desc.lpSurface;

				for (int y = 0; y < desc.dwHeight; y++)
				{
					auto ptr2 = ptr;

					for (int x = 0; x < desc.dwWidth; x++)
					{
						*sptr++ = *ptr2;
						ptr2 += 256 / width;
					}

					ptr += 256 * 256 / height;
				}
			}
			else if (bpp == 1)
			{
				auto ptr = (DWORD*)buf;
				auto sptr = (DWORD*)desc.lpSurface;

				for (int y = 0; y < desc.dwHeight; y++)
				{
					auto ptr2 = ptr;

					for (int x = 0; x < desc.dwWidth; x++)
					{
						*sptr++ = *ptr2;
						ptr2 += 256 / width;
					}

					ptr += 256 * 256 / height;
				}
			}
		}
	}

	DX_TRY(surf->Unlock(nullptr));

	if (mipmaps)
	{
		Unimpl();
	}

	return surf;
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate)
{
	UNIMPLEMENTED();
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
	UNIMPLEMENTED();
}

enum
{
	MENU_MAIN_MENU,
	MENU_LOAD_MENU,
	MENU_LEVEL_SELECT_MENU,
	MENU_SPECIAL_FEATURES_MENU
};

DWORD selected_menu_prev = 0;
DWORD dword_51CE44 = 0;
DWORD dword_51CE0C = 0;
DWORD unk_51CE3C = 0;
DWORD dword_51CE40 = 0;
DWORD selected_menu = 1;
DWORD qword_5082F4 = 1;
DWORD dword_51CE50 = 0;
DWORD unk_51CE2A = 0;
BYTE byte_5082C8[40] =
{
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

int DoCredits()
{
	UNIMPLEMENTED();
	return 0;
}

void do_dels_cutseq_selector()
{
	UNIMPLEMENTED();
}

void GetSaveLoadFiles()
{
	UNIMPLEMENTED();
}

int GetCampaignCheatValue()
{
	UNIMPLEMENTED();
	return 0;
}

void DoOptions()
{
	UNIMPLEMENTED();
}

void S_LoadGame(int a1)
{
	UNIMPLEMENTED();
}

int DoLoadSave(int a1)
{
	UNIMPLEMENTED();
	return 0;
}

int TitleOptions()
{
	int v5; // ebp
	int v6; // edi
	bool v18; // zf
	int v22; // [esp+Ch] [ebp-14h]
	int i; // [esp+10h] [ebp-10h]
	char v24; // [esp+10h] [ebp-10h]
	signed __int64 max_menu; // [esp+14h] [ebp-Ch]
	int v26; // [esp+14h] [ebp-Ch]

	signed int v1 = 0;
	if (dword_51CE44)
	{
		if (dword_C87BF0 == 2)
		{
			dword_51CE0C = 0;
			dword_51CE44 = 0;
			unk_51CE3C = 0;
			dword_51CE40 = 0;
			gfLevelComplete = dword_51CE0C;
			selected_menu = 1;
			return dword_51CE44;
		}
		input = 0;
		dbinput = 0;
	}
	if (bDoCredits)
	{
		if (DoCredits())
			return 0;
		bDoCredits = 0;
		DestFadeScreenHeight = 0;
	}
	if (unk_51CE2A)
	{
		dword_51CE40 = 0;
		selected_menu = 1;
		do_dels_cutseq_selector();
		return dword_51CE44;
	}
	if (!unk_51CE3C)
	{
		switch (dword_51CE40)
		{
		case 0:
			goto LABEL_37;
		case 1:
			PrintString(
				phd_centerx,
				font_height + phd_winymin,
				6,
				&gfStringWad[gfStringOffset[STR_SELECT_LEVEL]],
				FF_CENTER);
			v5 = font_height + font_height + phd_winymin;
			if (Gameflow->nLevels >= 10)
			{
				DWORD v7 = selected_menu;
				i = 10;
				int v8;
				for (v8 = 0; v7; ++v8)
					v7 >>= 1;
				v6 = v8 - 9;
				if (v8 - 9 >= 1)
				{
					if (v8 - 9 > 1)
					{
						PrintString(32, v5 + font_height, 6, "\x18", 0);
						PrintString(phd_winxmax - 48, v5 + font_height, 6, "\x18", 0);
					}
				}
				else
				{
					v6 = 1;
				}
				if (v8 != Gameflow->nLevels - 1)
				{
					PrintString(32, v5 + 10 * font_height, 6, "\x1A", 0);
					PrintString(phd_winxmax - 48, v5 + 10 * font_height, 6, "\x1A", 0);
				}
			}
			else
			{
				v6 = 1;
				i = Gameflow->nLevels - 1;
			}
			v22 = v6;
			v26 = i + v6;
			if (v6 < i + v6)
			{
				int v9 = v6 - 1;
				while (1)
				{
					v5 += font_height;
					if (selected_menu & (1 << v9))
						v24 = 1;
					else
						v24 = 3 - (byte_5082C8[v22 - 1] != 0);
					PrintString(
						phd_centerx,
						v5,
						v24,
						&gfStringWad[gfStringOffset[gfLevelNames[v9 + 1]]],
						FF_CENTER);
					if (selected_menu & (1 << v9))
						dword_51CE50 = v9;
					++v9;
					if (++v22 >= v26)
						break;
				}
			}
			v1 = 0;
			max_menu = 1i64 << (Gameflow->nLevels - 2);
			break;
		case 2:
			if (Gameflow->LoadSaveEnabled)
			{
				signed int v10 = DoLoadSave(0x800000);
				if (v10 >= 0)
				{
					S_LoadGame(v10);
					v1 = 2;
				}
			}
			else
			{
				SoundEffect(SFX_LARA_NO, nullptr, SFX_ALWAYS);
				dword_51CE40 = 0;
			LABEL_37:
				const int v11 = phd_winymax - 4 * font_height;
				SuperShowLogo();
				Chris_Menu = 0;

				PrintString(
					phd_centerx, 
					v11,
					(selected_menu & 1) ? 1 : 2,
					&gfStringWad[gfStringOffset[STR_SAVE_GAME_BIS]], 
					FF_CENTER);
				
				PrintString(
					phd_centerx,
					v11 + font_height,
					(selected_menu & 2) ? 1 : 2,
					&gfStringWad[gfStringOffset[STR_LOAD_GAME_BIS]],
					FF_CENTER);
				
				PrintString(
					phd_centerx,
					v11 + 2 * font_height,
					(selected_menu & 4) ? 1 : 2,
					&gfStringWad[gfStringOffset[STR_OPTIONS]],
					FF_CENTER);
				
				PrintString(
					phd_centerx,
					v11 + 2 * font_height + font_height,
					(selected_menu & 8) ? 1 : 2,
					&gfStringWad[gfStringOffset[STR_EXIT]],
					FF_CENTER);
				
				max_menu = 8;
			}
			break;
		case 3:
			DoOptions();
			break;
		default:
			break;
		}
		
		if (dword_51CE40 < 2)
		{
			if (dbinput & IN_FORWARD)
			{
				if (selected_menu > 1)
				{
					selected_menu >>= 1;
					qword_5082F4 >>= 1;
				}
				
				SoundEffect(SFX_MENU_CHOOSE, nullptr, SFX_ALWAYS);
			}
			
			if (dbinput & IN_BACK)
			{
				if (selected_menu < max_menu)
				{
					selected_menu <<= 1;
					qword_5082F4 <<= 1;
				}
				
				SoundEffect(SFX_MENU_CHOOSE, nullptr, SFX_ALWAYS);
			}
		}
		
		if (dbinput & IN_DESELECT)
		{
			v18 = dword_51CE40 == 0;
			if (dword_51CE40 <= 0)
				goto LABEL_60;
			dword_51CE40 = 0;
			selected_menu = selected_menu_prev;
			S_SoundStopAllSamples();
			SoundEffect(SFX_MENU_SELECT, nullptr, SFX_ALWAYS);
		}
		v18 = dword_51CE40 == 0;
	LABEL_60:
		if (v18)
		{
			const int v19 = GetCampaignCheatValue();
			if (v19)
			{
				gfLevelComplete = v19;
				v1 = 3;
			}
		}
		if (dbinput & IN_SELECT && !keymap[DIK_LMENU] && dword_51CE40 < 2)
		{
			SoundEffect(SFX_MENU_SELECT, nullptr, SFX_ALWAYS);
			if (dword_51CE40)
			{
				if (dword_51CE40 == 1 && byte_5082C8[dword_51CE50])
				{
					char v20 = 0;
					DWORD v21 = selected_menu;
					gfLevelComplete = 0;
					if (selected_menu)
					{
						do
						{
							v21 >>= 1;
							++v20;
						} while (v21);
						gfLevelComplete = v20;
					}
					v1 = 3;
				}
			}
			else if (selected_menu >= 1 && selected_menu <= 8)
			{
				switch (selected_menu)
				{
				case 1u:
					if (Gameflow->PlayAnyLevel)
					{
						selected_menu_prev = selected_menu;
						dword_51CE40 = 1;
					}
					else
					{
						gfLevelComplete = 1;
						v1 = 3;
					}
					break;
				case 2u:
					GetSaveLoadFiles();
					selected_menu_prev = selected_menu;
					dword_51CE40 = 2;
					break;
				case 3u:
				case 5u:
				case 6u:
				case 7u:
					break;
				case 4u:
					selected_menu_prev = selected_menu;
					dword_51CE40 = 3;
					break;
				case 8u:
					v1 = 4;
					break;
				}
			}
		}
	}
	if (thread_started)
		return 4;
	if (v1)
	{
		dword_51CE44 = v1;
		dword_51CE0C = gfLevelComplete;
		gfLevelComplete = 0;
		v1 = 0;
		SetFade(0, 255);
	}
	return v1;
}


void updateAnimFrame(PACKNODE* node, int flags, short* frame)// (F)
{
	frame[7] = 3 * node->yrot_run;

	short x = 3 * node->xrot_run;
	short z = 3 * node->zrot_run;

	switch (cutrot)
	{
	case 0:
		frame[6] = x;
		frame[8] = z;
		break;
	case 1:
		frame[6] = z;
		frame[8] = -x;
		break;
	case 2:
		frame[6] = -x;
		frame[8] = -z;
		break;
	case 3:
		frame[6] = -z;
		frame[8] = x;
		break;
	}

	short* next = frame + 9;

	for (int i = 1; i < flags; i++, next += 2)
	{
		short x = node[i].yrot_run;
		short y = node[i].zrot_run;
		short z = node[i].xrot_run;

		if (cutrot && i == 1)
		{
			x = (x + ((short)cutrot << 8)) & 0x3FF;
		}

		next[0] = (y | ((x | (z << 10)) << 10)) >> 16;
		next[1] = y | ((x | (z << 10)) << 10);
	}
}

void S_SetReverbType(short reverb)
{

}

void PlayFMV(int num)
{
	Unimpl();
}

void PlayFmvNow(int num)
{
	switch (num)
	{
	case 0:
		PlayFMV(0);
		break;
	case 1:
		PlayFMV(1);
		break;
	case 2:
		PlayFMV(2);
		break;
	case 3:
		PlayFMV(3);
		PlayFMV(4);
		break;
	case 4:
		PlayFMV(5);
		PlayFMV(6);
		break;
	case 5:
		PlayFMV(7);
		break;
	case 6:
		PlayFMV(8);
		break;
	}
}

void WadeSplash(struct ITEM_INFO* item, int water_height, int water_depth)
{
	UNIMPLEMENTED();
}

#ifdef __cplusplus
//}
#endif