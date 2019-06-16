#include "ROOMLETB.H"

#include "3D_OBJ.H"
#include "CAMERA.H"
#include "DRAW.H"
#include "EFFECT2.H"
#include "GPU.H"
#include "SPECIFIC.H"
#include "STYPES.H"
#include "MISC.H"
#include "LOAD_LEV.H"
#include "GTEREG.H"
#include "ROOMLOAD.H"

void DrawMesh(int* a0, struct DB_STRUCT* dbs)
{

}

void DrawRoomsAsm()//0x1BC380
{
	DrawRoomletListAsm(0, &room[camera.pos.room_number]);
}

#ifndef USE_ASM

void GetBounds(int* t0, int* t1, int* t6, int* t7, int* t8, int* t9, int* a0, int* a1, int* a2, int* a3, int* v0, int* s5)
{
	int v1 = *t0 << 16;
	v1 >>= 16;

	if (v1 < *a0)
	{
		*a0 = v1;
	}

	//loc_74B40
	*t0 >>= 16;

	if (v1 > * a1)
	{
		*a1 = v1;
	}

	//loc_74B4C
	if (*t0 < *a2)
	{
		*a2 = *t0;
	}

	//loc_74B5C
	v1 = *t6 << 16;
	if (*t0 > * a3)
	{
		*a3 = *t0;
	}

	//loc_74B68
	v1 >>= 16;

	if (v1 < *a0)
	{
		*a0 = v1;
	}

	//loc_74B7C
	*t6 >>= 16;

	if (v1 > * a1)
	{
		*a1 = v1;
	}

	//loc_74B88
	if (*t6 < *a2)
	{
		*a2 = *t6;
	}

	//loc_74B98
	v1 = *t8 << 16;
	if (*t6 > * a3)
	{
		*a3 = *t6;
	}

	//loc_74BA4
	v1 >>= 16;
	if (v1 < *a0)
	{
		*a0 = v1;
	}

	//loc_74BB8
	*t8 >>= 16;

	if (v1 > * a1)
	{
		*a1 = v1;
	}

	//loc_74BC4
	if (*t8 < *a2)
	{
		*a2 = *t8;
	}

	//loc_74BD4
	if (*t8 > * a3)
	{
		*a3 = *t8;
	}

	//loc_74BE0
	if (*t1 > 20479)
	{
		*v0 += 1;
	}//loc_74BEC

	if (*t7 > 20479)
	{
		*v0 += 1;
	}

	//loc_74BF8
	if (*t9 > 20479)
	{
		*v0 += 1;
	}

	//loc_74C04
	if (*t1 == 0)
	{
		*s5 += 1;
	}

	//loc_74C10
	if (*t7 == 0)
	{
		*s5 += 1;
	}

	//loc_74C1C
	if (*t9 == 0)
	{
		*s5 += 1;
	}
}

