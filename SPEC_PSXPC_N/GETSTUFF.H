#ifndef GETSTUFF_H
#define GETSTUFF_H

extern long CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, long x, long z);
extern long CheckNoColFloorTriangle(struct FLOOR_INFO* floor, long x, long z);
extern char GetDoor(struct FLOOR_INFO* floor);
extern int xLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);
extern int zLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);

extern long DIVFP(long A, long B);
extern long MULFP(long A, long B);

#endif