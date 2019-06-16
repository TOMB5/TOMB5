#include "ROOMLETB.H"

#include "3D_OBJ.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "EFFECT2.H"
#include "SPECIFIC.H"
#include "STYPES.H"
#include "MISC.H"
#include "LOAD_LEV.H"
#include "GTEREG.H"
#include "ROOMLOAD.H"

void DrawRoomsAsm()//0x1BC380
{
	DrawRoomletListAsm(0, &room[camera.pos.room_number]);
}

#ifndef USE_ASM
void DrawRoomletListAsmBinocular(long underwater, struct room_info* r)//roomletb
{
	int s0;
	struct SVECTOR* s3;
	short* s4;
	int t2;
	int* s2;
	int t0;
	int t6;
	int t7;
	int t8;
	int t1;
	int t3;
	int t4;
	int t5;
	int s6;
	int* s1;
	int fpp;
	int s7;
	int* a0;
	SVECTOR* t00;
	struct room_info* fp;
	struct WATERTAB* t11;
	struct room_info* s5;
	int at;
	int t9;

	RFC = underwater;
	RGB0 = (unsigned long)r;

	s0 = number_draw_rooms;
	s3 = &RoomBBoxes[0];
	s4 = &draw_rooms[0];
	LB3 = wibble & 0xFC;
	s2 = (int*)&tsv_buffer[0];

	//loc_74C88
	//t0 = *s4++;
	fp = &room[*s4++];
	
	t0 = fp->MeshEffect;
	t11 = &WaterTable[0][fp->MeshEffect];

	s2[0] = (unsigned long)fp;
	s2[1] = (unsigned long)t11;

	s1 = (int*)fp->data;
	//t0 = room.x (fp)
	//t1 = room.y (fp)
	s5 = (struct room_info*)RGB0;
	//t2 = room.z(fp)
	//t3 = r->x
	//t4 = r->y
	//t5 = r->z

	t6 = r->x - fp->x;
	t7 = r->y - fp->y;
	t8 = r->z - fp->z;

	if (t6 > -31745 && t6 < 31744 &&
		t7 > -31745 && t6 < 37144 &&
		t8 > -31745 && t8 < 37144)
	{
		t7 = fp->minfloor - r->y;
		t6 = (((fp->x_size - 2) << 10) + fp->z) - r->z;
		t8 = (((fp->y_size - 2) << 10) + fp->x) - r->x;

		if (t6 > -31745 && t6 < 37144 &&
			t7 > -31745 && t7 < 37144 &&
			t8 > -31745 && t8 < 37144)
		{
			t7 = s5->minfloor - fp->y;
			t6 = (((s5->x_size - 2) << 10) + r->x) - fp->x;
			t8 = (((s5->y_size - 2) << 10) + r->z) - fp->z;

			if (t6 > -31745 && t6 < 37144 &&
				t7 > -31745 && t7 < 37144 &&
				t8 > -31745 && t8 < 37144)
			{
				t6 = fp->x - r->x;
				t7 = fp->y - r->y;
				t8 = fp->z - r->z;

				t0 = r->x;
				t1 = r->y;
				t2 = r->z;
			}
			else
			{
				//loc_74DF8
				t6 = 0;
				t7 = 0;
				t8 = 0;
			}
		}
		else
		{
			//loc_74DF8
			t6 = 0;
			t7 = 0;
			t8 = 0;
		}
	}
	else
	{
		//loc_74DF8
		t6 = 0;
		t7 = 0;
		t8 = 0;
	}

	//loc_74E04
	s2[5] = (int)t6;
	s2[6] = (int)t7;
	s2[7] = (int)t8;

	t3 = ((int*)MatrixStack)[5];
	t4 = ((int*)MatrixStack)[6];
	t5 = ((int*)MatrixStack)[7];

	t0 -= t3;
	t1 -= t4;
	t2 -= t5;

	t3 = t0 >> 15;

	if (t0 < 0)
	{
		t0 = -t0;
		t3 = t0 >> 15;
		t0 &= 0x7FFF;
		t3 = -t3;
		t0 = -t0;
	}
	else
	{
		//loc_74E48
		t0 &= 0x7FFF;
	}

	t4 = t1 >> 15;
	if (t1 < 0)
	{
		t1 = -t1;
		t4 = t1 >> 15;
		t1 &= 0x7FFF;
		t4 = -t4;
		t1 = -t1;
	}
	else
	{
		//loc_74E6C
		t1 &= 0x7FFF;
	}

	t5 = t2 >> 15;

	if (t2 < 0)
	{
		t2 = -t2;
		t5 = t2 >> 15;
		t2 &= 0x7FFF;
		t5 = -t5;
		t2 = -t2;
	}
	else
	{
		t2 &= 0x7FFF;
	}

	//loc_74E94
	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = t0;
	IR2 = t1;
	IR3 = t2;

	docop2(0x49E012);

	t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}
	//loc_74ED8
	t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}//loc_74EEC

	t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}
	//loc_74F00
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;

	s2[2] = t0;
	s2[3] = t1;
	s2[4] = t2;

	s2 += 8;
	s6 = *s1++;//room.data?

	t0 = *(int*)&fp->left;//left & right
	t2 = *(int*)&fp->top;//top & bottom

	t1 = t0 >> 16;
	t0 &= 0xFFFF;
	t3 = t2 >> 16;
	t2 &= 0xFFFF;

	t1++;
	t3++;

	L11 = t0;
	L13 = t1;
	L22 = t2;
	L31 = t3;
	RBK = t6;

	fpp = t7;
	s7 = t8;
	//loc_74F78
	
	if (s6 != 0)
	{
		a0 = (int*)*s1++;
		t3 = *a0;
		s2[0] = (int)a0;
		t6 = RBK;
		t00 = &s3[t3 & 0xFFF8];
		t1 = t00->vz;
		at = t00->vx;
		t0 = t00->vy;

		at = (at + t6) & 0xFFFF;
		t0 += fpp;
		t1 += s7;
		t0 <<= 16;
		t0 |= at;

		SVECTOR* t33;///@CHECKME result of t3 :S

		t3 >>= 13;
		t3 &= 0xFFF8;
		t33 = &s3[t3];

		at = t33->vx;
		t2 = t33->vy;
		t3 = t33->vz;

		at += t6;
		at &= 0xFFFF;

		t2 += fpp;
		t3 += s7;
		t2 <<= 16;
		t2 |= at;

		VX0 = t0 & 0xFFFF;
		VY0 = (t0 >> 16) & 0xFFFF;
		VZ0 = t1;

		VX1 = t2 & 0xFFFF;
		VY1 = (t2 >> 16) & 0xFFFF;
		VZ1 = t1;

		VX2 = t2 & 0xFFFF;
		VY2 = (t2 >> 16) & 0xFFFF;
		VZ2 = t3;

		t4 = t0 & 0xFFFF;

		docop2(0x280030);
		t6 = t7 & 0xFFFF;
		t7 = 0xFFFF0000;
		t5 = t0 & t7;
		t7 &= t2;
		t4 |= t7;
		t5 |= t6;

		int a00, a11, a22, a33;

		a00 = 0x800;
		a11 = 0xFFFFF800;
		a22 = 0x800;
		a33 = 0xFFFFF800;

		s5 = 0;

		t1 = SZ1;
		t6 = SXY1;
		t7 = SZ2;
		t8 = SXY2;
		t9 = SZ3;

		VX0 = t4 & 0xFFFF;
		VY0 = (t4 >> 16) & 0xFFFF;

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;

		VX2 = t0 & 0xFFFF;
		VY2 = (t0 >> 16) & 0xFFFF;

		t0 = SXY0;

		docop2(0x280030);
		//v0 = 0
		//GetBounds();

	}//loc_75108

