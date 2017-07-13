#ifndef SETUP_H
#define SETUP_H

//FIXME: Not same as original
#define SETUP_MOD_FILE_SIZE (42012)
extern char setupBuff[SETUP_MOD_FILE_SIZE];

//extern unsigned long *RelocPtr[128]; // offset 0x1EDDC0 original game

void RelocateLevel();
void sub_B3974(unsigned long numSounds, unsigned long soundWadSize, char* ptr);
#endif