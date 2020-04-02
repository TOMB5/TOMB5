#include "CALCHAIR.H"

#include "GETSTUFF.H"
#include "CALCLARA.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "LARA.H"
#include "TYPES.H"
#include "MISC.H"
#include "GTEREG.H"
#include "SETUP.H"
#include "LARA.H"
#include "GAMEFLOW.H"
#include "HAIR.H"
#include "EFFECT2.H"
#include "CONTROL.H"
#include "LOAD_LEV.H"
#include "MATHS.H"

long phd_sqrt_asm_CH(long value)//83B30(<), 85B74(<) (F)
{
	LZCR = gte_leadingzerocount(value);

	long v0 = 0x1F;

	if (value != 0)
	{
		long v1 = LZCR;
		v1 &= 0xFFFFFFFE;
		v0 = v0 - v1 >> 1;
		long at = v1 - 0x18;

		if (v1 - 0x18 < 0)
		{
			//loc_85BA8
			value >>= 0x18 - v1;
		}
		else
		{
			value <<= v1 - 0x18;
		}

		//loc_85BB4
		value = SqrtTable[value - 0x40] << v0;

	}//locret_85BD0

	return (value >> 12);
}

int* snaff_sphere_special(int* at, short* s7)
{
	at[0] = TRX;
	at[1] = TRY;
	at[2] = TRZ;
	at[3] = (((s7[3] << 1) + s7[3]) + (((s7[3] << 1) + s7[3]) >> 31)) >> 1;
	return at + 45;
}

void load_matrix(int* at)
{
	R11 = at[0] & 0xFFFF;
	R12 = (at[0] >> 16) & 0xFFFF;
	R13 = at[1] & 0xFFFF;
	R21 = (at[1] >> 16) & 0xFFFF;
	R22 = at[2] & 0xFFFF;
	R23 = (at[2] >> 16) & 0xFFFF;
	R31 = at[3] & 0xFFFF;
	R32 = (at[3] >> 16) & 0xFFFF;
	R33 = at[4] & 0xFFFF;
	TRX = at[5];
	TRY = at[6];
	TRZ = at[7];

	at[5] = TRX;
	at[6] = TRY;
	at[7] = TRZ;
}

void snaff_sphere_normal(short* s7, int* at)
{
	at[0] = TRX;
	at[1] = TRY;
	at[2] = TRZ;
	at[3] = s7[3];
}

void mTranslateXYZ_CH(int x, int y, int z)
{
	int t4 = y >> 15;

	if (y < 0)
	{
		y = -y;
		t4 = y >> 15;
		y &= 0x7FFF;
		t4 = -t4;
		y = -y;
	}
	else
	{
		//loc_1378
		y &= 0x7FFF;
	}

	int t5 = z >> 15;
	if (z < 0)
	{
		z = -z;
		t5 = z >> 15;
		z &= 0x7FFF;
		t5 = -t5;
		z = -z;
	}
	else
	{
		z &= 0x7FFF;
	}

	//loc_13A0
	int t3 = x >> 15;
	if (x < 0)
	{
		x = -x;
		t3 = x >> 15;
		x &= 0x7FFF;
		t3 = -t3;
		x = -x;
	}
	else
	{
		x &= 0x7FFF;
	}

	//loc_13C4
	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = x;
	IR2 = y;
	IR3 = z;

	docop2(0x498012);

	int t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}

	//loc_1408
	int t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}

	//loc_1430
	int t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}

	//loc_1430
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;
}

