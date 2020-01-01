#include "LIBGPU.H"

#include "EMULATOR.H"
#include "EMULATOR_GLOBALS.H"
#include "EMULATOR_PRIVATE.H"


#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <LIBETC.H>

#include <stdio.h>
#include <stdlib.h>

DISPENV word_33BC;
DRAWENV activeDrawEnv;
DRAWENV byte_9CCA4;
int dword_3410 = 0;
char byte_3352 = 0;

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

int g_wireframeMode = 0;
int g_texturelessMode = 0;

struct VertexBufferSplitIndex
{
	unsigned short splitIndex;
	unsigned short numVertices;
	unsigned int textureId;
	unsigned char semiTrans;
	unsigned char abr;
	unsigned char primitiveType;
};

#define MAX_NUM_POLY_BUFFER_VERTICES (12040)//?FIXME
#define MAX_NUM_INDEX_BUFFERS (4096)
struct Vertex g_vertexBuffer[MAX_NUM_POLY_BUFFER_VERTICES];
unsigned char* g_IndexBuffer[MAX_NUM_INDEX_BUFFERS];
struct VertexBufferSplitIndex g_splitIndices[MAX_NUM_INDEX_BUFFERS];
int g_vertexIndex = 0;
int currentIndexBuffer = 0;
int g_numSplitIndices = 0;

//#define WIREFRAME_MODE

//Nasty hack, win32 is like original but due to memory differences
//Between Linux and Windows we must do this unfortunately.
#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
unsigned long terminator = -1;
#else
unsigned long* terminator;
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
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
	Emulator_CheckTextureIntersection(rect);
	glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
	glScissor(rect->x * RESOLUTION_SCALE, rect->y * RESOLUTION_SCALE, rect->w * RESOLUTION_SCALE, rect->h * RESOLUTION_SCALE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	Emulator_CheckTextureIntersection(rect);
	glScissor(rect->x * RESOLUTION_SCALE, rect->y * RESOLUTION_SCALE, rect->w * RESOLUTION_SCALE, rect->h * RESOLUTION_SCALE);
	Emulator_BindTexture(vramTexture);
	glTexSubImage2D(GL_TEXTURE_2D, 0, rect->x, rect->y, rect->w, rect->h, GL_RGBA, TEXTURE_FORMAT, &p[0]);

#if _DEBUG && 0
	Emulator_SaveVRAM("VRAM3.TGA", 0, 0, rect->w, rect->h, TRUE);
#endif

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
	//Emulator_CheckTextureIntersection(rect); Not yet need to construct actual rect
	glScissor(x * RESOLUTION_SCALE, y * RESOLUTION_SCALE, x + rect->w * RESOLUTION_SCALE, y + rect->h * RESOLUTION_SCALE);
	GLuint srcTexture;
	GLuint srcFrameBuffer;

	/* Read in src pixels for rect */
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);

	enum PixelBufferType
	{
		VRAM,
		NUM_PIXEL_BUFFER_OBJECTS
	};

	GLuint pixelBufferObjects[NUM_PIXEL_BUFFER_OBJECTS];

	//Generate PBO for faster transfer
	glGenBuffers(NUM_PIXEL_BUFFER_OBJECTS, &pixelBufferObjects[VRAM]);

	//Bind the VRAM PBO
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pixelBufferObjects[VRAM]);

	//Allocate PBO size for VRAM
	glBufferData(GL_PIXEL_PACK_BUFFER, (rect->w * rect->h) * sizeof(GLushort), NULL, GL_STREAM_READ);

	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, TEXTURE_FORMAT, NULL);

	glGenTextures(1, &srcTexture);
	Emulator_BindTexture(srcTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if defined(__ANDROID__)
	unsigned short* pixels = (unsigned short*)glMapBufferRange(GL_ARRAY_BUFFER, 0, (rect->w * rect->h) * sizeof(GLushort), GL_MAP_READ_BIT);
#else
	unsigned short* pixels = (unsigned short*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_WRITE);
#endif

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rect->w, rect->h, 0, GL_RGBA, TEXTURE_FORMAT, &pixels[0]);

	//Unmap VRAM pbo
	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);

	//Delete buffers
	glDeleteBuffers(NUM_PIXEL_BUFFER_OBJECTS, &pixelBufferObjects[VRAM]);

	/* Generate src Frame Buffer */
	glGenFramebuffers(1, &srcFrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, srcFrameBuffer);

	/* Bind src texture to src framebuffer */
