#include "LIGHT.H"

#include "EFFECT2.H"
#include "DRAW.H"
#include "MATHS.H"
#include "LOAD_LEV.H"
#include "GTEREG.H"

int mSqrt_L(int a0)
{
	LZCR = gte_leadingzerocount(a0);
	LZCS = a0;

	int v0 = 0x1F;

	if (a0 != 0)
	{
		int v1 = LZCR;
		int at = -2;
		v1 &= at;
		v0 -= v1;
		v0 >>= 1;
		at = v0 - 24;

		if (a0 >= 0)
		{
			a0 <<= at;
		}
		else
		{
			at = 24;
			at -= v1;
			a0 >>= at;
		}

		//loc_864DC
		a0 -= 64;
		a0 = SqrtTable[a0];
		a0 <<= v0;
	}

	//locret_864F8
	return a0 >> 12;
}

void S_CalculateStaticMeshLight(long floor, long touch_bits, long mesh_bits, int anim_state)//8669C(<)
{
	int t5 = 0;
	int t4 = 0;
	int t3 = 0;
	int t7;
	int t6;
	int t0;
	int a0;
	int a1;
	int a2;
	int v1;
	int at;
	int v0;
	int i;

	if (number_dynamics > 0)
	{
		t7 = floor;
		t6 = touch_bits;
		t0 = mesh_bits;

		//loc_866C4
		for(i = 0; i < number_dynamics; i++)
		{
			IR1 = floor - dynamics[i].x;

			//loc_866E4
			if (ABS(IR1) < 0x2001)
			{
				IR2 = touch_bits - dynamics[i].y;
				if (ABS(IR1) < 0x2001)
				{
					IR2 = mesh_bits - dynamics[i].z;
					if (ABS(IR2) < 0x2001)
					{
						docop2(0xA00428);

						a0 = MAC1;
						a1 = MAC2;
						a2 = MAC3;

						a0 += a1;
						a0 += a2;

						a0 = gte_leadingzerocount(a0);
						v0 = 0x1F;
						if (a0 != 0)
						{
							v1 = LZCR;
							at = -2;
							v1 &= at;
							v0 -= v1;
							v0 >>= 1;

							at = v1 - 0x18;
							if (at >= 0)
							{
								a0 <<= at;
							}//loc_86774
							else
							{
								at = 0x18;
								at -= v1;
								a0 >>= at;
							}
							//loc_86780
							a0 -= 0x40;
							a0 = SqrtTable[a0];
							a0 <<= v0;
						}
						//loc_8679C
						v0 = a0 >> 12;
						v1 = dynamics[i].falloff >> 1;
						a0 = v0;

						v0 = a0 << 13;
						if (v1 >= a0)
						{
							v0 -= a0;
							v0 = v0 / v1;
							v1 = 0x1FFF;
							a0 = dynamics[i].r;
							v1 -= v0;
							at = a0 * v1;
							v0 = dynamics[i].g;
							a0 = v0 * v1;
							v0 = dynamics[i].b;
							v1 = v0 * v1;
							v0 = at >> 13;
							t3 += v0;
							v0 = a0 >> 13;
							t4 += v0;
							v0 = v1 >> 13;
							t5 += v0;
						}
					}//loc_86810
				}//loc_86810
			}//loc_86810
		}
	}//loc_8681C
	v0 = t3 + t4;
	v0 += t5;
	a0 = anim_state;

	if (v0 != 0)
	{
		v0 = anim_state & 0x1F;
		v0 <<= 3;
		t3 += v0;
		v1 = anim_state & 0x3E0;
		v1 >>= 2;
		t4 += v1;
		v1 = anim_state & 0x7C00;
		v1 >>= 7;
		t5 += v1;

		if (t3 >= 0x100)
		{
			t3 = 0xFF;
		}//loc_86860

		if (t4 >= 0x100)
		{
			t4 = 0xFF;
		}//loc_8686C

		if (t5 >= 0x100)
		{
			t5 = 0xFF;
		}//loc_86878

		t4 <<= 8;
		t5 <<= 16;
		a0 = t3 | t4 | t5;
	}
	else
	{
		//loc_8688C
		v1 = a0 & 0x3E0;
		v0 = a0 & 0x7C00;
		a0 &= 0x1F;
		a0 <<= 3;
		v1 <<= 6;
		v0 <<= 9;
		a0 |= v1;
		a0 |= v0;
	}

	R = (a0 & 0xFF);
	G = (a0 & 0xFF00) >> 8;
	B = (a0 & 0xFF0000) >> 16;
	CODE = (a0 & 0xFF000000) >> 24;
}

