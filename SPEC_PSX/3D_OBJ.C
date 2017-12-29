#include "3D_OBJ.H"

#include "GPU.H"
#include "MISC.H"
#include "SPECIFIC.H"

struct TSV tsv_buffer[512];

void CreateMonoScreen()//5F450(<), 60130(<)
{
#if 0
	int i; // $s0
	struct RECT r; // stack offset -32
	unsigned short *s; // $s2 //src?
	unsigned char *d; // $s1 //dest?
#endif
	GPU_SyncBothScreens();
#if 0
	//la	$a1, loc_11848

	//s0 = 0xA0000
	//s3 = 0xA0000
	//s0 = 1;
	//v0 = 256;
	//v1 = 128;
	//a2 = &db;

	r.x = 0;
	r.w = 256;
	r.h = 128;

	//a3 = db.poly_buffer[0];
	//v1 = db.current_buffer;
	//s2 = (short*)db.poly_buffer[17938];
	//v1 ^= 1;

	//v1 = db.draw[v1].clip.y;

	//s1 = db.poly_buffer[0] + 35876;

	rect.y = v1;

	//loc_5F4CC:
	for (i = 0; i < 2; i++)
	{
		StoreImage(&rect, db.poly_buffer[1554]);
		DrawSync(0);
		MakeMono(s, d);
		d += 16384;
		rect.y += 128;
	}

	la	$a0, loc_11848
	li	$s0, 1
	addiu	$v1, $s3, 0x3BF0
	sh	$zero, 0x30 + var_1E($sp)
	lw	$a1, 0x28($v1)
	lhu	$v0, 0x30 + var_20($sp)
	addu	$s1, $a1, $a0
	addiu	$v0, 0x100
	sh	$v0, 0x30 + var_20($sp)

		//loc_5F52C
		for (i = 0; i < 2; i++)
		{
			StoreImage(&rect, db.poly_buffer[17938]);//db.poly_buffer[0] + 17938
			DrawSync(0);
			MakeMono(s, d);
			d += 16384;
			rect.y += 128;
		}

			addiu	$a0, $sp, 0x30 + var_20
			la	$s1, loc_11848
			li	$v0, 0x340
			li	$v1, 0x100
			sh	$v0, 0x30 + var_20($sp)
			li	$v0, 0x40
			addiu	$s0, $s3, 0x3BF0
			sh	$v1, 0x30 + var_1E($sp)
			sh	$v0, 0x30 + var_1C($sp)
			sh	$v1, 0x30 + var_1A($sp)
			lw	$a1, 0x24($s0)
			li	$s2, 0x9848
			jal	sub_659B4//StoreImage
			addu	$a1, $s2
			lw	$a1, 0x24($s0)
			addiu	$a0, $sp, 0x30 + var_20
			jal	sub_6597C//LoadImage
			addu	$a1, $s1
			addiu	$a0, $sp, 0x30 + var_20
			lw	$a1, 0x28($s0)
			lhu	$v0, 0x30 + var_20($sp)
			addu	$a1, $s2
			addiu	$v0, 0x40
			jal	sub_659B4//StoreImage
			sh	$v0, 0x30 + var_20($sp)
			lw	$a1, 0x28($s0)
			addiu	$a0, $sp, 0x30 + var_20
			jal	sub_6597C//LoadImage
			addu	$a1, $s1
			DrawSync(0);
		nop 
		lw	$a1, 0x24($s0)
		li	$a2, 0x2000
		addu	$a0, $a1, $s1
		jal	sub_5E964
		addu	$a1, $s2
		lw	$a1, 0x28($s0)
		li	$a2, 0x2000
		addu	$a0, $a1, $s1
		jal	sub_5E964
		addu	$a1, $s2
		lw	$ra, 0x30 + var_8($sp)
		lw	$s3, 0x30 + var_C($sp)
		lw	$s2, 0x30 + var_10($sp)
		lw	$s1, 0x30 + var_14($sp)
		lw	$s0, 0x30 + var_18($sp)
		jr	$ra
		addiu	$sp, 0x30
#endif

	S_Warn("[CreateMonoScreen] - Unimplemented!\n");
}