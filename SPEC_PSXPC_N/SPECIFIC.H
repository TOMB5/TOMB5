#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdio.h>
#include "STYPES.H"



#if PSXPC_VERSION
#define UNIMPLEMENTED() __asm("nop");
#else
#ifdef _MSC_VER
#define FUNCNAME __FUNCTION__
#else
#define FUNCNAME __func__
#endif

#define UNIMPLEMENTED() S_Warn("[%s] - Unimplemented!\n", FUNCNAME);
#endif

extern unsigned short AnimComp;
extern short AnimatingTexturesVOffset;
extern struct REQUESTER SettingsReq;
extern struct REQUESTER ConfigReq;
extern unsigned char SoundFXVolume;
extern unsigned short nAnimTextureRanges;
extern unsigned short* AnimTextureRanges;
extern unsigned short nAnimUVRanges;
extern int GtSFXEnabled;
extern short AnimatingTexturesV[16][8][3];

extern void S_control_screen_position();
extern long S_DumpScreen();
extern void S_ExitSystem(char* exit_message);
extern void DisplayConfig(int x, int y);
extern int DoPauseMenu();
extern void gInit();
extern short S_Death();
extern void DisplayStatsUCunt();
extern void S_CalculateLight(long x, long y, long z, short room, ITEM_LIGHT* light);
//extern void S_Warn(const char* warning_message);
#define BAR_W 133

#define S_DrawHealthBar(val) S_DrawGouraudBar(343, 18, BAR_W, (val * BAR_W) / 100, PoisonFlag ? &poisonBarColourSet : &healthBarColourSet)
#define S_DrawHealthBar2(val) S_DrawGouraudBar(189, 40, BAR_W, (val * BAR_W) / 100, PoisonFlag ? &poisonBarColourSet : &healthBarColourSet)
#define S_DrawAirBar(val) S_DrawGouraudBar(343, 32, BAR_W, (val * BAR_W) / 100, &airBarColourSet)
#define S_DrawDashBar(val) S_DrawGouraudBar(343, 46, BAR_W, (val * BAR_W) / 100, &dashBarColourSet)

#define S_Warn printf

#endif