#include "GTEMATH.H"
#include "LOAD_LEV.H"
#include "3D_GEN.H"
#include "GPU.H"

unsigned int gte_leadingzerocount(unsigned int lzcs) {
    unsigned int lzcr = 0;

    if ((lzcs & 0x80000000) == 0)
        lzcs = ~lzcs;

    while ((lzcs & 0x80000000) != 0) {
        lzcr++;
        lzcs <<= 1;
    }

    return lzcr;
}

unsigned int gte_divide(unsigned short numerator, unsigned short denominator)
{
    if (numerator < (denominator * 2))
    {
        static unsigned char table[] =
        {
            0xff, 0xfd, 0xfb, 0xf9, 0xf7, 0xf5, 0xf3, 0xf1, 0xef, 0xee, 0xec, 0xea, 0xe8, 0xe6, 0xe4, 0xe3,
            0xe1, 0xdf, 0xdd, 0xdc, 0xda, 0xd8, 0xd6, 0xd5, 0xd3, 0xd1, 0xd0, 0xce, 0xcd, 0xcb, 0xc9, 0xc8,
            0xc6, 0xc5, 0xc3, 0xc1, 0xc0, 0xbe, 0xbd, 0xbb, 0xba, 0xb8, 0xb7, 0xb5, 0xb4, 0xb2, 0xb1, 0xb0,
            0xae, 0xad, 0xab, 0xaa, 0xa9, 0xa7, 0xa6, 0xa4, 0xa3, 0xa2, 0xa0, 0x9f, 0x9e, 0x9c, 0x9b, 0x9a,
            0x99, 0x97, 0x96, 0x95, 0x94, 0x92, 0x91, 0x90, 0x8f, 0x8d, 0x8c, 0x8b, 0x8a, 0x89, 0x87, 0x86,
            0x85, 0x84, 0x83, 0x82, 0x81, 0x7f, 0x7e, 0x7d, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x77, 0x75, 0x74,
            0x73, 0x72, 0x71, 0x70, 0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64,
            0x63, 0x62, 0x61, 0x60, 0x5f, 0x5e, 0x5d, 0x5d, 0x5c, 0x5b, 0x5a, 0x59, 0x58, 0x57, 0x56, 0x55,
            0x54, 0x53, 0x53, 0x52, 0x51, 0x50, 0x4f, 0x4e, 0x4d, 0x4d, 0x4c, 0x4b, 0x4a, 0x49, 0x48, 0x48,
            0x47, 0x46, 0x45, 0x44, 0x43, 0x43, 0x42, 0x41, 0x40, 0x3f, 0x3f, 0x3e, 0x3d, 0x3c, 0x3c, 0x3b,
            0x3a, 0x39, 0x39, 0x38, 0x37, 0x36, 0x36, 0x35, 0x34, 0x33, 0x33, 0x32, 0x31, 0x31, 0x30, 0x2f,
            0x2e, 0x2e, 0x2d, 0x2c, 0x2c, 0x2b, 0x2a, 0x2a, 0x29, 0x28, 0x28, 0x27, 0x26, 0x26, 0x25, 0x24,
            0x24, 0x23, 0x22, 0x22, 0x21, 0x20, 0x20, 0x1f, 0x1e, 0x1e, 0x1d, 0x1d, 0x1c, 0x1b, 0x1b, 0x1a,
            0x19, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x12, 0x12, 0x11, 0x11,
            0x10, 0x0f, 0x0f, 0x0e, 0x0e, 0x0d, 0x0d, 0x0c, 0x0c, 0x0b, 0x0a, 0x0a, 0x09, 0x09, 0x08, 0x08,
            0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00,
            0x00
        };

        int shift = gte_leadingzerocount(denominator) - 16;

        int r1 = (denominator << shift) & 0x7fff;
        int r2 = table[((r1 + 0x40) >> 7)] + 0x101;
        int r3 = ((0x80 - (r2 * (r1 + 0x8000))) >> 8) & 0x1ffff;
        unsigned int reciprocal = ((r2 * r3) + 0x80) >> 8;

        return (unsigned int)((((unsigned long long)reciprocal * (numerator << shift)) + 0x8000) >> 16);
    }

    return 0xffffffff;
}

