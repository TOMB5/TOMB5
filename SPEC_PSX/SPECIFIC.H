#ifndef SPECIFIC_H
#define SPECIFIC_H

#include "SPECTYPES.H"


#define UNIMPLEMENTED() __asm("nop");

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
extern void S_Warn(const char* warning_message);

#endif