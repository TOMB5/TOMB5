#include "TEXT.H"

#include "PSXTYPES.H"

char AccentTable[46][2];
unsigned char PulseCnt;
unsigned char ScaleFlag;

struct CVECTOR FontShades[10][16];

static struct CVECTOR ShadeFromTo[10][2] = 
{
	128, 128, 128, 0, 128, 128, 128, 0, 128, 128, 128, 0, 128, 128, 128, 0,
	128, 128, 128, 0, 128, 128, 128, 0, 128,   0,   0, 0,  64,   0,   0, 0,
	  0,   0, 160, 0,   0,   0,  80, 0,
	
	128, 128, 128,  0,  16,  16,  16,  0, 192, 128,  64, 0,  64,  16,  0, 0, 
	 16,  16,  16,  0,  128, 128, 128, 0, 224, 192,   0, 0,  64,  32,  0, 0,
	128,   0,   0,  0,  64,    0,  0,  0
};

void InitFont()//115EC(<), 1169C(<)
{
	int i, j;
	unsigned short r, g, b;
	unsigned char fr, fg, fb;

	for(i = 0; i < 10; i++)
	{
		r = 0;
		g = 0;
		b = 0;

		int t5 = ShadeFromTo[i][0].b << 4;
		int t4 = ShadeFromTo[i][0].g << 4;
		int t3 = ShadeFromTo[i][0].r << 4;

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
}
