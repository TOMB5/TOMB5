#ifndef SPECIFIC_H
#define SPECIFIC_H

#include "SPECTYPES.H"

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

extern short S_Death();
extern void S_Warn(char* warning_message);
extern void DisplayStatsUCunt();
extern void gInit();
extern int DoPauseMenu();
extern void DisplayConfig(int x, int y);

extern int S_SoundPlaySample(int nSample, unsigned short wVol, int nPitch, short wPan, unsigned int distance);
extern int S_SoundPlaySampleLooped(int nSample, unsigned short wVol, int nPitch, short wPan, unsigned int distance);
extern void S_SoundSetPanAndVolume(int handle, short wPan, unsigned short wVolume, unsigned int distance);
extern void S_SoundStopSample(int handle);
extern void S_SoundStopAllSamples();
extern void S_PauseAllSamples();
extern void S_UnpauseAllSamples();
extern int S_SoundSampleIsPlaying(int handle);
extern void S_SoundSetPitch(int handle, int nPitch);

extern void S_CDPlay(short track, int mode);
extern void S_CDStop();
extern void S_CDPause();
extern void S_CDRestart();

extern void	S_Pause();
extern void S_Wait(int nFrames);
extern void S_control_screen_position();
extern void S_ExitSystem(char* exit_message);
extern long S_DumpScreen();
extern void S_AnimateTextures(long num_frames);
extern void S_SetupClutAdder(long unk);
extern void S_DrawFootPrints();
extern void S_DrawSparks();


#endif