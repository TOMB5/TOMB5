#include "DELTAPAK_S.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#include "MATHS.H"
#include "SETUP.H"
#include "SPECIFIC.H"

void DrawCutSeqActors()//90DCC(<),
{
	struct NEW_CUTSCENE* cut;//$s3

	cut = &GLOBAL_cutme[0];
	//a0 = meshes
	//v0 = cut->numactors
	//s6 = 1

	if (1 < cut->numactors)
	{
		mPushMatrix();

		//loc_90E1C
		mPushMatrix();

		//v1 = 1 << 2
		//s7 = cutseq_meshbits[1];//$v1 shft
		//fp = cutseq_meshswapbits[1];//$v1 shft
		//v0 = 0x80000000 & cutseq_meshbits[1];

		if (0x80000000 & cutseq_meshbits[1])
		{
			//v0 = &actor_pnodes[1];//$v1 shft

			//v1 = 1 << 3
			//v1 = &cut[2];
			sizeof(struct NEW_CUTSCENE);
		}//loc_90FDC
	}//loc_91000

#if 0
addu    $v1, $s3, $v1
lh      $a1, 0x1E($v1)
lw      $a0, 0($v0)
li      $a2, 0xA60FC
jal     sub_91030
addiu   $a1, 1
sll     $v1, $s6, 3
addu    $v1, $s3, $v1
lh      $v1, 0x1C($v1)
lw      $a0, 4($s3)
lw      $a1, 8($s3)
lw      $a2, 0xC($s3)
li      $v0, 0x1F2480
sll     $v1, 6
jal     sub_76568
addu    $s4, $v1, $v0
jal     sub_91110
nop
lh      $v0, 2($s4)
lw      $v1, 4($s4)
sll     $v0, 2
addu    $s1, $s0, $v0
lw      $v0, 0x2030($gp)
sll     $v1, 2
li      $a2, 0xA60FC
lh      $a0, 0xC($a2)
lh      $a1, 0xE($a2)
lh      $a2, 0x10($a2)
jal     sub_7658C
addu    $s2, $v0, $v1
addiu   $a0, $sp, 0x48+var_38
move    $a1, $zero
li      $v0, 0xA610E
jal     sub_768BC
sw      $v0, 0x48+var_38($sp)
andi    $v0, $s7, 1
beqz    $v0, loc_90F3C
andi    $v0, $fp, 1
beqz    $v0, loc_90F1C
lw      $a0, 0($s1)
lw      $a0, 4($s1)

loc_90F1C:
addiu   $at, $s6, -1
bnez    $at, loc_90F34
nop
lw      $a1, 0x410($gp)
jal     sub_7FAD4
addiu   $ra, 8

loc_90F34:
jal     sub_7EEC4
li      $a1, 0xFFFFFFFF

loc_90F3C:
lh      $s4, 0($s4)
li      $s5, 1
addiu   $s4, -1
blez    $s4, loc_90FDC
addiu   $s1, 8

loc_90F50:
lw      $a1, 0($s2)
addiu   $s4, -1
andi    $v0, $a1, 1
beqz    $v0, loc_90F6C
andi    $a1, 2
jal     sub_76520
nop

loc_90F6C:
beqz    $a1, loc_90F7C
sll     $s5, 1
jal     sub_764D0
nop

loc_90F7C:
lw      $a0, 4($s2)
lw      $a1, 8($s2)
jal     sub_7658C
lw      $a2, 0xC($s2)
addiu   $a0, $sp, 0x48+var_38
jal     sub_768BC
move    $a1, $zero
and     $v0, $s5, $s7
beqz    $v0, loc_90FD0
and     $v0, $s5, $fp
beqz    $v0, loc_90FB0
lw      $a0, 0($s1)
lw      $a0, 4($s1)

loc_90FB0:
addiu   $at, $s6, -1
bnez    $at, loc_90FC8
nop
lw      $a1, 0x410($gp)
jal     sub_7FAD4
addiu   $ra, 8

loc_90FC8:
jal     sub_7EEC4
li      $a1, 0xFFFFFFFF

loc_90FD0:
addiu   $s2, 0x10
bnez    $s4, loc_90F50
addiu   $s1, 8

loc_90FDC:
jal     sub_76520
nop
lh      $v1, 0($s3)
addiu   $s6, 1
slt     $v1, $s6, $v1
bnez    $v1, loc_90E1C
nop
jal     sub_76520
nop

loc_91000:
lw      $ra, 0x48+var_4($sp)
lw      $fp, 0x48+var_8($sp)
lw      $s7, 0x48+var_C($sp)
lw      $s6, 0x48+var_10($sp)
lw      $s5, 0x48+var_14($sp)
lw      $s4, 0x48+var_18($sp)
lw      $s3, 0x48+var_1C($sp)
lw      $s2, 0x48+var_20($sp)
lw      $s1, 0x48+var_24($sp)
lw      $s0, 0x48+var_28($sp)
jr      $ra
addiu   $sp, 0x48
#endif
}

