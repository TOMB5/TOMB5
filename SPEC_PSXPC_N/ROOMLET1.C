#include "ROOMLET1.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "EFFECT2.H"
#include "GTEREG.H"
#include "LOAD_LEV.H"
#include "3D_OBJ.H"
#include "ROOMLOAD.H"

void GetBoundsRL1(int* t0, int* t1, int* t6, int* t7, int* t8, int* t9, int* v0, int* s5, int* a0, int* a1, int* a2, int* a3)//sub_50
{
    int v1 = (*t0 << 16) >> 16;

    if (v1 < *a0)
    {
        *a0 = v1;
    }//loc_68

    *t0 >>= 16;
    if (v1 >= *a1)
    {
        *a1 = v1;
    }

    //loc_74
    if (*t0 < *a2)
    {
        *a2 = *t0;
    }

    //loc_84
    v1 = *t6 << 16;
    if (*t0 >= *a3)
    {
        *a3 = *t0;
    }

    //loc_90
    v1 >>= 16;
    if (v1 < *a0)
    {
        *a0 = v1;
    }

    //loc_A4
    *t6 >>= 16;
    if (v1 >= *a1)
    {
        *a1 = v1;
    }

    if (*t6 < *a2)
    {
        *a2 = *t6;
    }

    //loc_C0
    v1 = *t8 << 16;
    if (*t6 >= *a3)
    {
        *a3 = *t6;
    }

    //loc_CC
    v1 >>= 16;
    if (v1 < *a0)
    {
        *a0 = v1;
    }
    
    //loc_E0
    *t8 >>= 16;
    if (v1 >= *a1)
    {
        *a1 = v1;
    }
    //loc_EC
    if (*t8 < *a2)
    {
        *a2 = *t8;
    }

    if (*t8 >= *a3)
    {
        *a3 = *t8;
    }

    if ((unsigned)*t1 >= 0x5000)
    {
        *v0 += 1;
    }

    if ((unsigned)*t7 >= 0x5000)
    {
        *v0 += 1;
    }

    if ((unsigned)*t9 >= 0x5000)
    {
        *v0 += 1;
    }

    if (*t1 == 0)
    {
        *s5 += 1;
    }

    if (*t7 == 0)
    {
        *s5 += 1;
    }

    if (*t9 == 0)
    {
        *s5 += 1;
    }
}

