#include "DRAWSKY.H"

#include "GAMEFLOW.H"
#include "GPU.H"

#include "GTEREG.H"

void DrawSkyMesh(short* mesh)
{
	int s7;
	char* s5;
	unsigned long* t9;
	int v0;
	int s6;
	int a1;
	int scratchPad[256];
	int* a2;
	int at;
	int v1;
	int t0;
	int t1;
	int t2;
	int t3;
	int t4;
	int t5;
	int* a0;
	int a3;
	int t8;
	int t7;
	int t6;

	s7 = gfLevelFlags & 0x200;
	s5 = db.polyptr;
	t9 = db.ot;
	v0 = mesh[2];
	s6 = t9[2563];
	mesh += 3;
	a1 = v0 >> 16;
	v0 &= 0xFF;
	a1 += (int)mesh;
	a2 = &scratchPad[0];
	at = v0 << 3;
	v1 = v0;

	t0 = mesh[0];
	t1 = mesh[1];
	t2 = mesh[2];
	t3 = mesh[3];
	t4 = mesh[4];
	t5 = mesh[5];

	//loc_7DD00
	do
	{
		VX0 = t0 & 0xFFFF;
		VY0 = t0 >> 16;
		VZ0 = t1;

		VX1 = t2 & 0xFFFF;
		VY1 = t2 >> 16;
		VZ1 = t3;

		VX2 = t4 & 0xFFFF;
		VY2 = t4 >> 16;
		VZ2 = t5;

		mesh += 6;
		v0 -= 3;

		docop2(0x280030);

		t0 = mesh[0];
		t1 = mesh[1];
		t2 = mesh[2];
		t3 = mesh[3];
		t4 = mesh[4];
		t5 = mesh[5];

		a2[0] = SXY0;
		a2[1] = SXY1;
		a2[2] = SXY2;
		a2 += 3;
	} while (v0 > 0);

	a0 = &scratchPad[0];
	struct PSXTEXTSTRUCT* a22 = &psxtextinfo[0];
	v0 = ((int*)a1)[0];
	a3 = 0xF80000;
	at = v0 >> 16;
	DQA = at;
	v0 &= 0xFFFF;
	a1 += 4;
	if (v0 != 0)
	{
		t5 = ((int*)s5)[4164];
	}
	//loc_7DD78
	v0 = DQA;
	t0 = ((int*)a1)[0];

	if (v0 != 0)
	{
		//loc_7DD84
		a1 += 4;
		v1 = 1;
		//loc_7DD8C
		t1 = ((int*)a1)[0];
		v0--;
		t4 = (t1 >> 22) & 0x3FC;
		t4 += (int)a0;
		t8 = (t1 >> 14) & 0x3FC;
		t8 += (int)a0;
		t7 = (t1 >> 6) & 0x3FC;
		t7 += (int)a0;
		t6 = (t1 << 2) & 0x3FC;
		t6 += (int)a0;

		SXY0 = ((int*)t6)[0];
		SXY1 = ((int*)t7)[0];
		SXY2 = ((int*)t8)[0];

		docop2(0x1400006);
		t6 = 0x3C808080;

		t4 = ((int*)t4)[0];
		at = MAC0;

		t5 = (t0 & 0xFFF) << 4;
		t0 >>= 16;

		if (at >= 0)
		{
			t1 = SXY0;
			t2 = SXY1;
			t3 = SXY2;

			at = HorClipXY(t1, t2, t3, t4);

			
		}//loc_7DEB4
	}//loc_7DECC


#if 0

loc_7DE80:
sw      $t6, 4($s5)
sw      $t6, 0x10($s5)
sw      $at, 0x1C($s5)
sw      $at, 0x28($s5)
sw      $t2, 0xC($s5)
sw      $t3, 0x18($s5)
sw      $t4, 0x24($s5)
sw      $t5, 0x30($s5)
lui     $at, 0xC00
or      $t2, $s6, $at
sw      $t2, 0($s5)
move    $s6, $s5
addi    $s5, 0x34

loc_7DEB4:
beqz    $v0, loc_7DECC
addi    $a1, 4
bnez    $v1, loc_7DD8C
addi    $v1, -1
j       loc_7DD84
lw      $t0, 0($a1)

loc_7DECC:
sw      $s5, 0x3644($gp)
sw      $s6, 0x280C($t9)
lw      $ra, 0x34+var_4($sp)
lw      $s0, 0x34+var_24($sp)
lw      $s1, 0x34+var_20($sp)
lw      $s2, 0x34+var_1C($sp)
lw      $s3, 0x34+var_18($sp)
lw      $s4, 0x34+var_14($sp)
lw      $s5, 0x34+var_10($sp)
lw      $s6, 0x34+var_C($sp)
lw      $s7, 0x34+var_8($sp)
jr      $ra
addiu   $sp, 0x34
#endif
}

int HorClipXY(int t1, int t2, int t3, int t4)//7DF00, ? (F)
{
	int s0;
	int s1;
	int s2;
	int s3;
	int s4;

	s0 = RGB1;
	s1 = RGB2;

	if (!(t1 < s0) || !(t2 < s0) || !(t3 < s0) || !(t4 < s0))
	{
		//loc_7DF28
		if (t1 < s1 || t2 < s1 || t3 < s1 || t3 < s1)
		{
			//loc_7DF48
			s2 = t1 << 16;
			s3 = t2 << 16;
			s0 = t3 << 16;
			s4 = R | (G << 8) | (B << 16) | (CODE << 24);
			s1 = t4 << 16;

			if (!(s2 < s4) || !(s3 < s4) || !(s0 < s4) || !(s1 < s4))
			{
				//loc_7DF7C
				s4 = RGB0;

				if (s2 < s4 || s3 < s4 || s0 < s4 || s1 < s4)
				{
					return 0;
				}//locret_7DFB4
			}//locret_7DFB4
		}//locret_7DFB4
	}//locret_7DFB4

	return 1;
}

void DrawFlatSky_ASM(CVECTOR layer, short pos, int flags)
{
}
