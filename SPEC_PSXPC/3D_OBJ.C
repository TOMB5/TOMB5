#include "3D_OBJ.H"

#include "DRAWOBJ.H"
#include "GPU.H"
#include "MISC.H"

struct TSV tsv_buffer[512];

void CreateMonoScreen()//5F450, 60130
{
#if 1
	int i;
	unsigned short* s;
	unsigned char* d;

	GPU_SyncBothScreens();

	s = (unsigned short*)(db.poly_buffer[0] + 1554);
	d = (unsigned char*)(db.poly_buffer[0] + 17938);

	//loc_5F4CC:
	for (i = 1; i >= 0; i--)
	{
		MakeMono(s, d);

		d += 0x4000;
	}

	d = (unsigned char*)(db.poly_buffer[1] + 17938);

	//loc_5F52C:
	for (i = 1; i >= 0; i--)
	{
		MakeMono(s, d);

		d += 0x4000;
	}

	S_LongMemCpy(db.poly_buffer[0] + 17938, db.poly_buffer[0] + 9746, 8192);
	S_LongMemCpy(db.poly_buffer[1] + 17938, db.poly_buffer[1] + 9746, 8192);
#endif
}