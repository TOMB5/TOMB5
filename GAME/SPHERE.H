#ifndef SPHERE_H
#define SPHERE_H

#include "SPECTYPES.H"

extern char GotLaraSpheres;
extern int NumLaraSpheres;
extern SPHERE LaraSpheres[15];
extern SPHERE Slist[34];

extern int TestCollision(ITEM_INFO* item, ITEM_INFO* laraitem);
extern int GetSpheres(ITEM_INFO* item, SPHERE* sptr, int worldspace);

#endif