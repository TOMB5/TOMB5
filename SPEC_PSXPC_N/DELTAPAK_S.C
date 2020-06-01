#include "DELTAPAK_S.H"

#include "DELTAPAK.H"
#include "DRAW.H"
#include "MATHS.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "DRAWOBJ.H"
#include "MISC.H"
#include "GTEREG.H"
#include "SPHERES.H"
#include "CONTROL.H"
#include "LIGHT.H"

void CalcActorLighting()
{
	int scratchPad[256];
	int* s1 = &scratchPad[0];
	short room_no;

	S_MemSet((char*)&scratchPad, 0, 1024);

	mPushUnitMatrix();
	mSetTrans(0, 0, 0);
	mTranslateXYZ(temp_rotation_buffer[6], temp_rotation_buffer[7], temp_rotation_buffer[8]);
	s1[3] = (int)&temp_rotation_buffer[9];
	mRotSuperPackedYXZ((short**)&s1[3], 0);

	s1[0] = TRX + duff_item.pos.x_pos;
	s1[1] = TRY + duff_item.pos.y_pos;
	s1[2] = TRZ + duff_item.pos.z_pos;

	mPopMatrix();
	IsRoomOutside(s1[0], s1[1], s1[2]);

	if (IsRoomOutsideNo != -1)
	{
		room_no = IsRoomOutsideNo;
	}
	else
	{
		room_no = duff_item.room_number;
	}

	//loc_911C8
	duff_item.il.Light[3].pad = 0;
	S_CalculateLight(s1[0], s1[2], s1[3], room_no, &duff_item.il);
}

void DrawCutSeqActors()//90DCC(<), 92E10
{
	//s3 = GLOBAL_cutme
	//s0 = meshes
	//v0 = GLOBAL_cutme->numactors
	struct object_info* object = NULL;//$s4
	int s6 = 1;
	short** meshp = NULL;//$s1
	long* bone = NULL;//$s2
	short* rotation1 = NULL;//0x48+var_38
	int s4 = 0;
	int s5 = 0;

	if (s6 < GLOBAL_cutme->numactors)
	{
		mPushMatrix();

		//loc_90E1C
		do
		{
			mPushMatrix();
			//v1 = s6 << 2
			//s7 = &cutseq_meshbits[s6];
			//fp = &cutseq_meshswapbits[s6];
			//s7 = cutseq_meshbits[s6];
			//fp = cutseq_meshswapbits[s6];
			//v0 = 0x80000000

			if ((0x80000000 & cutseq_meshbits[s6]))
			{
				//v0 = actor_pnodes[s6]
				//a1 = GLOBAL_cutme->actor_data[s6].nodes
				//a0 = actor_pnodes[s6].
				updateAnimFrame(actor_pnodes[s6], GLOBAL_cutme->actor_data[s6].nodes + 1, temp_rotation_buffer);
				//v1 = GLOBAL_cutme->actor_data[s6].objslot
				//a0 = GLOBAL_cutme->orgx
				//a1 = GLOBAL_cutme->orgy
				//a2 = GLOBAL_cutme->orgz
				//v0 = &objects[0];
				object = &objects[GLOBAL_cutme->actor_data[s6].objslot];
				mTranslateAbsXYZ(GLOBAL_cutme->orgx, GLOBAL_cutme->orgy, GLOBAL_cutme->orgz);
				CalcActorLighting();
				//v0 = object->mesh_index
				//v1 = object->bone_index
				meshp = &meshes[object->mesh_index];
				//v0 = bones
				//a2 = temp_rotation_buffer
				bone = &bones[object->bone_index];
				mTranslateXYZ(temp_rotation_buffer[6], temp_rotation_buffer[7], temp_rotation_buffer[8]);
				rotation1 = &temp_rotation_buffer[9];
				mRotSuperPackedYXZ(&rotation1, 0);

				if ((cutseq_meshbits[s6] & 1))
				{
					if ((cutseq_meshswapbits[s6] & 1))
					{
						//a0 = meshp[1];
						if (s6 - 1 == 0)
						{
							phd_PutPolygons_seethrough(meshp[1], cut_seethrough);
						}
						else
						{
							phd_PutPolygons(meshp[0], -1);
						}
					}
					else
					{
						//loc_90F1C
						//a0 = meshp[0];
						if (s6 - 1 == 0)
						{
							phd_PutPolygons_seethrough(meshp[0], cut_seethrough);
						}
						else
						{
							phd_PutPolygons(meshp[0], -1);
						}
					}
				}//loc_90F3C

				s5 = 1;
				meshp += 2;
				s4 = object->nmeshes;
				s4--;
				if (s4 > 0)
				{
					//loc_90F50
					do
					{
						s4--;

						if ((*bone & 1))
						{
							mPopMatrix();
						}

						s5 <<= 1;
						if ((*bone & 2))
						{
							mPushMatrix();
						}

						//loc_90F7C
						mTranslateXYZ(bone[1], bone[2], bone[3]);
						mRotSuperPackedYXZ(&rotation1, 0);

						if (s5 & cutseq_meshbits[s6])
						{
							if (s5 & cutseq_meshswapbits[s6])
							{
								//loc_90FB0
								if (s6 - 1 == 0)
								{
									phd_PutPolygons_seethrough(meshp[1], cut_seethrough);
								}
								else
								{
									//loc_90FC8
									phd_PutPolygons(meshp[1], -1);
								}
							}
							else
							{
								//loc_90FB0
								if (s6 - 1 == 0)
								{
									phd_PutPolygons_seethrough(meshp[0], cut_seethrough);
								}
								else
								{
									//loc_90FC8
									phd_PutPolygons(meshp[0], -1);
								}
							}

						}
						//loc_90FD0
						bone += 4;
						meshp += 2;
					} while (s4 != 0);
				}
			}
			//loc_90FDC
			mPopMatrix();
			//v1 = 
			s6++;
		} while (s6 < GLOBAL_cutme->numactors);

		mPopMatrix();
	}
	//loc_91000
}

void updateAnimFrame(struct PACKNODE* node, int flags, short* frame)//91030(<), 93074 (F)
{
	int at = 0;
	unsigned int v1 = 0;
	unsigned int v0 = 0;
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
		a3 = &frame[9];
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
				at = 0;
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
	unsigned int at = 0;
	unsigned int v1 = 0;

	packed = &packed[v0];
	a0 &= 7;
	at = ((unsigned char*)packed)[0] | (((unsigned char*)packed)[1] << 8) | (((unsigned char*)packed)[2] << 16) | (((unsigned char*)packed)[3] << 24);
	at = at >> a0;
	v1 = (1 << packmethod) - 1;
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

void DecodeAnim(struct PACKNODE* node, int a1, int frame, unsigned short a3)//90A88(<), ?
{
	int t4 = 0;
	int xrot_run = 0;
	int yrot_run = 0;
	int zrot_run = 0;

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
		xrot_run = ((unsigned short)node->xrot_run + DecodeTrack(node->xpacked, &node->decode_x)) & a3;
		yrot_run = ((unsigned short)node->yrot_run + DecodeTrack(node->ypacked, &node->decode_y)) & a3;
		zrot_run = ((unsigned short)node->zrot_run + DecodeTrack(node->zpacked, &node->decode_z)) & a3;
		
		node->xrot_run = xrot_run;
		node->yrot_run = yrot_run;
		node->zrot_run = zrot_run;
		t4++;
		node++;
	} while (t4 < a1);
}
