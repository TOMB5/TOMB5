#ifndef COLLIDE_S_H
#define COLLIDE_S_H

extern void UpdateSky();
extern void UpdateLaraRoom(struct ITEM_INFO* item, int height);
extern void ItemNewRoom(short item_num, short room_number);
extern void GetCollisionInfo(struct COLL_INFO* coll, long xpos, long ypos, long zpos, short room_number, long objheight);

#endif