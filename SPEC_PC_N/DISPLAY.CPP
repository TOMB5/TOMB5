#include "DISPLAY.H"
#include "GLOBAL.H"
#include "CAMERA.H"
#include "DIRECTX.H"

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
	phd_winxmax = width - 1;
	phd_winheight = height;
	phd_winxmin = x;
	phd_winymax = height - 1;
	phd_winymin = y;
	phd_centerx = width / 2;
	phd_centery = height / 2;
	phd_znear = nearz << 14;
	f_centerx = (double)(width / 2);
	phd_zfar = farz << 14;
	f_centery = (double)(height / 2);
	AlterFOV(ANGLE(view_angle));
	SetZNearFar(phd_znear, phd_zfar);
	//flt_55D250 = (double)phd_winxmin;
	phd_right = phd_winxmax;
	phd_bottom = phd_winymax;
	//flt_55D664 = (double)phd_winymin;
	phd_top = y;
	phd_left = x;
	//flt_51D160 = (double)(phd_winxmax + 1);
	phd_mxptr = matrix_stack;
	/*unk_55DA34 = (double)(phd_winymax + 1);
	flt_51D14C = flt_51D160 - flt_55D250;
	unk_55DA40 = unk_55DA34 - flt_55D664;*/
}

void PrintString(long x, long y, int unk1, char* string, int options)
{
	char* buf = (char*)malloc(strlen(string) + 64);
	sprintf(buf, "PrintString - X:%d Y:%d Unk1:%d Flags:%04x - %s\n", x, y, unk1, options, string);
	S_Warn(buf);
	
	char* b2 = (char*)malloc(strlen(string) + 1);
	strcpy(b2, string);
	if (b2[strlen(b2) - 1] != '\n')
		strcat(b2, "\n");
	HDC hdc;
	App.lpBackBuffer->GetDC(&hdc);
	SetTextColor(hdc, 0x00ff7f00);
	SetBkColor(hdc, 0x000000);
	int last = 0;
	int num = 0;
	for(int i = 0; i < strlen(b2); i++)
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

void DrawChar(uint16_t x, uint16_t y, uint16_t a2, CHARDEF* def)
{
	Unimpl();
}