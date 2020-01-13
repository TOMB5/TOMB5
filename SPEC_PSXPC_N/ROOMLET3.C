#include "ROOMLET3.H"

#include "3D_OBJ.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "LOAD_LEV.H"

#if GTE
#include "GTE.H"
#endif

void DrawRoomletList()
{
#if !BETA_VERSION
	sub_158(0, &room[camera.pos.room_number]);
#else
	sub_158(camera_underwater, &room[camera.pos.room_number]);
#endif
}

void sub_158(long camera_underwater, struct room_info* room)
{
	short* s4 = 0;
	struct room_info* fp = NULL;
	int t7 = 0;
	int t6 = 0;
	int t8 = 0;
	int t0 = 0;
	int t1 = 0;
	int t2 = 0;
	int t3 = 0;
	int t4 = 0;
	int t5 = 0;

	//ctc2    $a0, $21
	//mtc2    $a1, $20

	//s0 = number_draw_rooms
	//s3 = RoomBBoxes
	s4 = &draw_rooms[0];
	//t2 = wibble & 0xFC
	//s2 = &tsv_buffer[0]

	//ctc2    $t2, $20
	//t0 = *draw_rooms++
	//t0 <<= 4;
	//at = t0 << 2;
	//t1 = room
	//t0 += at
	fp = &room[*s4++];
	//t0 = fp.MeshEffect
	//t1 = &WaterTable[0][fp.MeshEffect]

	((unsigned int*)&tsv_buffer)[0] = (unsigned long)fp;
	((unsigned int*)&tsv_buffer)[1] = (unsigned long)&WaterTable[0][fp->MeshEffect];
	
	//s1 = fp.data
	//s5 = room
	t0 = fp->x;
	t1 = fp->y;
	t2 = fp->z;

	//t3 = room.x
	//t4 = room.y
	//t5 = room.z

	t6 = room->x - fp->x;
	t7 = room->y - fp->y;
	t8 = room->z - fp->z;

	if (t6 > -0x7BFF && t6 < 0x7C00 &&
		t7 > -0x7BFF && t7 < 0x7C00 &&
		t8 > -0x7BFF && t8 < 0x7C00)
	{
		t7 = fp->minfloor - fp->y;
		t6 = ((((fp->x_size - 2) << 10) + fp->z) - room->z);
		t8 = ((((fp->y_size - 2) << 10) + fp->x) - room->x);

		if (t6 > -0x7BFF && t6 < 0x7C00 &&
			t7 > -0x7BFF && t7 < 0x7C00 &&
			t8 > -0x7BFF && t8 < 0x7C00)
		{
			t7 = room->minfloor - fp->y;
			t6 = (((room->x_size - 2) << 10) + room->x) - fp->x;
			t8 = (((room->y_size - 2) << 10) + room->z) - fp->z;

			if (t6 > -0x7BFF && t6 < 0x7C00 &&
				t7 > -0x7BFF && t7 < 0x7C00 &&
				t8 > -0x7BFF && t8 < 0x7C00)
			{
				t6 = fp->x - room->x;
				t7 = fp->y - room->y;
				t8 = fp->z - room->z;

				t0 = room->x;
				t1 = room->y;
				t2 = room->z;
			}
			else
			{
				//loc_320
				t6 = 0;
				t7 = 0;
				t8 = 0;
			}
		}
		else
		{
			//loc_320
			t6 = 0;
			t7 = 0;
			t8 = 0;
		}
	}
	else
	{
		//loc_320
		t6 = 0;
		t7 = 0;
		t8 = 0;
	}

	//loc_32C
	((unsigned int*)&tsv_buffer[0])[5] = t6;
	((unsigned int*)&tsv_buffer[0])[6] = t7;
	((unsigned int*)&tsv_buffer[0])[7] = t8;

	//t3 = MatrixStack[0].tx
	//t4 = MatrixStack[0].ty
	//t5 = MatrixStack[0].tz

	t0 -= MatrixStack[0].tx;
	t1 -= MatrixStack[0].ty;
	t2 -= MatrixStack[0].tz;

	t3 = (ABS(t0) >> 15) & 0x7FFF;
	t4 = (ABS(t1) >> 15) & 0x7FFF;
	t5 = (ABS(t2) >> 15) & 0x7FFF;

	t3 = 1;
	t4 = 2;
	t5 = 3;

#if GTE
	long long SSX, SSY, SSZ;
	_MVMVA_FUNC((short)t3, (short)t4, (short)t5, gteR);
#endif

	t3 = (Matrix->m00 * t3) + (Matrix->m01 * t4) + (Matrix->m02 * t5);
	t4 = (Matrix->m10 * t3) + (Matrix->m11 * t4) + (Matrix->m12 * t5);
	t5 = (Matrix->m20 * t3) + (Matrix->m21 * t4) + (Matrix->m22 * t5);

#if 0
		mtc2    $t3, $9
		mtc2    $t4, $10
		mtc2    $t5, $11
		nop
		cop2    0x41E012
		mfc2    $t3, $25
		mfc2    $t4, $26
		mtc2    $t0, $9
#endif

#if 0
		mtc2    $t1, $10
		mtc2    $t2, $11
		mfc2    $t5, $27
		cop2    0x49E012
		bgez    $t3, loc_400
		sll     $t0, $t3, 3
		negu    $t3, $t3
		sll     $t3, 3
		negu    $t0, $t3

		loc_400 : # CODE XREF : sub_158 + 294↑j
		bgez    $t4, loc_414
		sll     $t1, $t4, 3
		negu    $t4, $t4
		sll     $t4, 3
		negu    $t1, $t4

		loc_414 : # CODE XREF : sub_158:loc_400↑j
		bgez    $t5, loc_428
		sll     $t2, $t5, 3
		negu    $t5, $t5
		sll     $t5, 3
		negu    $t2, $t5

		loc_428 : # CODE XREF : sub_158:loc_414↑j
		mfc2    $t3, $25
		mfc2    $t4, $26
		mfc2    $t5, $27
		addu    $t0, $t3
		addu    $t1, $t4
		addu    $t2, $t5
		ctc2    $t0, $5
		ctc2    $t1, $6
		ctc2    $t2, $7
		sw      $t0, 8($s2)
		sw      $t1, 0xC($s2)
		sw      $t2, 0x10($s2)
		addi    $s2, 0x20  # ' '
		lw      $s6, 0($s1)
		addi    $s1, 4
		lw      $t0, 0x38 + arg_0($fp)
		lw      $t2, 0x38 + arg_4($fp)
		srl     $t1, $t0, 16
		andi    $t0, 0xFFFF
		srl     $t3, $t2, 16
		andi    $t2, 0xFFFF
		addi    $t1, 1
		addi    $t3, 1
		ctc2    $t0, $8
		ctc2    $t1, $9
		ctc2    $t2, $10
		ctc2    $t3, $11
		ctc2    $t6, $13
		move    $fp, $t7
		move    $s7, $t8

		loc_4A0 : # CODE XREF : sub_158:loc_628↓j
		beqz    $s6, loc_630
		lw      $a0, 0($s1)
		addi    $s1, 4
		lw      $t3, 0($a0)
		sw      $a0, 0($s2)
		cfc2    $t6, $13
		sll     $t0, $t3, 3
		andi    $t0, 0xFFF8
		add     $t0, $s3
		lh      $t1, 4($t0)
		lh      $at, 0($t0)
		lh      $t0, 2($t0)
		add     $at, $t6
		andi    $at, 0xFFFF
		add     $t0, $fp
		add     $t1, $s7
		sll     $t0, 16
		or $t0, $at
		srl     $t3, 13
		andi    $t3, 0xFFF8
		add     $t3, $s3
		lh      $at, 0($t3)
		lh      $t2, 2($t3)
		lh      $t3, 4($t3)
		add     $at, $t6
		andi    $at, 0xFFFF
		add     $t2, $fp
		add     $t3, $s7
		sll     $t2, 16
		or $t2, $at
		mtc2    $t0, $0
		mtc2    $t1, $1
		mtc2    $t2, $2
		mtc2    $t1, $3
		mtc2    $t2, $4
		mtc2    $t3, $5
		andi    $t4, $t0, 0xFFFF
		cop2    0x280030
		andi    $t6, $t2, 0xFFFF
		lui     $t7, 0xFFFF
		and $t5, $t0, $t7
		and     $t7, $t2
		or $t4, $t7
		or $t5, $t6
		li      $a0, 0x800
		li      $a1, 0xFFFFF800
		li      $a2, 0x800
		li      $a3, 0xFFFFF800
		move    $s5, $zero
		mfc2    $t1, $16
		mfc2    $t6, $13
		mfc2    $t7, $17
		mfc2    $t8, $14
		mfc2    $t9, $18
		mtc2    $t4, $0
		mtc2    $t5, $2
		mtc2    $t0, $4
		mfc2    $t0, $12
		cop2    0x280030
		jal     sub_50
		move    $v0, $zero
		mfc2    $t0, $12
		mfc2    $t1, $16
		mfc2    $t6, $13
		mfc2    $t7, $17
		mfc2    $t8, $14
		mtc2    $t3, $1
		mtc2    $t3, $3
		mfc2    $t9, $18
		cop2    0x280030
		jal     sub_50
		nop
		mfc2    $t0, $12
		mfc2    $t1, $16
		mfc2    $t6, $13
		mfc2    $t7, $17
		move    $t8, $t6
		jal     sub_50
		move    $t9, $t7
		sltiu   $at, $v0, 9
		beqz    $at, loc_628
		sltiu   $at, $s5, 9
		beqz    $at, loc_628
		nop
		cfc2    $t0, $8
		cfc2    $t1, $9
		cfc2    $t2, $10
		cfc2    $t3, $11
		slt     $at, $a1, $t0
		bnez    $at, loc_628
		slt     $at, $a0, $t1
		beqz    $at, loc_628
		slt     $at, $a3, $t2
		bnez    $at, loc_628
		slt     $at, $a2, $t3
		beqz    $at, loc_628
		nop
		addi    $s2, 4

		loc_628:                                 # CODE XREF : sub_158 + 488↑j
		# sub_158 + 490↑j ...
		j       loc_4A0
		addi    $s6, -1
# ---------------------------------------------------------------------------

		loc_630:                                 # CODE XREF : sub_158:loc_4A0↑j
		sw      $zero, 0($s2)
		addi    $s0, -1
		bnez    $s0, loc_1B0
		addi    $s2, 4
		sw      $zero, 0($s2)
		li      $s2, 0x1ECDC0

		loc_64C:                                 # CODE XREF : sub_158 + 58C↓j
		lw      $a1, 0($s2)
		lwc2    $20, 4($s2)
		beqz    $a1, loc_17B4
		addi    $s2, 0x20  # ' '
		lw      $t0, -0x18($s2)
		lw      $t1, -0x14($s2)
		lw      $t2, -0x10($s2)
		ctc2    $t0, $5
		ctc2    $t1, $6
		ctc2    $t2, $7
		lw      $t0, 0x14($a1)
		lw      $t1, 0x18($a1)
		lw      $t2, 0x1C($a1)
		sw      $t0, 0x38 + var_C($sp)
		sw      $t1, 0x38 + var_8($sp)
		sw      $t2, 0x34($sp)
		lw      $t0, 0x38($a1)
		lw      $t2, 0x3C($a1)
		lui     $at, 0xFFFF
		and $t1, $t0, $at
		and     $t3, $t2, $at
		lui     $at, 1
		add     $t1, $at
		add     $t3, $at
		sll     $t0, 16
		sll     $t2, 16
		ctc2    $t0, $8
		ctc2    $t1, $9
		ctc2    $t2, $10
		ctc2    $t3, $11
		lw      $t0, -0xC($s2)
		lw      $t1, -8($s2)
		lw      $t2, -4($s2)
		ctc2    $t0, $13
		ctc2    $t1, $14
		ctc2    $t2, $15

		loc_6DC : # CODE XREF : sub_158 + 8A4↓j
		lw      $a0, 0($s2)
		addi    $s2, 4
		beqz    $a0, loc_64C
		lw      $t5, 0($a0)
		move    $t6, $zero
		sll     $t0, $t5, 3
		andi    $t0, 0xFFF8
		add     $t0, $s3
		lh      $t2, 4($t0)
		lw      $t0, 0($t0)
		srl     $t5, 13
		andi    $t5, 0xFFF8
		add     $t5, $s3
		lw      $t3, 0($t5)
		lh      $t5, 4($t5)
		srl     $t1, $t0, 16
		andi    $t0, 0xFFFF
		srl     $t4, $t3, 16
		andi    $t3, 0xFFFF
		lw      $t7, 0x38 + var_C($sp)
		lw      $t8, 0x38 + var_8($sp)
		lw      $t9, 0x34($sp)
		add     $t0, $t7
		add     $t1, $t8
		add     $t2, $t9
		add     $t3, $t7
		add     $t4, $t8
		add     $t5, $t9
		li      $t7, 1
		lui     $t8, 0x1F80
		move    $t9, $zero
		addiu   $s1, $gp, 0x25B8
		li      $a3, 0x20  # ' '

		loc_760:                                 # CODE XREF : sub_158:loc_7EC↓j
		sb      $zero, 0x30C($s1)
		lb      $at, 0xC($s1)
		addi    $a3, -1
		beqz    $at, loc_7EC
		lh      $a2, 0x10($s1)
		lw      $v0, 0($s1)
		srl     $a2, 1
		add     $v1, $v0, $a2
		sub     $v0, $a2
		slt     $at, $v1, $t0
		bnez    $at, loc_7E8
		slt     $at, $v0, $t3
		lw      $v0, 4($s1)
		beqz    $at, loc_7E8
		add     $v1, $v0, $a2
		sub     $v0, $a2
		slt     $at, $v1, $t1
		bnez    $at, loc_7E8
		slt     $at, $v0, $t4
		lw      $v0, 8($s1)
		beqz    $at, loc_7E8
		add     $v1, $v0, $a2
		sub     $v0, $a2
		slt     $at, $v1, $t2
		bnez    $at, loc_7E8
		slt     $at, $v0, $t5
		beqz    $at, loc_7E8
		srl     $a2, 7
		sb      $t7, 0x12($s1)
		add     $t9, $a2
		sw      $s1, 0($t8)
		addi    $t8, 4
		j       loc_7EC
		addi    $t6, 1
# ---------------------------------------------------------------------------

		loc_7E8:                                 # CODE XREF : sub_158 + 630↑j
		# sub_158 + 63C↑j ...
		sb      $zero, 0x12($s1)

		loc_7EC:                                 # CODE XREF : sub_158 + 614↑j
		# sub_158 + 688↑j
		bnez    $a3, loc_760
		addi    $s1, 0x18
		addiu   $t8, $gp, 0x28B8

		loc_7F8:                                 # CODE XREF : sub_158:loc_810↓j
		# sub_158 + 810↓j
		slti    $at, $t9, 0x60
		bnez    $at, loc_970
		lui     $t7, 0xFFF
		move    $t3, $zero
		lui     $s1, 0x1F80
		move    $t5, $t6

		loc_810 : # CODE XREF : sub_158 + 6C4↓j
		beqz    $t5, loc_7F8
		lw      $a2, 0($s1)
		addi    $s1, 4
		beqz    $a2, loc_810
		addi    $t5, -1
		move    $a1, $s1
		addi    $t4, $t5, -1

		loc_82C:                                 # CODE XREF : sub_158 + 6E0↓j
		# sub_158 + 708↓j ...
		beqz    $t4, loc_8BC
		lw      $a3, 0($a1)
		addi    $a1, 4
		beqz    $a3, loc_82C
		addi    $t4, -1
		lw      $t0, 0($a2)
		lw      $at, 0($a3)
		lw      $t1, 4($a2)
		sub     $t0, $at
		bgtz    $t0, loc_85C
		lw      $at, 4($a3)
		neg     $t0, $t0

		loc_85C : # CODE XREF : sub_158 + 6F8↑j
		sltiu   $s4, $t0, 0x800
		beqz    $s4, loc_82C
		sub     $t1, $at
		lw      $ra, 8($a2)
		bgtz    $t1, loc_878
		lw      $at, 8($a3)
		neg     $t1, $t1

		loc_878 : # CODE XREF : sub_158 + 714↑j
		sltiu   $s4, $t1, 0x800
		beqz    $s4, loc_82C
		sub     $ra, $at
		bgtz    $ra, loc_890
		add     $t0, $t1
		neg     $ra, $ra

		loc_890 : # CODE XREF : sub_158 + 72C↑j
		sltiu   $s4, $ra, 0x800
		beqz    $s4, loc_82C
		add     $t0, $ra
		slt     $at, $t0, $t7
		beqz    $at, loc_82C
		move    $t2, $a2
		move    $t7, $t0
		addi    $v0, $s1, -4
		addi    $v1, $a1, -4
		j       loc_82C
		move    $t3, $a3
# ---------------------------------------------------------------------------

		loc_8BC:                                 # CODE XREF : sub_158:loc_82C↑j
		beqz    $t3, loc_970
		lh      $t0, 0x10($t2)
		lh      $t1, 0x10($t3)
		sw      $zero, 0($v1)
		slt     $at, $t0, $t1
		bnez    $at, loc_8E8
		sw      $t8, 0($v0)
		sh      $t0, 0x10($t8)
		srl     $t1, 8
		j       loc_8F4
		sub     $t9, $t1
# ---------------------------------------------------------------------------

		loc_8E8:                                 # CODE XREF : sub_158 + 778↑j
		sh      $t1, 0x10($t8)
		srl     $t0, 8
		sub     $t9, $t0

		loc_8F4 : # CODE XREF : sub_158 + 788↑j
		lw      $t0, 0xC($t2)
		lw      $t1, 0xC($t3)
		li      $t7, 0x7C7C7C00
		srl     $t0, 1
		srl     $t1, 1
		and $t0, $t7
		and     $t1, $t7
		addu    $t0, $t1
		ori     $t0, 1
		sw      $t0, 0xC($t8)
		sb      $t0, 0x12($t8)
		lw      $v0, 0($t2)
		lw      $v1, 0($t3)
		lw      $t0, 4($t2)
		lw      $t1, 4($t3)
		add     $v0, $v1
		srl     $v0, 1
		add     $t0, $t1
		sra     $t0, 1
		sw      $v0, 0($t8)
		lw      $v0, 8($t2)
		lw      $v1, 8($t3)
		sw      $t0, 4($t8)
		add     $v0, $v1
		srl     $v0, 1
		sw      $v0, 8($t8)
		sb      $zero, 0x12($t2)
		sb      $zero, 0x12($t3)
		j       loc_7F8
		addi    $t8, 0x18
# ---------------------------------------------------------------------------

		loc_970:                                 # CODE XREF : sub_158 + 6A4↑j
		# sub_158 : loc_8BC↑j
		addiu   $s1, $gp, 0x25B8
		lui     $a1, 0x1F80
		addi    $a1, 0x300
		li      $v1, 0xF
		li      $v0, 0x40  # '@'

		loc_984 : # CODE XREF : sub_158 + 88C↓j
		lb      $at, 0xC($s1)
		lb      $t0, 0x12($s1)
		beqz    $at, loc_9E0
		lw      $t1, 4($s1)
		beqz    $t0, loc_9E0
		lw      $t0, 0($s1)
		lw      $t2, 8($s1)
		srl     $t0, 7
		sw      $t0, 0($a1)
		sra     $t1, 7
		sw      $t1, 4($a1)
		srl     $t2, 7
		sw      $t2, 8($a1)
		lw      $t1, 0xC($s1)
		lh      $t0, 0x10($s1)
		srl     $t1, 8
		sll     $t1, 8
		srl     $t0, 8
		or $t1, $t0
		sw      $t1, 0xC($a1)
		addi    $a1, 0x10
		addi    $v1, -1
		beqz    $v1, loc_9EC

		loc_9E0 : # CODE XREF : sub_158 + 834↑j
		# sub_158 + 83C↑j
		addi    $v0, -1
		bnez    $v0, loc_984
		addi    $s1, 0x18

		loc_9EC:                                 # CODE XREF : sub_158 + 884↑j
		sw      $zero, 0xC($a1)
		jal     sub_10F8
		addiu   $a1, $gp, 0x363C
		addiu   $a1, $gp, 0x363C
		j       loc_6DC
		sw      $a3, 8($a1)
		# End of function sub_158


# =============== S U B R O U T I N E =======================================


		sub_A04:                                 # CODE XREF : sub_10F8 + 3E4↓p
		# sub_10F8 + 58C↓p
		lui     $s2, 0xF8
		srl     $t5, $s4, 7
		and $t5, $s2
		srl     $t6, $s4, 10
		andi    $t6, 0xF800
		srl     $fp, $s4, 13
		andi    $fp, 0xF8
		or $fp, $t5
		or $fp, $t6
		srl     $t5, $t8, 24
		ori     $t5, 0x40  # '@'
		sll     $t5, 24
		or $fp, $t5
		srl     $t5, $s5, 7
		and $t5, $s2
		srl     $t6, $s5, 10
		andi    $t6, 0xF800
		srl     $gp, $s5, 13
		andi    $gp, 0xF8
		or $gp, $t5
		or $gp, $t6
		srl     $t5, $s6, 7
		and $t5, $s2
		srl     $t6, $s6, 10
		andi    $t6, 0xF800
		srl     $s3, $s6, 13
		andi    $s3, 0xF8
		or $s3, $t5
		jr      $ra
		or $s3, $t6
#endif
}