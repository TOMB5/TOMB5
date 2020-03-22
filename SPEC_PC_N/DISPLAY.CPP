#include "DISPLAY.H"
#include "GLOBAL.H"
#include "CAMERA.H"
#include "DIRECTX.H"
#include "DRAWPRIMITIVE.H"
#include "FILE.H"
#include "TEXT.H"

#define MINZRANGE 0.005
#define MAXZRANGE 0.995

bool in_loading_screen;

void SetZNearFar(int znear, int zfar)
{
	phd_znear = znear;
	phd_zfar = zfar;
	/*f_zfar3 = (double)zfar;
	f_znear3 = (double)znear;
	flt_55D238 = flt_55D268 / f_znear3;*/
	f_znear = znear >> W2V_SHIFT;
	f_zfar = zfar >> W2V_SHIFT;
	f_perspoznear = f_persp / f_znear;
	f_oneoznear = one / f_znear;
	f_b = f_zfar * f_znear * MAXZRANGE / (f_znear - f_zfar);
	f_a = MINZRANGE - f_b / f_znear;
	f_b = -f_b;
	f_boo = f_b / one;
}

void InitWindow(int x, int y, int width, int height, int nearz, int farz, int view_angle)
{
	phd_winwidth = width;
	phd_winheight = height;

	phd_winxmin = x;
	phd_winxmax = width - 1;
	
	phd_winymin = y;
	phd_winymax = height - 1;
	
	phd_centerx = width / 2;
	phd_centery = height / 2;

	f_centerx = width / 2;
	f_centery = height / 2;

	phd_znear = nearz << W2V_SHIFT;	
	phd_zfar = farz << W2V_SHIFT;
	
	AlterFOV(ANGLE(view_angle));
	SetZNearFar(phd_znear, phd_zfar);

	phd_left = x;
	phd_top = y;

	phd_right = phd_winxmax;
	phd_bottom = phd_winymax;

	clip_xmin = phd_winxmin;
	clip_xmax = phd_winxmax + 1;

	clip_ymin = phd_winymin;
	clip_ymax = phd_winymax + 1;


	phd_mxptr = matrix_stack;

	/* flt_51D14C = clip_xmax - clip_xmin;
  unk_55DA40 = clip_ymax - clip_ymin;*/
}


int GetStringLength(const char* string, int a2, int* a3)
{
	UNIMPLEMENTED();
	return 0;
}

void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, const char* string, unsigned short flag)
{
	Log(LT_Enter, "PrintString - X:%d Y:%d Col:%d Flags:%04x - %s\n", x, y, colourFlag, flag, string);
	
	if (flag & FF_BLINK && GnFrameCounter & 16)
		return;

	ScaleFlag = (flag >> 12) & 1;

	int v17;
	int width = GetStringLength(string, 0, &v17);

	if (false)
	{
		char* b2 = (char*)malloc(strlen(string) + 1);
		strcpy(b2, string);
		if (b2[strlen(b2) - 1] != '\n')
			strcat(b2, "\n");
		HDC hdc;
		App.lpBackBuffer->GetDC(&hdc);
		SetTextColor(hdc, TRANSPARENT);
		SetBkColor(hdc, 0xffffff);
		int last = 0;
		int num = 0;
		for (int i = 0; i < strlen(b2); i++)
		{
			if (b2[i] == '\n')
			{
				TextOut(hdc, x, y + num * 16, b2 + last, i - last);
				last = i;
				num++;
			}
		}
		App.lpBackBuffer->ReleaseDC(hdc);
	}
}

void setXY4(D3DTLVERTEX p[4], int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, int z, WORD* a10)// (F) probably, TODO
{
	const int coords[4][2] =
	{
		{x0, y0},
		{x1, y1},
		{x2, y2},
		{x3, y3}
	};

	for (int i = 0; i < 3; i++, p++, a10++)
	{
		int x = coords[i][0];
		int y = coords[i][1];

		p->sx = x;
		p->sy = y;
		p->sz = z;
		p->rhw = f_oneopersp * f_persp / z;

		int v10 = 0;

		if (x >= phd_winxmin)
		{
			if (x > phd_winxmax)
				v10 = 2;
		}
		else
		{
			v10 = 1;
		}

		if (y >= phd_winymin)
		{
			if (y > phd_winymax)
				v10 += 8;
		}
		else
		{
			v10 += 4;
		}

		*a10 = v10;
	}
}

void DrawChar(uint16_t x, uint16_t y, uint16_t a3, font_thing* a4)// (F) probably TODO
{
    D3DTLVERTEX tlvert[4];

    setXY4(
        tlvert,
        phd_winxmin + x,
		phd_winymin + y + a4->a7,

		phd_winxmin + x + a4->a5,
		phd_winymin + y + a4->a7,

		phd_winxmin + x + a4->a5,
		phd_winymin + y + a4->a7 + a4->a6,

        phd_winxmin + x,
		phd_winymin + y + a4->a7 + a4->a6,
		
		f_znear, d9ab34);

	tlvert[0].color = FontShades[a3][a4->a8].color.rgbcd;
	tlvert[1].color = FontShades[a3][a4->a8].color.rgbcd;
    tlvert[2].color = FontShades[a3][a4->a9].color.rgbcd;
    tlvert[3].color = FontShades[a3][a4->a9].color.rgbcd;

	tlvert[0].specular = FontShades[a3][a4->a8].specular.rgbcd;
	tlvert[1].specular = FontShades[a3][a4->a8].specular.rgbcd;
	tlvert[2].specular = FontShades[a3][a4->a9].specular.rgbcd;
	tlvert[3].specular = FontShades[a3][a4->a9].specular.rgbcd;

	OBJECT_TEXTURE tex;
	
    tex.tile_and_flag = num_pages - 2;
    tex.attribute = OT_ALPHA_TESTING;
    tex.new_flags = 0;

	e4b100 = 4;
	
    const double fx = a4->a1 + 1 / 512.0;
    const double fx_right = a4->a1 + 512.0 / (phd_winxmax + 1) * a4->a5 / 256.0 - 1 / 512.0;

    const double fy = a4->a3 + 1 / 512.0;
    const double fy_bottom = a4->a3 + 240.0 / (phd_winymax + 1) * a4->a6 / 256.0 - 1 / 512.0;

    tex.vertices[0].x = fx;
    tex.vertices[1].x = fx_right;
    tex.vertices[2].x = fx_right;
    tex.vertices[3].x = fx;
	
    tex.vertices[0].y = fy;
    tex.vertices[1].y = fy;
    tex.vertices[2].y = fy_bottom;
    tex.vertices[3].y = fy_bottom;
	
    AddQuadClippedSorted(tlvert, 0, 1, 2, 3, &tex, 0);
}