VECTOR MVMVA(int x, int y, int z, char shift)//cop2 0x49E012
{
    VECTOR rv;
    rv.vx = (Matrix->m00 * x) + (Matrix->m01 * y) + (Matrix->m02 * z) >> shift;
    rv.vy = (Matrix->m10 * x) + (Matrix->m11 * y) + (Matrix->m12 * z) >> shift;
    rv.vz = (Matrix->m20 * x) + (Matrix->m21 * y) + (Matrix->m22 * z) >> shift;
    return rv;
}

VECTOR MVMVA(int x, int y, int z)//cop2 0x498012
{
    VECTOR rv;
    rv.vx = (Matrix->tx << 12) + (Matrix->m00 * x) + (Matrix->m01 * y) + (Matrix->m02 * z) >> 12;
    rv.vy = (Matrix->ty << 12) + (Matrix->m10 * x) + (Matrix->m11 * y) + (Matrix->m12 * z) >> 12;
    rv.vz = (Matrix->tz << 12) + (Matrix->m20 * x) + (Matrix->m21 * y) + (Matrix->m22 * z) >> 12;
    return rv;
}

SVECTOR MVMVA(SVECTOR* v0, int tx, int ty, int tz)//cop2 0x480012
{
    SVECTOR rv;
    rv.vx = (tx << 12) + (Matrix->m00 * v0->vx) + (Matrix->m01 * v0->vy) + (Matrix->m02 * v0->vz) >> 12;
    rv.vy = (ty << 12) + (Matrix->m10 * v0->vx) + (Matrix->m11 * v0->vy) + (Matrix->m12 * v0->vz) >> 12;
    rv.vz = (tz << 12) + (Matrix->m20 * v0->vx) + (Matrix->m21 * v0->vy) + (Matrix->m22 * v0->vz) >> 12;
    
    if (rv.vx > 0x7FFF)
    {
        rv.vx = 0x7FFF;
    }
    else if (rv.vx < -0x8000)
    {
        rv.vx = -0x8000;
    }

    if (rv.vy > 0x7FFF)
    {
        rv.vy = 0x7FFF;
    }
    else if (rv.vy < -0x8000)
    {
        rv.vy = -0x8000;
    }

    if (rv.vz > 0x7FFF)
    {
        rv.vz = 0x7FFF;
    }
    else if (rv.vz < -0x8000)
    {
        rv.vz = -0x8000;
    }
    
    return rv;
}

unsigned int SXY[3];
unsigned short SZ[4];

void RTPT(int tx, int ty, int tz, SVECTOR* v)//cop2 0x280030
{
    for (int i = 0; i < 3; i++)
    {
        int MAC1 = (tx << 12) + (Matrix->m00 * v[i].vx) + (Matrix->m01 * v[i].vy) + (Matrix->m02 * v[i].vz) >> 12;
        int MAC2 = (ty << 12) + (Matrix->m10 * v[i].vx) + (Matrix->m11 * v[i].vy) + (Matrix->m12 * v[i].vz) >> 12;
        int MAC3 = (tz << 12) + (Matrix->m20 * v[i].vx) + (Matrix->m21 * v[i].vy) + (Matrix->m22 * v[i].vz) >> 12;

        short IR1 = MAC1;
        if (MAC1 > 0x7FFF)
        {
            IR1 = 0x7FFF;
        }
        else if (MAC1 < -0x8000)
        {
            IR1 = -0x8000;
        }

        short IR2 = MAC2;
        if (MAC2 > 0x7FFF)
        {
            IR2 = 0x7FFF;
        }
        else if (MAC2 < -0x8000)
        {
            IR2 = -0x8000;
        }

        short IR3 = MAC3;
        if (MAC3 > 0x7FFF)
        {
            IR3 = 0x7FFF;
        }
        else if (MAC3 < -0x8000)
        {
            IR3 = -0x8000;
        }

        SZ[0] = SZ[1];
        SZ[1] = SZ[2];
        SZ[2] = SZ[3];

        if (MAC3 > 0xFFFF)
        {
            SZ[3] = 0xFFFF;
        }
        else if (MAC3 < 0x0000)
        {
            SZ[3] = 0x0000;
        }
        else
        {
            SZ[3] = MAC3;
        }

        int h_over_sz3 = gte_divide(phd_persp, SZ[3]);
        if (h_over_sz3 == 0xFFFFFFFF) 
        {
            h_over_sz3 =  0x1FFFF;
        }
        else if (h_over_sz3 > 0x1FFFF)
        {
            h_over_sz3 = 0x1FFFF;
        }

        int OFX = (SCREEN_WIDTH / 2) << 16;
        int OFY = (SCREEN_HEIGHT / 2) << 16;

        SXY[0] = SXY[1];
        SXY[1] = SXY[2];

        //Removed F();
        int SX = (OFX + (IR1 * h_over_sz3)) >> 16;
        if (SX > 0x3FF)
        {
            SX = 0x3FF;
        }
        else if (SX < -0x400)
        {
            SX = -0x400;
        }

        int SY = (OFY + (IR2 * h_over_sz3)) >> 16;
        if (SY > 0x3FF)
        {
            SY = 0x3FF;
        }
        else if (SY < -0x400)
        {
            SY = -0x400;
        }

        SXY[2] = (SX & 0xFFFF) | (SY << 16);
    }
}

