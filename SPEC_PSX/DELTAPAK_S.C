#include "DELTAPAK_S.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#include "MATHS.H"
#include "SETUP.H"
#include "SPECIFIC.H"

#ifndef USE_ASM

void DrawCutSeqActors()//90DCC(<), ? deltapak
{
	struct NEW_CUTSCENE* s3 = &GLOBAL_cutme[0];
	short** s0 = &meshes[0];
	long s6 = 1;
	struct object_info* object;
#if 0

	if (GLOBAL_cutme[0].numactors > 1)
	{
		//loc_91000
		return;
	}

	mPushMatrix();

	//loc_90E1C
	mPushMatrix();

	//v1 = s6 << 2;
	//s7 = &cutseq_meshbits[s6];//long[]
	//fp = &cutseq_meshswapbits[s6];//long[]
	//s7 = cutseq_meshbits[s6];
	// lw	$fp, 0x48 + var_48($fp) //?

	if (cutseq_meshbits[s6] & 0x80000000)
	{
		//v0 = &actor_pnodes[s6];
		//v1 = s6 << 3;//8
		//v1 = &s3[2];//2 ptr advance
		//a1 = GLOBAL_cutme[2].actor_data[0].nodes;
		//a0 = ((long*)&actor_pnodes[s6])[0];
		//a2 = &temp_rotation_buffer[0];

		//updateAnimFrame(((long*) &actor_pnodes[s6])[0], GLOBAL_cutme[2].actor_data[0].nodes + 1, &temp_rotation_buffer[0]);

		//v1 = GLOBAL_cutme[2].actor_data[0].objslot;
		//a0 = GLOBAL_cutme[0].orgx;
		//a1 = GLOBAL_cutme[0].orgy;
		//a2 = GLOBAL_cutme[0].orgz;
		object = &objects[GLOBAL_cutme[2].actor_data[0].objslot];

		mTranslateAbsXYZ(GLOBAL_cutme[0].orgx, GLOBAL_cutme[0].orgy, GLOBAL_cutme[0].orgz);

		//CalcActorLighting();

		//v0 = object->mesh_index;
		//v1 = object->bone_index;

		//s1 = &meshes[object->mesh_index];
		//s2 = &bones[object->bone_index];

		//a2 = &temp_rotation_buffer[0];

		mTranslateXYZ(temp_rotation_buffer[6], temp_rotation_buffer[7], temp_rotation_buffer[8]);
		//addiu	$a0, $sp, 0x48 + var_38
		//a1 = 0;
		//v0 = &temp_rotation_buffer[9];
		// sw	$v0, 0x48 + var_38($sp)

		//mRotSuperPackedYXZ(a0, 0);
		//v0 = s7 & 1;

		//if(s7 & 1)
		//{
		//if(fp & 1)
		//{
				//a0 = meshes[1]; 
		//}
		//else
		//{
				//a0 = meshes[0];
		//}
			//loc_90F1C

		//if(s6 - 1 == 0)
		{
			//phd_PutPolygons_seethrough(a0, cut_seethrough);

		}//loc_90F34
		//else
		{
			//phd_PutPolygons(a0, -1);
		}
		//}
		//loc_90F3C
	}
	sizeof(struct NEW_CUTSCENE);
	sizeof (struct ACTORME);
	
	//loc_90FDC


				 loc_90F3C :
				 lh	$s4, 0($s4)
				 li	$s5, 1
				 addiu	$s4, -1
				 blez	$s4, loc_90FDC
				 addiu	$s1, 8

				 loc_90F50 :
				 lw	$a1, 0($s2)
				 addiu	$s4, -1
				 andi	$v0, $a1, 1
				 beqz	$v0, loc_90F6C
				 andi	$a1, 2
				 jal	sub_76520
				 nop

				 loc_90F6C :
			 beqz	$a1, loc_90F7C
				 sll	$s5, 1
				 jal	sub_764D0
				 nop

				 loc_90F7C :
			 lw	$a0, 4($s2)
				 lw	$a1, 8($s2)
				 jal	sub_7658C
				 lw	$a2, 0xC($s2)
				 addiu	$a0, $sp, 0x48 + var_38
				 jal	sub_768BC
				 move	$a1, $zero
				 and	$v0, $s5, $s7
				 beqz	$v0, loc_90FD0
				 and	$v0, $s5, $fp
				 beqz	$v0, loc_90FB0
				 lw	$a0, 0($s1)
				 lw	$a0, 4($s1)

				 loc_90FB0:
			 addiu	$at, $s6, -1
				 bnez	$at, loc_90FC8
				 nop
				 lw	$a1, 0x410($gp)
				 jal	sub_7FAD4
				 addiu	$ra, 8

				 loc_90FC8:
			 jal	sub_7EEC4
				 li	$a1, 0xFFFFFFFF

				 loc_90FD0 :
				 addiu	$s2, 0x10
				 bnez	$s4, loc_90F50
				 addiu	$s1, 8

				 loc_90FDC :
				 jal	sub_76520
				 nop
				 lh	$v1, 0($s3)
				 addiu	$s6, 1
				 slt	$v1, $s6, $v1
				 bnez	$v1, loc_90E1C
				 nop
				 jal	sub_76520
				 nop

				 loc_91000 :
			 lw	$ra, 0x48 + var_4($sp)
				 lw	$fp, 0x48 + var_8($sp)
				 lw	$s7, 0x48 + var_C($sp)
				 lw	$s6, 0x48 + var_10($sp)
				 lw	$s5, 0x48 + var_14($sp)
				 lw	$s4, 0x48 + var_18($sp)
				 lw	$s3, 0x48 + var_1C($sp)
				 lw	$s2, 0x48 + var_20($sp)
				 lw	$s1, 0x48 + var_24($sp)
				 lw	$s0, 0x48 + var_28($sp)
				 jr	$ra
				 addiu	$sp, 0x48
				 # End of function sub_90DCC
#endif
	S_Warn("[DrawCutSeqActors] - Unimplemented!\n");
}
#endif