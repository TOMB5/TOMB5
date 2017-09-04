#ifndef GAME_H
#define GAME_H

#include "WINMAIN.H"
#include "SPECTYPES.H"

extern struct object_info objects[];
extern struct static_info static_objects[];

extern void GameClose();
extern char GameInitialise();
extern unsigned __stdcall GameMain(void* data);

#endif