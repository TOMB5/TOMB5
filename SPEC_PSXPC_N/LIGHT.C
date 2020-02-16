#include "LIGHT.H"

#include "EFFECT2.H"
#include "DRAW.H"
#include "MATHS.H"
#include "LOAD_LEV.H"
#include "GTEREG.H"
#include "MISC.H"
#include "DRAWSPKS.H"

void mNormaliseXYZ_L(int* x, int* y, int* z)//86500 (F)
{
	IR1 = *x;
	IR2 = *y;
	IR3 = *z;

	int a3 = 0x1F;
	docop2(0xA00428);
	int v0 = MAC1;
	int v1 = MAC2;
	int at = MAC3;
	v0 += v1;
	v0 += at;

	LZCR = gte_leadingzerocount(v0);
	LZCS = v0;

	IR1 = *x;
	IR2 = *y;

	v1 = LZCR;

	at = -2;
	v1 &= at;
	a3 -= v1;
	a3 >>= 1;
	at = v1 - 24;

	if (at >= 0)
	{
		v0 <<= at;
	}
	else
	{
		//loc_8655C
		at = 24;
		at -= v1;
		v0 >>= at;
	}

	//loc_86568
	v0 -= 64;
	v0 = ScalarTable[v0];

	IR3 = *z;
	IR0 = v0;

	docop2(0x190003D);

	*x = MAC1;
	*y = MAC2;
	*z = MAC3;

	*x >>= a3;
	*y >>= a3;
	*z >>= a3;
}

int mSqrt_L(int a0)//8649C (F)
{
	LZCR = gte_leadingzerocount(a0);
	LZCS = a0;

	int v0 = 0x1F;

	if (a0 != 0)
	{
		int v1 = LZCR;
		int at = -2;
		v1 &= at;
		v0 -= v1;
		v0 >>= 1;
		at = v1 - 24;

		if (at >= 0)
		{
			a0 <<= at;
		}
		else
		{
			at = 24;
			at -= v1;
			a0 >>= at;
		}

		//loc_864DC
		a0 -= 64;
		a0 = SqrtTable[a0];
		a0 <<= v0;
	}

	//locret_864F8
	return a0 >> 12;
}

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

