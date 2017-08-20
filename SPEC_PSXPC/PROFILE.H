#ifndef PROFILE_H
#define PROFILE_H

#include "PSXTYPES.H"

extern char ProfileDraw;
extern int numprof;
extern struct COCKSUCK ProfileInfo[32];

extern void ProfileAddDrawOT(unsigned long *ot);
extern void ProfileRGB(int r, int g, int b);
extern void ProfileAddOT(unsigned long *ot);
extern void ProfileReadCount();
extern void ProfileStartCount();
extern void ProfileInit(int scale);
extern void ProfileCallBack();

#endif