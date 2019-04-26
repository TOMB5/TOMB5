#include "3D_OBJ.H"

#include "DRAWOBJ.H"
#include "GPU.H"
#include "MISC.H"

struct TSV tsv_buffer[512];

void CreateMonoScreen()//5F450(<), 60130(<) (F) (*) (D)
{
	int i;
	RECT r;
	unsigned short* s;
	unsigned char* d;

	GPU_SyncBothScreens();

	setRECT(&r, 0, db.draw[db.current_buffer ^ 1].clip.y, 256, 128);

	s = (unsigned short*)(db.poly_buffer[0] + 1554);
	d = (unsigned char*)(db.poly_buffer[0] + 17938);

	//loc_5F4CC:
	for (i = 0; i < 2; i++)
	{
		StoreImage(&r, (unsigned long*)s);
		DrawSync(0);
		MakeMono(s, d);

		d += 0x4000;
		r.y += 128;
	}

	r.y = 0;
	r.x += 256;

	d = (unsigned char*)(db.poly_buffer[1] + 17938);

	//loc_5F52C:
	for (i = 0; i < 2; i++)
	{
		StoreImage(&r, (unsigned long*)s);
		DrawSync(0);
		MakeMono(s, d);

		d += 0x4000;
		r.y += 128;
	}

	setRECT(&r, 832, 256, 64, 256);

	StoreImage(&r, db.poly_buffer[0] + 9746);
	LoadImage(&r, db.poly_buffer[0] + 17938);

	r.x += 64;

	StoreImage(&r, db.poly_buffer[1] + 9746);
	LoadImage(&r, db.poly_buffer[1] + 17938);

	DrawSync(0);

	S_LongMemCpy(db.poly_buffer[0] + 17938, db.poly_buffer[0] + 9746, 8192);
	S_LongMemCpy(db.poly_buffer[1] + 17938, db.poly_buffer[1] + 9746, 8192);
}