#ifndef SPECIFIC_H
#define SPECIFIC_H

#include <stdio.h>
#include "SPECTYPES.H"



#if PSXPC_VERSION
#define UNIMPLEMENTED() __asm("nop");
#else
#define XSTR(x) STR(x)
#define STR(x) #x
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
//extern void S_Warn(const char* warning_message);
#define S_Warn printf

#endif