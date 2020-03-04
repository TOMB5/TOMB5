#include "ROOMLET1.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "EFFECT2.H"
#include "GTEREG.H"
#include "LOAD_LEV.H"
#include "3D_OBJ.H"
#include "ROOMLOAD.H"
#include "MISC.H"
#include "GPU.H"

char* DrawMeshRL1(int* scratchPad, int mesh, struct DB_STRUCT* cdb)
{
    //UNIMPLEMENTED();
    return NULL;
}

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
    int t3;
    int t4;
    int at;
    struct room_info* fp;
    struct WATERTAB* t11;
    unsigned int* s2;
    int* s1;
    struct room_info* s5;
    int t5;
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
    int v0;
    int v1;
    int ra;
    int scratchPad[256];
    int* sp = &scratchPad[0];

    S_MemSet((char*)&scratchPad[0], 0, 1024);

    RFC = (unsigned int)underwater;
    RGB0 = (unsigned int)r;

    int s0 = number_draw_rooms;
    int* s3 = (int*)RoomBBoxes;
    short* s4 = &draw_rooms[0];
    //t2 = wibble & 0xFC
    s2 = (unsigned int*)&tsv_buffer[0];
    LB3 = wibble & 0xFC;

    //loc_1B0
    do
    {
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

    loc_4A0:
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

            int s55 = 0;

            t1 = SZ1;
            t6 = SXY1;
            t7 = SZ2;
            t8 = SXY2;
            t9 = SZ3;

            VZ0 = t3;
            VZ1 = t3;

            docop2(0x280030);

            v0 = 0;
            GetBoundsRL1(&t0, &t1, &t6, &t7, &t8, &t9, &v0, &s55, &a0, &a1, &a2, &a3);

            t0 = SXY0;
            t1 = SZ1;
            t6 = SXY1;
            t7 = SZ2;
            t8 = SXY2;
            t9 = SZ3;

            VZ0 = t3;
            VZ1 = t3;

            docop2(0x280030);

            GetBoundsRL1(&t0, &t1, &t6, &t7, &t8, &t9, &v0, &s55, &a0, &a1, &a2, &a3);

            t0 = SXY0;
            t1 = SZ1;
            t6 = SXY1;
            t7 = SZ2;
            t8 = t6;
            t9 = t7;

            GetBoundsRL1(&t0, &t1, &t6, &t7, &t8, &t9, &v0, &s55, &a0, &a1, &a2, &a3);

            if ((unsigned)v0 < 9 && (unsigned)s5 < 9)
            {
                t0 = (L11 & 0xFFFF) | ((L12 & 0xFFFF) << 16);
                t1 = (L13 & 0xFFFF) | ((L21 & 0xFFFF) << 16);
                t2 = (L22 & 0xFFFF) | ((L23 & 0xFFFF) << 16);
                t3 = (L31 & 0xFFFF) | ((L32 & 0xFFFF) << 16);

                if (a1 >= t0 && a0 < t1 && a3 >= t2 && a2 < t3)
                {
                    s2++;
                }
            }

            //loc_628
            s6--;
            goto loc_4A0;

        }//loc_630

        *s2++ = 0;
    } while (--s0);

    s2[0] = 0;
    s2 = (unsigned int*)&tsv_buffer;

