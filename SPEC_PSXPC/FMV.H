#ifndef FMV_H
#define FMV_H

enum fmv
{
	FMV_COPYRIGHT_INTRO,
	FMV_GAME_INTRO
};

extern long S_PlayFMV(long sequence, long flag);
extern void FMV_InitialiseScreen();
#endif