#if 0
	mfc2    t0, r12
	mfc2    t1, r17
	mfc2    t6, r13
	mfc2    t7, r18
	mfc2    t8, r14
	mtc2    t3, r1
	mtc2    t3, r3
	mfc2    t9, r19
	nop
	nop
	cop2    0x280030
	jal     GetBounds
	nop
	mfc2    t0, r12
	mfc2    t1, r17
	mfc2    t6, r13
	mfc2    t7, r18
	move    t8, t6
	jal     GetBounds
	move    t9, t7
	sltiu   at, v0, 9
	beqz    at, loc_75100
	sltiu   at, s5, 9
	beqz    at, loc_75100
	nop
	cfc2    t0, r8
	cfc2    t1, r9
	cfc2    t2, r10
	cfc2    t3, r11
	slt     at, a1, t0
	bnez    at, loc_75100
	slt     at, a0, t1
	beqz    at, loc_75100
	slt     at, a3, t2
	bnez    at, loc_75100
	slt     at, a2, t3
	beqz    at, loc_75100
	nop
	addi    s2, 4

	loc_75100:
	j       loc_74F78
	addi    s6, -1

	loc_75108:
	sw      zero, 0(s2)
	addi    s0, -1
	bnez    s0, loc_74C88
	addi    s2, 4
	sw      zero, 0(s2)
	la      s2, tsv_buffer

	loc_75124:
	lw      a1, 0(s2)
	lwc2    r20, 4(s2)
	beqz    a1, loc_76420
	addi    s2, 0x20
	lw      t0, -0x18(s2)
	lw      t1, -0x14(s2)
	lw      t2, -0x10(s2)
	ctc2    t0, r5
	ctc2    t1, r6
	ctc2    t2, r7
	lw      t0, 0x14(a1)
	lw      t1, 0x18(a1)
	lw      t2, 0x1C(a1)
	sw      t0, 0x38-0xC(sp)
	sw      t1, 0x38-0x8(sp)
	sw      t2, 0x34(sp)
	lw      t0, 0x38(a1)
	lw      t2, 0x3C(a1)
	lui     at, 0xFFFF
	and     t1, t0, at
	and     t3, t2, at
	lui     at, 1
	add     t1, at
	add     t3, at
	sll     t0, 16
	sll     t2, 16
	ctc2    t0, r8
	ctc2    t1, r9
	ctc2    t2, r10
	ctc2    t3, r11
	lw      t0, -0xC(s2)
	lw      t1, -8(s2)
	lw      t2, -4(s2)
	ctc2    t0, r13
	ctc2    t1, r14
	ctc2    t2, r15

	loc_751B4:
	lw      a0, 0(s2)
	addi    s2, 4
	beqz    a0, loc_75124
	lw      t5, 0(a0)
	move    t6, zero
	sll     t0, t5, 3
	andi    t0, 0xFFF8
	add     t0, s3
	lh      t2, 4(t0)
	lw      t0, 0(t0)
	srl     t5, 13
	andi    t5, 0xFFF8
	add     t5, s3
	lw      t3, 0(t5)
	lh      t5, 4(t5)
	srl     t1, t0, 16
	andi    t0, 0xFFFF
	srl     t4, t3, 16
	andi    t3, 0xFFFF
	lw      t7, 0x38-0xC(sp)
	lw      t8, 0x38-0x8(sp)
	lw      t9, 0x34(sp)
	add     t0, t7
	add     t1, t8
	add     t2, t9
	add     t3, t7
	add     t4, t8
	add     t5, t9
	li      t7, 1
	lui     t8, 0x1F80
	move    t9, zero
	la	    s1, dynamics
	;addiu   s1, gp, dynamics-GP_ADDR
	li      a3, 0x20

	loc_75238:
	sb      zero, 0x30C(s1)
	lb      at, 0xC(s1)
	addi    a3, -1
	beqz    at, loc_752C4
	lh      a2, 0x10(s1)
	lw      v0, 0(s1)
	srl     a2, 1
	add     v1, v0, a2
	sub     v0, a2
	slt     at, v1, t0
	bnez    at, loc_752C0
	slt     at, v0, t3
	lw      v0, 4(s1)
	beqz    at, loc_752C0
	add     v1, v0, a2
	sub     v0, a2
	slt     at, v1, t1
	bnez    at, loc_752C0
	slt     at, v0, t4
	lw      v0, 8(s1)
	beqz    at, loc_752C0
	add     v1, v0, a2
	sub     v0, a2
	slt     at, v1, t2
	bnez    at, loc_752C0
	slt     at, v0, t5
	beqz    at, loc_752C0
	srl     a2, 7
	sb      t7, 0x12(s1)
	add     t9, a2
	sw      s1, 0(t8)
	addi    t8, 4
	j       loc_752C4
	addi    t6, 1

	loc_752C0:
	sb      zero, 0x12(s1)

	loc_752C4:
	bnez    a3, loc_75238
	addi    s1, 0x18
	la		t8, dynamics+0x300
	;addiu   t8, gp, dynamics+0x300-GP_ADDR

	loc_752D0:
	slti    at, t9, 0x60
	bnez    at, loc_75448
	lui     t7, 0xFFF
	move    t3, zero
	lui     s1, 0x1F80
	move    t5, t6

	loc_752E8:
	beqz    t5, loc_752D0
	lw      a2, 0(s1)
	addi    s1, 4
	beqz    a2, loc_752E8
	addi    t5, -1
	move    a1, s1
	addi    t4, t5, -1

	loc_75304:
	beqz    t4, loc_75394
	lw      a3, 0(a1)
	addi    a1, 4
	beqz    a3, loc_75304
	addi    t4, -1
	lw      t0, 0(a2)
	lw      at, 0(a3)
	lw      t1, 4(a2)
	sub     t0, at
	bgtz    t0, loc_75334
	lw      at, 4(a3)
	neg     t0, t0

	loc_75334:
	sltiu   s4, t0, 0x800
	beqz    s4, loc_75304
	sub     t1, at
	lw      ra, 8(a2)
	bgtz    t1, loc_75350
	lw      at, 8(a3)
	neg     t1, t1

	loc_75350:
	sltiu   s4, t1, 0x800
	beqz    s4, loc_75304
	sub     ra, at
	bgtz    ra, loc_75368
	add     t0, t1
	neg     ra, ra

	loc_75368:
	sltiu   s4, ra, 0x800
	beqz    s4, loc_75304
	add     t0, ra
	slt     at, t0, t7
	beqz    at, loc_75304
	move    t2, a2
	move    t7, t0
	addi    v0, s1, -4
	addi    v1, a1, -4
	j       loc_75304
	move    t3, a3

	loc_75394:
	beqz    t3, loc_75448
	lh      t0, 0x10(t2)
	lh      t1, 0x10(t3)
	sw      zero, 0(v1)
	slt     at, t0, t1
	bnez    at, loc_753C0
	sw      t8, 0(v0)
	sh      t0, 0x10(t8)
	srl     t1, 8
	j       loc_753CC
	sub     t9, t1

	loc_753C0:
	sh      t1, 0x10(t8)
	srl     t0, 8
	sub     t9, t0

	loc_753CC:
	lw      t0, 0xC(t2)
	lw      t1, 0xC(t3)
	lui     t7, 0x7C7C
	ori     t7, 0x7C00
	srl     t0, 1
	srl     t1, 1
	and     t0, t7
	and     t1, t7
	addu    t0, t1
	ori     t0, 1
	sw      t0, 0xC(t8)
	sb      t0, 0x12(t8)
	lw      v0, 0(t2)
	lw      v1, 0(t3)
	lw      t0, 4(t2)
	lw      t1, 4(t3)
	add     v0, v1
	srl     v0, 1
	add     t0, t1
	sra     t0, 1
	sw      v0, 0(t8)
	lw      v0, 8(t2)
	lw      v1, 8(t3)
	sw      t0, 4(t8)
	add     v0, v1
	srl     v0, 1
	sw      v0, 8(t8)
	sb      zero, 0x12(t2)
	sb      zero, 0x12(t3)
	j       loc_752D0
	addi    t8, 0x18

	loc_75448:
	la		s1, dynamics
	;addiu   s1, gp, dynamics-GP_ADDR
	lui     a1, 0x1F80
	addi    a1, 0x300
	li      v1, 0xF
	li      v0, 0x40

	loc_7545C:
	lb      at, 0xC(s1)
	lb      t0, 0x12(s1)
	beqz    at, loc_754B8
	lw      t1, 4(s1)
	beqz    t0, loc_754B8
	lw      t0, 0(s1)
	lw      t2, 8(s1)
	srl     t0, 7
	sw      t0, 0(a1)
	sra     t1, 7
	sw      t1, 4(a1)
	srl     t2, 7
	sw      t2, 8(a1)
	lw      t1, 0xC(s1)
	lh      t0, 0x10(s1)
	srl     t1, 8
	sll     t1, 8
	srl     t0, 8
	or      t1, t0
	sw      t1, 0xC(a1)
	addi    a1, 0x10
	addi    v1, -1
	beqz    v1, loc_754C4

	loc_754B8:
	addi    v0, -1
	bnez    v0, loc_7545C
	addi    s1, 0x18

	loc_754C4:
	sw      zero, 0xC(a1)
	jal     DrawMesh
	addiu   a1, gp, db-GP_ADDR
	addiu   a1, gp, db-GP_ADDR
	j       loc_751B4
	sw      a3, 8(a1)
