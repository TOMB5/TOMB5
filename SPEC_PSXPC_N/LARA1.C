#include "LARA1.H"

#include "DRAWSPKS.H"
#include "DELSTUFF.H"
#include "LARA.H"
#include "MATHS.H"
#include "DRAW.H"
#include "SETUP.H"
#include "GTEREG.H"
#include "GPU.H"

void sub_BAC(int* t2, int* t6, int* a3, int* t3, int* at, int* t7, int* t8)
{
    *t2 = *t6 >> 7;
    *t2 &= *a3;
    *t3 = *t6 >> 10;
    *t3 &= 0xF800;
    *t6 >>= 13;
    *t6 &= 0xF8;
    *t6 |= *t3;
    *t6 |= *t2;
    *at >>= 24;
    *at <<= 24;
    *t6 |= *at;
    *t2 = *t7 >> 7;
    *t2 &= *a3;
    *t3 = *t7 >> 10;
    *t3 &= 0xF800;
    *t7 >>= 13;
    *t7 &= 0xF8;
    *t7 |= *t3;
    *t7 |= *t2;
    *t2 = *t8 >> 7;
    *t2 &= *a3;
    *t3 = *t8 >> 10;
    *t3 &= 0xF800;
    *t8 >>= 13;
    *t8 &= 0xF8;
    *t8 |= *t3;
    *t8 |= *t2;
}

