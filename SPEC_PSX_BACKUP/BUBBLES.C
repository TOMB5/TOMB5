#include "BUBBLES.H"

#include "DRAW.H"
#include "GPU.H"
#include "SPECIFIC.H"
#include "TOMB4FX.H"

#ifndef USE_ASM

void DrawFlash()//8F704(<) 91748(<) (F)
{
	long fr = ((FlashFadeR * FlashFader) / 32) & 0xFF;
	long fg = ((FlashFadeB * FlashFader) / 32) & 0xFF;
	long fb = ((FlashFadeG * FlashFader) * 8) & 0xFF00;

	DrawPsxTile(0, 0xF00200, (fb << 16 | fg | fr | 0x6200), 1);
}

void insert_psx_clip_window(long x, long y, long w, long a3, long h)
{
	DRAWENV env;

#if 1

	if (db.current_buffer != 0)
	{
		env.dr_env.tag = 0xF000;
		y += 0xF0;
	}
	else
	{
		env.dr_env.tag = 0;
	}
	//loc_8FDCC:
	SetDefDrawEnv(&env, x, y, w, h);
	*(long*) &env.ofs[0] = env.dr_env.tag;
	env.dtd = 1;
	env.isbg = 0;
	SetDrawEnv((DR_ENV*)&db.polyptr[0], &env);
	*(long*)&db.polyptr[0] = db.ot[2563] |= 0x60000000;
	*(long*) &db.ot[2563] = (long)db.polyptr;
	db.polyptr += 0x1C;
#endif
}


void CalcClipWindow_ONGTE(short room_number, long unknown)//8F374,
{
	//t2 = unknown;
	//t5 = room_number;
	//t7 = lara_item;
	//t4 = number_draw_rooms;
	//t6 = &room[0];
	//t7 = lara_item->room_number;//fixme loads word but short?!?
	//a0 = 512;
	//a1 = 0;
	//a2 = 256;
	//a3 = 0;
	//t3 = 0;

	if (number_draw_rooms <= 0)
	{
		//locret_8F46C
		return;
	}

	//loc_8F3AC
	//t1 = &draw_rooms[0];
	//t0 = draw_rooms[0];
	//t3++;
	//v1 = &room[draw_rooms[0]];
	if (unknown != 0)
	{
		//at = r->flags;

	}//loc_8F3DC
#if 0

		lhu	$at, 0x4E($v1)
		nop
		andi	$at, 0x28
		beqz	$at, loc_8F440
		nop

		loc_8F3DC :
	bne	$t0, $t5, loc_8F3EC
		nop
		beqz	$t2, loc_8F440
		nop

		loc_8F3EC :
	bne	$t0, $t7, loc_8F3FC
		nop
		beqz	$t2, loc_8F440
		nop

		loc_8F3FC :
	lh	$t0, 0x38($v1)
		lh	$v0, 0x3A($v1)
		slt	$at, $t0, $a0
		beqz	$at, loc_8F414
		slt	$at, $a1, $v0
		addiu	$a0, $t0, 1

		loc_8F414:
	beqz	$at, loc_8F420
		lh	$t0, 0x3C($v1)
		addiu	$a1, $v0, -1

		loc_8F420 :
		lh	$v0, 0x3E($v1)
		slt	$at, $t0, $a2
		beqz	$at, loc_8F434
		slt	$at, $a3, $v0
		addiu	$a2, $t0, 1

		loc_8F434 :
		beqz	$at, loc_8F440
		nop
		addiu	$a3, $v0, -1

		loc_8F440 :
		slt	$at, $t3, $t4
		bnez	$at, loc_8F3AC
		addiu	$t1, 2

		loc_8F44C :
		sll	$a0, 16
		sll	$a1, 16
		sll	$a2, 16
		sll	$a3, 16
		mtc2	$a0, $6
		mtc2	$a1, $20
		mtc2	$a2, $21
		mtc2	$a3, $22

		locret_8F46C :
	jr	$ra
		nop
#endif
	S_Warn("[CalcClipWindow_ONGTE] - Unimplemented!\n");
}

void DrawPsxTile(long a0, long a1, long a2, long a3)//8F770(<), 917B4(<) (F)
{
	long t1 = 0;//lw $t1, arg_10($sp) OT index
	
	if ((unsigned long) db.polyptr < (unsigned long) db.polybuf_limit)
	{
		((long*)db.polyptr)[2] = 0;
		((long*)db.polyptr)[3] = a2;
		((long*)db.polyptr)[4] = a0;
		((long*)db.polyptr)[5] = a1;
		((long*)db.polyptr)[0] = db.ot[t1] | 0x5000000;
		db.ot[t1] = (unsigned long)db.polyptr;
		((long*)db.polyptr)[1] = (a3 & 3) << 5 | 0xE1000200;
		db.polyptr += 0x18;
	}
}
#endif

void S_DrawSparks()
{
	S_Warn("[S_DrawSparks] - Unimplemented!\n");
}