void RTPS(int tx, int ty, int tz, SVECTOR* v)//0x180001
{
    int MAC1 = (tx << 12) + (Matrix->m00 * v->vx) + (Matrix->m01 * v->vy) + (Matrix->m02 * v->vz) >> 12;
    int MAC2 = (ty << 12) + (Matrix->m10 * v->vx) + (Matrix->m11 * v->vy) + (Matrix->m12 * v->vz) >> 12;
    int MAC3 = (tz << 12) + (Matrix->m20 * v->vx) + (Matrix->m21 * v->vy) + (Matrix->m22 * v->vz) >> 12;

    short IR1 = MAC1;
    if (MAC1 > 0x7FFF)
    {
        IR1 = 0x7FFF;
    }
    else if (MAC1 < -0x8000)
    {
        IR1 = -0x8000;
    }

    short IR2 = MAC2;
    if (MAC2 > 0x7FFF)
    {
        IR2 = 0x7FFF;
    }
    else if (MAC2 < -0x8000)
    {
        IR2 = -0x8000;
    }

    short IR3 = MAC3;
    if (MAC3 > 0x7FFF)
    {
        IR3 = 0x7FFF;
    }
    else if (MAC3 < -0x8000)
    {
        IR3 = -0x8000;
    }

    SZ[0] = SZ[1];
    SZ[1] = SZ[2];
    SZ[2] = SZ[3];

    if (MAC3 > 0xFFFF)
    {
        SZ[3] = 0xFFFF;
    }
    else if (MAC3 < 0x0000)
    {
        SZ[3] = 0x0000;
    }
    else
    {
        SZ[3] = MAC3;
    }

    int h_over_sz3 = gte_divide(phd_persp, SZ[3]);
    if (h_over_sz3 == 0xFFFFFFFF)
    {
        h_over_sz3 = 0x1FFFF;
    }
    else if (h_over_sz3 > 0x1FFFF)
    {
        h_over_sz3 = 0x1FFFF;
    }

    int OFX = (SCREEN_WIDTH / 2) << 16;
    int OFY = (SCREEN_HEIGHT / 2) << 16;

    SXY[0] = SXY[1];
    SXY[1] = SXY[2];

    //Removed F();
    int SX = (OFX + (IR1 * h_over_sz3)) >> 16;
    if (SX > 0x3FF)
    {
        SX = 0x3FF;
    }
    else if (SX < -0x400)
    {
        SX = -0x400;
    }

    int SY = (OFY + (IR2 * h_over_sz3)) >> 16;
    if (SY > 0x3FF)
    {
        SY = 0x3FF;
    }
    else if (SY < -0x400)
    {
        SY = -0x400;
    }

    SXY[2] = SX | (SY << 16);
}