#ifndef SETUP_H
#define SETUP_H

//FIXME: Not same as original
#define SETUP_MOD_FILE_SIZE (42012)
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

extern char objects[32360];

#endif