#ifndef GAME_H
#define GAME_H

#include "OBJECTS.H"

#ifdef __cplusplus
extern "C" {
#endif

extern struct object_info objects[NUMBER_OBJECTS];
extern struct static_info static_objects[NUMBER_STATIC_OBJECTS];

#ifdef __cplusplus
}
#endif

unsigned __stdcall GameMain(void* data);

#endif