#if defined(OGLES)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, srcTexture, 0);
#elif defined(OGL)
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, srcTexture, 0);
#endif

#if defined(OGL) || defined(OGLES)
	while (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		eprinterr("Frame buffer error: %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
	}
#endif
	glBindFramebuffer(GL_READ_FRAMEBUFFER, srcFrameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, vramFrameBuffer);
	glBlitFramebuffer(0, 0, rect->w, rect->h, x, y, x+rect->w, y + rect->h, GL_COLOR_BUFFER_BIT, GL_LINEAR);
#if _DEBUG
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
	Emulator_SaveVRAM("VRAM3.TGA", 0, 0, VRAM_WIDTH, VRAM_HEIGHT, TRUE);
#endif

	Emulator_DestroyTextures(1, &srcTexture);
	Emulator_DestroyFrameBuffer(&srcFrameBuffer);

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
	glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
#if defined(OGL)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_1_5_5_5_REV, &p[0]);
#elif defined(OGLES)
	glReadPixels(rect->x, rect->y, rect->w, rect->h, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, (unsigned short*)&p[0]);
#endif
	return 0;
}

u_long* ClearOTag(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
	//last is special terminator
	ot[n-1] = (unsigned long)&terminator;
#else
	//last is special terminator
	ot[n-1] = (unsigned long)terminator;
#endif

	for (int i = n - 2; i > -1; i--)
	{
		ot[i] = (unsigned long)&ot[i + 1];
		//Asset - Not 24-bit address, we need to crash now!
		assert((ot[i] & 0xFF000000) == 0);
	}

	return NULL;
}

u_long* ClearOTagR(u_long* ot, int n)
{
	//Nothing to do here.
	if (n == 0)
		return NULL;

#if defined(_WINDOWS) || defined(__EMSCRIPTEN__)
	//First is special terminator
	ot[0] = (unsigned long)&terminator;
#else
	//First is special terminator
	ot[0] = (unsigned long)terminator;
#endif

	for (int i = 1; i < n; i++)
	{
		ot[i] = (unsigned long)& ot[i - 1];
		//Asset - Not 24-bit address, we need to crash now!
		assert(ot[i] & 0xFF000000 == 0);
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

#if defined(OGLES) || defined(OGL)
GLuint vbo;
GLuint vao;
#endif

static unsigned short lastTpage = 0xFFFF;
static unsigned short lastClut = 0xFFFF;
static unsigned short lastSemiTrans = 0xFFFF;
static unsigned short lastPolyType = 0xFFFF;
static unsigned short numVertices = 0;

void DrawOTagEnv(u_long* p, DRAWENV* env)//
{
	/* Tell the shader to discard black */
	glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "bDiscardBlack"), TRUE);

	PutDrawEnv(env);

	if (env->dtd)
	{
		//glEnable(GL_DITHER);
	}
	else
	{
		//glDisable(GL_DITHER);
	}

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
		SDL_memset(&g_vertexBuffer[0], 0, MAX_NUM_POLY_BUFFER_VERTICES * sizeof(struct Vertex));
		SDL_memset(&g_splitIndices[0], 0, MAX_NUM_INDEX_BUFFERS * sizeof(struct VertexBufferSplitIndex));
		Emulator_Ortho2D(0.0f, VRAM_WIDTH, 0.0f, VRAM_HEIGHT, 0.0f, 1.0f);
		Emulator_Scalef(RESOLUTION_SCALE, RESOLUTION_SCALE, RESOLUTION_SCALE);
		glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
		glViewport(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, VRAM_WIDTH, VRAM_HEIGHT);
		glScissor(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, activeDrawEnv.clip.w * RESOLUTION_SCALE, activeDrawEnv.clip.h * RESOLUTION_SCALE);
		P_TAG* pTag = (P_TAG*)p;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
		GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
		GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
		glEnableVertexAttribArray(posAttrib);
		glEnableVertexAttribArray(colAttrib);
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), 0);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)12);
		glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)20);

		do
		{
			if (pTag->len > 0)
			{
				ParseLinkedPrimitiveList((uintptr_t)pTag, (uintptr_t)pTag + (uintptr_t)(pTag->len * 4) + 4);
			}
			pTag = (P_TAG*)pTag->addr;
#if __linux__ || __APPLE_
		}while ((unsigned long)pTag != 0xFFFFFF);
