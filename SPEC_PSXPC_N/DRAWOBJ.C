#include "DRAWOBJ.H"

#include "DRAWSPKS.H"
#include "SPECIFIC.H"
#include "LIBGPU.H"
#include "EMULATOR.H"
#include "GPU.H"
#include "GTEREG.H"

void InitGT4(char* polyptr, int t6, int s4, int t2, int t7, int s5, int t3, int t8, int s6, int t4, int t9, int s7, int t5)
{
	((int*)polyptr)[1] = t6;
	((int*)polyptr)[2] = s4;
	((int*)polyptr)[3] = t2;
	((int*)polyptr)[4] = t7;
	((int*)polyptr)[5] = s5;
	((int*)polyptr)[6] = t3;
	((int*)polyptr)[7] = t8;
	((int*)polyptr)[8] = s6;
	((int*)polyptr)[9] = t4;
	((int*)polyptr)[10] = t9;
	((int*)polyptr)[11] = s7;
	((int*)polyptr)[12] = t5;
}

void InitGT3(char* polyptr, int t6, int s4, int t2, int t7, int s5, int t3, int t8, int s6, int t4)
{
	((int*)polyptr)[1] = t6;
	((int*)polyptr)[2] = s4;
	((int*)polyptr)[3] = t2;
	((int*)polyptr)[4] = t7;
	((int*)polyptr)[5] = s5;
	((int*)polyptr)[6] = t3;
	((int*)polyptr)[7] = t8;
	((int*)polyptr)[8] = s6;
	((int*)polyptr)[9] = t4;
}

void UnpackRGB(int fp, int* t6, int* t7, int* t8, int* at)
{
	int t2;
	int t3;

	t2 = (*t6 >> 7) & fp;
	t3 = (*t6 >> 10) & 0xF800;
	*t6 = (*t6 >> 13) & 0xF8;

	*t6 |= t3;
	*t6 |= t2;
	*at >>= 24;
	*at <<= 24;
	*t6 |= *at;

	t2 = (*t7 >> 7) & fp;
	t3 = (*t7 >> 10) & 0xF800;
	*t7 = (*t7 >> 13) & 0xF8;

	*t7 |= t3;
	*t7 |= t2;

	t2 = (*t8 >> 7) & fp;
	t3 = (*t8 >> 10) & 0xF800;
	*t8 = (*t8 >> 13) & 0xF8;
	
	*t8 |= t3;
	*t8 |= t2;
}

void MakeMono(unsigned short* s, unsigned char* d)//7F9E4, 81A28
{
	//at = 0x421
#if 0
	ctc2    $at, $29
	lw      $t0, 0($a0)
	li      $v0, 0x3FFF
	li      $v1, 0xD371F947
	li      $t4, 0x41C64E6D

	 loc_7FA04:
			 mult    $v1, $t4
				 srl     $t3, $t0, 26
				 srl     $t2, $t0, 21
				 srl     $t1, $t0, 16
				 andi    $t3, 0x1F
				 andi    $t2, 0x1F
				 andi    $t1, 0x1F
				 mtc2    $t3, $17
				 mtc2    $t2, $18
				 mtc2    $t1, $19
				 addi    $a0, 4
				 cop2    0x158002D
				 srl     $t2, $t0, 10
				 srl     $t1, $t0, 5
				 andi    $t2, 0x1F
				 andi    $t1, 0x1F
				 andi    $t0, 0x1F
				 mtc2    $t2, $17
				 mtc2    $t1, $18
				 mtc2    $t0, $19
				 mfc2    $t1, $7
				 cop2    0x158002D
				 mflo    $v1
				 addiu   $v1, 0x3039
				 lw      $t0, 0($a0)
				 mfc2    $at, $7
				 srl     $t3, $v1, 16
				 srl     $t5, $v1, 24
				 andi    $t3, 1
				 andi    $t5, 1
				 sltiu   $t2, $t1, 0xF
				 bnez    $t2, loc_7FA8C
				 sltiu   $t2, $at, 0xF
				 li      $t1, 0xF

				 loc_7FA8C:
			 bnez    $t2, loc_7FA98
				 sub     $t1, $t3
				 li      $at, 0xF

				 loc_7FA98 :
				 bgez    $t1, loc_7FAA4
				 sub     $at, $t5
				 move    $t1, $zero

				 loc_7FAA4 :
			 bgez    $at, loc_7FAB0
				 sll     $t1, 4
				 move    $at, $zero

				 loc_7FAB0 :
			 or $t1, $at
				 sb      $t1, 0($a1)
				 addi    $a1, 1
				 bnez    $v0, loc_7FA04
				 addi    $v0, -1
				 li      $v0, 0xAA
				 ctc2    $v0, $29
				 jr      $ra
				 nop
#endif
	S_Warn("[MakeMono] - Unimplemented!\n");
}

