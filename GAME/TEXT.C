#include "TEXT.H"

#if PC_VERSION
#include "GLOBAL.H"
#include "INCLUDE.H"
#elif PSX_VERSION || PSXPC_VERSION || PSXPC_TEST
//#include <SYS/TYPES.H>
#include <LIBGTE.H>
#endif

#include "STYPES.H"
#include "SPECIFIC.H"


char AccentTable[46][2] =
{
	{'{', ' '},
	{'u', '^'},
	{'e', '\\'},
	{'a', ']'},
	{'a', '^'},
	{'a', '['},
	{'a', '\\'},
	{'{', ' '},
	{'e', ']'},
	{'e', '^'},
	{'e', '['},
	{'|', '^'},
	{'|', ']'},
	{'|', '['},
	{'A', '^'},
	{'A', ']'},
	{'E', '\\'},
	{' ', ' '},
	{' ', ' '},
	{'o', ']'},
	{'o', '^'},
	{'o', '['},
	{'u', ']'},
	{'u', '['},
	{'y', '^'},
	{'O', '^'},
	{'U', '^'},
	{' ', ' '},
	{'O', '\\'},
	{' ', ' '},
	{' ', ' '},
	{' ', ' '},
	{'a', '\\'},
	{'|', '\\'},
	{'o', '\\'},
	{'u', '\\'},
	{'n', '_'},
	{'N', '_'},
	{' ', ' '},
	{' ', ' '},
	{'}', ' '},
	{' ', ' '},
	{' ', ' '},
	{' ', ' '},
	{' ', ' '},
	{'~', ' '}
};

unsigned char PulseCnt = 0;
unsigned char ScaleFlag;

static CVECTOR ShadeFromTo[10][2] =
{
	{{128, 128, 128, 0}, {128, 128, 128, 0}},
	{{128, 128, 128, 0}, {128, 128, 128, 0}},
	{{128, 128, 128, 0}, {128, 128, 128, 0}},
	{{128, 0, 0, 0}, {64, 0, 0, 0}},
	{{0, 0, 160, 0}, {0, 0, 80, 0}},
	{{128, 128, 128, 0}, {16, 16, 16, 0}},
	{{192, 128, 64, 0}, {64, 16, 0, 0}},
	{{16, 16, 16, 0}, {128, 128, 128, 0}},
	{{224, 192, 0, 0}, {64, 32, 0, 0}},
	{{128, 0, 0, 0}, {64, 0, 0, 0}}
};

#if PC_VERSION
CVECTOR2 FontShades[10][16];

int font_height;
DWORD dword_50A14C = true;


CHARDEF stru_E4DEC0[106];
DWORD dword_E4DC40;
DWORD dword_E4DC44;
DWORD dword_E4DEA4;
#else
CVECTOR FontShades[10][16];
#endif

void InitFont()//115EC(<), 1169C(<) (F) (D) (ND)
{
#if PC_VERSION
	Log(LT_Enter, "InitFont");
#endif
	
	int i;
	int j;

	unsigned char nr;
	unsigned char ng;
	unsigned char nb;

	unsigned char fr;
	unsigned char fg;
	unsigned char fb;

	unsigned short r;
	unsigned short g;
	unsigned short b;

	//loc_11634
	for(i = 0; i < 10; i++)
	{
		fr = ShadeFromTo[i][1].r;
		fg = ShadeFromTo[i][1].g;
		fb = ShadeFromTo[i][1].b;

		nr = ShadeFromTo[i][0].r;
		ng = ShadeFromTo[i][0].g;
		nb = ShadeFromTo[i][0].b;

		//loc_116A0
		for (j = 0; j < 16; j++)
		{
			r = (((nr << 4) + (-nr * j)) >> 4) + ((fr * j) >> 4);
			g = (((ng << 4) + (-ng * j)) >> 4) + ((fg * j) >> 4);
			b = (((nb << 4) + (-nb * j)) >> 4) + ((fb * j) >> 4);

			if (r > 255)
			{
				r = 255;
			}
			//loc_116DC
			if (g > 255)
			{
				g = 255;
			}
			//loc_116EC
			if (b > 255)
			{
				b = 255;
			}
#if PC_VERSION
			uint32_t c1, c2;
			CalcColorSplit(RGB_MAKE(r, g, b), &c1, &c2);

			c1 |= 0xFF000000;
			c2 |= 0xFF000000;
			
			FontShades[i][j].color.rgbcd = c1;
			FontShades[i][j].specular.rgbcd = c2;
#else
			//loc_116F8
			FontShades[i][j].r = r;
			FontShades[i][j].g = g;
			FontShades[i][j].b = b;
#endif
		}
	}

#if PC_VERSION
	if (dword_50A14C)
	{
		for (i = 0; i < 106; i++)
		{
			stru_E4DEC0[i].w = CharDef[i].w;
			stru_E4DEC0[i].h = CharDef[i].h;
			stru_E4DEC0[i].YOffset = CharDef[i].YOffset;
		}

		dword_50A14C = false;
	}

	for (i = 0; i < 106; i++)
	{
		CharDef[i].w = stru_E4DEC0[i].w * phd_winxmax / 512.0;
		CharDef[i].h = stru_E4DEC0[i].h * phd_winymax / 240.0;
		CharDef[i].YOffset = stru_E4DEC0[i].YOffset * phd_winymax / 240.0;
	}
	
	font_height = phd_winymax * 7.0 / 120.0;
	dword_E4DC40 = phd_winymax * 7.0 / 120.0;
	dword_E4DEA4 = 6;
#endif

	return;
}
