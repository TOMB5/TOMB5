#include "HEALTH.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#if PSXENGINE
#include "DRAWPHAS.H"
#include "FXTRIG.H"
#endif
#include "GAMEFLOW.H"
#include "LARA.H"
#include "SPOTCAM.H"

#include <stdio.h>
#include "SPECIFIC.H"
#include "OBJECTS.H"
#include "NEWINV2.H"
#include "TEXT.H"

int health_bar_timer = 0;
char PoisonFlag = 0;
struct DISPLAYPU pickups[8];
short PickupX = 0;
short PickupY = 0;
short PickupVel = 0;
short CurrentPickup = 0;

void AddDisplayPickup(short object_number)//3B6F4, ? (F)
{
	struct DISPLAYPU* pu = &pickups[0];
	long lp;
	if (gfCurrentLevel == LVL5_SUBMARINE && object_number == PUZZLE_ITEM1 ||
		gfCurrentLevel == LVL5_OLD_MILL && object_number == PUZZLE_ITEM3)
	{
		object_number = CROWBAR_ITEM;
	}

	for(lp = 0; lp < 8; lp++, pu++)
	{
		if (pu->life < 0)
		{
			pu->life = 45;
			pu->object_number = object_number;
			break;
		}
	}

	DEL_picked_up_object(object_number);
}

void DrawPickups(int timed)// (F)
{
	struct DISPLAYPU* pu = &pickups[CurrentPickup];
	long lp;

	if (pu->life > 0)
	{
		if (PickupX > 0)
		{
			PickupX += (-PickupX >> 3);
		}
		else
		{
			pu->life--;
		}
	}
	else if (pu->life == 0)
	{
		if (PickupX < 128)
		{
			if (PickupVel < 16)
				PickupX += ++PickupVel;
		}
		else
		{
			pu->life = -1;
			PickupVel = 0;
		}
	}
	else
	{
		for (lp = 0; lp < 8; lp++)
		{
			if (pickups[(CurrentPickup + lp) % 8].life > 0)
				break;
		}

		if (lp == 8)
		{
			CurrentPickup = 0;
			return;
		}

		CurrentPickup = (CurrentPickup + lp) % 8;
	}

	S_DrawPickup(pu->object_number);
}

void InitialisePickUpDisplay()//3B580, 3B9DC (F)
{
	int i;
	for (i = 7; i > -1; i--)
	{
		pickups[i].life = -1;
	}

	PickupY = 128;
	PickupX = 128;
	PickupVel = 0;
	CurrentPickup = 0;
}