void DrawRoomletListAsmBinocular(long underwater, struct room_info* r)//roomletb
{
	int s0;
	struct SVECTOR* s3;
	short* s4;
	int t2;
	int* s2;
	int t0;
	int t6;
	int t7;
	int t8;
	int t1;
	int t3;
	int t4;
	int t5;
	int s6;
	int* s1;
	int fpp;
	int s7;
	int* a0;
	struct SVECTOR* t00;
	struct room_info* fp;
	struct WATERTAB* t11;
	struct room_info* s5;
	int at;
	int t9;
	int v0;
	int* a1;
	int sp[256];
	int a3;
	int a2;
	int v1;
	int* a22;
	int* a33;
	int ra;

	RFC = underwater;
	RGB0 = (unsigned long)r;

	s0 = number_draw_rooms;
	s3 = &RoomBBoxes[0];
	s4 = &draw_rooms[0];
	LB3 = wibble & 0xFC;
	s2 = (int*)&tsv_buffer[0];

loc_74C88:
	//t0 = *s4++;
	fp = &room[*s4++];
	
	t0 = fp->MeshEffect;
	t11 = &WaterTable[0][fp->MeshEffect];

	s2[0] = (unsigned long)fp;
	s2[1] = (unsigned long)t11;

	s1 = (int*)fp->data;
	//t0 = room.x (fp)
	//t1 = room.y (fp)
	s5 = (struct room_info*)RGB0;
	//t2 = room.z(fp)
	//t3 = r->x
	//t4 = r->y
	//t5 = r->z

	t6 = r->x - fp->x;
	t7 = r->y - fp->y;
	t8 = r->z - fp->z;

	if (t6 > -31745 && t6 < 31744 &&
		t7 > -31745 && t6 < 37144 &&
		t8 > -31745 && t8 < 37144)
	{
		t7 = fp->minfloor - r->y;
		t6 = (((fp->x_size - 2) << 10) + fp->z) - r->z;
		t8 = (((fp->y_size - 2) << 10) + fp->x) - r->x;

		if (t6 > -31745 && t6 < 37144 &&
			t7 > -31745 && t7 < 37144 &&
			t8 > -31745 && t8 < 37144)
		{
			t7 = s5->minfloor - fp->y;
			t6 = (((s5->x_size - 2) << 10) + r->x) - fp->x;
			t8 = (((s5->y_size - 2) << 10) + r->z) - fp->z;

			if (t6 > -31745 && t6 < 37144 &&
				t7 > -31745 && t7 < 37144 &&
				t8 > -31745 && t8 < 37144)
			{
				t6 = fp->x - r->x;
				t7 = fp->y - r->y;
				t8 = fp->z - r->z;

				t0 = r->x;
				t1 = r->y;
				t2 = r->z;
			}
			else
			{
				//loc_74DF8
				t6 = 0;
				t7 = 0;
				t8 = 0;
			}
		}
		else
		{
			//loc_74DF8
			t6 = 0;
			t7 = 0;
			t8 = 0;
		}
	}
	else
	{
		//loc_74DF8
		t6 = 0;
		t7 = 0;
		t8 = 0;
	}

	//loc_74E04
	s2[5] = (int)t6;
	s2[6] = (int)t7;
	s2[7] = (int)t8;

	t3 = ((int*)MatrixStack)[5];
	t4 = ((int*)MatrixStack)[6];
	t5 = ((int*)MatrixStack)[7];

	t0 -= t3;
	t1 -= t4;
	t2 -= t5;

	t3 = t0 >> 15;

	if (t0 < 0)
	{
		t0 = -t0;
		t3 = t0 >> 15;
		t0 &= 0x7FFF;
		t3 = -t3;
		t0 = -t0;
	}
	else
	{
		//loc_74E48
		t0 &= 0x7FFF;
	}

	t4 = t1 >> 15;
	if (t1 < 0)
	{
		t1 = -t1;
		t4 = t1 >> 15;
		t1 &= 0x7FFF;
		t4 = -t4;
		t1 = -t1;
	}
	else
	{
		//loc_74E6C
		t1 &= 0x7FFF;
	}

	t5 = t2 >> 15;

	if (t2 < 0)
	{
		t2 = -t2;
		t5 = t2 >> 15;
		t2 &= 0x7FFF;
		t5 = -t5;
		t2 = -t2;
	}
	else
	{
		t2 &= 0x7FFF;
	}

	//loc_74E94
	IR1 = t3;
	IR2 = t4;
	IR3 = t5;

	docop2(0x41E012);

	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	IR1 = t0;
	IR2 = t1;
	IR3 = t2;

	docop2(0x49E012);

	t0 = t3 << 3;
	if (t3 < 0)
	{
		t3 = -t3;
		t3 <<= 3;
		t0 = -t3;
	}
	//loc_74ED8
	t1 = t4 << 3;
	if (t4 < 0)
	{
		t4 = -t4;
		t4 <<= 3;
		t1 = -t4;
	}//loc_74EEC

	t2 = t5 << 3;
	if (t5 < 0)
	{
		t5 = -t5;
		t5 <<= 3;
		t2 = -t5;
	}
	//loc_74F00
	t3 = MAC1;
	t4 = MAC2;
	t5 = MAC3;

	t0 += t3;
	t1 += t4;
	t2 += t5;

	TRX = t0;
	TRY = t1;
	TRZ = t2;

	s2[2] = t0;
	s2[3] = t1;
	s2[4] = t2;

	s2 += 8;
	s6 = *s1++;//room.data?

	t0 = *(int*)&fp->left;//left & right
	t2 = *(int*)&fp->top;//top & bottom

	t1 = t0 >> 16;
	t0 &= 0xFFFF;
	t3 = t2 >> 16;
	t2 &= 0xFFFF;

	t1++;
	t3++;

	L11 = t0;
	L13 = t1;
	L22 = t2;
	L31 = t3;
	RBK = t6;

	fpp = t7;
	s7 = t8;

loc_74F78:
	
	if (s6 != 0)
	{
		a0 = (int*)*s1++;
		t3 = *a0;
		s2[0] = (int)a0;
		t6 = RBK;
		t00 = &s3[t3 & 0xFFF8];
		t1 = t00->vz;
		at = t00->vx;
		t0 = t00->vy;

		at = (at + t6) & 0xFFFF;
		t0 += fpp;
		t1 += s7;
		t0 <<= 16;
		t0 |= at;

		SVECTOR* t33;///@CHECKME result of t3 :S

		t3 >>= 13;
		t3 &= 0xFFF8;
		t33 = &s3[t3];

		at = t33->vx;
		t2 = t33->vy;
		t3 = t33->vz;

		at += t6;
		at &= 0xFFFF;

		t2 += fpp;
		t3 += s7;
		t2 <<= 16;
		t2 |= at;

		VX0 = t0 & 0xFFFF;
		VY0 = (t0 >> 16) & 0xFFFF;
		VZ0 = t1;

		VX1 = t2 & 0xFFFF;
		VY1 = (t2 >> 16) & 0xFFFF;
		VZ1 = t1;

		VX2 = t2 & 0xFFFF;
		VY2 = (t2 >> 16) & 0xFFFF;
		VZ2 = t3;

		t4 = t0 & 0xFFFF;

		docop2(0x280030);
		t6 = t7 & 0xFFFF;
		t7 = 0xFFFF0000;
		t5 = t0 & t7;
		t7 &= t2;
		t4 |= t7;
		t5 |= t6;

		int a00, a11, a22, a33, s55;

		a00 = 0x800;
		a11 = 0xFFFFF800;
		a22 = 0x800;
		a33 = 0xFFFFF800;

		s55 = 0;

		t1 = SZ1;
		t6 = SXY1;
		t7 = SZ2;
		t8 = SXY2;
		t9 = SZ3;

		VX0 = t4 & 0xFFFF;
		VY0 = (t4 >> 16) & 0xFFFF;

		VX1 = t5 & 0xFFFF;
		VY1 = (t5 >> 16) & 0xFFFF;

		VX2 = t0 & 0xFFFF;
		VY2 = (t0 >> 16) & 0xFFFF;

		t0 = SXY0;

		docop2(0x280030);
		v0 = 0;
		GetBounds(&t0, &t1, &t6, &t7, &t8, &t9, &a00, &a11, &a22, &a33, &v0, &s55);

		t0 = SXY0;
		t1 = SZ1;
		t6 = SXY1;
		t7 = SZ2;
		t8 = SXY2;
		t9 = SZ3;

		VZ0 = t3;
		VZ1 = t3;

		docop2(0x280030);
		GetBounds(&t0, &t1, &t6, &t7, &t8, &t9, &a00, &a11, &a22, &a33, &v0, &s55);

		t0 = SXY0;
		t1 = SZ1;
		t6 = SXY1;
		t7 = SZ2;
		t8 = t6;
		t9 = t7;

		GetBounds(&t0, &t1, &t6, &t7, &t8, &t9, &a00, &a11, &a22, &a33, &v0, &s55);

		if (v0 < 9 && s55 < 9)
		{
			t0 = L11 | (L12 << 16);
			t1 = L13 | (L21 << 16);
			t2 = L22 | (L23 << 16);
			t3 = L31 | (L32 << 16);

			if (a11 > t0 && a00 < t1 && a33 > t2 && a22 < t3)
			{
				s2++;
			}//loc_75100
		}//loc_75100

		s6--;
		goto loc_74F78;

	}//loc_75108
	s2[0] = 0;
	s0--;
	s2++;

	if (s0 != 0)
	{
		goto loc_74C88;
	}

	s2[0] = 0;
	s2 = (int*)&tsv_buffer[0];

loc_75124:
	a1 = (int*)s2[0];
	RGB0 = s2[1];
	s2 += 8;

	if (a1 != NULL)
	{
		t0 = s2[-6];
		t1 = s2[-5];
		t2 = s2[-4];

		TRX = t0;
		TRY = t1;
		TRZ = t2;

		t0 = a1[5];
		t1 = a1[6];
		t2 = a1[7];

		sp[11] = t0;
		sp[12] = t1;
		sp[13] = t2;

		t0 = a1[14];
		t2 = a1[15];

		at = 0xFFFF0000;

		t1 = t0 & at;
		t3 = t2 & at;

		at = 0x10000;

		t1 += at;
		t3 += at;

		t0 <<= 16;
		t2 <<= 16;

		L11 = t0 & 0xFFFF;
		L12 = (t0 >> 16) & 0xFFFF;

		L13 = t1 & 0xFFFF;
		L21 = (t1 >> 16) & 0xFFFF;

		L22 = t2 & 0xFFFF;
		L23 = (t2 >> 16) & 0xFFFF;

		L31 = t3;

		t0 = s2[-3];
		t1 = s2[-2];
		t2 = s2[-1];

		RBK = t0;
		GBK = t1;
		BBK = t2;

		//loc_751B4
		a0 = (int*)s2[0];
		s2++;
		t5 = a0[0];

		if (a0 == NULL)
		{
			goto loc_75124;
		}


		t6 = 0;
		t00 = &s3[t5 & 0xFFF8];///@checkme result of t0 :S

		t2 = t00->vz;
		t0 = *(int*)& t00->vx;

		t5 >>= 13;
		t5 &= 0xFFF8;
		SVECTOR* t55 = &s3[t5];

		t3 = *(int*)& t55->vx;
		t5 = t55->vz;

		t1 = (t0 >> 16);
		t0 &= 0xFFFF;
		t4 = t3 >> 16;
		t3 &= 0xFFFF;

		t7 = sp[11];
		t8 = sp[12];
		t9 = sp[13];

		t0 += t7;
		t1 += t8;
		t2 += t9;
		t3 += t7;
		t4 += t8;
		t5 += t9;
		t7 = 1;

		int* t88;
		t88 = &sp[0];
		t9 = 0;

		struct DYNAMIC* s11 = dynamics;
		a3 = 32;

	loc_75238:
		dynamics[32].on = 0;
		at = s11->on;
		a3--;
		a2 = s11->falloff;

		if (s11->on)
		{
			v0 = s11->x;
			at >>= 1;
			v1 = v0 + a2;
			v0 -= a2;

			if (v1 > t0 && v0 < t3)
			{
				v0 = s11->y;
				v1 = v0 + a2;
				v0 -= a2;

				if (v1 > t1 && v0 < t4)
				{
					v0 = s11->z;
					v1 = v0 + a2;
					v0 -= a2;

					if (v1 > t2 && v0 < t5)
					{
						a2 >>= 7;
						s11->used = 1;
						t9 += a2;
						t88[0] = (int)s1;
						t88++;
						t6++;
					}
					else
					{
						//loc_752C0
						s11->used = 0;
					}
				}
				else
				{
					//loc_752C0
					s11->used = 0;
				}
			}
			else
			{
				//loc_752C0
				s11->used = 0;
			}
		}
		//loc_752C4
		s11++;

		if (a3 != 0)
		{
			goto loc_75238;
		}


		struct DYNAMIC* t888 = &dynamics[32];

	loc_752D0:
		t7 = 0xFFF0000;

		if (t9 > 95)
		{
			t3 = 0;
			s1 = &sp[0];
			t5 = t6;

		loc_752E8:
			a22 = (int*)s1[0];
			if (t5 == 0)
			{
				goto loc_752D0;
			}

			s1++;
			t5--;

			if (a22 == 0)
			{
				goto loc_752E8;
			}

			a1 = s1;
			t4 = t5 - 1;

		loc_75304:
			a33 = (int*)a1[0];
			if (t4 != 0)
			{
				a1++;
				t4--;

				if (a33 == 0)
				{
					goto loc_75304;
				}

				t0 = a22[0];
				at = a33[0];
				t1 = a22[1];

				t0 -= at;
				at = a33[1];

				if (t0 < 0)
				{
					t0 = -t0;
				}//loc_75334

				t1 -= at;
				if (t0 > 0x7FF)
				{
					goto loc_75304;
				}

				ra = a22[2];

				at = a33[2];

				if (t1 < 0)
				{
					t1 = -t1;
				}
				//loc_75350

				ra -= at;
				if (t1 > 0x7FF)
				{
					goto loc_75304;
				}

				t0 += t1;

				if (ra < 0)
				{
					ra = -ra;
				}
				//loc_75368

				t0 += ra;
				if (ra > 0x7FF)
				{
					goto loc_75304;
				}

				int t2 = (int)a22;
				if (t7 > t0)
				{
					goto loc_75304;
				}

				t7 = t0;
				v0 = (int)& s1[-1];
				v1 = (int)& a1[-1];
				t3 = a3;
				goto loc_75304;
			}
			//loc_75394
			t0 = ((short*)t2)[8];

			if (t3 != 0)
			{
				t1 = ((short*)t3)[8];
				((int*)v1)[0] = 0;
				((int*)v0)[0] = (int)t888;
				///@CONTINUE

				if (t0 > t1)
				{
					((short*)t888)[8] = t0;
					t1 >>= 8;
					t9 -= t1;
				}
				else
				{
					//loc_753C0
					((short*)t888)[8] = t1;
					t0 >>= 8;
					t9 -= t0;
				}
				//loc_753CC

				t0 = ((int*)t2)[3];
				t1 = ((int*)t3)[3];
				t7 = 0x7C7C7C00;

				t0 >>= 1;
				t1 >>= 1;
				t0 &= t7;
				t1 &= t7;
				t0 += t1;
				t0 |= 1;
				((int*)t888)[3] = t0;
				((char*)t888)[18] = t0;

				v0 = ((int*)t2)[0];
				v1 = ((int*)t3)[0];
				t0 = ((int*)t2)[1];
				t1 = ((int*)t3)[1];

				v0 += v1;
				v0 >>= 1;
				t0 += t1;
				t0 >>= 1;

				((int*)t888)[0] = v0;
				v0 = ((int*)t2)[2];
				v1 = ((int*)t3)[2];
				((int*)t888)[1] = t0;

				v0 += v1;
				v0 >>= 1;
				((int*)t888)[2] = v0;
				((char*)t2)[18] = 0;
				((char*)t3)[18] = 0;
				t8++;
				goto loc_752D0;
			}
			//loc_75448
		}//loc_75448
		
		s11 = dynamics;
		a1 = &sp[192];
		v1 = 15;
		v0 = 64;

		//loc_7545C
		do
		{
			t0 = s11->used;
			t1 = s11->y >> 7;
			if (s11->on && s11->used)
			{
				t0 = s11->x >> 7;
				t2 = s11->z >> 7;

				a1[0] = t0;
				a1[1] = t1;
				a1[2] = t2;

				t1 = (*(int*)& s11->on >> 8) << 8;
				t0 = s11->falloff >> 8;

				t1 |= t0;
				a1[3] = t1;
				a1 += 4;
				v1--;
				if (v1 == 0)
				{
					//loc_754C4
					break;
				}
			}//loc_754B8

			v0--;
			s11++;
		} while (v0 != 0);

		//loc_754C4
		a1[3] = 0;

		DrawMesh(a0, &db);

		///a1 = &db
		///a1[8] = a3 (db.polyptr store?)
		///j loc_751B4
	}///loc_76420?

	UNIMPLEMENTED();
}

void DrawRoomletListAsm(long unk, struct room_info* r)//0x1BC4D0
{
	UNIMPLEMENTED();
}

#endif