#ifndef PROFILE_H
#define PROFILE_H

#include "SPECTYPES.H"

extern char ProfileDraw;
extern int numprof;
extern struct COCKSUCK ProfileInfo[32];

extern void ProfileCallBack();
extern void ProfileInit(int scale);
extern void ProfileStartCount();
extern void ProfileReadCount();
extern void ProfileAddOT(unsigned long* ot);
extern void ProfileRGB(int r, int g, int b);
extern void ProfileAddDrawOT(unsigned long* ot);

#endif