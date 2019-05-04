#include "BUBBLES.H"

#include "DRAW.H"
#include "GPU.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"

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

#if PSXPC_VERSION
void SetInventoryLighting(struct MATRIX3D* m)
{
#if PSX_VERSION && !USE_ASM
	gte_ReadRotMatrix(m);
	gte_SetRotMatrix(CamGTE);
	//a0 = CamGTE
#else
	UNIMPLEMENTED();
#endif
}
#endif

void DrawMonoScreen(int a0)
{
}