void InitObjGTE()
{
	ZSF3 = 0xAA;
	ZSF4 = 0x80;
	RFC = 0;
	GFC = 0;
	BFC = 0;
}

void DrawClippedMesh(int vertcache, short* mesh, MMTEXTURE* text, char* ot, char* prim, char* prim_lim, long fp, long prim_len, long num_tri)
{
	UNIMPLEMENTED();
}

void DrawSubDivMesh()
{
	UNIMPLEMENTED();
}

void initialise_light_matrix()
{
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int at;

	t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	t4 = (R33);

	t5 = 0xFFFF0000;
	t6 = t0 & t5;
	t7 = t2 & t5;
	t0 &= 0xFFFF;
	at = t1 & t5;
	t0 |= at;
	t2 &= 0xFFFF;
	at = t3 & t5;
	t2 |= at;
	t1 &= 0xFFFF;
	t1 |= t7;
	t3 &= 0xFFFF;
	t3 |= t6;

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;

	L13 = t3 & 0xFFFF;
	L21 = (t3 >> 16) & 0xFFFF;

	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;

	L31 = t1 & 0xFFFF;
	L32 = (t1 >> 16) & 0xFFFF;
	L33 = t4;

	VX0 = LightPos.m00;
	VY0 = LightPos.m01;
	VZ0 = LightPos.m02;

	docop2(0x4A6012);

	VX1 = LightPos.m10;
	VY1 = LightPos.m11;
	VZ1 = LightPos.m12;

	t0 = IR1;
	t2 = IR2;
	t1 = IR3;

	docop2(0x4AE012);

	VX2 = LightPos.m20;
	VY2 = LightPos.m21;
	VZ2 = LightPos.m22;

	t0 &= 0xFFFF;
	t2 <<= 16;
	t0 |= t2;
	t1 &= 0xFFFF;

	t3 = IR1;
	t2 = IR2;
	t4 = IR3;

	docop2(0x4B6012);

	t3 <<= 16;
	t1 |= t3;
	t2 &= 0xFFFF;
	t4 <<= 16;
	t2 |= t4;

	t3 = IR1;
	t5 = IR2;
	t6 = IR3;

	t3 &= 0xFFFF;
	t5 <<= 16;
	t3 |= t5;

	L11 = t0 & 0xFFFF;
	L12 = (t0 >> 16) & 0xFFFF;
	L13 = t1 & 0xFFFF;
	L21 = (t1 >> 16) & 0xFFFF;
	L22 = t2 & 0xFFFF;
	L23 = (t2 >> 16) & 0xFFFF;
	L31 = t3 & 0xFFFF;
	L32 = (t3 >> 16) & 0xFFFF;
	L33 = t4;
}

void phd_PutPolygons_normal(short* mesh, short clip)
{
	initialise_light_matrix();

	mesh_header* mptr = (mesh_header*)mesh;

#if GLTEST
	Emulator_TestDrawVertices(mesh, RoomTextInfo);
#endif
	UNIMPLEMENTED();
}

void phd_PutPolygons_train(short* mesh, long shade)
{
	UNIMPLEMENTED();
}

void phd_PutPolygons(short* mesh, long shade)
{
	phd_PutPolygons_normal(mesh, shade);
}

