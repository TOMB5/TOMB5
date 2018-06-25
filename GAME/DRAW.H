#ifndef DRAW_H
#define DRAW_H

#include "SPECTYPES.H"

extern short LightningSFXDelay;
extern struct room_info* room;
extern short number_rooms;
extern long* bones;
extern struct ANIM_STRUCT* anims;
extern struct RANGE_STRUCT* ranges;
extern struct CHANGE_STRUCT* changes;
extern short** meshes;
extern short* commands;
extern short* frames;
extern short* binoculars_mesh_ptr;
extern short* target_mesh_ptr;
extern short SkyPos;
extern short SkyPos2;
extern int number_draw_rooms;
extern short draw_rooms[100];
extern int number_dynamics;
extern long camera_underwater;
extern long gfMirrorZPlane;
extern unsigned short LightningRGBs[3];
extern unsigned short LightningRGB[3];
extern short LightningCount;
extern short LightningRand;
extern short dLightningRand;
extern short interpolated_bounds[6];
extern short* GLOBAL_gunflash_meshptr;
extern int CurrentRoom;
extern unsigned char CreditsDone;
extern short GlobalRoomNumber;
extern long outside;
extern long outside_left;
extern long outside_right;
extern long outside_top;
extern long outside_bottom;
extern short HorizonClip;
extern struct door_vbuf vbufdoor[4];
extern short Sback_gun;
extern short* SRhandPtr;
extern short* SLhandPtr;

extern long GetFrames(struct ITEM_INFO* item, short* frames[], int* rate);
extern void UpdateSkyLightning();
extern void DrawSkyMesh(short* mesh);
extern void DrawMoon();
extern void DrawGunflashes();
extern short* GetBestFrame(struct ITEM_INFO* item);



#endif