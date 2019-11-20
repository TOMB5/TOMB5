#include "CALCLARA.H"

#include "SPECIFIC.H"
#include "DRAW.H"
#include "MATHS.H"
#include "LARA.H"
#include "GTEREG.H"

void S_SetupClutAdder(long underwater)
{
	DQB = underwater;
}

void DEL_CalcLaraMatrices_Normal_ASM(short* frame, long* bone, int flag)
{
#if 0//Nope
	S_Warn("[DEL_CalcLaraMatrices_Normal_ASM] - Unimplemented!\n");

	mPushMatrix();

	if (flag != 0 && flag != 2)
		mSetTrans(0, 0, 0);
	else
		mTranslateAbsXYZ(lara_item->pos.x_pos, lara_item->pos.y_pos, lara_item->pos.z_pos);

	mRotYXZ(lara_item->pos.y_rot, lara_item->pos.x_rot, lara_item->pos.z_rot);

	if (flag == 2)
	{
		ScaleCurrentMatrix({ -4096, -4096, -4096 });
	}

	mPushMatrix();

	mTranslateXYZ(frame[6], frame[7], frame[8]);
	/**/
	mPopMatrix();
	mPopMatrix();
#endif
}

void DEL_CalcLaraMatrices_Interpolated_ASM(short* frame1, short* frame2, int frac, int rate, long* bone, int flag)
{
#if 0
	lui     t8, 0x1F80
	sw      s0, 0x00(t8)
	sw      s1, 0x04(t8)
	sw      s2, 0x08(t8)
	sw      ra, 0x20(t8)
	sw      a2, 0xB8(t8)
	sw      a3, 0xBC(t8)
	move    s0, a0
	move    s1, a1
	addiu   a0, 0x12
	addiu   a1, 0x12
	sw      a0, 0x24(t8)
	sw      a1, 0x28(t8)
	lw      t9, lara_item-GP_ADDR(gp)
	la      s2, rcossin_tbl
	jal     snaff_current_gte_matrix_V1
	addiu   a0, t8, 0x120
	lw      a3, 0x14(sp)
	nop
	andi    a2, a3, 1
	beqz    a2, loc_843C8
	andi    a3, 2
	la      a0, lara_joint_matrices
	ctc2    zero, r5
	ctc2    zero, r6
	ctc2    zero, r7
	j       loc_843FC
	sw      a0, 0x34(t8)

	loc_843C8:
	la      a0, lara_matrices
	sw      a0, 0x34(t8)
	lw      a0, 0x40(t9)
	lw      a1, 0x44(t9)
	jal     mTranslateAbsXYZ
	lw      a2, 0x48(t9)
	beqz    a3, loc_843FC
	li      a0, 0
	li      a1, 0xFFFFF000
	li      a2, 0xFFFFF000
	jal     ScaleCurrentMatrix
	li      a3, 0xFFFFF000

	loc_843FC:
	lh      a0, 0x4E(t9)
	lh      a1, 0x4C(t9)
	jal     mRotYXZ
	lh      a2, 0x50(t9)
	jal     snaff_current_gte_matrix_V1
	addiu   a0, t8, 0x100
	ctc2    t0, r8
	ctc2    t1, r9
	ctc2    t2, r10
	ctc2    t3, r11
	ctc2    t4, r12
	ctc2    t5, r13
	ctc2    t6, r14
	ctc2    t7, r15
	lh      a0, 0xC(s0)
	lh      a1, 0xE(s0)
	jal     mTranslateXYZ
	lh      a2, 0x10(s0)
	lh      a3, 0xC(s1)
	lh      a1, 0xE(s1)
	jal     iTranslateXYZ2
	lh      a2, 0x10(s1)
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	lw      s0, 0x34(t8)
	jal     InterpolateMatrix
	move    a0, s0
	lw      s1, 0x10(sp)
	jal     DEL_stash_both_matrices
	addiu   a0, t8, 0xC0
	li      t9, 6

	loc_84480:
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 4
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x20
	addiu   t9, -1
	li      at, 3
	bne     t9, at, loc_844B8
	addiu   s1, 0x10
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0

	loc_844B8:
	bnez    t9, loc_84480
	addiu   s0, 0x20
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0
	addiu   s0, -0xC0
	addiu   s1, -0x60
	lw      t9, anims-GP_ADDR(gp)
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0x64
	lh      a0, lara+0x2A-GP_ADDR(gp)
	li      v0, 0xFFFFFFFF
	beq     a0, v0, loc_84594
	li      v0, 5
	lh      v1, lara+0x4-GP_ADDR(gp)
	nop
	bne     v1, v0, loc_84594
	sll     v0, a0, 2
	addu    v0, a0
	sll     v0, 2
	subu    v0, a0
	lw      v1, items-GP_ADDR(gp)
	sll     v0, 3
	addu    v0, v1
	lh      v1, 0xE(v0)
	nop
	beqz    v1, loc_84534
	li      v0, 2
	beq     v1, v0, loc_84534
	li      v0, 4
	bne     v1, v0, loc_84594
	nop

	loc_84534:
	lh      v1, lara+0xCE-GP_ADDR(gp)
	nop
	sll     v0, v1, 2
	addu    v0, v1
	sll     v0, 3
	addu    v0, t9
	lh      v0, 4(v0)
	lh      v1, lara+0xCC-GP_ADDR(gp)
	sra     v0, 8
	mult    v1, v0
	li      a1, 7
	lw      v0, lara+0xC8-GP_ADDR(gp)
	mflo    t0
	nop
	nop
	sll     v1, t0, 1
	addu    v0, v1
	addiu   v0, 0x12
	sw      v0, 0x28(t8)
	jal     mRotSuperPackedYXZ
	sw      v0, 0x24(t8)
	li      a1, 7
	jal     iRotSuperPackedYXZ
	addiu   ra, 0x10

	loc_84594:
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	lh      a0, lara+0xAE-GP_ADDR(gp)
	lh      a1, lara+0xB0-GP_ADDR(gp)
	jal     mRotYXZ
	lh      a2, lara+0xB2-GP_ADDR(gp)
	lh      a0, lara+0xAE-GP_ADDR(gp)
	lh      a1, lara+0xB0-GP_ADDR(gp)
	jal     iRotYXZ
	lh      a2, lara+0xB2-GP_ADDR(gp)
	jal     InterpolateMatrix
	addiu   a0, s0, 0xE0
	jal     DEL_stash_both_matrices
	addiu   a0, t8, 0xC0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xD4
	lw      v0, 0x24(t8)
	lw      v1, 0x28(t8)
	li      a1, 6
	sw      v0, 0x2C(t8)
	jal     mRotSuperPackedYXZ
	sw      v1, 0x30(t8)
	jal     iRotSuperPackedYXZ
	li      a1, 6
	lw      v0, 0x2C(t8)
	lw      v1, 0x30(t8)
	sw      v0, 0x24(t8)
	sw      v1, 0x28(t8)
	lh      a0, lara+0xA8-GP_ADDR(gp)
	lh      a1, lara+0xAA-GP_ADDR(gp)
	jal     mRotYXZ
	lh      a2, lara+0xAC-GP_ADDR(gp)
	lh      a0, lara+0xA8-GP_ADDR(gp)
	lh      a1, lara+0xAA-GP_ADDR(gp)
	jal     iRotYXZ
	lh      a2, lara+0xAC-GP_ADDR(gp)
	jal     InterpolateMatrix
	addiu   a0, s0, 0x100
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0x74
	lhu     a0, lara+0x2-GP_ADDR(gp)
	move    v1, zero
	li      v0, 2
	beq     a0, v0, loc_84670
	li      v0, 3
	beq     a0, v0, loc_84670
	li      v0, 4
	beq     a0, v0, loc_84670
	li      v0, 5
	bne     a0, v0, loc_8469C
	nop

	loc_84670:
	lh      v1, lara+0x4-GP_ADDR(gp)
	la      v0, .firearms_jumptable
	sltiu   at, v1, 0xA    # switch 9 cases
	beqz    at, def_84694   # jumptable 00084694 default case
	sll     v1, 2
	addu    v1, v0
	lw      v1, 0(v1)
	nop
	jr      v1
	nop

	loc_8469C:
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x120
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0x84
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x140
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0x94
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x160
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xA4
	lw      v0, lara+0x44-GP_ADDR(gp)
	nop
	andi    v0, 1
	beqz    v0, loc_84778
	nop
	lh      v1, lara+0xBA-GP_ADDR(gp)
	nop
	sll     v0, v1, 2
	addu    v0, v1
	sll     v0, 3
	addu    v0, t9
	lh      v1, lara+0xB8-GP_ADDR(gp)
	lh      a0, 0x18(v0)
	lh      v0, 4(v0)
	subu    v1, a0
	sra     v0, 8
	mult    v1, v0
	li      a1, 0xB
	lw      v0, lara+0xB4-GP_ADDR(gp)
	mflo    t0
	sll     v1, t0, 1
	addu    v0, v1
	addiu   v0, 0x12
	sw      v0, 0x28(t8)
	jal     mRotSuperPackedYXZ
	sw      v0, 0x24(t8)
	li      a1, 0xB
	jal     iRotSuperPackedYXZ
	addiu   ra, 0x10

	loc_84778:
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x180
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xB4
	move    a1, zero
	jal     mRotSuperPackedYXZ
	addiu   ra, 0x314

	loc_847A4:
	jal     InterpolateArmMatrix
	addiu   a0, t8, 0x100
	lh      a0, lara+0xD2-GP_ADDR(gp)
	lh      a1, lara+0xD4-GP_ADDR(gp)
	jal     mRotYXZ
	lh      a2, lara+0xD6-GP_ADDR(gp)
	lh      v1, lara+0xCE-GP_ADDR(gp)
	nop
	sll     v0, v1, 2
	addu    v0, v1
	sll     v0, 3
	addu    v0, t9
	lh      v1, lara+0xCC-GP_ADDR(gp)
	lh      a0, 0x18(v0)
	lh      v0, 4(v0)
	subu    v1, a0
	sra     v0, 8
	mult    v1, v0
	li      a1, 8
	lw      v0, lara+0xC8-GP_ADDR(gp)
	mflo    t0
	sll     v1, t0, 1
	addu    v0, v1
	addiu   v0, 0x12
	jal     mRotSuperPackedYXZ
	sw      v0, 0x24(t8)
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x120
	jal     Hardcore_mTranslateXYZ
	addiu   a2, s1, 0x84
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x140
	jal     Hardcore_mTranslateXYZ
	addiu   a2, s1, 0x94
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x160
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xA4
	jal     InterpolateArmMatrix
	addiu   a0, t8, 0x100
	lh      a0, lara+0xBE-GP_ADDR(gp)
	lh      a1, lara+0xC0-GP_ADDR(gp)
	lh      a2, lara+0xC2-GP_ADDR(gp)
	jal     mRotYXZ
	addiu   ra, 0xE8

	loc_84870:
	jal     InterpolateArmMatrix
	addiu   a0, t8, 0x100
	lh      a0, lara+0xAE-GP_ADDR(gp)
	lh      a1, lara+0xB0-GP_ADDR(gp)
	jal     mRotYXZ
	lh      a2, lara+0xB2-GP_ADDR(gp)
	lh      a0, lara+0xAE-GP_ADDR(gp)
	lh      a1, lara+0xB0-GP_ADDR(gp)
	jal     iRotYXZ
	lh      a2, lara+0xB2-GP_ADDR(gp)
	lh      v1, lara+0xCE-GP_ADDR(gp)
	nop
	sll     v0, v1, 2
	addu    v0, v1
	sll     v0, 3
	addu    v0, t9
	lh      v1, lara+0xCC-GP_ADDR(gp)
	lh      a0, 0x18(v0)
	lh      v0, 4(v0)
	subu    v1, a0
	sra     v0, 8
	mult    v1, v0
	li      a1, 8
	lw      v0, lara+0xC8-GP_ADDR(gp)
	mflo    t0
	sll     v1, t0, 1
	addu    v0, v1
	addiu   v0, 0x12
	jal     mRotSuperPackedYXZ
	sw      v0, 0x24(t8)
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x120
	jal     Hardcore_mTranslateXYZ
	addiu   a2, s1, 0x84
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x140
	jal     Hardcore_mTranslateXYZ
	addiu   a2, s1, 0x94
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x160
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xA4
	jal     InterpolateArmMatrix
	addiu   a0, t8, 0x100
	lh      a0, lara+0xAE-GP_ADDR(gp)
	lh      a1, lara+0xB0-GP_ADDR(gp)
	jal     mRotYXZ
	lh      a2, lara+0xB2-GP_ADDR(gp)
	lh      a0, lara+0xAE-GP_ADDR(gp)
	lh      a1, lara+0xB0-GP_ADDR(gp)
	jal     iRotYXZ
	lh      a2, lara+0xB2-GP_ADDR(gp)
	lh      v1, lara+0xBA-GP_ADDR(gp)
	nop
	sll     v0, v1, 2
	addu    v0, v1
	sll     v0, 3
	addu    v0, t9
	lh      v1, lara+0xB8-GP_ADDR(gp)
	lh      a0, 0x18(v0)
	lh      v0, 4(v0)
	subu    v1, a0
	sra     v0, 8
	mult    v1, v0
	li      a1, 0xB
	lw      v0, lara+0xB4-GP_ADDR(gp)
	mflo    t0
	sll     v1, t0, 1
	addu    v0, v1
	addiu   v0, 0x12
	jal     mRotSuperPackedYXZ
	sw      v0, 0x24(t8)
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x180
	jal     Hardcore_mTranslateXYZ
	addiu   a2, s1, 0xB4
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     snaff_current_gte_matrix_V1
	addiu   a0, s0, 0x1A0
	jal     Hardcore_mTranslateXYZ
	addiu   a2, s1, 0xC4
	jal     mRotSuperPackedYXZ
	move    a1, zero
	addiu   a0, s0, 0x1C0
	jal     snaff_current_gte_matrix_V1
	addiu   ra, 0x104

	loc_849E4:
	lh      v1, lara+0xCE-GP_ADDR(gp)
	nop
	sll     v0, v1, 2
	addu    v0, v1
	sll     v0, 3
	addu    v0, t9
	lh      v0, 4(v0)
	lh      v1, lara+0xCC-GP_ADDR(gp)
	sra     v0, 8
	mult    v1, v0
	li      a1, 8
	lw      v0, lara+0xC8-GP_ADDR(gp)
	mflo    t0
	sll     v1, t0, 1
	addu    v0, v1
	addiu   v0, 0x12
	sw      v0, 0x28(t8)
	jal     mRotSuperPackedYXZ
	sw      v0, 0x24(t8)
	jal     iRotSuperPackedYXZ
	li      a1, 8
	jal     InterpolateMatrix
	addiu   a0, s0, 0x120
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0x84
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x140
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0x94
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x160
	jal     DEL_restore_both_matrices
	addiu   a0, t8, 0xC0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xA4
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x180
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xB4
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x1A0
	jal     Hardcore_iTranslateXYZ
	addiu   a2, s1, 0xC4
	jal     mRotSuperPackedYXZ
	move    a1, zero
	jal     iRotSuperPackedYXZ
	move    a1, zero
	jal     InterpolateMatrix
	addiu   a0, s0, 0x1C0

	def_84694:
	jal     mLoadMatrix
	addiu   a0, t8, 0x120
	lw      ra, 0x20(t8)
	lw      s2, 8(t8)
	lw      s1, 4(t8)
	lw      s0, 0(t8)
	jr      ra
	nop
#endif
}

short* GetBoundsAccurate(struct ITEM_INFO* item)//858F8, 8793C
{
	int rate;
	short* frmptr[2];
	int frac = GetFrames(item, frmptr, &rate);

	if (frac == 0)
		return frmptr[0];

	short* bptr = interpolated_bounds;

	for (int i = 0; i < 6; i++, bptr++, frmptr[0]++, frmptr[1]++)
	{
		*bptr = *frmptr[0] + (*frmptr[1] - *frmptr[0]) * frac / rate;
	}

	return interpolated_bounds;
}

void snaff_current_gte_matrix_V1(MATRIX3D* m)
{
	UNIMPLEMENTED();
}

void GetLaraJointPos(struct PHD_VECTOR* pos, long joint)
{
	UNIMPLEMENTED();
}

short* GetBestFrame(struct ITEM_INFO* item)
{
	UNIMPLEMENTED();
	return NULL;
}