void DrawAirBar(int flash_state)
{
#if PC_VERSION
	if (lara.air == 1800 || lara_item->hit_points <= 0)
		return;

	short val = CLAMP(lara.air, 0, 1800);

	if (val > 450 || flash_state)
	{
		S_DrawAirBar(100 * val / 1800);
	}
	else
	{
		S_DrawAirBar(0);
	}

	if (lara.Gassed)
	{
		if (lara.dpoisoned < 2048)
			lara.dpoisoned += 2;

		lara.Gassed = FALSE;
	}
#else

	int air; // $v1

	//a2 = flash_state;
	//v1 = &lara
	//a0 = 0x708
	//a1 = lara.air;
	//s0  = 0xA0000;
	if (lara.air == 1800)
	{
		return;
	}

	//v0 = lara_item;
	//v1 = lara.air

	if (lara_item->hit_points <= 0)
	{
		return;
	}

	if (lara.air < 0)//v1
	{
		//v1 = 0
	}
	else if (lara.air > 0x708)//v1
	{
		//v1 = 0x708
	}

	//v0 = 0x38E30000;
	if (lara.air > 0x1C2)
	{
		//loc_3B4D0
	}
	else if (flash_state == 0)
	{
		//loc_3B4A8
	}

	sizeof(struct room_info);
#if 0
	
		bgez	$v1, loc_3B424
		slti	$v0, $v1, 0x709
		j	loc_3B430
		move	$v1, $zero

		loc_3B424 :
	bnez	$v0, loc_3B434
		slti	$v0, $v1, 0x1C3
		li	$v1, 0x708

		loc_3B430 :
		slti	$v0, $v1, 0x1C3

		loc_3B434 :
		beqz	$v0, loc_3B4D0
		lui	$v0, 0x38E3
		beqz	$a2, loc_3B4A8
		li	$v0, 0x38E38E39
		mult	$v1, $v0
		li	$t0, 0x51EB851F
		sra	$v1, 31
		mfhi	$v0
		sra	$v0, 2
		subu	$v0, $v1
		sll	$a3, $v0, 5
		addu	$a3, $v0
		sll	$a3, 2
		addu	$a3, $v0
		mult	$a3, $t0
		li	$a0, 0x157
		li	$a1, 0x20
		li	$a2, 0x85
		la	$v0, dword_A18E0
		sw	$v0, 0x20 + var_10($sp)
		sra	$a3, 31
		mfhi	$t0
		sra	$t0, 5
		jal	sub_86FD8
		subu	$a3, $t0, $a3
		j	loc_3B534
		addiu	$a0, $s0, 0x57DC

		loc_3B4A8:
	la	$v0, dword_A18E0
		sw	$v0, 0x20 + var_10($sp)
		li	$a0, 0x157
		li	$a1, 0x20
		li	$a2, 0x85
		jal	sub_86FD8
		move	$a3, $zero
		j	loc_3B534
		addiu	$a0, $s0, 0x57DC

		loc_3B4D0:
	ori	$v0, 0x8E39
		mult	$v1, $v0
		li	$t0, 0x51EB851F
		sra	$v1, 31
		mfhi	$v0
		sra	$v0, 2
		subu	$v0, $v1
		sll	$a3, $v0, 5
		addu	$a3, $v0
		sll	$a3, 2
		addu	$a3, $v0
		mult	$a3, $t0
		li	$a0, 0x157
		li	$a1, 0x20
		li	$a2, 0x85
		la	$v0, dword_A18E0
		sw	$v0, 0x20 + var_10($sp)
		sra	$a3, 31
		mfhi	$t0
		sra	$t0, 5
		jal	sub_86FD8//S_DrawGouraudBar
		subu	$a3, $t0, $a3
		addiu	$a0, $s0, 0x57DC

		loc_3B534:
	lw	$v0, 0x44($a0)
		nop
		andi	$v0, 0x200
		beqz	$v0, loc_3B570
		nop
		lh	$v0, 0x32($a0)
		lhu	$v1, 0x32($a0)
		slti	$v0, 0x800
		beqz	$v0, loc_3B560
		addiu	$v0, $v1, 2
		sh	$v0, 0x32($a0)

		loc_3B560:
	lw	$v0, 0x44($a0)
		li	$v1, 0xFFFFFDFF
		and $v0, $v1
		sw	$v0, 0x44($a0)

		loc_3B570 :
		lw	$ra, 0x20 + var_4($sp)
		lw	$s0, 0x20 + var_8($sp)
		jr	$ra
		addiu	$sp, 0x20
#endif
		UNIMPLEMENTED();
#endif
}

void DrawHealthBar(int flash_state)
{
#if PC_VERSION
	static short old_val = 0;
	short val = CLAMP(lara_item->hit_points, 0, 1000);

	if (old_val != val)
	{
		old_val = val;
		health_bar_timer = 40;
	}

	if (health_bar_timer < 0)
		health_bar_timer = 0;

	if (val <= 250)
	{
		if (BinocularRange)
		{
			if (flash_state)
				S_DrawHealthBar2(val / 10);
			else
				S_DrawHealthBar2(0);
		}
		else
		{
			if (flash_state)
				S_DrawHealthBar(val / 10);
			else
				S_DrawHealthBar(0);
		}
	}

	if (health_bar_timer > 0 
		|| val <= 0 
		|| lara.gun_status == LG_READY && lara.gun_type == WEAPON_FLARE_2 
		|| lara.poisoned >= 256)
	{
		if (BinocularRange || SniperOverlay)
		{
			S_DrawHealthBar2(val / 10);
		}
		else
		{
			S_DrawHealthBar(val / 10);
		}
	}

	if (PoisonFlag)
		PoisonFlag--;
#else
	UNIMPLEMENTED();
#endif
}

