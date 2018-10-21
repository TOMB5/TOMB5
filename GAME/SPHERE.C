#include "SPHERE.H"

#include "LARA.H"
#include "SPECIFIC.H"

char GotLaraSpheres;
int NumLaraSpheres;
struct SPHERE LaraSpheres[15];
struct SPHERE Slist[34];

int TestCollision(struct ITEM_INFO* item, struct ITEM_INFO* laraitem)//55C3C(<), 560DC(<) (F)
{
	int num1;
	int num2;
	int x1;
	int y1;
	int z1;
	int r1;
	int x;
	int y;
	int z;
	int r;
	int i;
	int j;
	unsigned long flags;
	struct SPHERE* ptr1;
	struct SPHERE* ptr2;

	num1 = GetSpheres(item, &Slist[0], 1);
	flags = 0;

	if (laraitem != item)
	{
		GotLaraSpheres = 0;
	}

	//loc_55C8C
	if (!GotLaraSpheres)
	{
		NumLaraSpheres = num2 = GetSpheres(laraitem, &LaraSpheres[0], 1);

		if (laraitem == lara_item)
		{
			GotLaraSpheres = 1;
		}
	}
	else
	{
		//loc_55CD0
		num2 = NumLaraSpheres;
	}

	laraitem->touch_bits = 0;

	//loc_55CD8
	ptr1 = &Slist[0];

	for (i = 0; i < num1; i++, ptr1++)
	{
		r1 = ptr1->r;

		if (r1 > 0)
		{
			ptr2 = &LaraSpheres[0];

			x1 = ptr1->x;
			y1 = ptr1->y;
			z1 = ptr1->z;

			//loc_55D1C
			for (j = 0; j < num2; j++, ptr2++)
			{
				r += r1;

				if (ptr2->r > 0)
				{
					x = (ptr2->x - x1) * ptr2->x;
					y = (ptr2->y - y1) * ptr2->y;
					z = (ptr2->z - z1) * ptr2->z;
					r *= r;

					if (x + y + z < r)
					{
						flags |= (1 << i);
						laraitem->touch_bits |= (1 << j);
					}//loc_55D14
				}//loc_55D14
			}
		}
	}
	//loc_55DBC
	item->touch_bits = flags;

	return flags;
}