loc_64C:
    a1 = s2[0];
    RGB0 = s2[1];
    s2 += 8;

    if (a1 != 0)
    {
        t0 = s2[-6];
        t1 = s2[-5];
        t2 = s2[-4];

        TRX = t0;
        TRY = t1;
        TRZ = t2;

        t0 = ((int*)a1)[5];
        t1 = ((int*)a1)[6];
        t2 = ((int*)a1)[7];

        sp[11] = t0;
        sp[12] = t1;
        sp[13] = t2;

        t0 = ((int*)a1)[14];
        t2 = ((int*)a1)[15];

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
        L31 = t3 & 0xFFFF;
        L32 = (t3 >> 16) & 0xFFFF;

        t0 = s2[-3];
        t1 = s2[-2];
        t2 = s2[-1];

        RBK = t0;
        GBK = t1;
        BBK = t2;

        //loc_6DC
        a0 = *s2++;

        if (a0 == 0)
        {
            goto loc_64C;
        }
        t5 = ((int*)a0)[0];
        t6 = 0;
        t0 = (t5 << 3) & 0xFFF8;
        t0 += (int)s3;
        t2 = ((short*)t0)[2];
        t0 = ((int*)t0)[0];
        t5 >>= 13;
        t5 &= 0xFFF8;
        t5 += (int)s3;
        t3 = ((int*)t5)[0];
        t5 = ((short*)t5)[2];
        t1 = t0 >> 16;
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

        t8 = (int)&scratchPad[0];
        t9 = 0;

        struct DYNAMIC* dyn = &dynamics[0];//$s1
        a3 = 0x20;
        //loc_760
        do
        {
            dynamics[32].on = FALSE;
            a3--;

            if (dyn->on)
            {
                //a2 = dyn->falloff >> 9
                //v0 = dyn->x - (dyn->falloff >> 2);
                //v1 = dyn->x + (dyn->falloff >> 2);

                if ((dyn->falloff >> 2) >= t0 && dyn->x - (dyn->falloff >> 2) < t3)
                {
                    //v0 = dyn->y - (dyn->falloff >> 2)
                    //v1 = dyn->y + (dyn->falloff >> 2)

                    if (dyn->y + (dyn->falloff >> 2) >= t1 && dyn->y - (dyn->falloff >> 2) < t4)
                    {
                        //v0 = dyn->z - (dyn->falloff >> 2)
                        //v1 = dyn->z + (dyn->falloff >> 2)

                        if (dyn->z + (dyn->falloff >> 2) >= t2 && dyn->z - (dyn->falloff >> 2) < t5)
                        {
                            dyn->used = TRUE;
                            t9 += dyn->falloff >> 9;
                            ((int*)t8)[0] = (int)dyn;
                            t8 += 4;
                            t6 += 1;
                        }
                        else
                        {
                            //loc_7E8
                            dyn->used = FALSE;
                        }
                    }
                    else
                    {
                        //loc_7E8
                        dyn->used = FALSE;
                    }
                }
                else
                {
                    //loc_7E8
                    dyn->used = FALSE;
                }
            }//loc_7EC

            dyn++;
        } while (a3 != 0);

        struct DYNAMIC* dyn2 = &dynamics[32];

    loc_7F8:
        if (t9 >= 0x60)
        {
            t7 = 0xFFF0000;
            t3 = 0;
            s1 = &scratchPad[0];
            t5 = t6;

        loc_810:
            if (t5 == 0)
                goto loc_7F8;

            a2 = *s1++;

            t5--;
            if (a2 == 0)
                goto loc_810;

            a1 = (int)s1;
            t4 = t5 - 1;

        loc_82C:
            if (t4 != 0)
            {
                a3 = ((int*)a1)[0];
                a1 += 4;

                t4--;
                if (a3 == 0)
                {
                    goto loc_82C;
                }

                t0 = ((int*)a2)[0];
                at = ((int*)a3)[0];
                t1 = ((int*)a2)[1];

                t0 -= at;
                at = ((int*)a3)[1];

                t1 -= at;
                if ((unsigned)ABS(t0) >= 0x800)
                    goto loc_82C;

                ra = ((int*)a2)[2];

                ra -= at;
                if (ABS(t1) >= 0x800)
                    goto loc_82C;

                t0 += ra;
                if (ABS(ra) >= 0x800)
                    goto loc_82C;

                t2 = a2;
                if (t0 >= t7)
                    goto loc_82C;

                t7 = t0;
                v0 = (int)&s1[-1];
                v1 = a1 - 4;
                t3 = a3;

                goto loc_82C;
            }//loc_8BC

            if (t3 != 0)
            {
                t0 = ((short*)t2)[8];
                t1 = ((short*)t3)[8];
                ((int*)v1)[0] = 0;

                if (t0 >= t1)
                {
                    ((int*)v1)[0] = t8;
                    ((short*)t8)[8] = t0;
                    t1 >>= 8;
                    t9 -= t1;
                }
                else
                {
                    ((short*)t8)[8] = t1;
                    t0 >>= 8;
                    t9 -= t0;
                }

                //loc_8F4
                t0 = ((int*)t2)[3] >> 1;
                t1 = ((int*)t2)[3] >> 1;
                t7 = 0x7C7C7C00;

                t0 &= t7;
                t1 &= t7;
                t0 += t1;
                t0 |= t1;

                ((int*)t8)[3] = t0;
                ((char*)t8)[18] = t0;

                v0 = ((int*)t2)[0];
                v1 = ((int*)t3)[0];
                t0 = ((int*)t2)[1];
                t1 = ((int*)t3)[1];

                v0 += v1;
                v0 >>= 1;
                t0 += t1;
                t0 >>= 1;

                ((int*)t8)[0] = v0;

                v0 = ((int*)t2)[2];
                v1 = ((int*)t3)[2];

                ((int*)t8)[1] = t0;

                v0 += v1;
                v0 >>= 1;

                ((char*)t2)[18] = 0;
                ((char*)t3)[18] = 0;
                t8 += 0x18;
            }
        }//loc_970

        dyn = &dynamics[0];
        a1 = (int)&scratchPad[192];
        v1 = 0xF;
        v0 = 0x40;

        //loc_984
        do
        {
            //at = dyn->on
            //t0 = dyn->used
            //t1 = dyn->y >> 7
            if (dyn->on && dyn->used)
            {
                //t0 = dyn->x >> 7
                //t2 = dyn->z
                ((int*)a1)[0] = dyn->x >> 7;
                ((int*)a1)[1] = dyn->y >> 7;
                ((int*)a1)[2] = dyn->z >> 7;

                ((int*)&dyn->on)[0] = ((((int*)&dyn->on)[0] >> 8) << 8) | (dyn->falloff >> 8);///@todo union

                a1 += 0x10;
                v1--;

                if (v1 == 0)
                    break;
            }

            //loc_9E0
            v0--;
            dyn++;

        } while (v0 != 0);

        //loc_9EC
        ((int*)a1)[3] = 0;
        db.polyptr = DrawMeshRL1(scratchPad, a0, &db);
    }
    //loc_1978 @ flat return
}

void DrawRoomletListAsmRL1()
{
    sub_158RL1(camera_underwater, &room[camera.pos.room_number]);
}