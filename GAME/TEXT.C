#include "TEXT.H"

#if PC_VERSION
#include "GLOBAL.H"
#else
//#include <SYS/TYPES.H>
#include <LIBGTE.H>
#endif

#include "SPECTYPES.H"

char AccentTable[46][2] =
{
	{ 0x7B, 0x20 },
	{ 0x75, 0x5E },
	{ 0x65, 0x5C },
	{ 0x61, 0x5D },
	{ 0x61, 0x5E },
	{ 0x61, 0x5B },
	{ 0x61, 0x5C },
	{ 0x7B, 0x20 },
	{ 0x65, 0x5D },
	{ 0x65, 0x5E },
	{ 0x65, 0x5B },
	{ 0x7C, 0x5E },
	{ 0x7C, 0x5D },
	{ 0x7C, 0x5B },
	{ 0x41, 0x5E },
	{ 0x41, 0x5D },
	{ 0x45, 0x5C },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x6F, 0x5D },
	{ 0x6F, 0x5E },
	{ 0x6F, 0x5B },
	{ 0x75, 0x5D },
	{ 0x75, 0x5B },
	{ 0x79, 0x5E },
	{ 0x4F, 0x5E },
	{ 0x55, 0x5E },
	{ 0x20, 0x20 },
	{ 0x4F, 0x5C },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x61, 0x5C },
	{ 0x7C, 0x5C },
	{ 0x6F, 0x5C },
	{ 0x75, 0x5C },
	{ 0x6E, 0x5F },
	{ 0x4E, 0x5F },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x7D, 0x20 },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x20, 0x20 },
	{ 0x7E, 0x20 }
};

unsigned char PulseCnt = 0;
unsigned char ScaleFlag;

CVECTOR FontShades[10][16];

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
int font_height;
#endif

void InitFont()//115EC(<), 1169C(<) (F) (D) (ND)
{
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

		nb = ShadeFromTo[i][0].b;
		ng = ShadeFromTo[i][0].g;
		nr = ShadeFromTo[i][0].r;

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
			//loc_116F8
			FontShades[i][j].r = r;
			FontShades[i][j].g = g;
			FontShades[i][j].b = b;
		}
	}

#if PC_VERSION
	font_height = phd_winymax * 7.0 / 120.0;
#endif

	return;
}
