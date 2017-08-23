#ifndef SETUP_H
#define SETUP_H

//FIXME: Not same as original
#define SETUP_MOD_FILE_SIZE (42012)
#include "SPECTYPES.H"
#include "OBJECTS.H"
extern char setupBuff[SETUP_MOD_FILE_SIZE];

//extern unsigned long *RelocPtr[128]; // offset 0x1EDDC0 original game

extern void RelocateLevel();
extern void sub_B3974(unsigned long numSounds, unsigned long soundWadSize, char* ptr);
extern void sub_B96EC(int unk);
extern void sub_B5328();
extern void sub_B84F0();
extern void sub_B7E04();

struct object
{
	char placeholder[64];
};

struct object_container
{
	struct object_info m_objects[NUMBER_OBJECTS];
	struct static_info m_static_objects[NUMBER_STATIC_OBJECTS];
	char m_SkinVertNums[480];
	char m_ScratchVertNums[480];
};

extern object_info* objects;
extern static_info* static_objects;
extern char* SkinVertNums;
extern char* ScratchVertNums;

#endif