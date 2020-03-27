#include "DISPLAY.H"
#include "GLOBAL.H"
#include "CAMERA.H"
#include "DIRECTX.H"
#include "DRAWPRIMITIVE.H"
#include "FILE.H"
#include "TEXT.H"
#include "TOMB4FX.H"

#define MINZRANGE 0.005
#define MAXZRANGE 0.99

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


int __cdecl GetStringLength(const char* string, int16_t* a2, int16_t* a3)
{
	font_thing* chardef; // ecx

	int width = 0;
	
	bool v11 = false;
	signed int max_y = -1024;
	signed int min_y = 1024;
	
	for (const char* p = string; *p; p++)
	{
		unsigned int v3 = *p;
		
		if (v3 == '\n')
			break;
		
		if (v3 == ' ')
		{
			width += (phd_winxmax + 1) / 640.0 * 8.0;
		}
		else if (v3 == 9)
		{
			width += 40;
			if (a2 && min_y > -12)
				min_y = -12;
			if (a3 && max_y < 2)
				max_y = 2;
		}
		else if (v3 >= 20)
		{
			if (v3 >= 32)
			{
				if (v3 >= 128 && v3 <= 173)
				{
					v3 = AccentTable[v3 - 128][0];
					v11 = true;
				}
				chardef = &stru_507AB8[v3 - 33];
			}
			else
			{
				chardef = &stru_507AB8[v3 + 74];
			}
			
			if (ScaleFlag)
				width += chardef->a5 - chardef->a5 / 4;
			else
				width += chardef->a5;
			
			if (a2 && chardef->a7 < min_y)
				min_y = chardef->a7;
			
			if (a3)
			{
				const int v9 = chardef->a6 + chardef->a7;
				if (v9 > max_y)
					max_y = v9;
			}
		}
	}
	
	if (a2)
	{
		if (v11)
			min_y -= 4;
		
		*a2 = min_y;
	}
	
	if (a3)
		*a3 = max_y;
	
	return width;
}

void PrintString(unsigned short x, unsigned short y, unsigned char colourFlag, const char* string, unsigned short flag)
{
	Log(LT_Enter, "PrintString - X:%d Y:%d Col:%d Flags:%04x - %s\n", x, y, colourFlag, flag, string);
	
	if (flag & FF_BLINK && GnFrameCounter & 16)
		return;

	ScaleFlag = (flag >> 12) & 1;

	short max_y;
	int strwidth = GetStringLength(string, nullptr, &max_y);

	int new_x = x;
	
	if (flag & FF_CENTER)
	{
		new_x = x;
		strwidth = strwidth >> 1;
		new_x -= strwidth;
	}
	else if (flag & FF_R_JUSTIFY)
	{
		new_x -= strwidth;
	}
	const char* p = string;
	if (*p)
	{
		unsigned char c = *p;
		p++;
		while (c != '\n')
		{
			if (c == ' ')
			{
				if (ScaleFlag)
				{
					new_x += 6;
				}
				else
				{
					new_x += (phd_winxmax + 1) / 640.0 * 8.0;
				}
			}
			else if (c == '\t')
			{
				new_x += 40;
			}
			else if (c >= 20)
			{
				const font_thing* charac;

				if (c >= 128 && c <= 173)
				{
					const char* tab = AccentTable[c - 128];

					charac = &stru_507AB8[tab[0] - 33];

					DrawChar(new_x, y, colourFlag, charac);

					if (tab[1] != ' ')
						DrawChar(charac->a5 / 2 + new_x - 3, y + charac->a7, colourFlag, &stru_507AB8[tab[1] - 33]);
				}
				else
				{
					if (c >= 32)
					{
						DrawChar(new_x, y, colourFlag, charac = &stru_507AB8[c - 33]);
					}
					else
					{
						DrawChar(new_x, y, colourFlag, charac = &stru_507AB8[c + 74]);
					}
				}
				new_x += charac->a5;

				if (ScaleFlag)
				{
					new_x -= charac->a5 / 4;
				}
			}
			else
			{
				colourFlag = c - 1; // ?
			}

			LBL_37:
			c = (unsigned char)*p++;

			if (!c)
				goto END;
		}

		if (*p == '\n')
		{
			max_y = 0;
			//y += 16;
			y += font_height;
			goto LBL_37;
		}

		short min_y, max_y_2;
		int len = GetStringLength(p, &min_y, &max_y_2);
		new_x = x;
		if (flag & FF_CENTER)
		{
			len /= 2;
		}
		else
		{
			if (!(flag & FF_R_JUSTIFY))
			{
				LBL_17:
				y += max_y - min_y + 2;
				max_y = max_y_2;
				goto LBL_37;
			}
		}
		new_x -= len;
		goto LBL_17;
	}

	END:
	ScaleFlag = false;

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
		UINT align = TA_BASELINE;
		if (flag & FF_CENTER)
			align |= TA_CENTER;
		SetTextAlign(hdc, align);
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

	for (int i = 0; i < 4; i++, p++, a10++)
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
		*a10 = 0;// TODO??
	}
}

void DrawChar(uint16_t x, uint16_t y, uint16_t a3, const font_thing* a4)// (F) probably TODO
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

	const double margin = 1 / 512.0;
	
    const double fx = a4->a1 + margin;
    const double fx_right = a4->a1 + 512.0 / (phd_winxmax + 1) * a4->a5 / 256.0 - margin;

    const double fy = a4->a3 + margin;
    const double fy_bottom = a4->a3 + 240.0 / (phd_winymax + 1) * a4->a6 / 256.0 - margin;

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