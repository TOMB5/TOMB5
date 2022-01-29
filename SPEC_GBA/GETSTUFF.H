#ifndef GETSTUFF_H
#define GETSTUFF_H

extern struct FLOOR_INFO* GetFloor(long x, long y, long z, short* room_number);
extern short GetHeight(struct FLOOR_INFO* floor, int x, int y, int z);
extern short GetCeiling(struct FLOOR_INFO* floor, int x, int y, int z);
extern long CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, long x, long z);
extern long CheckNoColFloorTriangle(struct FLOOR_INFO* floor, long x, long z);
extern char GetDoor(struct FLOOR_INFO* floor);
extern int xLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);
extern int zLOS(struct GAME_VECTOR* start, struct GAME_VECTOR* target);
extern long CheckNoColCeilingTriangle(struct FLOOR_INFO* floor, long x, long z);

extern long DIVFP(long A, long B);
extern long MULFP(long A, long B);
extern int ObjectOnLOS2(struct GAME_VECTOR* start, struct GAME_VECTOR* target, struct PHD_VECTOR* a3, struct MESH_INFO** a4);
extern int DoRayBox(struct GAME_VECTOR* start, GAME_VECTOR* target, short* bounds, int* unknown, int x /*var_40*/, int y/*var_3C*/, int z/*var_38*/, short y_rot/*var_32*/, struct PHD_VECTOR* /*var_48*/a3, int /*var_44*/ item_num);
#endif