#include "BUBBLES.H"

#include "DRAW.H"
#include "GPU.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "GTEREG.H"
#include "DRAWSPKS.H"
#include "LARA.H"

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
	int t2;
	int t5;
	int t4;
	int t7;
	int a0;
	int a1;
	int a2;
	int a3;
	int t3;
	short* t1;
	int t0;
	struct room_info* r;//v1
	int v0;

	t2 = unknown & 0xFFFF;
	t5 = room_number & 0xFFFF;
	//t7 = lara_item;
	t4 = number_draw_rooms;
	//t6 = room;
	t7 = ((int*)lara_item)[6];
	a0 = 512;
	a1 = 0;
	a2 = 256;
	a3 = 0;

	t3 = 0;
	if (t4 > 0)
	{
		t1 = &draw_rooms[0];

		//loc_8F3AC
		do
		{
			t0 = t1[0];
			t3++;

			r = &room[t0];

			if (t2 != 0)
			{
				if (!(r->flags & (RF_WIND_BLOWS_PONYTAIL | RF_SKYBOX_VISIBLE)))
				{
					goto loc_8F440;
				}
			}//loc_8F3DC

			if (t0 == t5)
			{
				if (t2 == 0)
				{
					goto loc_8F440;
				}
			}

			//loc_8F3EC
			if (t0 == t7)
			{
				if (t2 == 0)
				{
					goto loc_8F440;
				}
			}

			//loc_8F3FC
			t0 = r->left;
			v0 = r->right;

			if (t0 < a0)
			{
				a0 = t0 + 1;
			}
			//loc_8F414
			t0 = r->top;
			if (a1 < v0)
			{
				a1 = v0 - 1;
			}
			//loc_8F420
			v0 = r->bottom;

			if (t0 < a2)
			{
				a2 = t0 + 1;
			}

			if (a3 < v0)
			{
				a3 = v0 - 1;
			}

loc_8F440:
			t1++;
		} while (t3 < t4);

		a0 <<= 16;
		a1 <<= 16;
		a2 <<= 16;
		a3 <<= 16;

		R = a0 & 0xFF;
		G = (a0 >> 8) & 0xFF;
		B = (a0 >> 16) & 0xFF;
		CODE = (a0 >> 24) & 0xFF;
		RGB0 = a1;
		RGB1 = a2;
		RGB2 = a3;

	}//locret_8F46C
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
	int t5 = rgb0;
	int t6 = rgb1;
	int t7 = rgb2;
	int t8 = rgb3;
	int t0 = R11 | ((R12 & 0xFFFF) << 16);
	int t1 = R13 | ((R21 & 0xFFFF) << 16);
	int t2 = R22 | ((R23 & 0xFFFF) << 16);
	int t3 = R31 | ((R32 & 0xFFFF) << 16);
	int t4 = R33;

	int at = ((int*)&CamGTE.m00)[0];
	int v0 = ((int*)&CamGTE.m00)[1];
	int v1 = ((int*)&CamGTE.m00)[2];
	int a1 = ((int*)&CamGTE.m00)[3];
	int a0 = ((int*)&CamGTE.m00)[4];

	R11 = at & 0xFFFF;
	R12 = (at >> 16) & 0xFFFF;
	R13 = v0 & 0xFFFF;
	R21 = (v0 >> 16) & 0xFFFF;
	R22 = v1 & 0xFFFF;
	R23 = (v1 >> 16) & 0xFFFF;
	R31 = a1 & 0xFFFF;
	R32 = (a1 >> 16) & 0xFFFF;
	R33 = a0;

	DEL_ApplyMatrixSV(0xF000F000, 0x1000, &LightPos.m00);
	DEL_ApplyMatrixSV(0xF0001000, 0xFFFFF000, &LightPos.m10);
	DEL_ApplyMatrixSV(0x10000000, 0xFFFFF000, &LightPos.m20);

	R11 = t0 & 0xFFFF;
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = t1 & 0xFFFF;
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = t2 & 0xFFFF;
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = t3 & 0xFFFF;
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4;

	v0 = (t5 & 0xFF) << 4;
	v1 = (t6 & 0xFF) << 20;
	v0 |= v1;

	LR1 = v0 & 0xFFFF;
	LR2 = v0 >> 16;

	v0 = (t7 & 0xFF) << 4;
	v1 = (t5 & 0xFF00) << 12;
	v0 |= v1;

	LR3 = v0 & 0xFFFF;
	LG1 = v0 >> 16;

	v0 = (t6 >> 4) & 0xFF0;
	v1 = (t7 & 0xFF00) << 12;
	v0 |= v1;
	LG2 = v0 & 0xFFFF;
	LG3 = v0 >> 16;

	v0 = (t5 >> 12) & 0xFF0;
	v1 = ((t6 >> 12) & 0xFF0) << 16;
	v0 |= v1;

	LB1 = v0 & 0xFFFF;
	LB2 = v0 >> 16;

	v0 = (t7 >> 12) & 0xFF0;
	LB3 = v0;

	a0 = (t8 & 0xFF) << 4;
	a1 = (t8 >> 4) & 0xFF0;
	int a2 = (t8 >> 12) & 0xFF0;
	RBK = a0;
	GBK = a1;
	BBK = a2;

	R = 128;
	G = 128;
	B = 128;
	CODE = 0;
	DQB = 0;
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

			t5 = (unsigned long)a00;
			a00 += 0x1C;//TODO actual polytype
		}
		j = 0;
	}

	db.ot[2000] = (unsigned long)t5;
	db.polyptr = (char*)a00;

	return;
}