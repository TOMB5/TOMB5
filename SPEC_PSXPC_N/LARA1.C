#include "LARA1.H"

#include "3D_OBJ.H"
#include "MISC.H"
#include "CAMERA.H"
#include "DRAWSPKS.H"
#include "DELSTUFF.H"
#include "LARA.H"
#include "MATHS.H"
#include "DRAW.H"
#include "SETUP.H"
#include "GTEREG.H"
#include "GPU.H"
#include "TOMB4FX.H"

int scratchPad[256];

void sub_FC0(int x, int y, int z)
{
    int t0 = TRX;
    int t1 = TRY;
    int t2 = TRZ;

    x -= t0;
    y -= t1;
    z -= t2;

    int t4 = y >> 15;
    if (y < 0)
    {
        y = -y;
        t4 = y >> 15;
        t4 = -t4;
        y &= 0x7FFF;
        y = -y;
    }
    else
    {
        y &= 0x7FFF;
    }

    //loc_FFC
    int t5 = z >> 15;
    if (z < 0)
    {
        z = -z;
        t5 = z >> 15;
        t5 = -t5;
        z &= 0x7FFF;
        z = -z;
    }
    else
    {
        z &= 0x7FFF;
    }

    int t3 = x >> 15;
    if (x < 0)
    {
        x = -x;
        t3 = x >> 15;
        t3 = -t3;
        x &= 0x7FFF;
        x = -x;
    }
    else
    {
        x &= 0x7FFF;
    }

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

    docop2(0x49E012);

    int t0 = t3 << 3;
    if (t3 < 0)
    {
        t3 = -t3;
        t3 <<= 3;
        t0 = -t3;
    }

    int t1 = t4 << 3;
    if (t4 < 0)
    {
        t4 = -t4;
        t4 <<= 3;
        t1 = -t4;
    }

    int t2 = t5 << 3;
    if (t5 < 0)
    {
        t5 = -t5;
        t5 <<= 3;
        t1 = -t4;
    }

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

void sub_1184()
{
    int* s3 = &scratchPad[0];
    //s4 = ra
    struct GUNSHELL_STRUCT* s1 = &Gunshells[0];
    //s2 = 0x18;

    //loc_1198
    //v0 = s1->counter
    //s2--;
    if (s1->counter != 0)
    {
        sub_FC0(s1->pos.x_pos, s1->pos.y_pos, s1->pos.z_pos);

    }
    //loc_1234

}

void sub_E38()
{
    UNIMPLEMENTED();
}

void sub_1358(int x, int y, int z)
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

void sub_C1C(int a0)
{
    int* a00 = (int*)&tsv_buffer[(((a0 << 1) + a0) << 2)];
    char* a1 = (char*)&SkinVertNums[(((a0 << 1) + a0) << 2)];

    do
    {
        char v0 = *a1++;

        //loc_C38
        if (v0 >= 0)
        {
            int* a2 = &scratchPad[v0 << 1];
            a00[0] = a2[0];
            a00[1] = a2[1];
            a00 += 2;
        }
        else
        {
            break;
        }
    } while (1);
    //locret_C64
}

void sub_C6C(int a0)
{
    int* a00 = (int*)&tsv_buffer[(((a0 << 1) + a0) << 2)];
    char* a2 = (char*)&ScratchVertNums[(((a0 << 1) + a0) << 2)];

    //loc_C88
    do
    {
        char v0 = *a2++;

        //
        if (v0 >= 0)
        {
            int* a1 = &scratchPad[v0 << 1];
            a1[0] = a00[0];
            a1[1] = a00[1];
            a00 += 2;
        }
        else
        {
            break;
        }
    } while (1);
    //locret_CB4
}   

void sub_CBC(int a0)
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

int* sub_658(short* meshp, int* s5/*db.polyptr*/, int s6/*ot*/)
{
    unsigned int t00;
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

    int v0 = ((int*)meshp)[2];
    meshp += 6;
    unsigned int* a1 = (unsigned int*)&meshp[v0 >> 17];
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
        VZ2 = ((int*)&LightPos)[4] & 0xFFFF;

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

        a3 = (int*)&meshp[v0 << 2];

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

            a2[0] = SXY0;
            a2[1] = SZ1;
            a2[2] = SXY1;
            a2[3] = SZ2;
            a2[4] = SXY2;
            a2[5] = SZ3;

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

            ORGB = LIM(IR1 >> 7, 0x1F, 0, 0) | (LIM(IR2 >> 7, 0x1F, 0, 0) << 5) | (LIM(IR3 >> 7, 0x1F, 0, 0) << 10);
            t0 = ORGB; 
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
       t00 = a1[0];

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

       t5 = t00 & 0xFF;
       t00 >>= 8;
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
                   if ((t1 >> 16) < 0xF0 || (t2 >> 16) < 0xF0 || (t3 >> 16) < 0xF0)
                   {
                       t1 = OTZ;
                       if (t1 < 0xA01)
                       {
                           t1 <<= 2;
                           t4 = ((int*)t5)[2];
                           at = t4 << 8;
                           sub_BAC(&t2, &t6, &a33, &t3, &at, &t7, &t8);
                           at = DQB;
                           t2 = ((int*)t5)[0];
                           t3 = ((int*)t5)[1];
                           t2 -= at;
#if defined(USE_32_BIT_ADDR)
                           ((int*)s5)[3] = SXY0;
                           ((int*)s5)[6] = SXY1;
                           ((int*)s5)[9] = SXY2;
                           ((int*)s5)[2] = t6;
                           ((int*)s5)[4] = t2;
                           ((int*)s5)[5] = t7;
                           ((int*)s5)[7] = t3;
                           ((int*)s5)[8] = t8;
                           ((int*)s5)[10] = t4;
                           t1 *= 2;
                           t1 += s6;
                           setlen(s5, 9);
                           addPrim(t1, s5);
#else
                           ((int*)s5)[2] = SXY0;
                           ((int*)s5)[5] = SXY1;
                           ((int*)s5)[8] = SXY2;
                           ((int*)s5)[1] = t6;
                           ((int*)s5)[3] = t2;
                           ((int*)s5)[4] = t7;
                           ((int*)s5)[6] = t3;
                           ((int*)s5)[7] = t8;
                           ((int*)s5)[9] = t4;
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

       a1++;
       if (v0 != 0)
       {
           if (v1-- != 0)
           {
               goto loc_88C;
           }

           t00 = a1[0];
           goto loc_884;

       }//loc_9E8
   }
   //loc_9E8
   v0 = DQA;

   t00 = a1[0];

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
       t5 = t00 & 0xFFF;
       t00 >>= 16;
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
                   if ((t1 >> 16) < 0xF0 || (t2 >> 16) < 0xF0 || (t3 >> 16) < 0xF0 || (t4 >> 16) < 0xF0)
                   {
                       //loc_AEC
                       t5 += (int)a22;
                       t2 = t9 >> 7;
                       t1 = OTZ;
                       t2 &= a33;

                       if (t1 < 0xA01)
                       {
                           t1 <<= 2;
#if defined(USE_32_BIT_ADDR)
                           s5[3] = SXY0;
                           s5[6] = SXY1;
                           s5[9] = SXY2;
                           s5[12] = t4;
#else
                           s5[2] = SXY0;
                           s5[5] = SXY1;
                           s5[8] = SXY2;
                           s5[11] = t4;
#endif
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

#if defined(USE_32_BIT_ADDR)
                           s5[2] = t6;
                           s5[4] = t2;
                           s5[5] = t7;
                           s5[7] = t3;
                           s5[8] = t8;
                           s5[10] = t4;
                           s5[11] = t9;
                           s5[13] = t5;
                           t1 *= 2;
                           t1 += s6;
                           setlen(s5, 12);
                           addPrim(t1, s5);
#else
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
#endif
                           s5 += sizeof(POLY_GT4) / sizeof(unsigned long);
                       }//loc_B8C
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

           t00 = a1[0];
           goto loc_9F4;
       }
   }//loc_BA4

   return s5;
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

    S_MemSet((char*)&scratchPad[0], 0, 1024);

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
        if (!LaraNodeUnderwater[i])
        {
            break;
        }
        else
        {
            a1 = 1;
        }
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
    for (i = 0; i < 15; i++)///@TODO check < 15
    {
        int t0 = ((int*)&lara_matrices[i])[0];
        int t1 = ((int*)&lara_matrices[i])[1];
        int t2 = ((int*)&lara_matrices[i])[2];
        int t3 = ((int*)&lara_matrices[i])[3];

        R11 = t0 & 0xFFFF;
        R12 = (t0 >> 16) & 0xFFFF;

        R13 = t1 & 0xFFFF;
        R21 = (t1 >> 16) & 0xFFFF;

        R22 = t2 & 0xFFFF;
        R23 = (t2 >> 16) & 0xFFFF;

        R31 = t3 & 0xFFFF;
        R32 = (t3 >> 16) & 0xFFFF;

        t0 = ((int*)&lara_matrices[i])[4];
        t1 = ((int*)&lara_matrices[i])[5];
        t2 = ((int*)&lara_matrices[i])[6];
        t3 = ((int*)&lara_matrices[i])[7];

        R33 = t0;
        TRX = t1;
        TRY = t2;
        TRZ = t3;
        //a0 = &LaraNodeUnderwater[0];
        //a1 = 0xF - 
        if (LaraNodeUnderwater[i])
        {
            a0 = LaraNodeAmbient[1];
        }
        else
        {
            a0 = LaraNodeAmbient[0];
        }
        //loc_1A0
        RBK = (((int*)&a0.r)[0] & 0xFF) << 4;
        GBK = ((((int*)&a0.r)[0] >> 4) & 0xFF0);
        BBK = ((((int*)&a0.r)[0] >> 12) & 0xFF0);

        a00 = *s0++;
        //v1 = &lara.mesh_ptrs[0];
        //a00 = &lara.mesh_ptrs[lara_mesh_sweetness_table[0]]
        //v0 = (lara_item->mesh_bits >> 16) & (1 << 0xF)

        if ((lara_item->mesh_bits >> 16)& (1 << 0xF))
        {
#if defined(USE_32_BIT_ADDR)
            db.polyptr = (char*)sub_658(lara.mesh_ptrs[lara_mesh_sweetness_table[i]], (int*)db.polyptr, (int)(db.ot+1*2));
#else
            db.polyptr = (char*)sub_658(lara.mesh_ptrs[lara_mesh_sweetness_table[i]], (int*)db.polyptr, (int)(db.ot+1));
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
            if (NodesToStashFromScratch[i][j] != -1)
            {
                sub_C1C(NodesToStashFromScratch[i][j]);
            }
            else
            {
                //loc_238
                break;
            }
        }
    }
    //loc_238
    //s4 = lara_item
    //s0 = &SkinUseMatrix[0][0];
    //v0 = objects[LARA_SKIN_JOINTS].mesh_index
    //v1 = meshes
    short* s1 = (short*)&meshes[objects[LARA_SKIN_JOINTS].mesh_index];
    s1 += 4;
    //s3 = NodesToStashToScratch[0][0]
    i = 0xE;//s2
    //s4 = lara_item->mesh_bits

    //loc_278
    for (i = 0; i < 0xE; i++)
    {
        if (i == 7)
        {
            int test = 0;
            test++;
        }
        //v0 = 1 << 0xE
        //v0 = lara_item->mesh_bits & (1 << 0xE)

        if (lara_item->mesh_bits & (1 << 0xE))
        {
            //a0 = &LaraNodeUnderwater[0];
            //a2 = &lara_underwater_skin_sweetness_table[0];
            //a1 = 0xE
            //a1 -= s2
            //a2 = &lara_underwater_skin_sweetness_table[i]
            //v0 = lara_underwater_skin_sweetness_table[i]
            //a0 = &LaraNodeUnderwater[lara_underwater_skin_sweetness_table[i]];
            //v0 = LaraNodeUnderwater[lara_underwater_skin_sweetness_table[i]];

            int a0 = ((int*)&LaraNodeAmbient)[0];

            if (LaraNodeUnderwater[lara_underwater_skin_sweetness_table[i]])
            {
                a0 = ((int*)&LaraNodeAmbient)[1];
            }

            //loc_2C8
            RBK = (a0 & 0xFF) << 4;
            GBK = (a0 >> 4) & 0xFF0;
            BBK = (a0 >> 12) & 0xFF0;

            // int t2 = SkinUseMatrix[0][0];//derive from s0
             //t0 = &tsv_buffer[0];
             //t1 = &ScratchVertNums[0];
            sub_C6C(NodesToStashToScratch[i][0]);
            sub_C6C(NodesToStashToScratch[i][1]);

            if (SkinUseMatrix[i][0] < 0xFF)
            {
                //  v1 = SkinUseMatrix[0][1];
                  //t0 = lara_matrices
                  //v0 = &lara_matrices[SkinUseMatrix[0][0]];
                  //v1 = &lara_matrices[SkinUseMatrix[0][1]];
                int t0 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[0];
                int t1 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[1];
                int t2 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[2];
                int t3 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[3];
                int t4 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[4];
                int t5 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[5];
                int t6 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[6];
                int t7 = ((int*)&lara_matrices[SkinUseMatrix[i][1]])[7];

                a0 = ((short*)&lara_matrices[SkinUseMatrix[i][0]])[4];
                a1 = (t2 << 16) >> 16;
                a0 *= a1;

                a1 = ((short*)&lara_matrices[SkinUseMatrix[i][0]])[1];
                short a2 = ((short*)&lara_matrices[SkinUseMatrix[i][1]])[1];
                int at = a0 >> 1;
                a0 += at;
                at = a1 * a2;

                a1 = ((short*)&lara_matrices[SkinUseMatrix[i][0]])[7];
                a2 = ((short*)&lara_matrices[SkinUseMatrix[i][1]])[7];
                a0 += at;

                R11 = t0 & 0xFFFF;
                R12 = (t0 >> 16) & 0xFFFF;

                a1 = a1 * a2;

                R13 = t1 & 0xFFFF;
                R21 = (t1 >> 16) & 0xFFFF;
                R22 = t2 & 0xFFFF;
                R23 = (t2 >> 16) & 0xFFFF;
                R31 = t3 & 0xFFFF;
                R32 = (t3 >> 16) & 0xFFFF;
                R33 = t4;
                TRX = t5;
                TRY = t6;
                TRZ = t7;

                a0 += a1;
                a0 >>= 12;
                t0 = a0;
                a0 = a0 * a0;

                //0x1000000
                v0 = phd_atan_asm(t0, mSqrt(0x1000000 - a0));
                //at = 0xD

                if (i == 0xE - 0xD || i == 0xE - 0xA)//Really || 0xD and 0xA without 0xE - 
                {
                    v0 = -v0;
                }
                //loc_3FC
                a0 = v0 >> 1;
                a0 = -a0;
                sub_CBC(a0);

            }//loc_408

#if defined(USE_32_BIT_ADDR)
            db.polyptr = (char*)sub_658((short*)((int*)s1)[0], (int*)db.polyptr, (int)(db.ot + 1 * 2));
#else
            db.polyptr = (char*)sub_658((short*)((int*)s1)[0], (int*)db.polyptr, (int)(db.ot + 1));
#endif
        }
        //loc_410
        //s1 = &s1[0xD - i * 4];
        s1 += 4;
    }

    //s6 = db.ot[0];
    if (lara_item->mesh_bits + 1 == 0)
    {
        if (LaraNodeUnderwater[0] != 0)
        {
            a0 = LaraNodeAmbient[1];
        }
        else
        {
            a0 = LaraNodeAmbient[0];
        }

        RBK = (((int*)&a0.r)[0] & 0xFF) << 4;
        GBK = ((((int*)&a0.r)[0] >> 4) & 0xFF0);
        BBK = ((((int*)&a0.r)[0] >> 12) & 0xFF0);

        //v0 = lara.hostler
        //v1 = objects
        s0 = (int*)&meshes[objects[lara.holster].mesh_index];
        s0 += 8;
        int* v1 = (int*)&lara_matrices[1];
        int t0 = v1[0];
        int t1 = v1[1];
        int t2 = v1[2];
        int t3 = v1[3];
        int t4 = v1[4];
        int t5 = v1[5];
        int t6 = v1[6];
        int t7 = v1[7];

        R11 = t0 & 0xFFFF;
        R12 = (t0 >> 16) & 0xFFFF;

        R13 = t1 & 0xFFFF;
        R21 = (t1 >> 16) & 0xFFFF;

        R22 = t2 & 0xFFFF;
        R23 = (t2 >> 16) & 0xFFFF;

        R31 = t3 & 0xFFFF;
        R32 = (t3 >> 16) & 0xFFFF;
        R33 = t4;

        TRX = t5;
        TRY = t6;
        TRZ = t7;

        ///@FIXME for some reason at index 0 it wont draw left holster!
#if defined(USE_32_BIT_ADDR)
        db.polyptr = (char*)sub_658((short*)((int*)s0)[0], (int*)db.polyptr, (int)db.ot);
#else
        db.polyptr = (char*)sub_658((short*)((int*)s0)[0], (int*)db.polyptr, (int)db.ot);
#endif
        s0 += 8;

        v1 = (int*)&lara_matrices[4];

        t0 = v1[0];
        t1 = v1[1];
        t2 = v1[2];
        t3 = v1[3];
        t4 = v1[4];
        t5 = v1[5];
        t6 = v1[6];
        t7 = v1[7];

        R11 = t0 & 0xFFFF;
        R12 = (t0 >> 16) & 0xFFFF;

        R13 = t1 & 0xFFFF;
        R21 = (t1 >> 16) & 0xFFFF;

        R22 = t2 & 0xFFFF;
        R23 = (t2 >> 16) & 0xFFFF;

        R31 = t3 & 0xFFFF;
        R32 = (t3 >> 16) & 0xFFFF;
        R33 = t4;

        TRX = t5;
        TRY = t6;
        TRZ = t7;

        ///@FIXME for some reason at index 0 it wont draw right holster!
#if defined(USE_32_BIT_ADDR)
        db.polyptr = (char*)sub_658((short*)((int*)s0)[0], (int*)db.polyptr, (int)db.ot);
#else
        db.polyptr = (char*)sub_658((short*)((int*)s0)[0], (int*)db.polyptr, (int)db.ot);
#endif
    }
    //loc_538
    //v0 = lara.back_gun
    //v1 = objects

    if (lara.back_gun != 0)
    {
        //a2 = objects[lara.back_gun].bone_index
        //v1 = 
        long* bone = &bones[objects[lara.back_gun].bone_index];//a2
        //v0 =  objects[lara.back_gun].mesh_index
        s0 = (int*)&meshes[objects[lara.back_gun].mesh_index];//$s0

        int* v1 = (int*)&lara_matrices[7];

        int t0 = v1[0];
        int t1 = v1[1];
        int t2 = v1[2];
        int t3 = v1[3];
        int t4 = v1[4];
        int t5 = v1[5];
        int t6 = v1[6];
        int t7 = v1[7];

        R11 = t0 & 0xFFFF;
        R12 = (t0 >> 16) & 0xFFFF;

        R13 = t1 & 0xFFFF;
        R21 = (t1 >> 16) & 0xFFFF;

        R22 = t2 & 0xFFFF;
        R23 = (t2 >> 16) & 0xFFFF;

        R31 = t3 & 0xFFFF;
        R32 = (t3 >> 16) & 0xFFFF;
        R33 = t4;

        TRX = t5;
        TRY = t6;
        TRZ = t7;

        sub_1358(bone[53], bone[54], bone[55]);
        ///@FIXME for some reason at index 0 it wont draw back gun!
#if defined(USE_32_BIT_ADDR)
        db.polyptr = (char*)sub_658((short*)((int*)s0)[28], (int*)db.polyptr, (int)db.ot);
#else
        db.polyptr = (char*)sub_658((short*)((int*)s0)[28], (int*)db.polyptr, (int)db.ot);
#endif

    }
    //loc_5D0
    mPopMatrix();

    if (LaraNodeUnderwater[8] != 0)
    {
        a0 = LaraNodeAmbient[1];
    }
    else
    {
        a0 = LaraNodeAmbient[0];
    }

    //loc_5F0
    RBK = (((int*)&a0.r)[0] & 0xFF) << 4;
    GBK = ((((int*)&a0.r)[0] >> 4) & 0xFF0);
    BBK = ((((int*)&a0.r)[0] >> 12) & 0xFF0);

    sub_E38();

    sub_1184();
}

void DrawLara()
{
    sub_2C(lara_item);
}