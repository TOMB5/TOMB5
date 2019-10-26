#include "LIGHT.H"

#include "EFFECT2.H"
#include "DRAW.H"
#include "MATHS.H"
#include "LOAD_LEV.H"
#include "GTEREG.H"

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