#include "BUBBLES.H"

#include "DRAW.H"
#include "GPU.H"
#include "SPECIFIC.H"

void DrawFlash()
{
	UNIMPLEMENTED();
}

void insert_psx_clip_window(long x, long y, long w, long a3, long h)
{
	UNIMPLEMENTED();
}

void CalcClipWindow_ONGTE(short room_number, long unknown)//8F374,
{
	UNIMPLEMENTED();
}

void DrawPsxTile(long a0, long a1, long a2, long a3)//8F770(<), 917B4(<) (F)
{
	UNIMPLEMENTED();
}

void S_DrawSparks()
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