int GetSpheres(struct ITEM_INFO* item, struct SPHERE* sptr, int worldspace)
{
#if 0
	if (item == NULL)
	{
		return 0;
	}

	//s1 = item;
	//at = a2 & 1;
	//s4 = sptr;
	if (worldspace & 1)
	{
		///@CHECK
		//s3 = item->pos.y_pos;
		//fp = item->pos.x_pos;
		//s7 = item->pos.z_pos;
		mPushUnitMatrix();
		mSetTrans(0, 0, 0);
		//ra += 0x20
	}
	//loc_8E4AC

				 loc_8E4AC:
				 move	$s7, $zero
				 jal	sub_764D0
				 move	$s3, $zero
				 lw	$a0, 0x40($s1)
				 lw	$a1, 0x44($s1)
				 lw	$a2, 0x48($s1)
				 jal	sub_76568
				 move	$fp, $zero
				 lh	$a0, 0x4E($s1)
				 lh	$a1, 0x4C($s1)
				 jal	sub_767E8
				 lh	$a2, 0x50($s1)
				 jal	sub_858C8
				 move	$a0, $s1
				 move	$s0, $v0
				 lh	$a0, 0xC($s0)
				 lh	$a1, 0xE($s0)
				 lh	$a2, 0x10($s0)
				 jal	sub_7658C
				 addiu	$s0, 0x12
				 addiu	$a0, $sp, 0x50 + var_40
				 move	$a1, $zero
				 jal	sub_768BC
				 sw	$s0, 0x50 + var_40($sp)
				 lh	$v1, 0xC($s1)
				 li	$s5, 0x1F2480
				 sll	$v1, 6
				 addu	$s5, $v1
				 lh	$v0, 2($s5)
				 lw	$v1, 0x204C($gp)
				 sll	$v0, 2
				 addu	$s6, $v1, $v0
				 lw	$v0, 4($s5)
				 lw	$v1, 0x2030($gp)
				 lw	$s0, 0($s6)
				 sll	$v0, 2
				 jal	sub_764D0
				 addu	$s2, $v1, $v0
				 lw	$at, 0x50 + var_34($sp)
				 nop
				 andi	$at, 2
				 bnez	$at, loc_8E568
				 lh	$a0, 0($s0)
				 lh	$a1, 2($s0)
				 lh	$a2, 4($s0)
				 jal	sub_7658C

				 loc_8E568 :
			 addiu	$s6, 8
				 cfc2	$t4, $5
				 cfc2	$t5, $6
				 cfc2	$t6, $7
				 lh	$v1, 6($s0)
				 addu	$t4, $fp
				 addu	$t5, $s3
				 addu	$t6, $s7
				 sw	$t4, 0($s4)
				 sw	$t5, 4($s4)
				 sw	$t6, 8($s4)
				 sw	$v1, 0xC($s4)
				 jal	sub_76520
				 addiu	$s4, 0x10
				 lh	$at, 0($s5)
				 lw	$s1, 0x3C($s1)
				 addiu	$s5, $at, -1
				 blez	$s5, loc_8E6C0
				 sw	$at, 0x50 + var_38($sp)

				 loc_8E5B4:
			 lw	$s0, 0($s2)
				 nop
				 andi	$v0, $s0, 1
				 beqz	$v0, loc_8E5D0
				 addiu	$s2, 4
				 jal	sub_76520
				 nop

				 loc_8E5D0 :
			 andi	$v0, $s0, 2
				 beqz	$v0, loc_8E5E4
				 nop
				 jal	sub_764D0
				 nop

				 loc_8E5E4 :
			 lw	$a0, 0($s2)
				 lw	$a1, 4($s2)
				 jal	sub_7658C
				 lw	$a2, 8($s2)
				 addiu	$a0, $sp, 0x50 + var_40
				 jal	sub_768BC
				 move	$a1, $zero
				 beqz	$s1, loc_8E654
				 andi	$v0, $s0, 0x1C
				 beqz	$v0, loc_8E654
				 andi	$v0, $s0, 8
				 beqz	$v0, loc_8E628
				 andi	$v0, $s0, 4
				 lh	$a0, 0($s1)
				 jal	sub_76744
				 addiu	$s1, 2
				 andi	$v0, $s0, 4

				 loc_8E628:
			 beqz	$v0, loc_8E640
				 andi	$v0, $s0, 0x10
				 lh	$a0, 0($s1)
				 jal	sub_7669C
				 addiu	$s1, 2
				 andi	$v0, $s0, 0x10

				 loc_8E640:
			 beqz	$v0, loc_8E654
				 nop
				 lh	$a0, 0($s1)
				 jal	sub_76804
				 addiu	$s1, 2

				 loc_8E654 :
				 lw	$s0, 0($s6)
				 jal	sub_764D0
				 addiu	$s6, 8
				 lw	$at, 0x50 + var_34($sp)
				 nop
				 andi	$at, 2
				 bnez	$at, loc_8E680
				 lh	$a0, 0($s0)
				 lh	$a1, 2($s0)
				 lh	$a2, 4($s0)
				 jal	sub_7658C

				 loc_8E680 :
			 addiu	$s5, -1
				 cfc2	$t4, $5
				 cfc2	$t5, $6
				 cfc2	$t6, $7
				 lh	$v1, 6($s0)
				 addu	$t4, $fp
				 addu	$t5, $s3
				 addu	$t6, $s7
				 sw	$t4, 0($s4)
				 sw	$t5, 4($s4)
				 sw	$t6, 8($s4)
				 sw	$v1, 0xC($s4)
				 jal	sub_76520
				 addiu	$s2, 0xC
				 bgtz	$s5, loc_8E5B4
				 addiu	$s4, 0x10

				 loc_8E6C0:
			 jal	sub_76520
				 nop
				 lw	$v0, 0x50 + var_38($sp)
				 lw	$ra, 0x50 + var_4($sp)
				 lw	$fp, 0x50 + var_8($sp)
				 lw	$s7, 0x50 + var_C($sp)
				 lw	$s6, 0x50 + var_10($sp)
				 lw	$s5, 0x50 + var_14($sp)
				 lw	$s4, 0x50 + var_18($sp)
				 lw	$s3, 0x50 + var_1C($sp)
				 lw	$s2, 0x50 + var_20($sp)
				 lw	$s1, 0x50 + var_24($sp)
				 lw	$s0, 0x50 + var_28($sp)
				 jr	$ra
				 addiu	$sp, 0x50
#endif
	UNIMPLEMENTED();
	return 0;
}

