#ifndef SPECIFIC_H
#define SPECIFIC_H

#include "PSXTYPES.H"

extern unsigned short AnimComp;
extern short AnimatingTexturesVOffset;
extern struct REQUESTER SettingsReq;
extern struct REQUESTER ConfigReq;
extern unsigned char SoundFXVolume;
extern unsigned short nAnimTextureRanges;
extern unsigned short *AnimTextureRanges;
extern unsigned short nAnimUVRanges;
extern int GtSFXEnabled;
extern short AnimatingTexturesV[16][8][3];

extern int S_SoundStopAllSamples();
extern void S_ExitSystem(char* exit_message);
extern void S_Warn(char* warning_message);
extern long S_DumpScreen();

#endif