#else
		}while ((unsigned long)pTag != (unsigned long)&terminator);
#endif

		glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, &g_vertexBuffer[0], GL_STATIC_DRAW);

		for (int i = 0; i < g_numSplitIndices; i++)
		{
			if (g_texturelessMode)
			{
				Emulator_BindTexture(nullWhiteTexture);
			}
			else
			{
				assert(g_splitIndices[i].textureId < 1000);
				Emulator_BindTexture(g_splitIndices[i].textureId);
			}

			Emulator_SetBlendMode(g_splitIndices[i].abr, g_splitIndices[i].semiTrans);

#if !defined(OGLES)
			if (g_wireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
#endif

			glDrawArrays(g_splitIndices[i].primitiveType, g_splitIndices[i].splitIndex, g_splitIndices[i].numVertices);

#if !defined(OGLES)
			if (g_wireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
#endif
		}

		glDeleteBuffers(1, &vbo);
		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(colAttrib);
		glDisableVertexAttribArray(texAttrib);
		glDeleteVertexArrays(1, &vao);

		glViewport(0, 0, windowWidth, windowHeight);
	}

	Emulator_CheckTextureIntersection(&env->clip);

#if defined(PGXP)
	/* Reset the ztable */
	memset(&pgxp_polygons[0], 0, pgxp_polgon_table_index * sizeof(PGXPPolygon));

	/* Reset the ztable index of used */
	pgxp_polgon_table_index = 0;
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
				lastPolyType = GL_TRIANGLES;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

			g_vertexIndex += 3;
			numVertices += 3;

			currentAddress += sizeof(POLY_F3);
			break;
		}
		case 0x24:
		{
			POLY_FT3* poly = (POLY_FT3*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

			g_vertexIndex += 3;
			numVertices += 3;
			currentAddress += sizeof(POLY_FT3);
			break;
		}
		case 0x28:
		{
			POLY_F4* poly = (POLY_F4*)pTag;

			if (lastTpage == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
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
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0,	NULL, NULL, NULL, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;
			currentAddress += sizeof(POLY_F4);

			break;
		}
		case 0x2C:
		{
			POLY_FT4* poly = (POLY_FT4*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = poly->tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(POLY_FT4);
			break;
		}
		case 0x30:
		{
			POLY_G3* poly = (POLY_G3*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastSemiTrans = semi_transparent;
				lastTpage = activeDrawEnv.tpage;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastSemiTrans = semi_transparent;
				lastTpage = activeDrawEnv.tpage;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL, TRUE);

			g_vertexIndex += 3;
			numVertices += 3;

			currentAddress += sizeof(POLY_G3);
			break;
		}
		case 0x34:
		{
			POLY_GT3* poly = (POLY_GT3*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL, TRUE);

			g_vertexIndex += 3;
			numVertices += 3;

			currentAddress += sizeof(POLY_GT3);
			break;
		}
		case 0x38:
		{
			POLY_G4* poly = (POLY_G4*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
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
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(POLY_G4);
			break;
		}
		case 0x3C:
		{
			POLY_GT4* poly = (POLY_GT4*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = poly->tpage;
				lastClut = poly->clut;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = poly->tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(POLY_GT4);
			break;
		}
		case 0x40:
		{
			LINE_F2* poly = (LINE_F2*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_LINES)
			{
				lastPolyType = GL_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

			g_vertexIndex += 2;
			numVertices += 2;

			currentAddress += sizeof(LINE_F2);
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
					lastPolyType = GL_LINES;
					lastTpage = activeDrawEnv.tpage;
					lastSemiTrans = semi_transparent;
					g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
					g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
					g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
					g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
					g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				}
				else if (semi_transparent != lastSemiTrans || lastPolyType != GL_LINES || forceNewLine == TRUE)
				{
					lastPolyType = GL_LINES;
					lastTpage = activeDrawEnv.tpage;
					lastSemiTrans = semi_transparent;
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
					Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);
					g_vertexIndex += 2;
					numVertices += 2;
					forceNewLine = TRUE;
				}
				else
				{
					//Second line
					Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x1, &poly->x2, NULL, NULL);
					Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);
					g_vertexIndex += 2;
					numVertices += 2;
				}
			}

			currentAddress += sizeof(LINE_F3);
			break;
		}
		case 0x50:
		{
			LINE_G2* poly = (LINE_G2*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_LINES)
			{
				lastPolyType = GL_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, NULL, NULL, TRUE);

			g_vertexIndex += 2;
			numVertices += 2;

			currentAddress += sizeof(LINE_G2);
			break;
		}
		case 0x60:
		{
			TILE* poly = (TILE*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE);

			break;
		}
		case 0x64:
		{
			SPRT* poly = (SPRT*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, poly->w, poly->h);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT);
			break;
		}
		case 0x68:
		{
			TILE_1* poly = (TILE_1*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
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
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE_1);
			break;
		}
		case 0x70:
		{
			TILE_8* poly = (TILE_8*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
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
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE_8);
			break;
		}
		case 0x74:
		{
			SPRT_8* poly = (SPRT_8*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 8, 8);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, 8, 8);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT_8);
			break;
		}
		case 0x78:
		{
			TILE_16* poly = (TILE_16*)pTag;

			if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = nullWhiteTexture;
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
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
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(TILE_16);
			break;
		}
		case 0x7C:
		{
			SPRT_16* poly = (SPRT_16*)pTag;

			if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
			{
				lastPolyType = GL_TRIANGLES;
				lastClut = poly->clut;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
				numVertices = 0;
			}

			Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 16, 16);
			Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, 16, 16);
			Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

			//Make tri
			g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
			g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
			g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

			g_vertexIndex += 6;
			numVertices += 6;

			currentAddress += sizeof(SPRT_16);
			break;
		}
		case 0xE0:
		{
			switch (pTag->code)
			{
			case 0xE1:
			{
				unsigned short tpage = ((unsigned short*)pTag)[2];
				//if (tpage != 0)
				{
					activeDrawEnv.tpage = tpage;
				}
				currentAddress += 8;
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

void ParsePrimitive(P_TAG* pTag)
{
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
		break;
	}
	case 0x20:
	{
		POLY_F3* poly = (POLY_F3*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

		g_vertexIndex += 3;
		numVertices += 3;
		break;
	}
	case 0x24:
	{
		POLY_FT3* poly = (POLY_FT3*)pTag;

		if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = poly->tpage;
			lastClut = poly->clut;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = poly->tpage;
			lastClut = poly->clut;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

		g_vertexIndex += 3;
		numVertices += 3;
		break;
	}
	case 0x28:
	{
		POLY_F4* poly = (POLY_F4*)pTag;

		if (lastTpage == 0xFFFF || lastPolyType == 0xFFFF || lastSemiTrans == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastSemiTrans = semi_transparent;
			lastTpage = activeDrawEnv.tpage;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastSemiTrans = semi_transparent;
			lastTpage = activeDrawEnv.tpage;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x2C:
	{
		POLY_FT4* poly = (POLY_FT4*)pTag;

		if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = poly->tpage;
			lastClut = poly->clut;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = poly->tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x30:
	{
		POLY_G3* poly = (POLY_G3*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL, TRUE);

		g_vertexIndex += 3;
		numVertices += 3;
		break;
	}
	case 0x34:
	{
		POLY_GT3* poly = (POLY_GT3*)pTag;

		if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = poly->tpage;
			lastClut = poly->clut;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = poly->tpage;
			lastClut = poly->clut;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x2, NULL, -1, -1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u2, NULL, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r2, NULL, TRUE);

		g_vertexIndex += 3;
		numVertices += 3;
		break;
	}
	case 0x38:
	{
		POLY_G4* poly = (POLY_G4*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x3C:
	{
		POLY_GT4* poly = (POLY_GT4*)pTag;

		if (lastTpage == 0xFFFF || lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = poly->tpage;
			lastClut = poly->clut;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (poly->tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = poly->tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, &poly->x3, &poly->x2, -1, -1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, &poly->u1, &poly->u3, &poly->u2, -1, -1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, &poly->r3, &poly->r2, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x40:
	{
		LINE_F2* poly = (LINE_F2*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_LINES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (semi_transparent != lastSemiTrans || lastPolyType != GL_LINES)
		{
			lastPolyType = GL_LINES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

		g_vertexIndex += 2;
		numVertices += 2;
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
				lastPolyType = GL_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
				g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
				g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			}
			else if (semi_transparent != lastSemiTrans || lastPolyType != GL_LINES || forceNewLine == TRUE)
			{
				lastPolyType = GL_LINES;
				lastTpage = activeDrawEnv.tpage;
				lastSemiTrans = semi_transparent;
				g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
				g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
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
				Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);
				g_vertexIndex += 2;
				numVertices += 2;
				forceNewLine = TRUE;
			}
			else
			{
				//Second line
				Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x1, &poly->x2, NULL, NULL);
				Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);
				g_vertexIndex += 2;
				numVertices += 2;
			}
		}
		break;
	}
	case 0x50:
	{
		LINE_G2* poly = (LINE_G2*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_LINES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (semi_transparent != lastSemiTrans || lastPolyType != GL_LINES)
		{
			lastPolyType = GL_LINES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (lastTpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateLineArray(&g_vertexBuffer[g_vertexIndex], &poly->x0, &poly->x1, NULL, NULL);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r1, NULL, NULL, TRUE);

		g_vertexIndex += 2;
		numVertices += 2;
		break;
	}
	case 0x60:
	{
		TILE* poly = (TILE*)pTag;

		if (lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;

		break;
	}
	case 0x64:
	{
		SPRT* poly = (SPRT*)pTag;

		if (lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, poly->w, poly->h);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, poly->w, poly->h);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x68:
	{
		TILE_1* poly = (TILE_1*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 1, 1);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, 1, 1);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x70:
	{
		TILE_8* poly = (TILE_8*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 8, 8);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, 8, 8);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x74:
	{
		SPRT_8* poly = (SPRT_8*)pTag;

		if (lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 8, 8);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, 8, 8);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x78:
	{
		TILE_16* poly = (TILE_16*)pTag;

		if (lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 16, 16);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], NULL, NULL, NULL, NULL, 16, 16);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, &poly->r0, &poly->r0, &poly->r0, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0x7C:
	{
		SPRT_16* poly = (SPRT_16*)pTag;

		if (lastClut == 0xFFFF || lastSemiTrans == 0xFFFF || lastPolyType == 0xFFFF)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
		}
		else if (activeDrawEnv.tpage != lastTpage || poly->clut != lastClut || semi_transparent != lastSemiTrans || lastPolyType != GL_TRIANGLES)
		{
			lastPolyType = GL_TRIANGLES;
			lastClut = poly->clut;
			lastTpage = activeDrawEnv.tpage;
			lastSemiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].primitiveType = lastPolyType;
			g_splitIndices[g_numSplitIndices].textureId = Emulator_GenerateTpage(lastTpage, lastClut);
			g_splitIndices[g_numSplitIndices].semiTrans = semi_transparent;
			g_splitIndices[g_numSplitIndices].abr = (activeDrawEnv.tpage >> 5) & 3;
			g_splitIndices[g_numSplitIndices - 1].numVertices = numVertices;
			g_splitIndices[g_numSplitIndices++].splitIndex = g_vertexIndex;
			numVertices = 0;
		}

		Emulator_GenerateVertexArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->x0, NULL, NULL, NULL, 16, 16);
		Emulator_GenerateTexcoordArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->u0, NULL, NULL, NULL, 16, 16);
		Emulator_GenerateColourArrayQuad(&g_vertexBuffer[g_vertexIndex], &poly->r0, NULL, NULL, NULL, TRUE);

		//Make tri
		g_vertexBuffer[g_vertexIndex + 5] = g_vertexBuffer[g_vertexIndex + 3];
		g_vertexBuffer[g_vertexIndex + 3] = g_vertexBuffer[g_vertexIndex];
		g_vertexBuffer[g_vertexIndex + 4] = g_vertexBuffer[g_vertexIndex + 2];

		g_vertexIndex += 6;
		numVertices += 6;
		break;
	}
	case 0xE0:
	{
		switch (pTag->code)
		{
		case 0xE1:
		{
			unsigned short tpage = ((unsigned short*)pTag)[2];
			if (tpage != 0)
			{
				activeDrawEnv.tpage = tpage;
			}
			break;
		}
		default:
		{
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

	//Reset for vertex colours
#if !defined(OGLES) && !defined(OGL)
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
#endif

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

void DrawOTag(u_long* p)
{
	/* Tell the shader to discard black */
	glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "bDiscardBlack"), TRUE);

	if (activeDrawEnv.dtd)
	{
		//glEnable(GL_DITHER);
	}
	else
	{
		//glDisable(GL_DITHER);
	}

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

		SDL_memset(&g_vertexBuffer[0], 0, MAX_NUM_POLY_BUFFER_VERTICES * sizeof(struct Vertex));
		SDL_memset(&g_splitIndices[0], 0, MAX_NUM_INDEX_BUFFERS * sizeof(struct VertexBufferSplitIndex));

		Emulator_Ortho2D(0.0f, VRAM_WIDTH, 0.0f, VRAM_HEIGHT, 0.0f, 1.0f);
		Emulator_Scalef(RESOLUTION_SCALE, RESOLUTION_SCALE, RESOLUTION_SCALE);

		glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
		glViewport(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, VRAM_WIDTH, VRAM_HEIGHT);
		glScissor(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, activeDrawEnv.clip.w * RESOLUTION_SCALE, activeDrawEnv.clip.h * RESOLUTION_SCALE);
		P_TAG* pTag = (P_TAG*)p;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
		GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
		GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
		glEnableVertexAttribArray(posAttrib);
		glEnableVertexAttribArray(colAttrib);
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), 0);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)12);
		glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)20);

		do
		{
			if (pTag->len > 0)
			{
				ParseLinkedPrimitiveList((uintptr_t)pTag, (uintptr_t)pTag + (uintptr_t)(pTag->len * 4) + 4);
			}
			pTag = (P_TAG*)pTag->addr;
#if __linux__ || __APPLE_
		} while ((unsigned long)pTag != 0xFFFFFF);
#else
		} while ((unsigned long)pTag != (unsigned long)& terminator);
#endif

		glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, &g_vertexBuffer[0], GL_STATIC_DRAW);

		for (int i = 0; i < g_numSplitIndices; i++)
		{
			if (g_texturelessMode)
			{
				Emulator_BindTexture(nullWhiteTexture);
			}
			else
			{
				Emulator_BindTexture(g_splitIndices[i].textureId);
			}

			Emulator_SetBlendMode(g_splitIndices[i].abr, g_splitIndices[i].semiTrans);

#if !defined(OGLES)
			if (g_wireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
#endif
			glDrawArrays(g_splitIndices[i].primitiveType, g_splitIndices[i].splitIndex, g_splitIndices[i].numVertices);

#if !defined(OGLES)
			if (g_wireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
#endif
		}

		glDeleteBuffers(1, &vbo);
		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(colAttrib);
		glDisableVertexAttribArray(texAttrib);
		glDeleteVertexArrays(1, &vao);

		glViewport(0, 0, windowWidth, windowHeight);
	}

	Emulator_CheckTextureIntersection(&activeDrawEnv.clip);

#if defined(PGXP)
	/* Reset the ztable */
	memset(&pgxp_polygons[0], 0, pgxp_polgon_table_index * sizeof(PGXPPolygon));

	/* Reset the ztable index of used */
	pgxp_polgon_table_index = 0;
#endif
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

void DrawPrim(void* p)
{
	/* Tell the shader to discard black */
	glUniform1i(glGetUniformLocation(g_defaultShaderProgram, "bDiscardBlack"), TRUE);

	if (activeDrawEnv.dtd)
	{
		//glEnable(GL_DITHER);
	}
	else
	{
		//glDisable(GL_DITHER);
	}

	if (p != NULL)
	{
		lastClut = 0xFFFF;
		lastTpage = 0xFFFF;
		numVertices = 0;
		g_vertexIndex = 0;
		g_numSplitIndices = 0;
		SDL_memset(&g_vertexBuffer[0], 0, MAX_NUM_POLY_BUFFER_VERTICES * sizeof(struct Vertex));
		SDL_memset(&g_splitIndices[0], 0, MAX_NUM_INDEX_BUFFERS * sizeof(struct VertexBufferSplitIndex));
		Emulator_Ortho2D(0.0f, VRAM_WIDTH, 0.0f, VRAM_HEIGHT, 0.0f, 1.0f);
		Emulator_Scalef(RESOLUTION_SCALE, RESOLUTION_SCALE, RESOLUTION_SCALE);
		glBindFramebuffer(GL_FRAMEBUFFER, vramFrameBuffer);
		glViewport(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, VRAM_WIDTH, VRAM_HEIGHT);
		glScissor(activeDrawEnv.clip.x * RESOLUTION_SCALE, activeDrawEnv.clip.y * RESOLUTION_SCALE, activeDrawEnv.clip.w * RESOLUTION_SCALE, activeDrawEnv.clip.h * RESOLUTION_SCALE);
		P_TAG* pTag = (P_TAG*)p;

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		GLint posAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_position");
		GLint colAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_colour");
		GLint texAttrib = glGetAttribLocation(g_defaultShaderProgram, "a_texcoord");
		glEnableVertexAttribArray(posAttrib);
		glEnableVertexAttribArray(colAttrib);
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), 0);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)12);
		glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex), (GLvoid*)20);

		ParsePrimitive(pTag);

		glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * MAX_NUM_POLY_BUFFER_VERTICES, &g_vertexBuffer[0], GL_STATIC_DRAW);

		for (int i = 0; i < g_numSplitIndices; i++)
		{
			if (g_texturelessMode)
			{
				Emulator_BindTexture(nullWhiteTexture);
			}
			else
			{
				Emulator_BindTexture(g_splitIndices[i].textureId);
			}

			Emulator_SetBlendMode(g_splitIndices[i].abr, g_splitIndices[i].semiTrans);

#if !defined(OGLES)
			if (g_wireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
#endif
			glDrawArrays(g_splitIndices[i].primitiveType, g_splitIndices[i].splitIndex, g_splitIndices[i].numVertices);

#if !defined(OGLES)
			if (g_wireframeMode)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
#endif
		}

		glDeleteBuffers(1, &vbo);
		glDisableVertexAttribArray(posAttrib);
		glDisableVertexAttribArray(colAttrib);
		glDisableVertexAttribArray(texAttrib);
		glDeleteVertexArrays(1, &vao);

		glViewport(0, 0, windowWidth, windowHeight);
	}

	Emulator_CheckTextureIntersection(&activeDrawEnv.clip);

#if defined(PGXP)
	/* Reset the ztable */
	memset(&pgxp_polygons[0], 0, pgxp_polgon_table_index * sizeof(PGXPPolygon));

	/* Reset the ztable index of used */
	pgxp_polgon_table_index = 0;
#endif
}

void TermPrim(void* p)
{
	termPrim(p);
}