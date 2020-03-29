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

void updateAnimFrame(struct PACKNODE* node, int flags, short* frame)//91030(<) (F)
{
	int at = 0;
	int v1 = 0;
	int v0 = 0;
	int a0 = 0;
	int t0 = 0;
	short* a3 = NULL;
	struct PACKNODE* a2 = NULL;

	frame[7] = (node->yrot_run << 1) + node->yrot_run;

	if (cutrot == 0)
	{
		//loc_91098
		frame[6] = (node->xrot_run << 1) + node->xrot_run;
		frame[8] = (node->zrot_run << 1) + node->zrot_run;
	}
	else if (cutrot - 1 == 0)
	{
		//loc_91088
		frame[6] = (node->zrot_run << 1) + node->zrot_run;
		frame[8] = -((node->xrot_run << 1) + node->xrot_run);
	}
	else if (cutrot - 2 == 0)
	{
		//loc_91080
		frame[6] = -((node->xrot_run << 1) + node->xrot_run);
		frame[8] = -((node->zrot_run << 1) + node->zrot_run);
	}
	else
	{
		frame[8] = (node->xrot_run << 1) + node->xrot_run;
		frame[6] = -((node->zrot_run << 1) + node->zrot_run);
	}

	//loc_910A0
	if (1 < flags)
	{
		a3 = &frames[9];
		a2 = &node[1];
		t0 = flags - 1;
		at = 1;

		//loc_910BC
		do
		{
			v1 = a2->xrot_run;
			v0 = a2->yrot_run;
			a0 = a2->zrot_run;

			a2++;
			if (at)
			{
				v0 += cutrot << 8;
				v0 &= 0x3FF;
			}//loc_910E0

			t0--;
			v1 <<= 20;
			v0 <<= 10;
			v1 |= v0;
			v1 |= a0;
			v0 = v1 >> 16;
			a3[0] = v0;
			a3[1] = v1;
			a3 += 2;
		} while (t0 != 0);
	}
	//locret_91108
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

int DecodeTrack(char* packed, struct RTDECODE* decode)//90BD8(<), ?
{
	int t0 = 0;
	int v0 = 0;

	if (decode->decodetype == 0)
	{
		t0 = GetTrackWord(decode->off, packed, decode->packmethod);

		if (!(t0 & 0x20))
		{
			decode->decodetype = 2;

			if ((t0 & 0x10))
			{
				GetTrackWord(decode->off + 1, packed, decode->packmethod);
				decode->counter = ((t0 & 7) << 5) | (GetTrackWord(decode->off + 1, packed, decode->packmethod) & 0x1F);
				decode->data = GetTrackWord(decode->off + 2, packed, decode->packmethod);
				decode->off += 3;
				decode->length -= 3;
			}
			else
			{
				//loc_90C70
				decode->data = GetTrackWord(decode->off + 1, packed, decode->packmethod);
				decode->counter = t0 & 0x7;
				decode->off += 2;
				decode->length -= 2;
			}
		}
		else
		{
			//loc_90CA0
			if (!(t0 & 0xF))
			{
				decode->counter = 16;
			}
			else
			{
				decode->counter = (t0 & 0xF);
			}

			//loc_90CAC
			decode->decodetype = 1;
			decode->off += 1;
			decode->length -= 1;
		}
	}
	//loc_90CD0
	if (decode->decodetype == 2)
	{
		if (--decode->counter == 0)
		{
			decode->decodetype = 0;
		}

		//loc_90CFC
		return decode->data;
	}

	//loc_90D08
	v0 = GetTrackWord(decode->off, packed, decode->packmethod);

	decode->counter -= 1;
	decode->off += 1;
	decode->length -= 1;

	if (!(decode->counter & 0xFFFF))
	{
		decode->decodetype = 0;
	}
	//loc_90D48
	v0 <<= 16;
	v0 >>= 16;

	return v0;
}

void DecodeAnim(struct PACKNODE* node, int a1, int frame, short a3)//90A88(<), ?
{
	int t4 = 0;

	if (frame == 0)
	{
		t4 = 0;
		if (a1 > 0)
		{
			//loc_90AA8
			do
			{
				t4++;

				node->decode_x.off = 0;
				node->decode_x.counter = 0;
				node->decode_x.data = 0;
				node->decode_x.decodetype = 0;

				node->decode_y.off = 0;
				node->decode_y.counter = 0;
				node->decode_y.data = 0;
				node->decode_y.decodetype = 0;

				node->decode_z.off = 0;
				node->decode_z.counter = 0;
				node->decode_z.data = 0;
				node->decode_z.decodetype = 0;

				node->xrot_run = (unsigned short)node->xkey;
				node->yrot_run = (unsigned short)node->ykey;
				node->zrot_run = (unsigned short)node->zkey;

				node->decode_x.length = node->xlength;
				node->decode_y.length = node->ylength;
				node->decode_z.length = node->zlength;
				node++;
			} while (t4 < a1);
		}
		//loc_90BD0
		return;
	}
	else
	{
		//loc_90B14
		node->xrot_run += DecodeTrack(node->xpacked, &node->decode_x);
		node->yrot_run += DecodeTrack(node->ypacked, &node->decode_y);
		node->zrot_run += DecodeTrack(node->zpacked, &node->decode_z);
		t4 = 1;
		node++;
		if (t4 >= a1)
		{
			return;
		}
	}

	//loc_90B6C
	do
	{
		node->xrot_run += DecodeTrack(node->xpacked, &node->decode_x) & a3;
		node->yrot_run += DecodeTrack(node->ypacked, &node->decode_y) & a3;
		node->zrot_run += DecodeTrack(node->zpacked, &node->decode_z) & a3;
		t4++;
		node++;
	} while (t4 < a1);
}
