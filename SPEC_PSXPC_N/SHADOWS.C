#include "SHADOWS.H"
#include "SPECIFIC.H"
#include "GPU.H"

/*
 * calcval :
 * at = (v0 * value + at * (width - value)) / width
 */

#define BLEND(left, right, value, width) (((left) * ((width) - (value)) + (right) * (value)) / (width))

void DelLine(short x0, short y0, short x1, short y1, int color1, int color2)
{
	LINE_G2* ptr = (LINE_G2*)db.polyptr;

	setLineG2(ptr);	

	setRGB0(ptr, getR(color1), getG(color1), getB(color1));
	setRGB1(ptr, getR(color2), getG(color2), getB(color2));

	setXY2(ptr, x0, y0, x1, y1);

	addPrim(db.ot, ptr);

	db.polyptr += sizeof(LINE_G2);
}

void DelBox(short x, short y, short w, short h, int color)
{
	TILE* ptr = (TILE*)db.polyptr;

	setTile(ptr);

	setRGB0(ptr, getR(color), getG(color), getB(color));

	setXY0(ptr, x, y);
	setWH(ptr, w, h);

	addPrim(db.ot, ptr);

	db.polyptr += sizeof(TILE);
}

void S_DrawGouraudBar(int x, int y, int width, int value, GouraudBarColourSet* colour)
{
	if ((unsigned long)db.polyptr < (unsigned long)db.polybuf_limit)
	{
		if (value-- != 0)
		{
			for(int i = 0; i < 5; i++)
			{
				u_char r0 = colour->abLeftRed[i];
				u_char g0 = colour->abLeftGreen[i];
				u_char b0 = colour->abLeftBlue[i];
				u_char r1 = BLEND(r0, colour->abRightRed[i], value, width);
				u_char g1 = BLEND(g0, colour->abRightGreen[i], value, width);
				u_char b1 = BLEND(b0, colour->abRightBlue[i], value, width);

				DelLine(x, y + i, x + value, y + i, genRGB(r0, g0, b0), genRGB(r1, g1, b1));
			}
		}

		DelLine(x - 2, y - 2, x + width + 2, y - 2, genRGB(80, 130, 130), genRGB(160, 160, 160)); // top
		DelLine(x - 2, y + 6, x + width + 2, y + 6, genRGB(80, 130, 130), genRGB(160, 160, 160)); // bottom
		DelLine(x + width + 2, y - 2, x + width + 2, y + 6, genRGB(80, 130, 130), genRGB(160, 160, 160)); // right
		DelLine(x - 2, y - 2, x - 2, y + 6, genRGB(80, 130, 130), genRGB(160, 160, 160)); // left

		DelLine(x - 3, y - 1, x - 3, y + 5, genRGB(40, 65, 65), genRGB(80, 80, 80));
		DelLine(x + width + 3, y - 1, x + width + 3, y + 5, genRGB(40, 65, 65), genRGB(80, 80, 80));

		DelBox(x - 1, y - 1, width + 3, 7, genRGB(0, 0, 0));
	}
}

long OptimiseOTagR(unsigned long* ot, int nOTSize)//86CC4(<), 88D08(<)
{
	unsigned long* a1;
	unsigned long* a3;
	unsigned long v0;
	unsigned long* v1;
	long at = 0;

	if (nOTSize < 8)
	{
		return 0;
	}

	//a1 <<= 2
	//a1 -= 4
	a1 = &ot[nOTSize - 1];
	v1 = &ot[1];
	v0 = a1[0];

	//loc_86CE4:
	do
	{
		--a1;
		a3 = &a1[1];
		if (v0 == (unsigned long)a1)
		{
			if (a1 == ot)
			{
				return 0;
			}

			//loc_86CF4
			do
			{
				v0 = a1[0];
				a1--;

				if (&a1[1] == v1)
				{
					break;
				}

				at++;
			} while ((unsigned long)v0 == (unsigned long)a1);

			//loc_86D08
			a3[0] = v0;

		}//loc_86D0C

		v0 = a1[0];
	} while (a1 != ot);

	return at;
}