void phd_PutPolygons_pickup(short* mesh, long shade)
{
	int v0;
	int* a1;
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int t6;
	int t7;
	int t8;
	int at;
	int v1;
	int* a3;
	int sp[1024];//0x1F800000
	int* a2;
	int* s7;
	int* a0;
	int fp;
	int s2;
	int s4;
	int s5;
	int s6;
	char* s0;
	int t9;

	initialise_light_matrix();

	v0 = ((int*)mesh)[2];
	mesh += 6;
	a1 = (int*)&mesh[v0 >> 17];
	v0 &= 0xFF;
	a2 = &sp[0];
	s7 = a2;
	t0 = TRZ - 12288;
	t1 = 0;

	at = v0 << 3;

	if (t0 > 0)
	{
		t1 = t0 >> 1;
	}
	//loc_80548
	IR0 = t1;
	v1 = v0;
	a3 = (int*)&mesh[at >> 1];
	t0 = 0x808080;
	R = 128;
	G = 128;
	B = 128;

	//loc_80560
	do
	{
		VX0 = a3[0] & 0xFFFF;
		VY0 = (a3[0] >> 16) & 0xFFFF;
		VZ0 = a3[1];
		a3 += 2;

		docop2(0xE80413);
		v1--;
		a2 += 2;
		t0 = ORGB;
	} while (v1 != 0);

	((short*)a2)[-1] = t0;

	a2 = s7;

	t0 = mesh[0];
	t1 = mesh[1];
	t2 = mesh[2];
	t3 = mesh[3];
	t4 = mesh[4];
	t5 = mesh[5];

	//loc_805A0
	do
	{
		VX0 = (t0 & 0xFFFF);
		VY0 = (t0 >> 16) & 0xFFFF;
		VZ0 = t1;

		VX1 = (t2 & 0xFFFF);
		VY1 = (t2 >> 16) & 0xFFFF;
		VZ1 = t3;

		VX2 = (t4 & 0xFFFF);
		VY2 = (t4 >> 16) & 0xFFFF;
		VZ2 = t5;

		mesh += 12;
		v0 -= 3;

		docop2(0x280030);

		t0 = ((int*)mesh)[0];
		t1 = ((int*)mesh)[1];
		t2 = ((int*)mesh)[2];
		t3 = ((int*)mesh)[3];
		t4 = ((int*)mesh)[4];
		t5 = ((int*)mesh)[5];

		t6 = SZ1;
		t7 = SZ2;
		t8 = SZ3;

		a2[0] = SXY0;
		((short*)a2)[2] = t6;
		a2[2] = SXY1;
		((short*)a2)[6] = t7;
		a2[4] = SXY2;
		((short*)a2)[10] = t8;
		a2 += 6;

	} while (v0 > 0);

	a0 = s7;
	//a2 = psxtextinfo
	//a3 = db.pickup_ot
	s0 = db.polyptr;
	//s1 = db.polybuf_limit
	v0 = a1[0];
	fp = 0xF80000;
	at = v0 >> 16;
	DQA = at;
	v0 &= 0xFFFF;
	s2 = 0x9000000;
	a1 += 1;

	if (v0 != 0)
	{
		t0 = a1[0];

	loc_80640:
		a1 += 1;
		v1 = 3;

	loc_80648:
		t1 = a1[0];
		v0--;

		if ((unsigned long)s0 < (unsigned long)db.polybuf_limit)
		{
			int* t88;
			int* t77;
			int* t66;
			t88 = &a0[((t1 >> 13) & 0x7F8) >> 2];
			t77 = &a0[((t1 >> 5) & 0x7F8) >> 2];
			t66 = &a0[((t1 << 3) & 0x7F8) >> 2];

			s4 = t66[0];
			s5 = t77[0];
			s6 = t88[0];

			SXY0 = s4;
			SXY1 = s5;
			SXY2 = s6;

			t5 = t0 & 0xFF;
			t0 >>= 8;

			docop2(0x1400006);

			t6 = t66[1];
			t7 = t77[1];
			t8 = t88[1];

			SZ1 = t6;
			SZ2 = t7;
			SZ3 = t8;

			t1 >>= 16;
			t1 &= 0xF00;

			at = MAC0;
			docop2(0x158002D);
			t5 |= t1;

			if (at >= 0)
			{
				struct PSXTEXTSTRUCT* t55 = &psxtextinfo[t5];

				t1 = OTZ >> 1;
				at = t1;
				//t1 <<= 2;
				if (at < 256)
				{
					t4 = t55->u2v2pad;
					at = t4 << 8;
					UnpackRGB(fp, &t6, &t7, &t8, &at);
					t2 = t55->u0v0clut;
					t3 = t55->u1v1tpage;
					InitGT3(s0, t6, s4, t2, t7, s5, t3, t8, s6, t4);

					unsigned long* t11 = &db.pickup_ot[t1];
					t2 = t11[0] | s2;
					t11[0] = (unsigned long)s0;
					((unsigned long*)s0)[0] = t2;
					s0 += 0x28;
				}//loc_80724
			}//loc_80724

			a1++;

			if (v0 != 0)
			{
				if (v1-- != 0)
				{
					goto loc_80648;
				}

				t0 = a1[0];
				goto loc_80640;
			}
			//loc_8073C
			v0 = DQA;
			s2 = 0xC000000;

			t0 = a1[0];
			if (v0 != 0)
			{
			loc_8074C:
				a1++;
				v1 = 1;

			loc_80754:
				t1 = a1[0];
				v0--;
				if ((unsigned long)s0 < (unsigned long)db.polybuf_limit)
				{
					int* t99;
					int* t88;
					int* t77;
					int* t66;
					int s77;

					t88 = &a0[((t1 >> 13) & 0x7F8) >> 2];
					t77 = &a0[((t1 >> 5) & 0x7F8) >> 2];
					t66 = &a0[((t1 << 3) & 0x7F8) >> 2];

					s4 = t66[0];
					s5 = t77[0];
					s6 = t88[0];
					SXY0 = s4;
					SXY1 = s5;
					SXY2 = s6;

					t99 = &a0[((t1 >> 21) & 0x7F8) >> 2];

					docop2(0x1400006);

					t6 = t66[1];
					t7 = t77[1];
					t8 = t88[1];
					s77 = t99[0];
					t9 = t99[1];

					SZ0 = t6;
					SZ1 = t7;
					SZ2 = t8;
					SZ3 = t9;

					at = MAC0;

					docop2(0x168002E);

					t5 = (t0 & 0xFFF);
					t0 >>= 16;

					if (at > 0)
					{
						struct PSXTEXTSTRUCT* t55;
						t55 = &psxtextinfo[t5];

						t2 = t9 >> 7;
						t1 = OTZ >> 1;
						t2 &= fp;
						at = t1;

						if (at < 256)
						{
							t3 = (t9 >> 10) & 0xF800;
							t9 = (t9 >> 13) & 0xF8;
							t9 |= t3;
							t9 |= t2;
							t4 = t55->u2v2pad;
							at = t4;
							UnpackRGB(fp, &t6, &t7, &t8, &at);

							t2 = t55->u0v0clut;
							t3 = t55->u1v1tpage;
							t5 = t55->u3v3pad;
							InitGT4(s0, t6, s4, t2, t7, s5, t3, t8, s6, t4, t9, s77, t5);

							unsigned long* t11 = &db.pickup_ot[t1];
							t2 = t11[0] | s2;
							t11[0] = (unsigned long)s0;
							((unsigned long*)s0)[0] = t2;
							s0 += 0x34;
						}//loc_80858
					}//loc_80858

					a1++;

					if (v0 != 0)
					{
						v1--;

						if (v1 != 0)
						{
							goto loc_80754;
						}

						t0 = a1[0];
						goto loc_8074C;
					}
				}//loc_80870
			}//loc_80870
		}//loc_80870
	}//loc_80870

	RFC = 0;
	db.polyptr = s0;
}