#endif
	UNIMPLEMENTED();
}

void DrawRoomletListAsm(long unk, struct room_info* r)//0x1BC4D0
{
	UNIMPLEMENTED();
}

void GetBounds(int* t0, int* t1, int* t6, int* t7, int* t8, int* t9, int* a0, int* a1, int* a2, int* a3, int* v0, int* s5)
{
	int v1 = *t0 << 16;
	v1 >>= 16;

	if (v1 < *a0)
	{
		*a0 = v1;
	}
	
	//loc_74B40
	*t0 >>= 16;

	if (v1 > * a1)
	{
		*a1 = v1;
	}

	//loc_74B4C
	if (*t0 < *a2)
	{
		*a2 = *t0;
	}
	
	//loc_74B5C
	v1 = *t6 << 16;
	if (*t0 > * a3)
	{
		*a3 = *t0;
	}
	
	//loc_74B68
	v1 >>= 16;

	if (v1 < *a0)
	{
		*a0 = v1;
	}
	
	//loc_74B7C
	*t6 >>= 16;

	if (v1 > *a1)
	{
		*a1 = v1;
	}
	
	//loc_74B88
	if (*t6 < *a2)
	{
		*a2 = *t6;
	}
	
	//loc_74B98
	v1 = *t8 << 16;
	if (*t6 > *a3)
	{
		*a3 = *t6;
	}
	
	//loc_74BA4
	v1 >>= 16;
	if (v1 < *a0)
	{
		*a0 = v1;
	}
	
	//loc_74BB8
	*t8 >>= 16;

	if (v1 > *a1)
	{
		*a1 = v1;
	}
	
	//loc_74BC4
	if (*t8 < *a2)
	{
		*a2 = *t8;
	}
	
	//loc_74BD4
	if (*t8 > *a3)
	{
		*a3 = *t8;
	}
	
	//loc_74BE0
	if (*t1 > 20479)
	{
		*v0 += 1;
	}//loc_74BEC

	if (*t7 > 20479)
	{
		*v0 += 1;
	}

	//loc_74BF8
	if (*t9 > 20479)
	{
		*v0 += 1;
	}

	//loc_74C04
	if (*t1 == 0)
	{
		*s5 += 1;
	}
	
	//loc_74C10
	if (*t7 == 0)
	{
		*s5 += 1;
	}

	//loc_74C1C
	if (*t9 == 0)
	{
		*s5 += 1;
	}
}
#endif