#include "3D_OBJ.H"

#include "DRAWOBJ.H"
#include "GPU.H"
#include "MISC.H"

#include <SYS\TYPES.H>
#include <LIBGPU.H>

struct TSV tsv_buffer[512];

void CreateMonoScreen()//5F450(<), 60130(<) (F)
{
	int i;
	RECT r;
	unsigned short* s;
	unsigned char* d;

	GPU_SyncBothScreens();

	r.x = 0;
	r.w = 256;
	r.h = 128;

	s = (unsigned short*)(db.poly_buffer[0] + 1554);
	r.y = db.draw[db.current_buffer ^ 1].clip.y;

	//loc_5F4CC:
	for(i = 1; i >= 0; i--)
	{
		StoreImage(&r, (unsigned long*)s);
		DrawSync(0);
		MakeMono(s, d);

		d += 0x4000;
		r.y += 128;
	}

	r.y = 0;

	d = (unsigned char*) (db.poly_buffer[1] + 17938);
	r.x += 256;

	//loc_5F52C:
	for (i = 1; i >= 0; i--)
	{
		StoreImage(&r, (unsigned long*)s);
		DrawSync(0);
		MakeMono(s, d);

		d += 0x4000;
		r.y += 128;
	}

	r.x = 832;
	r.y = 256;
	r.w = 64;
	r.h = 256;

	StoreImage(&r, db.poly_buffer[0] + 9746);
	LoadImage(&r, db.poly_buffer[0] + 17938);

	r.x += 64;

	StoreImage(&r, db.poly_buffer[1] + 9746);
	LoadImage(&r, db.poly_buffer[1] + 17938);

	DrawSync(0);

	S_LongMemCpy(db.poly_buffer[0] + 17938, db.poly_buffer[0] + 9746, 8192);
	S_LongMemCpy(db.poly_buffer[1] + 17938, db.poly_buffer[1] + 9746, 8192);
}