void phd_PutPolygons_seethrough(short* mesh, unsigned char shade)
{
	if (shade == 0)
	{
		return;
	}

	//.doit
	//s2 = shade & 0xFF
	if (shade == 128)
	{
		phd_PutPolygons_normal(mesh, shade);
	}

	initialise_light_matrix();


#if 0
	li      a1, 1
	jal     initialise_light_matrix
	nop
	lw      v0, 8(a0)
	addi    a0, 0xC
	move    s6, v0
	srl     a1, v0, 16
	andi    v1, v0, 0x8000
	andi    v0, 0xFF
	li      a2, 0x7E
	slt     at, v0, a2
	bnez    at, loc_7FB60
	add     a1, a0
	lui     a2, 0x1E
	j       loc_7FB64
	la      a2, tsv_buffer

	loc_7FB60:
	lui     a2, 0x1F80

	loc_7FB64:
	move    s7, a2
	cfc2    t0, r7
	move    t1, zero
	move    s4, t0
	addi    t0, -0x3000
	blez    t0, loc_7FB84
	sll     at, v0, 3
	srl     t1, t0, 1

	loc_7FB84:
	mtc2    t1, r8
	beqz    v1, loc_7FBC4
	move    v1, v0
	move    a3, a0

	loc_7FB94:
	lh      t0, 6(a3)
	addi    a3, 8
	mtc2    t0, r28
	addi    v1, -1
	addi    a2, 8
	nop
	nop
	cop2    0x680029
	mfc2    t0, r29
	bnez    v1, loc_7FB94
	sh      t0, -2(a2)
	j       loc_7FBF0
	move    a2, s7

	loc_7FBC4:
	add     a3, a0, at

	loc_7FBC8:
	lwc2    r0, 0(a3)
	lwc2    r1, 4(a3)
	addi    a3, 8
	nop
	nop
	cop2    0xE80413
	addi    v1, -1
	addi    a2, 8
	mfc2    t0, r29
	bnez    v1, loc_7FBC8
	sh      t0, -2(a2)
	move    a2, s7

	loc_7FBF0:
	lw      t0, 0(a0)
	lw      t1, 4(a0)
	lw      t2, 8(a0)
	lw      t3, 0xC(a0)
	lw      t4, 0x10(a0)
	lw      t5, 0x14(a0)
	ctc2    a0, r21

	loc_7FC0C:
	mtc2    t0, r0
	mtc2    t1, r1
	mtc2    t2, r2
	mtc2    t3, r3
	mtc2    t4, r4
	mtc2    t5, r5
	addi    a0, 0x18
	addi    v0, -3
	nop
	nop
	cop2    0x280030
	lw      t0, 0(a0)
	lw      t1, 4(a0)
	lw      t2, 8(a0)
	lw      t3, 0xC(a0)
	lw      t4, 0x10(a0)
	lw      t5, 0x14(a0)
	mfc2    t6, r17
	mfc2    t7, r18
	mfc2    t8, r19
	swc2    r12, 0(a2)
	sh      t6, 4(a2)
	swc2    r13, 8(a2)
	sh      t7, 0xC(a2)
	swc2    r14, 0x10(a2)
	sh      t8, 0x14(a2)
	bgtz    v0, loc_7FC0C
	addi    a2, 0x18
	move    a0, s7
	lw      a2, psxtextinfo-GP_ADDR(gp)
	lw      a3, db+0x4-GP_ADDR(gp)
	lw      s0, db+0x8-GP_ADDR(gp)
	lw      s1, db+0x10-GP_ADDR(gp)
	lw      v0, 0(a1)
	lui     fp, 0xF8
	srl     at, v0, 16
	ctc2    at, r27
	andi    v0, 0xFFFF
	lui     gp, 0x900
	beqz    v0, loc_7FDD0
	addi    a1, 4
	lw      t0, 0(a1)

	loc_7FCAC:
	addi    a1, 4
	li      v1, 3

	loc_7FCB4:
	lw      t1, 0(a1)
	slt     at, s0, s1
	beqz    at, DrawExit
	addi    v0, -1
	srl     t8, t1, 13
	andi    t8, 0x7F8
	add     t8, a0
	srl     t7, t1, 5
	andi    t7, 0x7F8
	add     t7, a0
	sll     t6, t1, 3
	andi    t6, 0x7F8
	add     t6, a0
	lw      s4, 0(t6)
	lw      s5, 0(t7)
	lw      s6, 0(t8)
	mtc2    s4, r12
	mtc2    s5, r13
	mtc2    s6, r14
	andi    t5, t0, 0xFF
	srl     t0, 8
	nop
	nop
	cop2    0x1400006
	lw      t6, 4(t6)
	lw      t7, 4(t7)
	lw      t8, 4(t8)
	mtc2    t6, r17
	mtc2    t7, r18
	mtc2    t8, r19
	srl     t1, 16
	andi    t1, 0xF00
	mfc2    at, r24
	nop
	nop
	cop2    0x158002D
	bltz    at, loc_7FDB8
	or      t5, t1
	sll     t5, 4
	add     t5, a2
	mfc2    t1, r7
	nop
	slti    at, t1, 0xA02
	beqz    at, loc_7FDB8
	slti    at, t1, 0x21
	bnez    at, loc_7FDB8
	sll     t1, 2
	lw      t4, 8(t5)
	jal     UnpackRGB
	sll     at, t4, 8
	cfc2    at, r28
	lw      t2, 0(t5)
	lw      t3, 4(t5)
	subu    t2, at
	add     t1, a3
	lui     at, 0xFF9F
	ori		at, 0xFFFF
	and     t3, at
	lui     at, 0x20
	or      t3, at
	jal     InitGT3_V2
	andi    at, s2, 0xFF
	lw      t2, 0(t1)
	sw      s0, 0(t1)
	or      t2, gp
	sw      t2, 0(s0)
	addi    s0, 0x28
	jal     do_the_flat_colursub_poly_tri
	nop

	loc_7FDB8:
	beqz    v0, loc_7FDD0
	addi    a1, 4
	bnez    v1, loc_7FCB4
	addi    v1, -1
	j       loc_7FCAC
	lw      t0, 0(a1)

	loc_7FDD0:
	cfc2    v0, r27
	lui     gp, 0xC00
	beqz    v0, DrawExit
	lw      t0, 0(a1)

	loc_7FDE0:
	addi    a1, 4
	li      v1, 1

	loc_7FDE8:
	lw      t1, 0(a1)
	slt     at, s0, s1
	beqz    at, DrawExit
	addi    v0, -1
	srl     t9, t1, 21
	srl     t8, t1, 13
	andi    t8, 0x7F8
	add     t8, a0
	srl     t7, t1, 5
	andi    t7, 0x7F8
	add     t7, a0
	sll     t6, t1, 3
	andi    t6, 0x7F8
	add     t6, a0
	lw      s4, 0(t6)
	lw      s5, 0(t7)
	lw      s6, 0(t8)
	mtc2    s4, r12
	mtc2    s5, r13
	mtc2    s6, r14
	andi    t9, 0x7F8
	add     t9, a0
	nop
	nop
	cop2    0x1400006
	lw      t6, 4(t6)
	lw      t7, 4(t7)
	lw      t8, 4(t8)
	lw      s7, 0(t9)
	lw      t9, 4(t9)
	mtc2    t6, r16
	mtc2    t7, r17
	mtc2    t8, r18
	mtc2    t9, r19
	mfc2    at, r24
	nop
	nop
	cop2    0x168002E
	andi    t5, t0, 0xFFF
	srl     t0, 16
	bltz    at, loc_7FF20
	sll     t5, 4
	add     t5, a2
	srl     t2, t9, 7
	mfc2    t1, r7
	and     t2, fp
	slti    at, t1, 0xA02
	beqz    at, loc_7FF20
	slti    at, t1, 0x21
	bnez    at, loc_7FF20
	sll     t1, 2
	srl     t3, t9, 10
	andi    t3, 0xF800
	srl     t9, 13
	andi    t9, 0xF8
	or      t9, t3
	or      t9, t2
	lw      t4, 8(t5)
	jal     UnpackRGB
	move    at, t4
	cfc2    at, r28
	lw      t2, 0(t5)
	lw      t3, 4(t5)
	lw      t5, 0xC(t5)
	subu    t2, at
	add     t1, a3
	lui     at, 0x3E00
	or      t6, at
	lui      at, 0xFF9F
	ori     at, 0xFFFF
	and     t3, at
	lui     at, 0x20
	or      t3, at
	jal     InitGT4_V2
	andi    at, s2, 0xFF
	lw      at, 0(t1)
	sw      s0, 0(t1)
	or      at, gp
	sw      at, 0(s0)
	addi    s0, 0x34
	jal     do_the_flat_colursub_poly_quad
	nop

	loc_7FF20:
	beqz    v0, DrawExit
	addi    a1, 4
	bnez    v1, loc_7FDE8
	addi    v1, -1
	j       loc_7FDE0
	lw      t0, 0(a1)

WANK1:
	lui     gp, 0x900
	beqz    v0, loc_7E514
	addi    a1, 4
	lw      t0, 0(a1)

	loc_7E418:
	addi    a1, 4
	li      v1, 3

	loc_7E420:
	lw      t1, 0(a1)
	slt     at, s0, s1
	beqz    at, loc_7E64C
	addi    v0, -1
	ctc2    t1, r22
	srl     t8, t1, 13
	andi    t8, 0x7F8
	add     t8, a0
	srl     t7, t1, 5
	andi    t7, 0x7F8
	add     t7, a0
	sll     t6, t1, 3
	andi    t6, 0x7F8
	add     t6, a0
	lw      s4, 0(t6)
	lw      s5, 0(t7)
	lw      s6, 0(t8)
	mtc2    s4, r12
	mtc2    s5, r13
	mtc2    s6, r14
	andi    t5, t0, 0xFF
	srl     t1, 16
	cop2    0x1400006
	andi    t1, 0xF00
	or      t5, t1
	jal     ultimate_clipper
	move    s7, s6
	bnez    at, loc_7E4FC
	srl     t0, 8
	lwc2    r17, 4(t6)
	lwc2    r18, 4(t7)
	lwc2    r19, 4(t8)
	mfc2    at, r24
	nop
	nop
	cop2    0x158002D
	bltz    at, loc_7E4FC
	lw      t6, 4(t6)
	lw      t7, 4(t7)
	lw      t8, 4(t8)
	sll     t5, 4
	mfc2    t1, r7
	add     t5, a2
	slti    at, t1, 0xA02
	beqz    at, loc_7E4FC
	slti    at, t1, 0x21
	bnez    at, loc_7E4FC
	sll     t1, 2
	lw      t4, 8(t5)
	jal     UnpackRGB
	sll     at, t4, 8
	cfc2    at, r28
	lw      t2, 0(t5)
	lw      t3, 4(t5)
	subu    t2, at
	jal     SubDiv3
	add     t1, a3

	loc_7E4FC:
	beqz    v0, loc_7E514
	addi    a1, 4
	bnez    v1, loc_7E420
	addi    v1, -1
	j       loc_7E418
	lw      t0, 0(a1)

	loc_7E514:
	cfc2    v0, r27
	lui     gp, 0xC00
	beqz    v0, loc_7E64C
	lw      t0, 0(a1)

	loc_7E524:
	addi    a1, 4
	li      v1, 1

	loc_7E52C:
	lw      t1, 0(a1)
	slt     at, s0, s1
	beqz    at, loc_7E64C
	addi    v0, -1
	ctc2    t1, r22
	srl     t9, t1, 21
	andi    t9, 0x7F8
	srl     t8, t1, 13
	andi    t8, 0x7F8
	add     t8, a0
	srl     t7, t1, 5
	andi    t7, 0x7F8
	add     t7, a0
	sll     t6, t1, 3
	andi    t6, 0x7F8
	add     t6, a0
	lw      s4, 0(t6)
	lw      s5, 0(t7)
	lw      s6, 0(t8)
	mtc2    s4, r12
	mtc2    s5, r13
	mtc2    s6, r14
	add     t9, a0
	andi    t5, t0, 0xFFF
	cop2    0x1400006
	jal     ultimate_clipper
	lw      s7, 0(t9)
	bnez    at, loc_7E634
	srl     t0, 16
	lwc2    r16, 4(t6)
	lwc2    r17, 4(t7)
	lwc2    r18, 4(t8)
	lwc2    r19, 4(t9)
	mfc2    at, r24
	nop
	nop
	cop2    0x168002E
	bltz    at, loc_7E634
	lw      t6, 4(t6)
	lw      t7, 4(t7)
	lw      t8, 4(t8)
	lw      t9, 4(t9)
	sll     t5, 4
	mfc2    t1, r7
	add     t5, a2
	slti    at, t1, 0xA02
	beqz    at, loc_7E634
	slti    at, t1, 0x21
	bnez    at, loc_7E634
	sll     t1, 2
	srl     t2, t9, 7
	and     t2, fp
	srl     t3, t9, 10
	andi    t3, 0xF800
	srl     t9, 13
	andi    t9, 0xF8
	or      t9, t3
	or      t9, t2
	lw      t4, 8(t5)
	jal     UnpackRGB
	move    at, t4
	cfc2    at, r28
	lw      t2, 0(t5)
	lw      t3, 4(t5)
	lw      t5, 0xC(t5)
	subu    t2, at
	jal     SubDiv4
	add     t1, a3

	loc_7E634:
	beqz    v0, loc_7E64C
	addi    a1, 4
	bnez    v1, loc_7E52C
	addi    v1, -1
	j       loc_7E524
	lw      t0, 0(a1)

	loc_7E64C:
	ctc2    zero, r22
	ctc2    zero, r23
	j       DrawExit
	nop

	MakeMono:
	li      at, 0x421
	ctc2    at, r29
	lw      t0, 0(a0)
	li      v0, 0x3FFF
	li      v1, 0xD371
	ori     v1, 0xF947
	li      t4, 0x41C6
	ori     t4, 0x4E6D

	loc_7FA04:
	mult    v1, t4
	srl     t3, t0, 26
	srl     t2, t0, 21
	srl     t1, t0, 16
	andi    t3, 0x1F
	andi    t2, 0x1F
	andi    t1, 0x1F
	mtc2    t3, r17
	mtc2    t2, r18
	mtc2    t1, r19
	addi    a0, 4
	nop
	nop
	cop2    0x158002D
	srl     t2, t0, 10
	srl     t1, t0, 5
	andi    t2, 0x1F
	andi    t1, 0x1F
	andi    t0, 0x1F
	mtc2    t2, r17
	mtc2    t1, r18
	mtc2    t0, r19
	mfc2    t1, r7
	nop
	nop
	cop2    0x158002D
	mflo    v1
	addiu   v1, 0x3039
	lw      t0, 0(a0)
	mfc2    at, r7
	srl     t3, v1, 16
	srl     t5, v1, 24
	andi    t3, 1
	andi    t5, 1
	sltiu   t2, t1, 0xF
	bnez    t2, loc_7FA8C
	sltiu   t2, at, 0xF
	li      t1, 0xF

	loc_7FA8C:
	bnez    t2, loc_7FA98
	sub     t1, t3
	li      at, 0xF

	loc_7FA98:
	bgez    t1, loc_7FAA4
	sub     at, t5
	move    t1, zero

	loc_7FAA4:
	bgez    at, loc_7FAB0
	sll     t1, 4
	move    at, zero

	loc_7FAB0:
	or      t1, at
	sb      t1, 0(a1)
	addi    a1, 1
	bnez    v0, loc_7FA04
	addi    v0, -1
	li      v0, 0xAA
	ctc2    v0, r29
	jr      ra
	nop
#endif
	UNIMPLEMENTED();
}
