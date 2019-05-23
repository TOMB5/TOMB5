#ifndef MOVIE_H
#define MOVIE_H

enum fmv
{
	FMV_COPYRIGHT_INTRO,
	FMV_GAME_INTRO,
	FMV_UNK02,
	FMV_UNK03,
	FMV_UNK04,
	FMV_UNK05,
	FMV_UNK06,
	FMV_NEXT_GENERATION_PREVIEW
};

extern int S_PlayFMV(int sequence, int flag);
extern void FMV_InitialiseVRAM();

#endif