void S_CalculateLight(long x, long y, long z, short room_num, struct ITEM_LIGHT* light)
{
	struct room_info* r;//$t0
	int scratchPad[256];
	int t3;
	int t4;
	int t5;
	int t6;

	S_MemSet((char*)&scratchPad[0], 0, 1024);
	int* s1 = &scratchPad[21];
	//at = 0x1000
	s1[3] = 0;
	s1[4] = 0;
	((short*)s1)[10] = 0x1000;
	int* s2 = &s1[8];
	s2[3] = 0;
	s2[4] = 0;
	((short*)s2)[10] = 0x1000;
	int* s3 = &s2[8];
	s3[3] = 0;
	s3[4] = 0;
	((short*)s3)[10] = 0x1000;
	int s4 = 0;
	int s5 = 0;
	int s6 = 0;
	int s7 = 4096;
	int t7 = x;
	int t8 = y;
	int t9 = z;

	//t0 = &room[0];
	//s0 = gp
	r = &room[room_num];

	struct LIGHTINFO* gp = r->light;
	int v0 = ((int*)&r->ambient)[0];
	unsigned short fp = r->num_lights;

	int t2 = (v0 >> 12) & 0xFF0;
	int t1 = (v0 >> 4) & 0xFF0;
	int t0 = (v0 << 4) & 0xFF0;

	SXY0 = t0;
	SXY1 = t1;
	SXY2 = t2;

loc_85D34:
	if (fp-- != 0)
	{
		int t3 = gp->Type;
		int t2 = ((int*)&gp->Inner)[0];
		int t0 = t2 & 0xFF00;

		if (gp->Type == 0)
		{
			s4 |= 0x2000;
			int a0 = ((int*)&gp->nx)[0];
			int a1 = ((int*)&gp->nz)[0];
			int a2 = ((int*)&gp->Type)[0];
			s1[4] = a0;
			s1[5] = a1;
			s1[3] = a2;
			gp++;
			goto loc_85D34;
		}
		else
		{
			//loc_85D70
			t4 = gp->x;
			t5 = gp->y;
			t6 = gp->z;

			t4 -= t7;
			t5 -= t8;
			t6 -= t9;

			IR1 = t4;
			IR2 = t5;
			IR3 = t6;

			t0 >>= 1;

			docop2(0xA00428);

			t1 = (t2 & 0xFF) << 7;
			t2 >>= 16;
			int a3 = t3 & 1;
			int a0 = MAC1;
			int a1 = MAC2;
			int a2 = MAC3;
			a0 += a1;
			a0 += a2;
			int v0 = mSqrt_L(a0);

			a0 = t4;
			if (v0 < t0)
			{
				a1 = t5;
				a2 = t6;

				if (a3 != 0)
				{
					t4 = v0;
					mNormaliseXYZ_L(&a0, &a1, &a2);
					t5 = gp->Intensity;

					a3 = t5;
					if (t4 >= t1)
					{
						t4 -= t1;
						t5 = t0 - t1;
						t5 -= t4;
						a3 = (t5 * t2) >> 8;
					}
					//loc_85E0C
					int at = 4096;
					if (t3 - 3 == 0)
					{
						a3 = at - a3;

						if (a3 < s7)
						{
							gp++;
							s7 = a3;
						}

						goto loc_85D34;

					}

					goto loc_85ED0;
				}
				else
				{
					//loc_85E30
					t4 = v0;
					mNormaliseXYZ_L(&a0, &a1, &a2);
					v0 = (R11 & 0xFFFF) | (R12 << 16) & 0xFFFF;
					int v1 = (R13 & 0xFFFF) | (R21 << 16) & 0xFFFF;

					VX0 = ((int*)&gp->nx)[0] & 0xFFFF;
					VY0 = (((int*)&gp->nx)[0] >> 16) & 0xFFFF;
					VZ0 = ((int*)&gp->nz)[0] & 0xFFFF;

					a1 <<= 16;
					a0 &= 0xFFFF;
					a0 |= a1;

					R11 = a0 & 0xFFFF;
					R12 = (a0 >> 16) & 0xFFFF;
					R13 = a2 & 0xFFFF;
					R21 = (a2 >> 16) & 0xFFFF;

					t3 = t4 - t1;
					docop2(0x486012);
					t5 = t0 - t1;
					t5 -= t3;
					t1 = t5 * t2;
					t5 = ((int*)&gp->Length)[0];
					t3 = ((unsigned short*)&gp->Intensity)[0];
					t6 = t5 >> 16;
					t0 = IR1;
					R11 = v0 & 0xFFFF;
					R12 = (v0 >> 16) & 0xFFFF;
					R13 = v1 & 0xFFFF;
					R21 = (v1 >> 16) & 0xFFFF;

					t5 &= 0xFFFF;
					if (t0 >= t6)
					{
						if (t0 >= t5)
						{
							t0 = 4096;
						}
						//loc_85EA4
						t1 >>= 8;
						a0 = (VX0 & 0xFFFF) | ((VY0 & 0xFFFF) << 16);
						if (t1 >= t3)
						{
							t1 = t3;
						}
						//loc_85EB8
						a3 = t0 * t1;
						a2 = VZ0;
						a1 = a0 >> 16;
						a0 &= 0xFFFF;
						a3 >>= 12;

					loc_85ED0:
						int at = s5 - a3;
						if (s4 - a3 < 0)
						{
							s6 = s5;
							s5 = s4;
							s4 = a3;
							at = (int)s3;
							s3 = s2;
							s2 = s1;
							s1 = (int*)at;
							//j loc_85F2C
						}
						else if (s5 - a3 < 0)
						{
							//loc_85EFC
							s6 = s5;
							s5 = a3;
							at = (int)s3;
							s3 = s2;
							s2 = (int*)at;
							//j loc_85F2C
						}
						else if (s6 - a3 < 0)
						{
							//loc_85F1C
							s6 = a3;
							at = (int)s3;
						}
						else
						{
							goto loc_85F40;
						}

					loc_85F2C:///@TODO expand (implant) into ifs then let it all fall through.
						t0 = ((int*)&gp->Type)[0];
						((short*)at)[8] = a0;
						((short*)at)[9] = a1;
						((short*)at)[10] = a2;
						((int*)at)[3] = t0;
					}//loc_85F40
				}
			}
		loc_85F40:
			gp++;
			goto loc_85D34;
		}
	}
	//loc_85F48
	int at = 4096;
	if (s4 != 0 || s7 - 4096 != 0)
	{
		IR0 = s7;
		IR1 = s4;
		IR2 = s5;
		IR3 = s6;

		t0 = (at - s7) + 4096;
		docop2(0x198003D);
		t1 = SXY0;
		t2 = SXY1;
		int t3 = SXY2;
		at = s4 < 4096 ? 1 : 0;
		
		s4 = IR1;
		s5 = IR2;
		s6 = IR3;
		
		IR1 = t1;
		IR2 = t2;
		IR3 = t3;

		docop2(0x198003D);

		t1 = IR1;
		t2 = IR2;
		t3 = IR3;

		SXY0 = t1;
		SXY1 = t2;
		SXY2 = t3;

		if (at == 0)
		{
			s4 = t0;
		}
	}

	//loc_85FCC
	fp = number_dynamics;
	struct DYNAMIC* gpp = &dynamics[0];

loc_85FD4:
	if (fp--)
	{
		t4 = gpp->x;
		t5 = gpp->y;
		t6 = gpp->z;

		t4 -= t7;
		t5 -= t8;
		t6 -= t9;

		IR1 = t4;
		IR2 = t5;
		IR3 = t6;

		int a0 = t4;
		if (t4 < 0)
		{
			a0 = -t4;
		}

		//loc_8600C
		docop2(0xA00428);
		int a1 = t5;
		if (t5 < 0)
		{
			a1 = -t5;
		}

		//loc_8601C
		int a2 = t6;
		if (t6 < 0)
		{
			a2 = -t6;
		}

		//loc_86028
		if ((unsigned)a0 < 0x2000 && (unsigned)a1 < 0x2000 && (unsigned)a2 < 0x2000)
		{
			t0 = ((int*)&gpp->falloff)[0] >> 1;
			t1 = gpp->FalloffScale;

			a0 = MAC1;
			a1 = MAC2;
			a2 = MAC3;

			a0 += a1;
			a0 += a2;
			
			if (mSqrt_L(a0) < t0)
			{
				v0 = (v0 * t1) >> 8;
				a0 = t4;
				a1 = t5;
				a2 = t6;
				mNormaliseXYZ_L(&a0, &a1, &a2);
				int a3 = 4096 - v0;
				//at = s5 - a3
				if (s4 - a3 < 0)
				{
					s6 = s5;
					s5 = s4;
					s4 = a3;
					at = (int)s3;
					s3 = s2;
					s2 = s1;
					s1 = (int*)at;
					//goto loc_860EC;
				}//loc_860BC
				else if (s5 - a3 < 0)
				{
					s6 = s5;
					s5 = a3;
					at = (int)s3;
					s3 = s2;
					s2 = (int*)at;
					//goto loc_860EC
				}
				else if (s6 - a3 < 0)
				{
					//loc_860DC
					s6 = a3;
					at = (int)s3;
				}
				else
				{
					goto loc_86108;
				}

				//loc_860EC
				t0 = ((int*)&gpp->on)[0];
				((short*)at)[8] = a0;
				((short*)at)[9] = a1;
				((short*)at)[10] = a2;
				((int*)at)[3] = t0;

				if (s7 != 0)
				{
					s7 = a3;
				}

			}//loc_86108
		}
	loc_86108:
		gpp++;
		goto loc_85FD4;
	}//loc_86110

	at = s4 - 4096;
	int* t00 = &scratchPad[0];

	if (at >= 0)
	{
		s4 = at;
	}
	//loc_86120
	t00[0] = s4;
	t00[1] = (int)s1;
	t00[7] = s5;
	t00[8] = (int)s2;
	t00[14] = s6;
	t00[15] = (int)s3;

	int* s66 = t00;
	s5 = (int)light;

	int s11 = SXY0;
	int s22 = SXY1;
	int s33 = SXY2;

	v0 = 3;
	int v1 = light->Light[3].pad;

loc_86154:
	if (v0 != 0)
	{
		s4 = s66[1];
		IR0 = s66[0];
		t0 = ((int*)s4)[3];
		int t3 = ((int*)s5)[2];
		int s0 = t0 & 0xFF;
		t2 = t0 >> 20;
		t1 = (t0 >> 12) & 0xFF0;
		t0 >>= 4;
		t0 &= 0xFF0;

		IR1 = t0;
		IR2 = t1;
		IR3 = t2;

		int t5 = t3 >> 12;
		int t4 = t3 >> 4;
		docop2(0x198003D);
		v0--;
		if (v1 == 0)
		{
			t3 = ((short*)s4)[8];
			t4 = ((short*)s4)[9];
			t5 = ((short*)s4)[10];
			t0 = t3;
			t1 = t4;
			t2 = t5;
		}
		else
		{
			//loc_861BC
			t3 <<= 4;
			t3 &= 0xFF0;
			t4 &= 0xFF0;
			t5 &= 0xFF0;
			RFC = t3;
			GFC = t4;
			BFC = t5;
			IR0 = 3584;
			t3 = ((short*)s4)[8];
			docop2(0x980011);
			t4 = ((short*)s4)[9];
			t5 = ((short*)s4)[10];
			((int*)s5)[0] = t0;
			((short*)s5)[2] = t2;
			t1 = t0 >> 16;
			t0 <<= 16;
			t0 >>= 16;
		}
		//loc_86204
		((int*)s5)[2] = RGB2;
		((int*)s66)[2] = IR1;
		((int*)s66)[3] = IR2;
		((int*)s66)[4] = IR3;
		
		MAC1 = s11;
		MAC2 = s22;
		MAC3 = s33;

		IR0 = 2048;

		t3 -= t0;
		t4 -= t1;
		t5 -= t2;

		docop2(0x1A8003E);

		t3 >>= 3;
		t4 >>= 3;
		t5 >>= 3;

		t0 += t3;
		t1 += t4;
		t2 += t5;

		((short*)s66)[10] = t0;
		((short*)s66)[11] = t1;
		((short*)s66)[12] = t2;
		t0 &= 0xFFFF;
		t1 <<= 16;
		t0 |= t1;
		((int*)s5)[0] = t0;
		((int*)s5)[1] = t2;

		if (s0 != 0)
		{
			s11 = IR1;
			s22 = IR2;
			s33 = IR3;
		}
		//loc_86280
		s66 += 7;
		s5 += 0xC;

		goto loc_86154;
	}
	//loc_8628C
	at = 0x1000000;
	if (v1 != 0)
	{
		IR1 = ((int*)s5)[0];
		IR2 = ((int*)s5)[1];
		IR3 = ((int*)s5)[2];

		RFC = s11;
		GFC = s22;
		BFC = s33;

		IR0 = 1536;

		docop2(0x980011);

		s11 = IR1;
		s22 = IR2;
		s33 = IR3;

	}//loc_862C8

	((int*)s5)[0] = s11;
	((int*)s5)[1] = s22;
	((int*)s5)[2] = s33 | at;

	s11 <<= 1;
	s22 <<= 1;
	s33 <<= 1;

	RBK = s11;
	GBK = s22;
	BBK = s33;

	int s00 = (R11 & 0xFFFF) | ((R12 << 16) & 0xFFFF);
	s11 = (R13 & 0xFFFF) | ((R21 << 16) & 0xFFFF);
	s22 = (R22 & 0xFFFF) | ((R23 << 16) & 0xFFFF);
	s33 = (R31 & 0xFFFF) | ((R32 << 16) & 0xFFFF);
	s4 = R33;
	t0 = 0x808080;

	if (s7 != 0 && s7 < 0xFFF)
	{
		s7 >>= 5;
		t0 = s7 << 16;
		t1 = s7 << 8;
		t0 |= t1;
		t0 |= s7;
	}
	//loc_86330
	R = (t0 & 0xFF);
	G = (t0 & 0xFF00) >> 8;
	B = (t0 & 0xFF0000) >> 16;
	CODE = (t0 & 0xFF000000) >> 24;
	
	struct MATRIX3D* s55 = &CamGTE;
	struct MATRIX3D* s666 = &LightPos;
	int* s77 = &scratchPad[0];

	t0 = ((int*)s55)[0];
	t1 = ((int*)s55)[1];
	t2 = ((int*)s55)[2];
	t3 = ((int*)s55)[3];
	t4 = ((int*)s55)[4];

	R11 = t0 & 0xFFFF;
	R12 = (t0 >> 16) & 0xFFFF;
	R13 = t1 & 0xFFFF;
	R21 = (t1 >> 16) & 0xFFFF;
	R22 = t2 & 0xFFFF;
	R23 = (t2 >> 16) & 0xFFFF;
	R31 = t3 & 0xFFFF;
	R32 = (t3 >> 16) & 0xFFFF;
	R33 = t4;

	VX0 = s77[5] & 0xFFFF;
	VY0 = (s77[5] >> 16) & 0xFFFF;
	VZ0 = s77[6] & 0xFFFF;
	
	VX1 = s77[12] & 0xFFFF;
	VY1 = (s77[12] >> 16) & 0xFFFF;

	docop2(0x486012);

	VZ1 = s77[13];
	VX2 = s77[19] & 0xFFFF;
	VY2 = (s77[19] >> 16) & 0xFFFF;
	VZ2 = s77[20] & 0xFFFF;

	t1 = ((unsigned short*)s77)[18];
	t0 = ((unsigned short*)s77)[4];
	t1 <<= 16;
	t0 |= t1;
	t2 = ((unsigned short*)s77)[6];

	t5 = IR1;
	t8 = IR2;
	t9 = IR3;

	docop2(0x48E012);
	t1 = ((unsigned short*)s77)[32];
	t2 <<= 16;
	t1 |= t2;
	t3 = ((unsigned short*)s77)[34];
	t2 = ((unsigned short*)s77)[20];
	t3 <<= 16;
	t2 |= t3;
	t4 = ((unsigned short*)s77)[22];
	t9 = IR1;
	t7 = IR2;
	int a0 = IR3;
	docop2(0x496012);
	t3 = ((unsigned short*)s77)[8];
	t4 <<= 16;
	t3 |= t4;
	t4 = ((unsigned short*)s77)[36];
	t5 &= 0xFFFF;
	t8 <<= 16;
	t5 |= t8;
	t6 &= 0xFFFF;
	t9 <<= 16;
	t6 |= t9;
	t7 &= 0xFFFF;
	a0 <<= 16;
	t7 |= a0;
	t8 = IR1;
	a0 = IR2;
	t9 = IR3;
	t8 &= 0xFFFF;
	a0 <<= 16;
	t8 |= a0;

	((int*)s666)[0] = t5;
	((int*)s666)[1] = t6;
	((int*)s666)[2] = t7;
	((int*)s666)[3] = t8;
	((int*)s666)[4] = t9;

	SZ0 = t0;
	SZ1 = t1;
	SZ2 = t2;
	SZ3 = t3;
	RGB0 = t4;

	R11 = s00 & 0xFFFF;
	R12 = (s00 >> 16) & 0xFFFF;
	R13 = s11 & 0xFFFF;
	R21 = (s11 >> 16) & 0xFFFF;
	R22 = s22 & 0xFFFF;
	R23 = (s22 >> 16) & 0xFFFF;
	R31 = s33 & 0xFFFF;
	R32 = (s33 >> 16) & 0xFFFF;
	RFC = 0;
	GFC = 0;
	BFC = 0;
}