void mRotY_CH(int y_rot)
{
	y_rot >>= 2;
	y_rot &= 0x3FFC;

	if (y_rot != 0)
	{
		int t5 = ((int*)&rcossin_tbl[y_rot >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t5 >> 16;
		t5 &= 0xFFFF;
		int t2 = -t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = t2;

		int t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
		t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
		int t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

		docop2(0x486012);
		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6;

		t0 &= t7;
		t2 &= 0xFFFF;
		t3 &= t7;
		int t4 = MAC1;
		int t1 = MAC2;
		t5 = MAC3;
		docop2(0x48E012);
		t4 &= 0xFFFF;
		t0 |= t4;
		t1 <<= 16;
		t5 &= 0xFFFF;
		t3 |= t5;
		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;
		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;
		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;
		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;
		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;
		R33 = t4;
	}
}

void mRotX_CH(int a0)
{
	a0 >>= 2;
	a0 &= 0x3FFC;

	if (a0 != 0)
	{
		int t5 = ((int*)&rcossin_tbl[a0 >> 1])[0];
		int t7 = 0xFFFF0000;
		int t6 = t7 & t5;

		VX0 = t6 & 0xFFFF;
		VY0 = (t6 >> 16) & 0xFFFF;
		VZ0 = t5;

		int t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
		int t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
		int t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);

		docop2(0x486012);

		t6 = t5 >> 16;
		t5 <<= 16;
		t5 = -t5;

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;
		VZ1 = t6 & 0xFFFF;

		t0 &= 0xFFFF;
		t1 &= t7;
		t3 &= 0xFFFF;

		int t4 = MAC1;
		int t2 = MAC2;
		t5 = MAC3;

		docop2(0x48E012);
		t4 <<= 16;
		t0 |= t4;
		t2 &= 0xFFFF;
		t5 <<= 16;
		t3 |= t5;

		t5 = MAC1;
		t6 = MAC2;
		t4 = MAC3;

		t5 &= 0xFFFF;
		t1 |= t5;
		t6 <<= 16;
		t2 |= t6;

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;
		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;
		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;
		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;
		R33 = t4;
	}
}

void mRotZ_CH(int a0)
{
	a0 >>= 2;
	a0 &= 0x3FFC;

	if (a0 != 0)
	{
		int t0 = ((int*)&rcossin_tbl[a0 >> 1])[0];
		int t7 = 0xFFFF0000;
		int t1 = (t0 >> 16) & 0xFFFF;
		int t2 = t0 << 16;
		t1 |= t2;

		VX0 = t1 & 0xFFFF;
		VY0 = (t1 >> 16) & 0xFFFF;
		VZ0 = 0;

		t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
		t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
		int t4 = R33;

		docop2(0x486012);

		int t3 = t0 & t7;
		t0 &= 0xFFFF;
		t0 = -t0;
		t0 &= 0xFFFF;
		t0 |= t3;

		VX1 = t0 & 0xFFFF;
		VY1 = (t0 >> 16) & 0xFFFF;
		VZ1 = 0;

		t1 &= 0xFFFF;

		t0 = MAC1;
		int t5 = MAC2;
		t3 = MAC3;

		docop2(0x48E012);

		t2 &= t7;
		t0 &= 0xFFFF;
		t5 <<= 16;
		t1 |= t5;
		t3 &= 0xFFFF;

		t5 = MAC1;
		int t6 = MAC2;
		int a0 = MAC3;

		t5 <<= 16;
		t0 |= t5;
		t6 &= 0xFFFF;
		t2 |= t6;
		a0 <<= 16;
		t3 |= a0;

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;
		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;
		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;
		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;
		R33 = t4;
	}
}

void mRotSuperPackedYXZ_CH(int* fp, int a1)
{
	unsigned short* a2 = (unsigned short*)fp[10];
	int v0 = *a2;

	if (a1 != 0)
	{
		//loc_83A88
		do
		{
			v0 = *a2;
			a1--;
			if (!(v0 & 0xC000))
			{
				a2++;
			}
			a2++;

			//loc_83AA0
		} while (a1 != 0);

		v0 = *a2;
	}
	//loc_83AAC
	a2++;

	int at = v0 >> 14;
	if (at-- != 0)
	{
		fp[10] = (int)a2;

		if (at-- != 0)
		{
			if (at != 0)
			{
				mRotZ_CH((v0 & 0xFFF) << 4);
				return;
			}
			//loc_83AD8
			mRotY_CH((v0 & 0xFFF) << 4);
			return;
		}
		//loc_83AE0
		mRotX_CH((v0 & 0xFFF) << 4);
		return;
	}
	//loc_83AEC
	at = *a2++;
	fp[10] = (int)a2;
	v0 <<= 16;
	v0 |= at;

	mRotY_CH((v0 >> 4) & 0xFFC0);
	mRotX_CH((v0 >> 14) & 0xFFC0);
	mRotZ_CH((v0 & 0x3FF) << 6);
}

void mRotYXZ_CH(int y_rot, int x_rot, int z_rot)
{
	mRotY_CH(y_rot);
	mRotX_CH(x_rot);
	mRotZ_CH(z_rot);
}

void save_matrix(int* at)
{
	at[0] = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
	at[1] = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
	at[2] = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
	at[3] = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
	at[4] = (R33 & 0xFFFF);
	at[5] = TRX;
	at[6] = TRY;
	at[7] = TRZ;
}

void HairControl(int unk01, int bIsYoungLara, short* frame)
{
	struct ANIM_STRUCT* anim = NULL;//$v1
	int scratchPad[256];
	short* hit_frame = NULL;//$s3
	struct object_info* object = NULL;//$at
	long* bone = NULL;//$s6
	int* at = NULL;
	struct HAIR_STRUCT* s7 = NULL;
	int* a1 = NULL;
	int s5 = 0;
	int s3 = 1;
	int height;//$a2
	int t3;
	struct room_info* r = NULL;
	S_MemSet((char*)&scratchPad, 0, 1024);

	//s0 = gfLevelFlags & 1
	int* fp = &scratchPad[0];
	//s5 = lara_item
	//v1 = lara.hit_direction
	//s4 = bIsYoungLara
	fp[11] = unk01;
	hit_frame = frame;
	int a0 = 0;

	if (frame == NULL)
	{
		if (lara.hit_direction >= 0)
		{
			//a1 = anims
			if (lara.hit_direction == 0)
			{
				//loc_82DAC
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x7D;
				}
				else
				{
					a0 = 0x126;
				}
			}
			else if (lara.hit_direction == 2)
			{
				//loc_82DBC
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x7E;
				}
				else
				{
					a0 = 0x125;
				}
			}
			else if (lara.hit_direction == 1)
			{
				//loc_82DCC
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x7F;
				}
				else
				{
					a0 = 0x127;
				}
			}
			else
			{
				if (lara.BurnSmoke == 0)
				{
					a0 = 0x80;
				}
				else
				{
					a0 = 0x128;
				}
			}

			//loc_82DD8
			anim = &anims[a0];//$v1
			//v0 = anim->interpolation >> 8
			//a0 = lara.hit_frame
			//t1 = (lara.hit_frame * (anim->interpolation >> 8))
			//s3 = anim->frame_ptr
			hit_frame = &anim->frame_ptr[(lara.hit_frame * (anim->interpolation >> 8))];
		}
		else
		{
			//loc_82E00
			hit_frame = GetBestFrame(lara_item);
		}
	}//loc_82E0C

	save_matrix(&fp[37]);

	R11 = 4096;
	R12 = 0;
	R13 = 0;
	R21 = 0;
	R22 = 4096;
	R23 = 0;
	R31 = 0;
	R32 = 0;
	R33 = 4096;

	fp[10] = (int)&hit_frame[9];

	TRX = lara_item->pos.x_pos;
	TRY = lara_item->pos.y_pos;
	TRZ = lara_item->pos.z_pos;

	mRotYXZ_CH(lara_item->pos.y_rot, lara_item->pos.x_rot, lara_item->pos.z_rot);
	object = &objects[LARA];
	//v0 = objects.bone_index
	bone = &bones[object->bone_index];
	mTranslateXYZ_CH(hit_frame[6], hit_frame[7], hit_frame[8]);
	mRotSuperPackedYXZ_CH(fp, 0);

	//s7 = lara.mesh_ptrs[0];
	save_matrix(&fp[45]);
	mTranslateXYZ_CH(lara.mesh_ptrs[0][0], lara.mesh_ptrs[0][1], lara.mesh_ptrs[0][2]);
	snaff_sphere_normal(lara.mesh_ptrs[0], &fp[17]);
	mTranslateXYZ_CH(bone[25], bone[26], bone[27]);
	mRotSuperPackedYXZ_CH(fp, 6);
	mRotYXZ_CH(lara.torso_y_rot, lara.torso_x_rot, lara.torso_z_rot);
	save_matrix(&fp[45]);
	mTranslateXYZ_CH(lara.mesh_ptrs[0][0], lara.mesh_ptrs[0][1], lara.mesh_ptrs[0][2]);

	//at = &fp[21];
	//v0 = lara.mesh_ptrs[0][3];
	fp[21] = TRX;
	fp[22] = TRY;
	fp[23] = TRZ;

	//a0 = v0 >> 2
	if ((gfLevelFlags & 1))
	{
		fp[24] = lara.mesh_ptrs[0][3] - ((lara.mesh_ptrs[0][3] >> 2) + lara.mesh_ptrs[0][3] >> 3);
	}
	else
	{
		fp[24] = lara.mesh_ptrs[0][3];
	}

	//loc_82F1C
	load_matrix(&fp[45]);
	//s7 = lara.mesh_ptrs[8];
	mTranslateXYZ_CH(bone[29], bone[30], bone[31]);
	mRotSuperPackedYXZ_CH(fp, 0);
	mTranslateXYZ_CH(lara.mesh_ptrs[8][0], lara.mesh_ptrs[8][1], lara.mesh_ptrs[8][2]);

	at = snaff_sphere_special(&fp[29], lara.mesh_ptrs[8]);
	//s7 = lara.mesh_ptrs[11];
	mTranslateXYZ_CH(bone[41], bone[42], bone[43]);
	mRotSuperPackedYXZ_CH(fp, 2);
	mTranslateXYZ_CH(lara.mesh_ptrs[11][0], lara.mesh_ptrs[11][1], lara.mesh_ptrs[11][2]);
	at = snaff_sphere_special(&fp[33], lara.mesh_ptrs[11]);
	mTranslateXYZ_CH(bone[53], bone[54], bone[55]);
	mRotSuperPackedYXZ_CH(fp, 2);
	mRotYXZ_CH(lara.head_y_rot, lara.head_x_rot, lara.head_z_rot);
	//s7 = lara.mesh_ptrs[14]
	save_matrix(&fp[45]);
	mTranslateXYZ_CH(lara.mesh_ptrs[14][0], lara.mesh_ptrs[14][1], lara.mesh_ptrs[14][2]);
	snaff_sphere_normal(lara.mesh_ptrs[14], &fp[25]);

	fp[21] = (fp[21] + fp[25]) >> 1;
	fp[22] = (fp[22] + fp[26]) >> 1;
	fp[23] = (fp[23] + fp[27]) >> 1;

	//loc_83020
	if (bIsYoungLara == 0)
	{
		if ((gfLevelFlags & 1))
		{
			mTranslateXYZ_CH(-52, -48, -50);
		}
		else
		{
			//loc_83040
			mTranslateXYZ_CH(-4, -4, -48);
		}
	}
	else
	{
		//loc_83054
		mTranslateXYZ_CH(44, -48, -50);
	}

	fp[12] = TRX;
	fp[13] = TRY;
	fp[14] = TRZ;

	load_matrix(&fp[37]);
	s7 = &hairs[bIsYoungLara][0];
	a1 = &first_hair[bIsYoungLara];
	//a0 = objects[HAIR].bone_index
	bone = &bones[objects[HAIR].bone_index];

	if (lara.hit_direction != 0)
	{
		a1[0] = 0;
		s7->pos.x_pos = fp[12];
		s7->pos.y_pos = fp[13];
		s7->pos.z_pos = fp[14];

		s5 = 6;
		//loc_830DC
		do
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

			TRX = s7->pos.x_pos;
			TRY = s7->pos.y_pos;
			TRZ = s7->pos.z_pos;
			s5--;
			mRotYXZ_CH(s7->pos.y_rot, s7->pos.x_rot, 0);
			mTranslateXYZ_CH(bone[1], bone[2], bone[3]);

			s7[1].pos.x_pos = TRX;
			s7[1].pos.y_pos = TRY;
			s7[1].pos.z_pos = TRZ;
			bone += 4;
			s7++;

		} while (s5 != 0);

		SmokeWindZ = 0;
		SmokeWindX = 0;
		hair_wind = 0;
		hair_dwind_angle = 2048;
		hair_wind_angle = 2048;
		load_matrix(&fp[37]);
		return;
	}

	//loc_8316C
	//v0 = fp[12]
	//v1 = fp[13]
	//a0 = fp[14]

	s7->pos.x_pos = fp[12];
	s7->pos.y_pos = fp[13];
	s7->pos.z_pos = fp[14];
	//t1 = fp[11];
	//a3 = lara_item->room_number
	((short*)fp)[30] = lara_item->room_number;

	if (fp[11] != 0)
	{
		fp[16] = -32512;
	}
	else
	{
		//loc_831A0
		fp[16] = GetWaterHeight(lara_item->pos.x_pos + ((hit_frame[0] + hit_frame[1]) >> 1), lara_item->pos.y_pos + ((hit_frame[2] + hit_frame[3]) >> 1), lara_item->pos.z_pos + ((hit_frame[4] + hit_frame[5]) >> 1), lara_item->room_number);
	}

	//loc_831F0
	int v1 = (hair_wind - 3) + (GetRandomControl() & 7);
	int v0 = 1;

	if (v1 >= -1)
	{
		v0 = -1;
		if (v1 >= 9)
		{
			v1 += v0;
		}
		//loc_83224
	}
	else
	{
		//loc_83220
		v1 += v0;
	}

	//loc_83224
	hair_wind = v1;
	
	v1 = (hair_dwind_angle + (((GetRandomControl() & 0x3F) - 0x20) << 1)) & 0x1FFE;

	if (v1 < 0x400)
	{
		v1 += ((0x400 - v1) << 1);
	}
	else if (v1 >= 0xC01)
	{
		v1 -= ((v1 - 0xC00) << 1);
	}

	//loc_8327C
	hair_dwind_angle = v1;

	//v0 = ((hair_dwind_angle - hair_wind_angle) >> 3)
	//v1 = hair_wind_angle + ((hair_dwind_angle - hair_wind_angle) >> 3)
	//a0 = hair_wind
	hair_wind_angle = hair_wind_angle + ((hair_dwind_angle - hair_wind_angle) >> 3);

	v0 = ((int*)&rcossin_tbl)[hair_wind_angle >> 2];
	s7++;
	
	SmokeWindZ = ((v0 >> 16) * hair_wind) >> 12;//a1
	SmokeWindX = (((v0 << 16) >> 16) * hair_wind) >> 12;//a2
	s3 = 1;

	//loc_832E4
	do
	{
		//a0 = s7->pos.x_pos
		//a1 = s7->pos.y_pos
		//a2 = s7->pos.z_pos
		//t1 = fp[11]

		fp[12] = s7->pos.x_pos;
		fp[13] = s7->pos.y_pos;
		fp[14] = s7->pos.z_pos;

		if (!fp[11])
		{
			//a3 = &fp[15];
			height = GetHeight(GetFloor(fp[12], fp[13], fp[14], (short*)&fp[15]), fp[12], fp[13], fp[14]);
		}
		else
		{
			//loc_83328
			height = 32767;
		}

		//loc_8332C
		//v1 = (((s7->vel.x << 1) + s7->vel.x) >> 2)
		s7->pos.x_pos = s7->pos.x_pos + (((s7->vel.x << 1) + s7->vel.x) >> 2);
		//v1 = s7->vel.y
		s7->pos.y_pos = s7->pos.y_pos + (((s7->vel.y << 1) + s7->vel.y) >> 2);
		//at = (((s7->vel.y << 1) + s7->vel.y) >> 2)
		//v1 = (((s7->vel.z << 1) + s7->vel.z) >> 2)
		s7->pos.z_pos = s7->pos.z_pos + (((s7->vel.z << 1) + s7->vel.z) >> 2);

		//a3 = lara.water_status
		//v1 = ((short*)fp)[30]
		if (lara.water_status == 0)
		{
			r = &room[((short*)fp)[30]];
			if ((r->flags & 0x20))
			{
				s7->pos.x_pos += SmokeWindX;
				s7->pos.z_pos += SmokeWindZ;
			}//loc_833D4
		}
		//loc_833D4
		//v1 = s7->pos.y_pos
		//t1 = fp[16];
		//at = 1

		if (lara.water_status != 0)
		{
			if (lara.water_status == 1 || lara.water_status == 2 || lara.water_status == 3)
			{
				//loc_833F8
				if (s7->pos.y_pos < fp[16])
				{
					s7->pos.y_pos = fp[16];
				}
				else if (height < s7->pos.y_pos)
				{
					s7->pos.y_pos = height;
				}
			}
		}
		else
		{
			//loc_8341C
			//v0 = -32512
			s7->pos.y_pos += 10;
			if (fp[16] != -32512 && fp[16] < s7->pos.y_pos)
			{
				s7->pos.y_pos = fp[16];
			}
			else if (height < s7->pos.y_pos)//loc_83434
			{
				s7->pos.x_pos = fp[12];
				s7->pos.z_pos = fp[14];
			}
		}

		//loc_8344C
		t3 = 5;
		int* t4 = &fp[17];

		//loc_83454
		do
		{
			//a0 = s7->pos.x_pos
			//a1 = s7->pos.y_pos
			//a2 = s7->pos.z_pos

			//at = fp[17];
			//v0 = fp[18];
			//v1 = fp[19];

			IR1 = s7->pos.x_pos - fp[0];
			IR2 = s7->pos.y_pos - fp[1];
			IR3 = s7->pos.z_pos - fp[2];

			//v0 = fp[20] * fp[20]
			docop2(0xA00428);

			//a0 = MAC1 + MAC2 + MAC3

			t3--;
			if (MAC1 + MAC2 + MAC3 < fp[3] * fp[3])
			{
				v0 = phd_sqrt_asm_CH(MAC1 + MAC2 + MAC3);

				if (v0 == 0)
				{
					v0 = 1;
				}
				//loc_834C8
				//v1 = (fp[20] << 16)
				//at = fp[17]
				//a0 = (fp[20] << 16) / v0;
				//v0 = fp[18];
				//v1 = fp[19];
				s7->pos.x_pos = ((((fp[3] << 16) / v0) * (s7->pos.x_pos - fp[0])) >> 16) + fp[0];
				s7->pos.y_pos = ((((fp[3] << 16) / v0) * (s7->pos.y_pos - fp[1])) >> 16) + fp[1];
				s7->pos.z_pos = ((((fp[3] << 16) / v0) * (s7->pos.z_pos - fp[2])) >> 16) + fp[2];
			}
			//loc_8351C
			t4 += 4;
		} while (t3 != 0);

		R11 = 4096;
		R12 = 0;
		R13 = 0;
		R21 = 0;
		R22 = 4096;
		R23 = 0;
		R31 = 0;
		R32 = 0;
		R33 = 4096;

		//v0 = s7->pos.z_pos;
		//v1 = s7[-1].z_pos;
		//a0 = s7->pos.x_pos;
		//a1 = s7[-1].x_pos;

		IR1 = s7->pos.z_pos - s7[-1].pos.z_pos;
		IR2 = s7->pos.x_pos - s7[-1].pos.x_pos;

		docop2(0xA00428);

		int t2 = phd_sqrt_asm_CH(MAC1 + MAC2);
		s7[-1].pos.y_rot = phd_atan_asm(s7->pos.z_pos - s7[-1].pos.z_pos, s7->pos.x_pos - s7[-1].pos.x_pos);

		//v1 = s7->pos.y_pos;
		//a1 = s7[-1].y_pos;
		s7[-1].pos.x_rot = -phd_atan_asm(t2, s7->pos.y_pos - s7[-1].pos.y_pos);

		TRX = s7[-1].pos.x_pos;
		TRY = s7[-1].pos.y_pos;
		TRZ = s7[-1].pos.z_pos;

		mRotYXZ_CH(s7[-1].pos.y_rot, s7[-1].pos.x_rot, 0);

		if (s3 == 6)
		{
			mTranslateXYZ_CH(bone[-3], bone[-2], bone[-1]);
		}
		else
		{
			//loc_835E8
			mTranslateXYZ_CH(bone[1], bone[2], bone[3]);
		}

		bone += 4;

		s7->pos.x_pos = TRX;
		s7->pos.y_pos = TRY;
		s7->pos.z_pos = TRZ;

		s7->vel.x = TRX - fp[12];
		s7->vel.y = TRY - fp[13];
		s7->vel.z = TRZ - fp[14];

		load_matrix(&fp[37]);
		s3++;
		s7++;
	}while (s3 < 7);
}
