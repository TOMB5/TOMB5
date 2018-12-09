#ifndef SPHERES_H
#define SPHERES_H

extern int GetSpheres(struct ITEM_INFO* item, struct SPHERE* sptr, int worldspace);
extern void GetJointAbsPosition(struct ITEM_INFO* item, struct PHD_VECTOR* pos, int joint);

#endif