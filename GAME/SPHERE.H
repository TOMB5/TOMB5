#ifndef SPHERE_H
#define SPHERE_H

#include "PSXTYPES.H"

extern char GotLaraSpheres;
extern int NumLaraSpheres;
extern struct SPHERE LaraSpheres[15];
extern struct SPHERE Slist[34];

extern int TestCollision(struct ITEM_INFO *item, struct ITEM_INFO *laraitem);

#endif