void updateAnimFrame(struct PACKNODE* node, int flags, short* frame)// (F)
{
	frame[7] = 3 * node->yrot_run;

	short x = 3 * node->xrot_run;
	short z = 3 * node->zrot_run;

	switch (cutrot)
	{
	case 0:
		frame[6] = x;
		frame[8] = z;
		break;
	case 1:
		frame[6] = z;
		frame[8] = -x;
		break;
	case 2:
		frame[6] = -x;
		frame[8] = -z;
		break;
	case 3:
		frame[6] = -z;
		frame[8] = x;
		break;
	}

	short* next = frame + 9;

	for (int i = 1; i < flags; i++, next += 2)
	{
		short x = node[i].yrot_run;
		short y = node[i].zrot_run;
		short z = node[i].xrot_run;

		if (cutrot && i == 1)
		{
			x = (x + ((short)cutrot << 8)) & 0x3FF;
		}

		next[0] = (y | ((x | (z << 10)) << 10)) >> 16;
		next[1] = y | ((x | (z << 10)) << 10);
	}
}

int GetTrackWord(unsigned long off, char* packed, unsigned char packmethod)
{
	int a0 = off * packmethod;
	int v0 = a0 >> 3;
	packed = &packed[v0];
	a0 &= 7;
	unsigned int at = ((unsigned char*)packed)[0] | (((unsigned char*)packed)[1] << 8) | (((unsigned char*)packed)[2] << 16) | (((unsigned char*)packed)[3] << 24);
	at = at >> a0;
	unsigned int v1 = (1 << packmethod) - 1;
	at &= v1;
	packmethod -= 1;
	v0 = (1 << packmethod);
	v0 = at & v0;

	if (v0 != 0)
	{
		v0 = v1 ^ -1;///@CHECKME nor     $v0, $zero, $v1
		at |= v0;
	}
	else
	{
		v0 = v1 ^ -1;///@CHECKME nor     $v0, $zero, $v1
	}
	//loc_90DC0
	v0 = at << 16;
	v0 >>= 16;

	return v0;
}

void DecodeTrack(char* packed, struct RTDECODE* decode)//90BD8(<), ?
{
	//v0 = decode->decodetype
	//a3 = decode
	//t1 = packed

	if (decode->decodetype == 0)
	{
		//a0 = decode->off
		//a2 = decode->packmethod
		//a1 = packed
		//GetTrackWord(decode->off, packed, decode->packmethod);

	}//loc_90CD0

#if 0
jal     sub_90D58
move    $a1, $t1
move    $t0, $v0
andi    $v0, $t0, 0x20
bnez    $v0, loc_90CA0
andi    $v0, $t0, 0xF
li      $v0, 2
sb      $v0, 0xC($a3)
andi    $v0, $t0, 0x10
beqz    $v0, loc_90C70
move    $a1, $t1
lw      $a0, 4($a3)
lbu     $a2, 0xD($a3)
jal     sub_90D58
addiu   $a0, 1
move    $a1, $t1
andi    $v1, $t0, 7
sll     $v1, 5
andi    $v0, 0x1F
or      $v1, $v0
lbu     $a2, 0xD($a3)
lw      $a0, 4($a3)
sh      $v1, 8($a3)
jal     sub_90D58
addiu   $a0, 2
sh      $v0, 0xA($a3)
lw      $v0, 4($a3)
lw      $v1, 0($a3)
addiu   $v0, 3
j       loc_90CC8
addiu   $v1, -3

loc_90C70:
lw      $a0, 4($a3)
lbu     $a2, 0xD($a3)
jal     sub_90D58
addiu   $a0, 1
sh      $v0, 0xA($a3)
andi    $v0, $t0, 7
sh      $v0, 8($a3)
lw      $v0, 4($a3)
lw      $v1, 0($a3)
addiu   $v0, 2
j       loc_90CC8
addiu   $v1, -2

loc_90CA0:
bnez    $v0, loc_90CAC
nop
li      $v0, 0x10

loc_90CAC:
sh      $v0, 8($a3)
li      $v0, 1
sb      $v0, 0xC($a3)
lw      $v0, 4($a3)
lw      $v1, 0($a3)
addiu   $v0, 1
addiu   $v1, -1

loc_90CC8:
sw      $v0, 4($a3)
sw      $v1, 0($a3)

loc_90CD0:
lbu     $v1, 0xC($a3)
li      $v0, 2
bne     $v1, $v0, loc_90D08
nop
lhu     $v0, 8($a3)
nop
addiu   $v0, -1
sh      $v0, 8($a3)
bnez    $v0, loc_90CFC
nop
sb      $zero, 0xC($a3)

loc_90CFC:
lh      $v0, 0xA($a3)
j       loc_90D50
nop

loc_90D08:
lw      $a0, 4($a3)
lbu     $a2, 0xD($a3)
jal     sub_90D58
move    $a1, $t1
lhu     $v1, 8($a3)
lw      $a0, 4($a3)
lw      $a1, 0($a3)
addiu   $v1, -1
addiu   $a0, 1
addiu   $a1, -1
sh      $v1, 8($a3)
andi    $v1, 0xFFFF
sw      $a0, 4($a3)
bnez    $v1, loc_90D48
sw      $a1, 0($a3)
sb      $zero, 0xC($a3)

loc_90D48:
sll     $v0, 16
sra     $v0, 16

loc_90D50:
jr      $t2
nop
#endif
}

