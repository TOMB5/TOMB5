#ifndef FMV_H
#define FMV_H

enum fmv
{
	FMV_COPYRIGHT_INTRO,
	FMV_GAME_INTRO
};

extern int S_PlayFMV(int sequence, int flag);
extern void FMV_InitialiseScreen();

#endif