void sub_658(short* meshp, int* s5/*db.polyptr*/, int s6/*ot*/)
{
    int t0;
    int t1;
    int t2;
    int t3;
    int t4;
    int t5;
    int t6;
    int t7;
    int t8;
    int t9;
    int at;
    int v1;
    int* a3;
    int* a0;
    int scratchPad[256];
    int v0 = ((int*)meshp)[2];
    meshp += 6;
    int* a1 = (int*)&meshp[v0 >> 17];
    v0 &= 0xFF;
    int* a2 = &scratchPad[0];

    if (v0 != 0)
    {
        t0 = (R11 & 0xFFFF) | ((R12 & 0xFFFF) << 16);
        t1 = (R13 & 0xFFFF) | ((R21 & 0xFFFF) << 16);
        t2 = (R22 & 0xFFFF) | ((R23 & 0xFFFF) << 16);
        t3 = (R31 & 0xFFFF) | ((R32 & 0xFFFF) << 16);
        t4 = (R33 & 0xFFFF);

        t5 = 0xFFFF0000;
        t6 = t0 & t5;
        t7 = t2 & t5;
        t0 &= 0xFFFF;
        at = t1 & t5;
        t0 |= at;
        t2 &= 0xFFFF;
        at = t3 & t5;
        t2 |= at;
        t1 &= 0xFFFF;
        t1 |= t7;
        t3 &= 0xFFFF;
        t3 |= t6;

        L11 = t0 & 0xFFFF;
        L12 = (t0 >> 16) & 0xFFFF;
        L13 = t3 & 0xFFFF;
        L21 = (t3 >> 16) & 0xFFFF;
        L22 = t2 & 0xFFFF;
        L23 = (t2 >> 16) & 0xFFFF;
        L31 = t1 & 0xFFFF;
        L32 = (t1 >> 16) & 0xFFFF;
        L33 = t4 & 0xFFFF;

        //t9 = &LightPos

        t0 = ((int*)&LightPos)[0];
        t1 = ((int*)&LightPos)[1];
        VX0 = (t0 & 0xFFFF);
        VY0 = (t0 >> 16) & 0xFFFF;
        VZ0 = (t1 & 0xFFFF);
        docop2(0x4A6012);
        t0 = ((int*)&LightPos)[2];
        t1 >>= 16;
        at = t0 << 16;
        t1 |= at;
        t0 >>= 16;

        VX1 = t1 & 0xFFFF;
        VY1 = (t1 >> 16) & 0xFFFF;
        VZ1 = t0;

        t0 = IR1;
        t2 = IR2;
        t1 = IR3;

        docop2(0x4AE012);
        VX2 = ((int*)&LightPos)[3] & 0xFFFF;
        VY2 = (((int*)&LightPos)[3] >> 16) & 0xFFFF;
        VZ2 = ((int*)&LightPos)[4];

        t0 &= 0xFFFF;
        t2 <<= 16;
        t0 |= t2;
        t1 &= 0xFFFF;

        t3 = IR1;
        t2 = IR2;
        t4 = IR3;

        docop2(0x4B6012);

        t3 <<= 16;
        t1 |= t3;
        t2 &= 0xFFFF;
        t4 <<= 16;
        t2 |= t4;

        t3 = IR1;
        t5 = IR2;
        t4 = IR3;

        t3 &= 0xFFFF;
        t5 <<= 16;
        t3 |= t5;

        L11 = t0 & 0xFFFF;
        L12 = (t0 >> 16) & 0xFFFF;

        L13 = t1 & 0xFFFF;
        L21 = (t1 >> 16) & 0xFFFF;

        L22 = t2 & 0xFFFF;
        L23 = (t2 >> 16) & 0xFFFF;

        L31 = t3 & 0xFFFF;
        L32 = (t3 >> 16) & 0xFFFF;

        L33 = t4;

        at = v0 << 3;
        v1 = v0;

        a3 = (int*)&meshp[v0 << 2];///@CHECKME result ptr

        t0 = ((int*)meshp)[0];
        t1 = ((int*)meshp)[1];
        t2 = ((int*)meshp)[2];
        t3 = ((int*)meshp)[3];
        t4 = ((int*)meshp)[4];
        t5 = ((int*)meshp)[5];

        //loc_7AC
        do
        {
            VX0 = t0 & 0xFFFF;
            VY0 = (t0 >> 16) & 0xFFFF;
            VZ0 = t1 & 0xFFFF;

            VX1 = t2 & 0xFFFF;
            VY1 = (t2 >> 16) & 0xFFFF;
            VZ1 = t3 & 0xFFFF;

            VX2 = t4 & 0xFFFF;
            VY2 = (t4 >> 16) & 0xFFFF;
            VZ2 = t5 & 0xFFFF;

            meshp += 12;
            v0 -= 3;

            docop2(0x280030);

            t0 = ((int*)meshp)[0];
            t1 = ((int*)meshp)[1];
            t2 = ((int*)meshp)[2];
            t3 = ((int*)meshp)[3];
            t4 = ((int*)meshp)[4];
            t5 = ((int*)meshp)[5];

            SXY0 = a2[0];
            SZ1 = a2[1];
            SXY1 = a2[2];
            SZ2 = a2[3];
            SXY2 = a2[4];
            SZ3 = a2[5];

            a2 += 6;
        } while (v0 > 0);


        t0 = TRZ;
        t1 = 0;
        t0 -= 0x3000;
        at = v0 << 3;

        if (t0 > 0)
        {
            t1 = t0 >> 1;
        }

        //loc_820
        IR0 = t1;
        t1 = a3[0];
        t2 = a3[1];
        a2 = &scratchPad[0];

        //loc_830
        do
        {
            VX0 = t1 & 0xFFFF;
            VY0 = (t1 >> 16) & 0xFFFF;
            VZ0 = t2 & 0xFFFF;

            a3 += 2;
            docop2(0xE80413);
            t1 = a3[0];
            t2 = a3[1];
            v1--;
            a2 += 2;

            t0 = LIM(IR1 >> 7, 0x1f, 0, 0) | (LIM(IR2 >> 7, 0x1f, 0, 0) << 5) | (LIM(IR3 >> 7, 0x1f, 0, 0) << 10);
            ((short*)a2)[-1] = t0;
        } while (v1 != 0);

   }
    //loc_85C
   a0 = &scratchPad[0];
   PSXTEXTSTRUCT* a22 = psxtextinfo;
   v0 = a1[0];
   int a33 = 0xF80000;
   at = v0 >> 16;
   DQA = at;
   v0 &= 0xFFFF;
   a1++;

   if (v0 != 0)
   {
       t0 = a1[0];

loc_884:
       a1++;
       v1 = 3;

loc_88C:
       t1 = a1[0];
       v0--;

       t8 = (t1 >> 13) & 0x7F8;
       t8 += (int)a0;
       t7 = (t1 >> 5) & 0x7F8;
       t7 += (int)a0;
       t6 = (t1 << 3) & 0x7F8;
       t6 += (int)a0;

       SXY0 = ((int*)t6)[0];
       SXY1 = ((int*)t7)[0];
       SXY2 = ((int*)t8)[0];

       t5 = t0 & 0xFF;
       t0 >>= 8;
       docop2(0x1400006);

       t6 = ((int*)t6)[1];
       t7 = ((int*)t7)[1];
       t8 = ((int*)t8)[1];

       SZ1 = t6;
       SZ2 = t7;
       SZ3 = t8;

       t1 >>= 16;
       t1 &= 0xF00;
       at = MAC0;
       docop2(0x158002D);
       t5 |= t1;
       t5 <<= 4;

       if (at >= 0)
       {
           t5 += (int)a22;
           t1 = SXY0;
           t2 = SXY1;
           t3 = SXY2;

           if (!(t1 & 0xFE00) || !(t2 & 0xFE00) || !(t3 & 0xFE00))
           {
               //loc_92C
               at = t1 & t2;
               at &= t3;
               

               if (at >= 0)
               {
                   at = t1 >> 16;
                   if (at < 0xF0)
                   {
                       at = t2 >> 16;
                       if (at < 0xF0)
                       {
                           at = t3 >> 16;
                           if (at < 0xF0)
                           {
                               t1 = OTZ;
                               if (t1 < 0xA01)
                               {
                                   t1 <<= 2;
                                   t4 = ((int*)t5)[3];
                                   at = t4 << 8;
                                   sub_BAC(&t2, &t6, &a33, &t3, &at, &t7, &t8);
                                   at = DQB;
                                   t2 = ((int*)t5)[0];
                                   t3 = ((int*)t5)[1];
                                   t2 -= at;

                                   ((int*)s5)[2] = SXY0;
                                   ((int*)s5)[5] = SXY1;
                                   ((int*)s5)[8] = SXY2;
                                   ((int*)s5)[1] = t6;
                                   ((int*)s5)[3] = t2;
                                   ((int*)s5)[4] = t7;
                                   ((int*)s5)[6] = t3;
                                   ((int*)s5)[7] = t8;
                                   ((int*)s5)[9] = t4;
#if defined(USE_32_BIT_ADDR)
                                   t1 *= 2;
                                   t1 += s6;
                                   setlen(s5, 9);
                                   addPrim(t1, s5);
#else
                                   t1 += s6;
                                   t2 = ((int*)t1)[0];
                                   at = 0x9000000;
                                   t2 |= at;
                                   ((int*)t1)[0] = (int)s5;
                                   s5[0] = t2;
#endif
                                   s5 += sizeof(POLY_GT3) / sizeof(unsigned long);
                               }//loc_9D0
                           }//loc_9D0
                       }//loc_9D0
                   }//loc_9D0
               }//loc_9D0
           }//loc_9D0
       }//loc_9D0

       a1++;
       if (v0 != 0)
       {
           if (v1-- != 0)
           {
               goto loc_88C;
           }

           t0 = a1[0];
           goto loc_884;

       }//loc_9E8
   }
   //loc_9E8
   v0 = DQA;

   t0 = a1[0];

   if (v0 != 0)
   {
loc_9F4:
       a1++;
       v1 = 1;

loc_9FC:
       t1 = a1[0];
       v0--;
       
       t9 = t1 >> 21;
       t8 = t1 >> 13;
       t8 &= 0x7F8;
       t8 += (int)a0;
       t7 = t1 >> 5;
       t7 &= 0x7F8;
       t7 += (int)a0;
       t6 = t1 << 3;
       t6 &= 0x7F8;
       t6 += (int)a0;
       SXY0 = ((int*)t6)[0];
       SXY1 = ((int*)t7)[0];
       SXY2 = ((int*)t8)[0];
       t9 &= 0x7F8;
       t9 += (int)a0;
       docop2(0x1400006);
       t6 = ((int*)t6)[1];
       t7 = ((int*)t7)[1];
       t8 = ((int*)t8)[1];
       t4 = ((int*)t9)[0];
       t9 = ((int*)t9)[1];
       SZ0 = t6;
       SZ1 = t7;
       SZ2 = t8;
       SZ3 = t9;
       at = MAC0;
       docop2(0x168002E);
       t5 = t0 & 0xFFF;
       t0 >>= 16;
       t5 <<= 4;

       if (at >= 0)
       {
           t1 = SXY0;
           t2 = SXY1;
           t3 = SXY2;

           if (!(t1 & 0xFE00) || !(t2 & 0xFE00) || !(t3 & 0xFE00) || !(t4 & 0xFE00))
           {
               //loc_AAC
               at = t1 & t2;
               at &= t3;
               at &= t4;

               if (at >= 0)
               {
                   at = t1 >> 16;
                   if (at < 0xF0)
                   {
                       at = t2 >> 16;
                       if (at < 0xF0)
                       {
                           at = t3 >> 16;
                           if (at < 0xF0)
                           {
                               at = t4 >> 16;
                               if (at < 0xF0)
                               {
                                   //loc_AEC
                                   t5 += (int)a22;
                                   t2 = t9 >> 7;
                                   t1 = OTZ;
                                   t2 &= a33;

                                   if (t1 < 0xA01)
                                   {
                                       t1 <<= 2;
                                       s5[2] = SXY0;
                                       s5[5] = SXY1;
                                       s5[8] = SXY2;
                                       s5[11] = t4;
                                       t3 = t9 >> 10;
                                       t3 &= 0xF800;
                                       t9 >>= 13;
                                       t9 &= 0xF8;
                                       t9 |= t3;
                                       t9 |= t2;
                                       t4 = ((int*)t5)[2];
                                       at = t4;
                                       sub_BAC(&t2, &t6, &a33, &t3, &at, &t7, &t8);
                                       at = DQB;
                                       t2 = ((int*)t5)[0];
                                       t3 = ((int*)t5)[1];
                                       t5 = ((int*)t5)[3];
                                       t2 -= at;

                                       s5[1] = t6;
                                       s5[3] = t2;
                                       s5[4] = t7;
                                       s5[6] = t3;
                                       s5[7] = t8;
                                       s5[9] = t4;
                                       s5[10] = t9;
                                       s5[12] = t5;
                                       t1 += s6;
                                       t2 = ((int*)t1)[0];
                                       at = 0xC000000;
                                       t2 |= at;
                                       ((int*)t1)[0] = (int)s5;
                                       ((int*)s5)[0] = t2;
                                       s5 += sizeof(POLY_GT4) / sizeof(unsigned long);
                                   }//loc_B8C
                               }
                           }
                       }
                   }
               }//loc_B8C
           }//loc_B8C
       }
       //loc_B8C
       a1++;
       if (v0 != 0)
       {
           if (v1-- != 0)
           {
               goto loc_9FC;
           }

           goto loc_9F4;
           t0 = a1[0];
       }
   }//loc_BA4
}

