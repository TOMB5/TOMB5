#include "LIBGPU.H"

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"

#include <stdint.h>

#include <LIBETC.H>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

DISPENV word_33BC;
DRAWENV activeDrawEnv;
DRAWENV byte_9CCA4;
int dword_3410 = 0;
char byte_3352 = 0;

enum POLY_TYPE {
    POLY_TYPE_TRIANGLES,
    POLY_TYPE_LINES,
};

#if 0
char fontDebugTexture[] = 
{ 
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x10,0x11,0x00,0x00,0x11,0x11,0x01,0x00,0x10,0x00,0x00,0x00,0x10,0x01,0x00,
0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x10,0x00,0x00,0x10,0x10,0x00,
0x00,0x01,0x01,0x01,0x00,0x11,0x00,0x01,0x00,0x01,0x01,0x00,0x00,0x11,0x00,0x00,
0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x01,
0x00,0x01,0x01,0x00,0x00,0x00,0x10,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x11,0x00,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,
0x00,0x10,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x11,0x11,0x01,
0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,
0x00,0x00,0x01,0x01,0x00,0x10,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x11,0x00,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x11,0x01,
0x00,0x01,0x01,0x01,0x00,0x01,0x10,0x01,0x00,0x01,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x01,0x00,
0x00,0x10,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x00,0x01,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x00,
0x00,0x10,0x11,0x00,0x00,0x01,0x10,0x01,0x00,0x10,0x01,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x10,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x10,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x00,
0x00,0x00,0x10,0x00,0x00,0x11,0x11,0x01,0x00,0x00,0x11,0x00,0x00,0x11,0x11,0x01,
0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x11,0x00,
0x00,0x01,0x00,0x01,0x00,0x10,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x00,0x11,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x01,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x01,
0x00,0x01,0x10,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,
0x00,0x10,0x10,0x00,0x00,0x11,0x11,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x10,0x00,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x10,0x01,0x00,0x00,0x10,0x01,0x00,
0x00,0x00,0x01,0x00,0x00,0x11,0x11,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x00,
0x00,0x01,0x01,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x11,0x00,
0x00,0x01,0x10,0x00,0x00,0x00,0x00,0x01,0x00,0x11,0x11,0x00,0x00,0x00,0x10,0x00,
0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x01,0x00,0x10,0x01,0x00,0x00,0x10,0x01,0x00,
0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,
0x00,0x11,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,
0x00,0x11,0x11,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,
0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x00,0x00,0x11,0x11,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x01,
0x00,0x00,0x10,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,
0x00,0x01,0x00,0x01,0x00,0x00,0x10,0x00,0x00,0x10,0x01,0x00,0x00,0x10,0x01,0x00,
0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x00,0x00,0x11,0x11,0x01,0x00,0x10,0x11,0x00,
0x00,0x00,0x10,0x00,0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x00,0x00,0x00,0x01,0x00,
0x00,0x10,0x11,0x00,0x00,0x10,0x01,0x00,0x00,0x10,0x01,0x00,0x00,0x10,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x00,0x00,0x11,0x11,0x00,0x00,0x10,0x11,0x00,
0x00,0x11,0x11,0x00,0x00,0x11,0x11,0x01,0x00,0x11,0x11,0x01,0x00,0x10,0x11,0x00,
0x00,0x01,0x00,0x01,0x00,0x10,0x11,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x10,0x11,0x00,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x10,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x10,0x00,
0x00,0x01,0x00,0x00,0x00,0x11,0x10,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x11,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,
0x00,0x10,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01,0x00,
0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x11,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x01,0x01,0x00,0x11,0x11,0x01,0x00,0x11,0x11,0x00,0x00,0x01,0x00,0x00,
0x00,0x10,0x00,0x01,0x00,0x11,0x11,0x00,0x00,0x11,0x11,0x00,0x00,0x01,0x00,0x00,
0x00,0x11,0x11,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x11,0x00,0x00,
0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x01,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x11,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,
0x00,0x10,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x10,0x01,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x01,0x00,
0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x10,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x10,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x10,0x00,
0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x10,0x11,0x00,0x00,0x01,0x00,0x01,0x00,0x11,0x11,0x00,0x00,0x10,0x11,0x00,
0x00,0x11,0x11,0x00,0x00,0x11,0x11,0x01,0x00,0x01,0x00,0x00,0x00,0x10,0x11,0x00,
0x00,0x01,0x00,0x01,0x00,0x10,0x11,0x00,0x00,0x10,0x11,0x00,0x00,0x01,0x00,0x01,
0x00,0x11,0x11,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x10,0x11,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x11,0x11,0x00,0x00,0x10,0x11,0x00,0x00,0x11,0x11,0x00,0x00,0x10,0x11,0x00,
0x00,0x11,0x11,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x11,0x01,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,
0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x00,
0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,
0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x10,0x10,0x00,0x00,0x10,0x10,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,
0x00,0x10,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x11,0x11,0x00,0x00,0x01,0x00,0x01,0x00,0x11,0x11,0x00,0x00,0x10,0x11,0x00,
0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,
0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x11,0x11,0x01,0x00,0x00,0x01,0x00,
0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x01,
0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x01,0x01,0x01,
0x00,0x10,0x10,0x00,0x00,0x00,0x01,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x01,0x00,
0x00,0x00,0x10,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x00,0x00,0x00,0x01,0x10,0x00,0x00,0x01,0x10,0x00,0x00,0x01,0x00,0x01,
0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x11,0x10,0x01,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x00,0x00,0x00,0x10,0x01,0x01,0x00,0x01,0x00,0x01,0x00,0x10,0x11,0x00,
0x00,0x00,0x01,0x00,0x00,0x10,0x11,0x00,0x00,0x00,0x01,0x00,0x00,0x01,0x00,0x01,
0x00,0x01,0x00,0x01,0x00,0x00,0x01,0x00,0x00,0x11,0x11,0x01,0x00,0x00,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11,0x01,
0x00,0x00,0x00,0x00,0x00,0x11,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
#endif
//unk_E88
unsigned char fontDebugClut[] = { 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

int g_swapInterval = 0;
int g_wireframeMode = 0;
int g_texturelessMode = 0;

struct VertexBufferSplitIndex
{
	TextureID      textureId;
	unsigned short splitIndex;
	unsigned short numVertices;
	unsigned short semiTrans;
	unsigned short abr;
	unsigned short primitiveType;
	unsigned short page;
	unsigned short clut;
};

//#define DEBUG_POLY_COUNT

#if defined(DEBUG_POLY_COUNT)
static int polygon_count = 0;
#endif

struct Vertex g_vertexBuffer[MAX_NUM_POLY_BUFFER_VERTICES];
struct VertexBufferSplitIndex g_splitIndices[MAX_NUM_INDEX_BUFFERS];
int g_vertexIndex = 0;
int currentIndexBuffer = 0;
int g_numSplitIndices = 0;

//#define WIREFRAME_MODE

#if defined(USE_32_BIT_ADDR)
unsigned long terminator[2] = { -1, 0 };
#else
unsigned long terminator = -1;
#endif

void(*drawsync_callback)(void) = NULL;

void* off_3348[]=
{
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

int ClearImage(RECT16* rect, u_char r, u_char g, u_char b)
{
	Emulator_Clear(rect->x, rect->y, rect->w, rect->h, r, g, b);
	return 0;
}

int DrawSync(int mode)
{
	if (drawsync_callback != NULL)
	{
		drawsync_callback();
	}

	return 0;
}

int LoadImagePSX(RECT16* rect, u_long* p)
{
	Emulator_CopyVRAM((unsigned short*)p, 0, 0, rect->w, rect->h, rect->x, rect->y);
	return 0;
}

int MargePrim(void* p0, void* p1)
{
	int v0 = ((unsigned char*)p0)[3];
	int v1 = ((unsigned char*)p1)[3];

	v0 += v1;
	v1 = v0 + 1;

	if (v1 < 0x11)
	{
		((char*)p0)[3] = v1;
		((int*)p1)[0] = 0;
		return 0;
	}

	return -1;
}

int MoveImage(RECT16* rect, int x, int y)
{
	Emulator_CopyVRAM(NULL, x, y, rect->w, rect->h, rect->x, rect->y);
	return 0;
}

int ResetGraph(int mode)
{
	UNIMPLEMENTED();
	return 0;
}

int SetGraphDebug(int level)
{
	UNIMPLEMENTED();
	return 0;
}

int StoreImage(RECT16* rect, u_long * p)
{
#if defined(OGL) || defined(OGLES)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, &p[0]);
#elif defined(D3D9)
	assert(FALSE);//Unimplemented
#elif defined(VK)
	assert(FALSE);//Unimplemented
#endif
	return 0;
}

u_long* ClearOTag(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

	//last is special terminator
	ot[n - 1] = (unsigned long)&terminator;

	for (int i = n - 2; i > -1; i--)
	{
		ot[i] = (unsigned long)&ot[i + 1];
	}

	return NULL;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

	//First is special terminator
	setaddr(ot, &terminator);
	setlen(ot, 0);

#if defined(USE_32_BIT_ADDR)
	for (int i = 2; i < n * 2; i+=2)
#else
	for (int i = 1; i < n ; i++)
#endif
	{
#if defined(USE_32_BIT_ADDR)
		setaddr(&ot[i], (unsigned long)&ot[i - 2]);
#else
		setaddr(&ot[i], (unsigned long)&ot[i - 1]);
#endif
		setlen(&ot[i], 0);
	}

	return NULL;
}

void SetDispMask(int mask)
{
	UNIMPLEMENTED();
}

int FntPrint(char* text, ...)
{
	UNIMPLEMENTED();
	return 0;
}

DISPENV* GetDispEnv(DISPENV* env)//(F)
{
	memcpy(env, &word_33BC, sizeof(DISPENV));
	return env;
}

DISPENV* PutDispEnv(DISPENV* env)//To Finish
{
	memcpy((char*)&word_33BC, env, sizeof(DISPENV));
	return 0;
}

DISPENV* SetDefDispEnv(DISPENV* env, int x, int y, int w, int h)//(F)
{
	env->disp.x = x;
	env->disp.y = y;
	env->disp.w = w;
	env->screen.x = 0;
	env->screen.y = 0;
	env->screen.w = 0;
	env->screen.h = 0;
	env->isrgb24 = 0;
	env->isinter = 0;
	env->pad1 = 0;
	env->pad0 = 0;
	env->disp.h = h;
	return 0;
}

DRAWENV* GetDrawEnv(DRAWENV* env)
{
	UNIMPLEMENTED();
	return NULL;
}

DRAWENV* PutDrawEnv(DRAWENV* env)//Guessed
{
	memcpy((char*)&activeDrawEnv, env, sizeof(DRAWENV));
	return 0;
}

DRAWENV* SetDefDrawEnv(DRAWENV* env, int x, int y, int w, int h)//(F)
{
	env->clip.x = x;
	env->clip.y = y;
	env->clip.w = w;
	env->tw.x = 0;
	env->tw.y = 0;
	env->tw.w = 0;
	env->tw.h = 0;
	env->r0 = 0;
	env->g0 = 0;
	env->b0 = 0;
	env->dtd = 1;
	env->clip.h = h;

	if (GetVideoMode() == 0)
	{
		env->dfe = h < 0x121 ? 1 : 0;
	}
	else
	{
		env->dfe = h < 0x101 ? 1 : 0;
	}

	env->ofs[0] = x;
	env->ofs[1] = y;

	env->tpage = 10;
	env->isbg = 0;

	return env;
}

void SetDrawEnv(DR_ENV* dr_env, DRAWENV* env)
{

}

void SetDrawMode(DR_MODE* p, int dfe, int dtd, int tpage, RECT16* tw)
{
	setDrawMode(p, dfe, dtd, tpage, tw);
}

u_long DrawSyncCallback(void(*func)(void))
{
	drawsync_callback = func;
	return 0;
}

u_short GetClut(int x, int y)
{
	return getClut(x, y);
}

static unsigned short lastTpage = 0xFFFF;
static unsigned short lastClut = 0xFFFF;
static unsigned short lastSemiTrans = 0xFFFF;
static unsigned short lastPolyType = 0xFFFF;
static unsigned short numVertices = 0;

void DrawSplit(const VertexBufferSplitIndex &split)
{
	Emulator_SetTexture(g_texturelessMode ? nullWhiteTexture : vramTexture, split.page, split.clut);
	Emulator_SetBlendMode(split.abr, split.semiTrans);

	if (split.primitiveType == POLY_TYPE_TRIANGLES) {
		Emulator_DrawTriangles(split.splitIndex, split.numVertices / 3);
	} else {
		Emulator_DrawLines(split.splitIndex, split.numVertices / 2);
	}
}

void DrawOTagEnv(u_long* p, DRAWENV* env)
{
#if defined(DEBUG_POLY_COUNT)
	polygon_count = 0;
#endif

	PutDrawEnv(env);

	if (activeDrawEnv.isbg)
	{
		ClearImage(&activeDrawEnv.clip, activeDrawEnv.r0, activeDrawEnv.g0, activeDrawEnv.b0);
	}

	if (p != NULL)
	{
		lastClut = 0xFFFF;
		lastTpage = 0xFFFF;
		lastSemiTrans = 0xFFFF;
		lastPolyType = 0xFFFF;
		numVertices = 0;
		g_vertexIndex = 0;
		g_numSplitIndices = 0;

		P_TAG* pTag = (P_TAG*)p;

		do
		{
			if (pTag->len > 0)
			{
				ParseLinkedPrimitiveList((uintptr_t)pTag, (uintptr_t)pTag + (uintptr_t)(pTag->len * 4) + 4 + LEN_OFFSET);
			}
			pTag = (P_TAG*)pTag->addr;
		}while ((uintptr_t)pTag != (uintptr_t)&terminator);

		Emulator_UpdateVertexBuffer(g_vertexBuffer, g_vertexIndex);

		for (int i = 0; i < g_numSplitIndices; i++)
		{
			DrawSplit(g_splitIndices[i]);
		}
	}

#if defined(PGXP)
	/* Reset the ztable */
	memset(&pgxp_vertex_buffer[0], 0, pgxp_vertex_index * sizeof(PGXPVertex));

	/* Reset the ztable index of */
	pgxp_vertex_index = 0;
#endif
}

void ParseLinkedPrimitiveList(unsigned int packetStart, unsigned int packetEnd)//@TODO sync with ParsePrimitive
{
	unsigned int currentAddress = packetStart;

	while (currentAddress != packetEnd)
	{
		P_TAG* pTag = (P_TAG*)currentAddress;

		int textured = (pTag->code & 0x4) != 0;

		int blend_mode = 0;

		if (textured)
		{
			if ((pTag->code & 0x1) != 0)
			{
				blend_mode = 2;
			}
			else
			{
				blend_mode = 1;
			}
		}
		else
		{
			blend_mode = 0;
		}

		int semi_transparent = (pTag->code & 2) != 0;

		switch (pTag->code & ~3)
		{
		case 0x0:
		{
			currentAddress += 4;
			break;
		}
		case 0x20:
		{
			POLY_F3* poly = (POLY_F3*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);

			g_vertexIndex += 3;
			numVertices += 3;

			currentAddress += sizeof(POLY_F3);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x24:
		{
			POLY_FT3* poly = (POLY_FT3*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);

			g_vertexIndex += 3;
			numVertices += 3;
			currentAddress += sizeof(POLY_FT3);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x28:
		{
			POLY_F4* poly = (POLY_F4*)pTag;

			if (lastTpage == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0,	NULL, NULL, NULL);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;
			currentAddress += sizeof(POLY_F4);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x2C:
		{
			POLY_FT4* poly = (POLY_FT4*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = poly->tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(POLY_FT4);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x30:
		{
			POLY_G3* poly = (POLY_G3*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastSemiTrans = semi_transparent;
				lastTpage = activeDrawEnv.tpage;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastSemiTrans = semi_transparent;
				lastTpage = activeDrawEnv.tpage;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL);

			g_vertexIndex += 3;
			numVertices += 3;

			currentAddress += sizeof(POLY_G3);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x34:
		{
			POLY_GT3* poly = (POLY_GT3*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u1, &poly->u1, &poly->u2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL);

			g_vertexIndex += 3;
			numVertices += 3;

			currentAddress += sizeof(POLY_GT3);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x38:
		{
			POLY_G4* poly = (POLY_G4*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(POLY_G4);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x3C:
		{
			POLY_GT4* poly = (POLY_GT4*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = poly->tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(POLY_GT4);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x40:
		{
			LINE_F2* poly = (LINE_F2*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_LINES)
			{
				lastPolyType = POLY_TYPE_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);

			g_vertexIndex += 2;
			numVertices += 2;

			currentAddress += sizeof(LINE_F2);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x48:
		{
			LINE_F3* poly = (LINE_F3*)pTag;
			int forceNewLine = FALSE;

			for (int i = 0; i < 2; i++)
			{
				if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
				{
					lastPolyType = POLY_TYPE_LINES;
					lastTpage = activeDrawEnv.tpage;
					lastSemiTrans = semi_transparent;
					g_splitIndices[g_numSplitIndices].page = 0;
					g_splitIndices[g_numSplitIndices].clut = 0;
					g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
					g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
					g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
					g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
					g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				}
				else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_LINES || forceNewLine == TRUE)
				{
					lastPolyType = POLY_TYPE_LINES;
					lastTpage = activeDrawEnv.tpage;
					lastSemiTrans = semi_transparent;
					g_splitIndices[g_numSplitIndices].page = 0;
					g_splitIndices[g_numSplitIndices].clut = 0;
					g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
					g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
					g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
					g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
					g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
					g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
					numVertices = 0;
				}

				if (i == 0)
				{
					//First line
					Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
					Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);
					g_vertexIndex += 2;
					numVertices += 2;
					forceNewLine = TRUE;
				}
				else
				{
					//Second line
					Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x1, &poly->x2, NULL, NULL);
					Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);
					g_vertexIndex += 2;
					numVertices += 2;
				}
#if defined(DEBUG_POLY_COUNT)
				polygon_count++;
#endif
			}

			currentAddress += sizeof(LINE_F3);
			break;
		}
		case 0x50:
		{
			LINE_G2* poly = (LINE_G2*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_LINES)
			{
				lastPolyType = POLY_TYPE_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, NULL, NULL);

			g_vertexIndex += 2;
			numVertices += 2;

			currentAddress += sizeof(LINE_G2);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x60:
		{
			TILE* poly = (TILE*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif

			break;
		}
		case 0x64:
		{
			SPRT* poly = (SPRT*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x68:
		{
			TILE_1* poly = (TILE_1*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 1, 1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, 1, 1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE_1);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x70:
		{
			TILE_8* poly = (TILE_8*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 8, 8);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, 8, 8);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE_8);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x74:
		{
			SPRT_8* poly = (SPRT_8*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 8, 8);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, 8, 8);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT_8);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x78:
		{
			TILE_16* poly = (TILE_16*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = 0;
				g_splitIndices[g_numSplitIndices].clut = 0;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 16, 16);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, 16, 16);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE_16);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0x7C:
		{
			SPRT_16* poly = (SPRT_16*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != POLY_TYPE_TRIANGLES)
			{
				lastPolyType = POLY_TYPE_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].page = lastTpage;
				g_splitIndices[g_numSplitIndices].clut = lastClut;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = vramTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 16, 16);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, 16, 16);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT_16);
#if defined(DEBUG_POLY_COUNT)
			polygon_count++;
#endif
			break;
		}
		case 0xE0:
		{
			switch (pTag->code)
			{
			case 0xE1:
			{
#if defined(USE_32_BIT_ADDR)
				unsigned short tpage = ((unsigned short*)pTag)[4];
#else
				unsigned short tpage = ((unsigned short*)pTag)[2];
#endif
				//if (tpage != 0)
				{
					activeDrawEnv.tpage = tpage;
				}

				currentAddress += sizeof(DR_TPAGE);
#if defined(DEBUG_POLY_COUNT)
				polygon_count++;
#endif

				break;
			}
			default:
			{
				eprinterr("Primitive type error");
				assert(FALSE);
				break;
			}
			}
			break;
		}
		default:
			//Unhandled poly type
			eprinterr("Unhandled primitive type: %02X type2:%02X\n", pTag->code, pTag->code & ~3);
			break;
		}
	}

	g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
}

void SetSprt16(SPRT_16* p)
{
	setSprt16(p);
}

void SetSprt8(SPRT_8* p)
{
	setSprt8(p);
}

void SetTile(TILE* p)
{
	setTile(p);
}

void SetPolyGT4(POLY_GT4* p)
{
	setPolyGT4(p);
}

void SetSemiTrans(void* p, int abe)
{
	setSemiTrans(p, abe);
}

void SetShadeTex(void* p, int tge)
{
	setShadeTex(p, tge);
}

void SetSprt(SPRT* p)
{
	UNIMPLEMENTED();
}

void SetDumpFnt(int id)
{
	UNIMPLEMENTED();
}

void SetLineF3(LINE_F3* p)
{
	setLineF3(p);
}

void FntLoad(int tx, int ty)
{
	UNIMPLEMENTED();
}

void AddPrim(void* ot, void* p)
{
	addPrim(ot, p);
}

void AddPrims(void* ot, void* p0, void* p1)
{
	addPrims(ot, p0, p1);
}

void CatPrim(void* p0, void* p1)
{
	catPrim(p0, p1);
}

u_short LoadTPage(u_long* pix, int tp, int abr, int x, int y, int w, int h)
{
	RECT16 imageArea;
	imageArea.x = x;
	imageArea.y = y;
	imageArea.h = h;

	enum
	{
		TP_4BIT,
		TP_8BIT,
		TP_16BIT
	};

	switch (tp)
	{
	case TP_4BIT:
	{
		//loc_278
		if (w >= 0)
		{
			imageArea.w = w >> 2;
		}
		else
		{
			imageArea.w = (w + 3) >> 2;
		}
		break;
	}
	case TP_8BIT:
	{
		//loc_290
		imageArea.w = (w + (w >> 31)) >> 1;
		break;
	}
	case TP_16BIT:
	{
		//loc_2A4
		imageArea.w = w;
		break;
	}
	}

	//loc_2AC
	LoadImagePSX(&imageArea, pix);
	return GetTPage(tp, abr, x, y) & 0xFFFF;
}

u_short GetTPage(int tp, int abr, int x, int y)
{
	return getTPage(tp, abr, x, y);
}

u_short LoadClut(u_long* clut, int x, int y)
{
	RECT16 rect;//&var_18
	setRECT16(&rect, x, y, 256, 1);
	LoadImagePSX(&rect, clut);
	return GetClut(x, y) & 0xFFFF;
}

u_short LoadClut2(u_long* clut, int x, int y)
{
	RECT16 drawArea;
	drawArea.x = x;
	drawArea.y = y;
	drawArea.w = 16;
	drawArea.h = 1;
	LoadImagePSX(&drawArea, clut);
	return getClut(x, y);
}

u_long* KanjiFntFlush(int id)
{
	UNIMPLEMENTED();
	return 0;
}

u_long* FntFlush(int id)
{
	UNIMPLEMENTED();
	return 0;
}

int KanjiFntOpen(int x, int y, int w, int h, int dx, int dy, int cx, int cy, int isbg, int n)
{
	UNIMPLEMENTED();
	return 0;
}

int FntOpen(int x, int y, int w, int h, int isbg, int n)
{
	UNIMPLEMENTED();
	return 0;
}

void SetPolyF4(POLY_F4* p)
{
	setPolyF4(p);
}

void SetPolyFT4(POLY_FT4* p)
{
	setPolyFT4(p);
}

void SetPolyG4(POLY_G4* p)
{
	setPolyG4(p);
}

void TermPrim(void* p)
{
	termPrim(p);
}