void DrawGameInfo(int timed)//3AD68(<), 3B268(!)
{ 
	// line 2, offset 0x3ad68
	int flash_state; // $s0
					 //{ // line 17, offset 0x3adac
	char sbuf[80]; // stack offset -192
				   //} // line 19, offset 0x3adac
	{ // line 53, offset 0x3af50
		char buf[80]; // stack offset -112
		int seconds; // $s3
	} // line 77, offset 0x3b0a0

	sizeof(struct room_info);
#if PC_VERSION
	if (GLOBAL_playing_cutseq == 0 &&
		!bDisableLaraControl &&
		gfGameMode != 1)
	{
		int flash_state = FlashIt();
		DrawHealthBar(flash_state);
		DrawAirBar(flash_state);
		DrawPickups(timed);
		/*if (DashTimer < 120)
			s_drawdas*/
	}
#elif 0


	if (GLOBAL_playing_cutseq != 0 || bDisableLaraControl != 0)
	{
		return;
	}
	
#if DEBUG_VERSION
	sprintf(sbuf, "Room:%d X:%d Y:%d Z:%d", lara_item->room_number, (lara_item->pos.x_pos - room[lara_item->room_number].x) / SECTOR(1), (lara_item->pos.y_pos - room[lara_item->room_number].minfloor) / CLICK, (lara_item->pos.z_pos - room[lara_item->room_number].z) / SECTOR(1));
	PrintString(256, 24, 0, sbuf, 0);
#endif

	//^Not verified for retail/internal split

	if (gfGameMode == 1)
	{
		//loc_3B0A0
		return;
	}

	flash_state = FlashIt();
	DrawHealthBar(flash_state);
	DrawAirBar(flash_state);
	DrawPickups(timed);//Arg does not seem right imo

	if (DashTimer < 120)
	{
		//TODO
	}//loc_3AF14
	

	return;

#else
	//v0 = GLOBAL_playing_cutseq

	if (GLOBAL_playing_cutseq != 0 || bDisableLaraControl)
	{
		return;
	}

	//a1 = ""Room:%d X:%d Y:%d Z:%d"";
	//t1 = lara_item;
	//t3 = room;

	//a2 = lara_item->room_number;
	//v1 = lara_item->pos.y_pos;

	
	//v0 = a2 << 2;
	//v0 += a2;
	//v0 <<= 4;
	//v0 += t3;
	//v0 = &room[lara_item->room_number];
	
	//a3 = room->minfloor;
	//t2 = room->z;
	//v1 -= a3;

	//a3 = lara_item->pos.z_pos;
	//v1 >>= 8;
	// sw	$v1, 0xD8 + var_C8($sp)

	//t0 = lara_item->room_number;
	//v1 = lara_item->pos.x_pos;
	//a3 -= t2;
	//v0 = &room[lara_item->room_number];
	//t0 = room[lara_item->room_number].x
	//a3 >>= 10;
	//v1 -= t0;
	//v1 >>= 10;
	//sw	$v1, 0xD8 + var_C4($sp)

#if DEBUG_VERSION
	sprintf(&sbuf[0], "Room:%d X:%d Y:%d Z:%d", lara_item->room_number, (lara_item->pos.z_pos - room[lara_item->room_number].z) >> 10, (lara_item->pos.y_pos - room->minfloor) >> 8, (lara_item->pos.x_pos - room[lara_item->room_number].x) >> 10);
	PrintString(256, 24, 0, &sbuf[0], 0x8000);
#endif

	if (gfGameMode == 1)
	{
		return;
	}
	
	flash_state = FlashIt();//$s0

	DrawHealthBar(flash_state);
	DrawAirBar(flash_state);
	DrawPickups(0);//? original psx pass nothing.

	//v1 = 0x88880000;
	if (DashTimer < 120)
	{
		//a0 = DashTimer;
		//v1 =  0x88888889;

		//v0 = DashTimer << 1;
		//v0 += DashTimer;
		//v0 <<= 3;
		//v0 += DashTimer;
		//v0 <<= 2;
		//v0 *= v1;
		//t0 = 0x51EB851F;
		//v1 = v0;//mfhi
	}
	//loc_3AF14

#if 0
				 addu	$v1, $v0
				 sra	$v1, 6
				 sra	$v0, 31
				 subu	$v1, $v0
				 sll	$a3, $v1, 5
				 addu	$a3, $v1
				 sll	$a3, 2
				 addu	$a3, $v1
				 mult	$a3, $t0
				 li	$a1, 0x2E
				 li	$a2, 0x85
				 li	$a0, 0x157
				 la	$v0, dword_A1900
				 sra	$a3, 31
				 sw	$v0, 0xD8 + var_C8($sp)
				 mfhi	$t0
				 sra	$t0, 5
				 jal	sub_86FD8
				 subu	$a3, $t0, $a3

				 loc_3AF14 :
			 lhu	$v0, word_A1FE4
				 nop
				 andi	$v0, 0x1000
				 beqz	$v0, loc_3B0A0
				 lui	$v0, 0xB
				 addiu	$s6, $v0, -0x4C24
				 lw	$v1, 0x170($s6)
				 nop
				 beqz	$v1, loc_3B0A0
				 lui	$v0, 1
				 la	$v0, (sub_1A5DC + 3)
				 sltu	$v0, $v1
				 bnez	$v0, loc_3B0A0
				 lui	$s0, 0x8888
				 li	$s2, 0x88888889
				 multu	$v1, $s2
				 mfhi	$s3
				 li	$s0, 0x88888889
				 srl	$s3, 4
				 mult	$s3, $s0
				 addiu	$s4, $sp, 0xD8 + var_70
				 move	$a0, $s4
				 la	$s5, a_2d	 # "%.2d"
				 move	$a1, $s5
				 sra	$v0, $s3, 31
				 mfhi	$s0
				 addu	$s0, $s3
				 sra	$s0, 5
				 subu	$s0, $v0
				 jal	sub_68654
				 move	$a2, $s0
				 li	$a0, 0x28
				 li	$a1, 0x18
				 move	$a2, $zero
				 move	$a3, $s4
				 jal	sub_8DB4C
				 sw	$zero, 0xD8 + var_C8($sp)
				 li	$a0, 0x3C
				 li	$a1, 0x18
				 move	$a2, $zero
				 la	$s1, asc_A0B20	 # ":"
				 move	$a3, $s1
				 jal	sub_8DB4C
				 sw	$zero, 0xD8 + var_C8($sp)
				 move	$a0, $s4
				 move	$a1, $s5
				 sll	$a2, $s0, 4
				 subu	$a2, $s0
				 sll	$a2, 2
				 jal	sub_68654
				 subu	$a2, $s3, $a2
				 li	$a0, 0x42
				 li	$a1, 0x18
				 move	$a2, $zero
				 move	$a3, $s4
				 jal	sub_8DB4C
				 sw	$zero, 0xD8 + var_C8($sp)
				 li	$a0, 0x56
				 li	$a1, 0x18
				 move	$a2, $zero
				 move	$a3, $s1
				 jal	sub_8DB4C
				 sw	$zero, 0xD8 + var_C8($sp)
				 lw	$v1, 0x170($s6)
				 nop
				 multu	$v1, $s2
				 li	$a3, 0x51EB851F
				 mfhi	$s2
				 srl	$s2, 4
				 sll	$v0, $s2, 4
				 subu	$v0, $s2
				 sll	$v0, 1
				 subu	$v1, $v0
				 sll	$a2, $v1, 2
				 addu	$a2, $v1
				 sll	$a2, 2
				 addu	$a2, $v1
				 sll	$a2, 3
				 subu	$a2, $v1
				 sll	$a2, 1
				 mult	$a2, $a3
				 move	$a0, $s4
				 move	$a1, $s5
				 sra	$a2, 31
				 mfhi	$a3
				 sra	$a3, 5
				 jal	sub_68654
				 subu	$a2, $a3, $a2
				 li	$a0, 0x5C
				 li	$a1, 0x18
				 move	$a2, $zero
				 move	$a3, $s4
				 jal	sub_8DB4C
				 sw	$zero, 0xD8 + var_C8($sp)

				 loc_3B0A0:
			 lw	$ra, 0xD8 + var_4($sp)
				 lw	$s6, 0xD8 + var_8($sp)
				 lw	$s5, 0xD8 + var_C($sp)
				 lw	$s4, 0xD8 + var_10($sp)
				 lw	$s3, 0xD8 + var_14($sp)
				 lw	$s2, 0xD8 + var_18($sp)
				 lw	$s1, 0xD8 + var_1C($sp)
				 lw	$s0, 0xD8 + var_20($sp)
				 jr	$ra
				 addiu	$sp, 0xD8
				 # End of function sub_3AD68
#endif

#endif
} // line 79, offset 0x3b0a0

int FlashIt()//3AD2C, 3B22C (F)
{
	static int flash_state;
	static int flash_count;

	if (--flash_count != 0)
	{
		flash_count = 5;
		flash_state ^= 1;
	}

	return flash_state;
}



