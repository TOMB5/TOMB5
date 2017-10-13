#ifndef SPECIFIC_H
#define SPECIFIC_H

#include "SPECTYPES.H"

extern unsigned short AnimComp;
extern short AnimatingTexturesVOffset;
extern REQUESTER SettingsReq;
extern REQUESTER ConfigReq;
extern unsigned char SoundFXVolume;
extern unsigned short nAnimTextureRanges;
extern unsigned short *AnimTextureRanges;
extern unsigned short nAnimUVRanges;
extern int GtSFXEnabled;
extern short AnimatingTexturesV[16][8][3];

extern void DisplayStatsUCunt();
extern short S_Death();
extern void gInit();
extern int DoPauseMenu();
extern void DisplayConfig(int x, int y);
extern int S_SoundStopAllSamples();
extern void S_ExitSystem(char* exit_message);
extern void S_Warn(char* warning_message);
extern long S_DumpScreen();
extern void S_control_screen_position();
extern void S_AnimateTextures(long num_frames);
extern void S_SetupClutAdder(long unk);
extern void S_DrawFootPrints();
extern void S_DrawSparks();

#endif