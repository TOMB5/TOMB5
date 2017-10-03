#ifndef FMV_H
#define FMV_H

enum fmv
{
	FMV_COPYRIGHT_INTRO,
	FMV_GAME_INTRO
};

extern long S_PlayFMV(long fmv_index, long a1);
extern void FMV_InitialiseScreen();
#endif