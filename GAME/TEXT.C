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

	for(i = 0; i < 10; i++)
	{
		int t9 = 0;
		int t8 = 0;
		int t7 = 0;

		int t5 = ShadeFromTo[i][0].b << 4;
		int t4 = ShadeFromTo[i][0].g << 4;
		int t3 = ShadeFromTo[i][0].r << 4;

		for (j = 0; j < 16; j++)
		{
			r = ((t3 >> 4) + (t7 >> 4)) & 0xFFFF;
			g = ((t4 >> 4) + (t8 >> 4)) & 0xFFFF;
			b = ((t5 >> 4) + (t9 >> 4)) & 0xFFFF;

			if (r > 0x100)
			{
				r = 0xFF;
			}

			if (g > 0x100)
			{
				g = 0xFF;
			}

			if (b > 0x100)
			{
				b = 0xFF;
			}

			FontShades[i][j].r = r;
			FontShades[i][j].g = g;
			FontShades[i][j].b = b;

			t7 += ShadeFromTo[i][1].r;
			t8 += ShadeFromTo[i][1].g;
			t9 += ShadeFromTo[i][1].b;

			t3 += -ShadeFromTo[i][0].r;
			t4 += -ShadeFromTo[i][0].g;
			t5 += -ShadeFromTo[i][0].b;
		}
	}
}