void DecodeAnim(struct PACKNODE* node, int a1, int frame, short a3)//90A88(<), ?
{
	int t4;
	//t7 = a3
	//t3 = node
	//t5 = a1
	struct PACKNODE* pn = NULL;//$t0

	if (frame == 0)
	{
		t4 = 0;
		if (a1 > 0)
		{
			pn = node;
			//loc_90AA8
			do
			{
				t4++;

				pn->decode_x.off = 0;
				pn->decode_x.counter = 0;
				pn->decode_x.data = 0;
				pn->decode_x.decodetype = 0;

				pn->decode_y.off = 0;
				pn->decode_y.counter = 0;
				pn->decode_y.data = 0;
				pn->decode_y.decodetype = 0;

				pn->decode_z.off = 0;
				pn->decode_z.counter = 0;
				pn->decode_z.data = 0;
				pn->decode_z.decodetype = 0;

				pn->xrot_run = (unsigned short)pn->xkey;
				pn->yrot_run = (unsigned short)pn->ykey;
				pn->zrot_run = (unsigned short)pn->zkey;

				pn->decode_x.length = pn->xlength;
				pn->decode_y.length = pn->ylength;
				pn->decode_z.length = pn->zlength;
				pn++;
			} while (t4 < a1);
		}//loc_90BD0
	}
	else
	{
		//loc_90B14
		DecodeTrack(node->xpacked, &node->decode_x);
	}
#if 0
loc_90B14:
lw      $a0, 0x48($t3)
jal     sub_90BD8
addiu   $a1, $t3, 0xC

addiu   $a1, $t3, 0x1C
lhu     $v1, 0($t3)
lw      $a0, 0x4C($t3)
addu    $v1, $v0
jal     sub_90BD8
sh      $v1, 0($t3)

addiu   $a1, $t3, 0x2C
lhu     $v1, 2($t3)
lw      $a0, 0x50($t3)
addu    $v1, $v0
jal     sub_90BD8
sh      $v1, 2($t3)

lhu     $v1, 4($t3)
li      $t4, 1
addu    $v1, $v0
slt     $v0, $t4, $t5
beqz    $v0, loc_90BD0
sh      $v1, 4($t3)
addiu   $t3, 0x54

loc_90B6C:
lw      $a0, 0x48($t3)
jal     sub_90BD8
addiu   $a1, $t3, 0xC

addiu   $a1, $t3, 0x1C
lhu     $v1, 0($t3)
lw      $a0, 0x4C($t3)
addu    $v1, $v0
and     $v1, $t7
jal     sub_90BD8
sh      $v1, 0($t3)

addiu   $a1, $t3, 0x2C
lhu     $v1, 2($t3)
lw      $a0, 0x50($t3)
addu    $v1, $v0
and     $v1, $t7
jal     sub_90BD8
sh      $v1, 2($t3)

lhu     $v1, 4($t3)
addiu   $t4, 1
addu    $v1, $v0
and     $v1, $t7
sh      $v1, 4($t3)
slt     $v0, $t4, $t5
bnez    $v0, loc_90B6C
addiu   $t3, 0x54

loc_90BD0:
jr      $t6
nop
#endif
}
