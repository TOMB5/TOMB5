#ifndef DRAWOBJ_H
#define DRAWOBJ_H

extern void MakeMono(unsigned short* s, unsigned char* d);
extern void InitObjGTE();
extern void phd_PutPolygons(short* mesh, short clip);
extern void phd_PutPolygons_pickup(short* meshp, long unk);
extern void phd_PutPolygons_seethrough(short* meshp, long unk);

#endif