void sub_1330(struct ITEM_INFO* item)
{
	struct object_info* object = &objects[item->object_number];
	//S_PrintNiceShadow(object->shadow_size, GLaraShadowframe, 0);
}

void sub_2C(struct ITEM_INFO* item)
{
	int i;
	int underwater_node = 0;//$v1
	int a1 = 0;
	int v0;
	int at;
	int v1;
	struct CVECTOR a0;
	int* s0;
	int a00;
	int j;//$t6

	//v0 = item->hit_points
	if (item->hit_points > 0)
	{
		sub_1330(item);
	}
	//loc_6C
	mPushMatrix();
	CalculateObjectLightingLara();
	//a0 = LaraNodeUnderwater
	a1 = 0;
	//a2 = 14
	//loc_8C
	//v0 = LaraNodeUnderwater[0];
	//a2--;
	for (i = 0; i < 15; i++)
	{
		if(LaraNodeUnderwater[i])
		{
			underwater_node = LaraNodeUnderwater[i];
			break;
		}
		a1 = 1;
	}
	//loc_A0
	if (a1 == 0)
	{
		v0 = RBK >> 5;
		at = GBK >> 5;
		v1 = BBK >> 5;

		if (v0 >= 0xFF)
		{
			v0 = 0xFF;
		}

		if (v1 >= 0xFF)
		{
			v1 = 0xFF;
		}

		if (at >= 0xFF)
		{
			at = 0xFF;
		}

		//loc_E4
		if (a1 >= 0xFF)
		{
			a1 = 0xFF;
		}

		//loc_F0
		at <<= 8;
		v1 <<= 16;
		v0 |= v1;
		v0 |= at;

		((int*)&LaraNodeAmbient[0].r)[0] = v0;
	}
	//loc_104
	//s5 = db.polyptr
	//s6 = db.ot[1]
	//s3 = lara_item
	s0 = &lara_mesh_sweetness_table[0];
	//s1 = &lara_matrices
	//s2 = 0xF
	//s4 = &NodesToStashFromScratch
	//s3 = lara_item->mesh_bits >> 16;

	//loc_138
	for(i = 0; i < 15; i++)///@TODO check < 15
	{
		int t0 = ((int*)& lara_matrices[i])[0];
		int t1 = ((int*)& lara_matrices[i])[1];
		int t2 = ((int*)& lara_matrices[i])[2];
		int t3 = ((int*)& lara_matrices[i])[3];

		R11 = t0 & 0xFFFF;
		R12 = (t0 >> 16) & 0xFFFF;

		R13 = t1 & 0xFFFF;
		R21 = (t1 >> 16) & 0xFFFF;

		R22 = t2 & 0xFFFF;
		R23 = (t2 >> 16) & 0xFFFF;

		R31 = t3 & 0xFFFF;
		R32 = (t3 >> 16) & 0xFFFF;

		t0 = ((int*)& lara_matrices[0])[4];
		t1 = ((int*)& lara_matrices[0])[5];
		t2 = ((int*)& lara_matrices[0])[6];
		t3 = ((int*)& lara_matrices[0])[7];

		R33 = t0;
		TRX = t1;
		TRY = t2;
		TRZ = t3;
		//a0 = &LaraNodeUnderwater[0];
		//a1 = 0xF - 
		if (LaraNodeUnderwater[a1 - 15])
		{
			a0 = LaraNodeAmbient[1];
		}
		else
		{
			a0 = LaraNodeAmbient[0];
		}
		//loc_1A0
		RBK = (((int*)& a0.r)[0] & 0xFF) << 4;
		GBK = ((((int*)& a0.r)[0] >> 4) & 0xFF0);
		BBK = ((((int*)& a0.r)[0] >> 12) & 0xFF0);

		a00 = *s0++;
		//v1 = &lara.mesh_ptrs[0];
		//a00 = &lara.mesh_ptrs[lara_mesh_sweetness_table[0]]
		//v0 = (lara_item->mesh_bits >> 16) & (1 << 0xF)

		if ((lara_item->mesh_bits >> 16) & (1 << 0xF))
		{
#if defined(USE_32_BIT_ADDR)
            sub_658(lara.mesh_ptrs[lara_mesh_sweetness_table[0]], (int*)db.polyptr, db.ot[1 * 2]);
#else
			sub_658(lara.mesh_ptrs[lara_mesh_sweetness_table[0]], (int*)db.polyptr, db.ot[1]);
#endif
		}//loc_1FC

		//s2--;
		//int t7 = &NodesToStashFromScratch[0];
		int t6 = 4;
		//t0 = &tsv_buffer[0]
		//t1 = &SkinVertNums[0];

		//loc_218
		for (j = 0; j < 4; j++)
		{
			if (NodesToStashFromScratch[i][j] != 255)
			{
				//sub_C1C(NodesToStashFromScratch[i][j]);
			}
			else
			{
				//loc_238
				break;
			}
		}
	}
	//loc_238

}

void DrawLara()
{
    sub_2C(lara_item);
}