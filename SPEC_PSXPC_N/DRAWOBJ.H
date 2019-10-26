#ifndef DRAWOBJ_H
#define DRAWOBJ_H

extern void MakeMono(unsigned short* s, unsigned char* d);
extern void InitObjGTE();
extern void phd_PutPolygons(short* mesh, long clip);
extern void phd_PutPolygons_pickup(short* mesh, long shade);
extern void phd_PutPolygons_seethrough(short* mesh, unsigned char shade);

#endif