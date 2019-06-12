#include "BUBBLES.H"

#include "DRAW.H"
#include "GPU.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "GTEREG.H"
#include "DRAWSPKS.H"

void DrawFlash()
{
	UNIMPLEMENTED();
}

void insert_psx_clip_window(long x, long y, long w, long h, long arg_10)
{
#if 0
	DRAWENV env;//0x1F800000
	int v0;

	v0 = db.current_buffer;

	if (db.current_buffer != 0)
	{
		v0 = 0xF00000;
		y += SCREEN_HEIGHT;
	}
	//loc_8FDCC
	SetDefDrawEnv(&env, x, y, w, h);
	((int*)&env.ofs)[0] = v0;
	env.dtd = 1;
	env.isbg = 0;
	SetDrawEnv((DR_ENV*)db.polyptr, &env);
	db.ot[2563] = (unsigned int)db.polyptr;
	((unsigned int*)db.polyptr)[0] = (unsigned int)db.ot[2563] | 0x6000000;
	db.polyptr += 0x1C;
#endif
}

void CalcClipWindow_ONGTE(short room_number, long unknown)//8F374,
{
	UNIMPLEMENTED();
}

void DrawPsxTile(long a0, long a1, long a2, long a3)//8F770(<), 917B4(<) (F)
{
	UNIMPLEMENTED();
}

void TriggerDynamic(long x, long y, long z, int falloff, int r, int g, int b)
{
	UNIMPLEMENTED();
}

void DEL_ApplyMatrixSV(int v0, int v1, short* m)//(F)
{
	VX0 = (v0 & 0xFFFF);
	VY0 = (v0 >> 16) & 0xFFFF;
	VZ0 = v1;

	docop2(0x486012);

	m[0] = IR1;
	m[1] = IR2;
	m[2] = IR3;
}

void SetInventoryLighting(int rgb0, int rgb1, int rgb2, int rgb3)//(F)
{
	int t0, t1, t2, t3, t4;

	t0 = COP(0);
	t1 = COP(1);
	t2 = COP(2);
	t3 = COP(3);
	t4 = COP(4);

	COP(0) = ((int*)&CamGTE.m00)[0];
	COP(1) = ((int*)&CamGTE.m02)[0];
	COP(2) = ((int*)&CamGTE.m11)[0];
	COP(3) = ((int*)&CamGTE.m20)[0];
	COP(4) = ((int*)&CamGTE.m22)[0];

	DEL_ApplyMatrixSV(0xF000F000, 0x1000, &LightPos.m00);
	DEL_ApplyMatrixSV(0xF0001000, 0xFFFFF000, &LightPos.m10);
	DEL_ApplyMatrixSV(0x10000000, 0xFFFFF000, &LightPos.m20);

	COP(0) = t0;
	COP(1) = t1;
	COP(2) = t2;
	COP(3) = t3;
	COP(4) = t4;

	COP(16) = ((rgb0 & 0xFF) << 4)   | ((rgb1 & 0xFF) << 20);
	COP(17) = ((rgb2 & 0xFF) << 4)   | ((rgb0 & 0xFF00) << 12);
	COP(18) = ((rgb1 >> 4) & 0xFF0)  | ((rgb2 & 0xFF00) << 12);
	COP(19) = ((rgb0 >> 12) & 0xFF0) | (((rgb1 >> 12) & 0xFF0) << 16);

	COP(20) = (rgb2 >> 12) & 0xFF0;
	COP(13) = ((rgb3 & 0xFF) << 4);
	COP(14) = ((rgb3 >> 4) & 0xFF0);
	COP(15) = ((rgb3 >> 12) & 0xFF0);

	DAT(16) = 0x808080;
	COP(28) = 0;
}

void DrawMonoScreen(int a0)
{
	int i = 0;
	int j = 0;
	unsigned long* pp = db.ot;//a2
	unsigned long t5 = db.ot[2000];
	char* a00 = db.polyptr;

	//loc_8F17C
	for(i = 0; i < 4; i++)
	{
		//loc_8F180 
		for (j = 0; j < 8; j++)
		{
			((int*)a00)[2] = 0;
			((int*)a00)[3] = a0 | 0x64000000;
			((int*)a00)[4] = ((i << 6) << 16) | (j << 6);
			((int*)a00)[6] = 0x400040;

			((int*)a00)[0] = t5 | 0x6000000;
			((int*)a00)[1] = (((j << 6) >> 8) + 13) | 0xE1000610;
			((short*)a00)[10] = (((i << 6) & 0xFF) << 8) | ((j << 6) & 0xFF);
			((short*)a00)[11] = (ClutStartY << 6) | 0x3C;

			t5 = (unsigned long)db.polyptr;
			a00 += 0x1C;//TODO actual polytype
		}
		j = 0;
	}

	db.ot[2000] = (unsigned long)pp;
	db.polyptr = (char*)a00;

	return;
}