void sub_158RL1(long underwater, struct room_info* r)
{
    int t0;
    int t1;
    int t2;
    int at;
    struct room_info* fp;
    struct WATERTAB* t11;
    unsigned int* s2;
    int* s1;
    struct room_info* s5;
    int t6;
    int t7;
    int t8;
    int s6;
    int fpp;
    int s7;
    int a0;
    int a1;
    int a2;
    int a3;
    int t9;

    RFC = (unsigned int)underwater;
    RGB0 = (unsigned int)r;

    //s0 = number_draw_rooms
    int* s3 = (int*)RoomBBoxes;
    short* s4 = &draw_rooms[0];
    //t2 = wibble & 0xFC
    s2 = (unsigned int*)&tsv_buffer[0];
    LB3 = wibble & 0xFC;

    //loc_1B0
    fp = &room[*s4++];
    //t0 = fp->mesheffect
    t11 = &WaterTable[0][fp->MeshEffect];///@FIXME WaterTable bad values...
    s2[0] = (unsigned int)fp;
    s2[1] = (unsigned int)t11;

    s1 = (int*)fp->data;
    t0 = fp->x;
    t1 = fp->y;
    t2 = fp->z;
    //t3 = s5->x
    //t4 = s5->y
    //t5 = s5->z
    s5 = (struct room_info*)RGB0;

    t6 = s5->x - fp->x;
    t7 = s5->y - fp->y;
    t8 = s5->z - fp->z;

    if (t6 >= -31744 && t6 < 31744 &&
        t7 >= -31744 && t7 < 31744 &&
        t8 >= -31744 && t8 < 31744)
    {
        t7 = (fp->minfloor - s5->y);
        t6 = (((fp->x_size - 2) << 16) + fp->x) - s5->z;
        t8 = (((fp->y_size - 2) << 16) + fp->z) - s5->x;

        if (t6 >= -31744 && t6 < 31744 &&
            t7 >= -31744 && t7 < 31744 &&
            t8 >= -31744 && t8 < 31744)
        {
            t7 = (s5->minfloor - fp->y);
            t6 = (((s5->x_size - 2) << 16) + s5->x) - fp->x;
            t8 = (((s5->y_size - 2) << 16) + s5->z) - fp->z;

            if (t6 >= -31744 && t6 < 31744 &&
                t7 >= -31744 && t7 < 31744 &&
                t8 >= -31744 && t8 < 31744)
            {
                t6 = fp->x - s5->x;
                t7 = fp->y - s5->y;
                t8 = fp->z - s5->z;

                t0 = s5->x;
                t1 = s5->y;
                t2 = fp->z;
            }
            else
            {
                t6 = 0;
                t7 = 0;
                t8 = 0;
            }
        }
        else
        {
            t6 = 0;
            t7 = 0;
            t8 = 0;
        }
    }
    else
    {
        //loc_320
        t6 = 0;
        t7 = 0;
        t8 = 0;
    }

    //loc_32C
    s2[5] = t6;
    s2[6] = t7;
    s2[7] = t8;

    int t3 = ((int*)&MatrixStack[0])[5];
    int t4 = ((int*)&MatrixStack[0])[6];
    int t5 = ((int*)&MatrixStack[0])[7];

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

    t1 = t4 << 3;
    if (t4 < 0)
    {
        t4 = -t4;
        t4 <<= 3;
        t1 = -t4;
    }

    t2 = t5 << 3;
    if (t5 < 0)
    {
        t5 = -t5;
        t5 <<= 3;
        t2 = -t5;
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

    s2[2] = t0;
    s2[3] = t1;
    s2[4] = t2;

    s2 += 8;
    s6 = *s1++;
    t0 = ((int*)&fp->left)[0];
    t2 = ((int*)&fp->top)[0];
    t1 = (t0 >> 16) & 0xFFFF;
    t3 = (t2 >> 16) & 0xFFFF;

    t1++;
    t3++;

    L11 = t0 & 0xFFFF;
    L12 = (t0 >> 16) & 0xFFFF;
    L13 = t1 & 0xFFFF;
    L21 = (t1 >> 16) & 0xFFFF;
    L22 = t2 & 0xFFFF;
    L23 = (t2 >> 16) & 0xFFFF;
    L31 = t3 & 0xFFFF;
    L32 = (t3 >> 16) & 0xFFFF;
    RBK = t6;

    fpp = t7;
    s7 = t8;

    a0 = *s1;

    if (s6 != 0)
    {
        s1++;
        t3 = ((int*)a0)[0];
        s2[0] = a0;
        t6 = RBK;

        t0 = (t3 << 3) & 0xFFF8;
        t0 += (int)s3;

        t1 = ((short*)t0)[2];
        at = ((short*)t0)[0];
        t0 = ((short*)t0)[1];

        at += t6;
        at &= 0xFFFF;

        t0 += fpp;
        t1 += s7;
        t0 <<= 16;
        t0 |= at;
        t3 >>= 13;
        t3 &= 0xFFF8;
        t3 += (int)s3;

        at = ((short*)t3)[0];
        t2 = ((short*)t3)[1];
        t3 = ((short*)t3)[2];

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
        t6 = t2 & 0xFFFF;
        t7 = 0xFFFF0000;
        t5 = t0 & t7;
        t7 &= t2;
        t4 |= t7;
        t5 |= t6;

        a0 = 2048;
        a1 = -2048;
        a2 = 2048;
        a3 = -2048;

        s5 = 0;

        t1 = SZ1;
        t6 = SXY1;
        t7 = SZ2;
        t8 = SXY2;
        t9 = SZ3;

        VZ0 = t3;
        VZ1 = t3;

        docop2(0x280030);

        //sub_50();

    }//loc_630
}

void DrawRoomletListAsmRL1()
{
    sub_158RL1(camera_underwater, &room[camera.pos.room_number]);
}