#ifndef GAME_H
#define GAME_H

#include "SPECTYPES.H"
#include "OBJECTS.H"

extern struct object_info objects[NUMBER_OBJECTS];
extern struct static_info static_objects[NUMBER_STATIC_OBJECTS];

extern void GameClose();
extern char GameInitialise();
extern unsigned __stdcall GameMain(void* data);
extern void sub_4D3150();

#endif