void CalculateObjectLighting(struct ITEM_INFO* item/*a0*/, short* frmptr/*a1*/, struct STASHEDOBJ* sobject/*s0*/, short numnodestodraw/*s1*/)
{
	if (item->shade < 0)
	{
		R11 = 4096;
		R12 = 0;
		R13 = 0;
		R21 = 0;
		R22 = 4096;
		R23 = 0;
		R31 = 0;
		R32 = 0;
		R33 = 4096;
		TRX = 0;
		TRY = 0;
		TRZ = 0;
		Matrix++;
		mRotYXZ(item->pos.y_rot, item->pos.x_rot, item->pos.z_rot);
		mTranslateXYZ((frmptr[0] + frmptr[1]) >> 1, (frmptr[2] + frmptr[4]) >> 1, (frmptr[3] + frmptr[5]) >> 1);
		mPopMatrix();
		//S_CalculateLight(item->pos.x_pos + TRX, item->pos.y_pos + TRY, item->pos.z_pos + TRZ, item->room_number, &item->il);
	}
	else
	{
		//loc_8668C
		S_CalculateStaticMeshLight(item->pos.x_pos, item->pos.y_pos, item->pos.z_pos, 0x7FFF);
	}
}

void S_CalculateLight(long x, long y, long z, short room_num, struct ITEM_LIGHT* light)
{
	struct room_info* r;//$t0
	int scratchPad[256];
	int* s1 = &scratchPad[21];
	//at = 0x1000
	s1[3] = 0;
	s1[4] = 0;
	((short*)s1)[10] = 0x1000;
	int* s2 = &s1[8];
	s2[3] = 0;
	s2[4] = 0;
	((short*)s2)[10] = 0x1000;
	int* s3 = &s2[8];
	s3[3] = 0;
	s3[4] = 0;
	((short*)s3)[10] = 0x1000;
	int s4 = 0;
	int s5 = 0;
	int s6 = 0;
	//s7 = 0x1000;
	int t7 = x;
	int t8 = y;
	int t9 = z;

	//t0 = &room[0];
	//s0 = gp
	r = &room[room_num];

	struct LIGHTINFO* gp = r->light;
	int v0 = ((int*)&r->ambient)[0];
	unsigned short fp = r->num_lights;

	int t2 = (v0 >> 12) & 0xFF0;
	int t1 = (v0 >> 4) & 0xFF0;
	int t0 = (v0 << 4) & 0xFF0;

	SXY0 = t0;
	SXY1 = t1;
	SXY2 = t2;

loc_85D34:
	if (fp-- != 0)
	{
		int t3 = gp->Type;
		int t2 = ((int*)&gp->Inner)[0];
		int t0 = t2 & 0xFF00;

		if (gp->Type == 0)
		{
			s4 |= 0x2000;
			int a0 = ((int*)&gp->nx)[0];
			int a1 = ((int*)&gp->nz)[0];
			int a2 = ((int*)&gp->Type)[0];
			s1[4] = a0;
			s1[5] = a1;
			s1[3] = a2;
			gp++;
			goto loc_85D34;
		}
		else
		{
			//loc_85D70
			int t4 = gp->x;
			int t5 = gp->y;
			int t6 = gp->z;

			t4 -= t7;
			t5 -= t8;
			t6 -= t9;

			IR1 = t4;
			IR2 = t5;
			IR3 = t6;

			t0 >>= 1;

			docop2(0xA00428);

			t1 = (t2 & 0xFF) << 7;
			t2 >>= 16;
			int a3 = t3 & 1;
			int a0 = MAC1;
			int a1 = MAC2;
			int a2 = MAC3;
			a0 += a1;
			a0 += a2;
			int v0 = mSqrt_L(a0);

			a0 = t4;
			if (v0 < t0)
			{
				a1 = t5;
				a2 = t6;

				if (a3 != 0)
				{

				}//loc_85E30
			}//loc_85F40
		}
	}//loc_85F48

#if 0
	jal     mNormaliseXYZ
	move    t4, v0
	lhu     t5, 0x16(gp)
	slt     at, t4, t1
	bnez    at, loc_85E0C
	move    a3, t5
	sub     t4, t1
	sub     t5, t0, t1
	sub     t5, t4
	mult    t5, t2
	mflo    a3
	srl     a3, 8

	loc_85E0C:
	addi    at, t3, -3
	bnez    at, loc_85ED0
	li      at, 0x1000
	sub     a3, at, a3
	slt     at, a3, s7
	beqz    at, loc_85D34
	addi    gp, 0x20
	j       loc_85D34
	move    s7, a3

	loc_85E30:
	jal     mNormaliseXYZ
	move    t4, v0
	cfc2    v0, r0
	cfc2    v1, r1
	lwc2    r0, 0x10(gp)
	lwc2    r1, 0x14(gp)
	sll     a1, 16
	andi    a0, 0xFFFF
	or      a0, a1
	ctc2    a0, r0
	ctc2    a2, r1
	sub     t3, t4, t1
	nop
	nop
	cop2    0x486012
	sub     t5, t0, t1
	sub     t5, t3
	mult    t5, t2
	lw      t5, 0x1C(gp)
	lhu     t3, 0x16(gp)
	srl     t6, t5, 16
	mfc2    t0, r9
	ctc2    v0, r0
	ctc2    v1, r1
	slt     at, t0, t6
	bnez    at, loc_85F40
	andi    t5, 0xFFFF
	slt     at, t0, t5
	bnez    at, loc_85EA4
	mflo    t1
	li      t0, 0x1000

	loc_85EA4:
	srl     t1, 8
	slt     at, t1, t3
	bnez    at, loc_85EB8
	mfc2    a0, r0
	move    t1, t3

	loc_85EB8:
	mult    t0, t1
	mfc2    a2, r1
	srl     a1, a0, 16
	andi    a0, 0xFFFF
	mflo    a3
	srl     a3, 12

	loc_85ED0:
	sub     at, s4, a3
	bgtz    at, loc_85EFC
	sub     at, s5, a3
	move    s6, s5
	move    s5, s4
	move    s4, a3
	move    at, s3
	move    s3, s2
	move    s2, s1
	j       loc_85F2C
	move    s1, at

	loc_85EFC:
	bgtz    at, loc_85F1C
	sub     at, s6, a3
	move    s6, s5
	move    s5, a3
	move    at, s3
	move    s3, s2
	j       loc_85F2C
	move    s2, at

	loc_85F1C:
	bgtz    at, loc_85F40
	nop
	move    s6, a3
	move    at, s3

	loc_85F2C:
	lw      t0, 0xC(gp)
	sh      a0, 0x10(at)
	sh      a1, 0x12(at)
	sh      a2, 0x14(at)
	sw      t0, 0xC(at)

	loc_85F40:
	j       loc_85D34
	addi    gp, 0x20

	loc_85F48:
	beqz    s4, loc_85FCC
	addi    at, s7, -0x1000
	beqz    at, loc_85FCC
	li      at, 0x1000
	mtc2    s7, r8
	mtc2    s4, r9
	mtc2    s5, r10
	mtc2    s6, r11
	sub     t0, at, s7
	addi    t0, 0x1000
	cop2    0x198003D
	mfc2    t1, r12
	mfc2    t2, r13
	mfc2    t3, r14
	slti    at, s4, 0x1000
	mfc2    s4, r9
	mfc2    s5, r10
	mfc2    s6, r11
	mtc2    t1, r9
	mtc2    t2, r10
	mtc2    t3, r11
	nop
	nop
	cop2    0x198003D
	mfc2    t1, r9
	mfc2    t2, r10
	mfc2    t3, r11
	mtc2    t1, r12
	mtc2    t2, r13
	mtc2    t3, r14
	bnez    at, loc_85FCC
	nop
	move    s4, t0

	loc_85FCC:
	lw      fp, number_dynamics-GP_ADDR(s0)
	;addiu   gp, s0, dynamics-GP_ADDR original
	la		gp, dynamics

	loc_85FD4:
	beqz    fp, loc_86110
	addi    fp, -1
	lw      t4, 0(gp)
	lw      t5, 4(gp)
	lw      t6, 8(gp)
	sub     t4, t7
	sub     t5, t8
	sub     t6, t9
	mtc2    t4, r9
	mtc2    t5, r10
	mtc2    t6, r11
	bgez    t4, loc_8600C
	move    a0, t4
	neg     a0, t4

	loc_8600C:
	cop2    0xA00428
	bgez    t5, loc_8601C
	move    a1, t5
	neg     a1, t5

	loc_8601C:
	bgez    t6, loc_86028
	move    a2, t6
	neg     a2, t6

	loc_86028:
	sltiu   at, a0, 0x2000
	beqz    at, loc_86108
	sltiu   at, a1, 0x2000
	beqz    at, loc_86108
	sltiu   at, a2, 0x2000
	beqz    at, loc_86108
	lh      t0, 0x10(gp)
	lw      t1, 0x14(gp)
	srl     t0, 1
	mfc2    a0, r25
	mfc2    a1, r26
	mfc2    a2, r27
	add     a0, a1
	jal     mSqrt
	add     a0, a2
	slt     at, v0, t0
	beqz    at, loc_86108
	mult    v0, t1
	move    a0, t4
	move    a1, t5
	jal     mNormaliseXYZ
	move    a2, t6
	mflo    v0
	li      a3, 0x1000
	srl     v0, 8
	sub     a3, v0
	sub     at, s4, a3
	bgtz    at, loc_860BC
	sub     at, s5, a3
	move    s6, s5
	move    s5, s4
	move    s4, a3
	move    at, s3
	move    s3, s2
	move    s2, s1
	j       loc_860EC
	move    s1, at

	loc_860BC:
	bgtz    at, loc_860DC
	sub     at, s6, a3
	move    s6, s5
	move    s5, a3
	move    at, s3
	move    s3, s2
	j       loc_860EC
	move    s2, at

	loc_860DC:
	bgtz    at, loc_86108
	nop
	move    s6, a3
	move    at, s3

	loc_860EC:
	lw      t0, 0xC(gp)
	sh      a0, 0x10(at)
	sh      a1, 0x12(at)
	sh      a2, 0x14(at)
	beqz    s7, loc_86108
	sw      t0, 0xC(at)
	add     s7, a3

	loc_86108:
	j       loc_85FD4
	addi    gp, 0x18

	loc_86110:
	addi    at, s4, -0x1000
	bltz    at, loc_86120
	lui     t0, 0x1F80
	move    s4, at

	loc_86120:
	sw      s4, 0(t0)
	sw      s1, 4(t0)
	sw      s5, 0x1C(t0)
	sw      s2, 0x20(t0)
	sw      s6, 0x38(t0)
	sw      s3, 0x3C(t0)
	move    s6, t0
	lw      s5, 0x2C+0x10(sp)
	mfc2    s1, r12
	mfc2    s2, r13
	mfc2    s3, r14
	li      v0, 3
	lbu     v1, 0x2F(s5)

	loc_86154:
	beqz    v0, loc_8628C
	lw      s4, 4(s6)
	lwc2    r8, 0(s6)
	lw      t0, 0xC(s4)
	lw      t3, 8(s5)
	andi    s0, t0, 0xFF
	srl     t2, t0, 20
	srl     t1, t0, 12
	andi    t1, 0xFF0
	srl     t0, 4
	andi    t0, 0xFF0
	mtc2    t0, r9
	mtc2    t1, r10
	mtc2    t2, r11
	srl     t5, t3, 12
	srl     t4, t3, 4
	cop2    0x198003D
	bnez    v1, loc_861BC
	addi    v0, -1
	lh      t3, 0x10(s4)
	lh      t4, 0x12(s4)
	lh      t5, 0x14(s4)
	move    t0, t3
	move    t1, t4
	j       loc_86204
	move    t2, t5

	loc_861BC:
	sll     t3, 4
	andi    t3, 0xFF0
	andi    t4, 0xFF0
	andi    t5, 0xFF0
	ctc2    t3, r21
	ctc2    t4, r22
	ctc2    t5, r23
	li      at, 0xE00
	mtc2    at, r8
	lh      t3, 0x10(s4)
	nop
	nop
	cop2    0x980011
	lh      t4, 0x12(s4)
	lh      t5, 0x14(s4)
	lw      t0, 0(s5)
	lh      t2, 4(s5)
	sra     t1, t0, 16
	sll     t0, 16
	sra     t0, 16

	loc_86204:
	swc2    r22, 8(s5)
	swc2    r9, 8(s6)
	swc2    r10, 0xC(s6)
	swc2    r11, 0x10(s6)
	mtc2    s1, r25
	mtc2    s2, r26
	mtc2    s3, r27
	li      at, 0x800
	mtc2    at, r8
	sub     t3, t0
	sub     t4, t1
	cop2    0x1A8003E
	sub     t5, t2
	sra     t3, 3
	sra     t4, 3
	sra     t5, 3
	add     t0, t3
	add     t1, t4
	add     t2, t5
	sh      t0, 0x14(s6)
	sh      t1, 0x16(s6)
	sh      t2, 0x18(s6)
	andi    t0, 0xFFFF
	sll     t1, 16
	or      t0, t1
	sw      t0, 0(s5)
	beqz    s0, loc_86280
	sw      t2, 4(s5)
	mfc2    s1, r9
	mfc2    s2, r10
	mfc2    s3, r11

	loc_86280:
	addi    s6, 0x1C
	j       loc_86154
	addi    s5, 0xC

	loc_8628C:
	beqz    v1, loc_862C8
	lui     at, 0x100
	lwc2    r9, 0(s5)
	lwc2    r10, 4(s5)
	lwc2    r11, 8(s5)
	ctc2    s1, r21
	ctc2    s2, r22
	ctc2    s3, r23
	li      s1, 0x600
	mtc2    s1, r8
	nop
	nop
	cop2    0x980011
	mfc2    s1, r9
	mfc2    s2, r10
	mfc2    s3, r11

	loc_862C8:
	sw      s1, 0(s5)
	sw      s2, 4(s5)
	or      at, s3
	sw      at, 8(s5)
	sll     s1, 1
	sll     s2, 1
	sll     s3, 1
	ctc2    s1, r13
	ctc2    s2, r14
	ctc2    s3, r15
	cfc2    s0, r0
	cfc2    s1, r1
	cfc2    s2, r2
	cfc2    s3, r3
	lw      gp, 0x2C-0x8(sp)
	cfc2    s4, r4
	li      t0, 0x808080
	beqz    s7, loc_86330
	slti    at, s7, 0xFFF
	beqz    at, loc_86330
	srl     s7, 5
	sll     t0, s7, 16
	sll     t1, s7, 8
	or      t0, t1
	or      t0, s7

	loc_86330:
	mtc2    t0, r6
	addiu   s5, gp, CamGTE-GP_ADDR
	addiu   s6, gp, LightPos-GP_ADDR
	lui     s7, 0x1F80
	lw      t0, 0(s5)
	lw      t1, 4(s5)
	lw      t2, 8(s5)
	lw      t3, 0xC(s5)
	lw      t4, 0x10(s5)
	ctc2    t0, r0
	ctc2    t1, r1
	ctc2    t2, r2
	ctc2    t3, r3
	ctc2    t4, r4
	lwc2    r0, 0x14(s7)
	lwc2    r1, 0x18(s7)
	lwc2    r2, 0x30(s7)
	nop
	nop
	cop2    0x486012
	lwc2    r3, 0x34(s7)
	lwc2    r4, 0x4C(s7)
	lwc2    r5, 0x50(s7)
	lhu     t1, 0x24(s7)
	lhu     t0, 8(s7)
	sll     t1, 16
	or      t0, t1
	lhu     t2, 0xC(s7)
	mfc2    t5, r9
	mfc2    t8, r10
	mfc2    t6, r11
	cop2    0x48E012
	lhu     t1, 0x40(s7)
	sll     t2, 16
	or      t1, t2
	lhu     t3, 0x44(s7)
	lhu     t2, 0x28(s7)
	sll     t3, 16
	or      t2, t3
	lhu     t4, 0x2C(s7)
	mfc2    t9, r9
	mfc2    t7, r10
	mfc2    a0, r11
	cop2    0x496012
	lhu     t3, 0x10(s7)
	sll     t4, 16
	or      t3, t4
	lhu     t4, 0x48(s7)
	andi    t5, 0xFFFF
	sll     t8, 16
	or      t5, t8
	andi    t6, 0xFFFF
	sll     t9, 16
	or      t6, t9
	andi    t7, 0xFFFF
	sll     a0, 16
	or      t7, a0
	mfc2    t8, r9
	mfc2    a0, r10
	mfc2    t9, r11
	andi    t8, 0xFFFF
	sll     a0, 16
	or      t8, a0
	sw      t5, 0(s6)
	sw      t6, 4(s6)
	sw      t7, 8(s6)
	sw      t8, 0xC(s6)
	sw      t9, 0x10(s6)
	ctc2    t0, r16
	ctc2    t1, r17
	ctc2    t2, r18
	ctc2    t3, r19
	ctc2    t4, r20
	ctc2    s0, r0
	ctc2    s1, r1
	ctc2    s2, r2
	ctc2    s3, r3
	ctc2    s4, r4
	ctc2    zero, r21
	ctc2    zero, r22
	ctc2    zero, r23
	lw      ra, 0x2C-0x2C(sp)
	lw      s0, 0x2C-0x28(sp)
	lw      s1, 0x2C-0x24(sp)
	lw      s2, 0x2C-0x20(sp)
	lw      s3, 0x2C-0x1C(sp)
	lw      s4, 0x2C-0x18(sp)
	lw      s5, 0x2C-0x14(sp)
	lw      s6, 0x2C-0x10(sp)
	lw      s7, 0x2C-0xC(sp)
	lw      fp, 0x2C-0x4(sp)
	jr      ra
	addi    sp, 0x2C
#endif
}