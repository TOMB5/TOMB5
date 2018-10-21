#include "TEXT.H"

#if PC_VERSION
#include "GLOBAL.H"
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

struct CVECTOR FontShades[10][16];

static struct CVECTOR ShadeFromTo[10][2] =
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

void InitFont()//115EC(<), 1169C(<) (F)
{
	int i, j;
	unsigned short r, g, b;
	unsigned char fr, fg, fb;
	int t3, t4, t5;

	for(i = 0; i < 10; i++)
	{
		r = 0;
		g = 0;
		b = 0;

		t5 = ShadeFromTo[i][0].b << 4;
		t4 = ShadeFromTo[i][0].g << 4;
		t3 = ShadeFromTo[i][0].r << 4;

		for (j = 0; j < 16; j++)
		{
			fr = ((t3 >> 4) + (r >> 4)) & 0xFFFF;
			fg = ((t4 >> 4) + (g >> 4)) & 0xFFFF;
			fb = ((t5 >> 4) + (b >> 4)) & 0xFFFF;

			if (fr > 0x100)
			{
				fr = 0xFF;
			}

			if (fg > 0x100)
			{
				fg = 0xFF;
			}

			if (fb > 0x100)
			{
				fb = 0xFF;
			}

			FontShades[i][j].r = fr;
			FontShades[i][j].g = fg;
			FontShades[i][j].b = fb;

			r += ShadeFromTo[i][1].r;
			g += ShadeFromTo[i][1].g;
			b += ShadeFromTo[i][1].b;

			t3 += -ShadeFromTo[i][0].r;
			t4 += -ShadeFromTo[i][0].g;
			t5 += -ShadeFromTo[i][0].b;
		}
	}

#if PC_VERSION
	font_height = phd_winymax * 7.0 / 120.0;
#endif

	return;
}
