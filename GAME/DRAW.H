#ifndef DRAW_H
#define DRAW_H

#include "ROOMLOAD.H"
#include "PSXTYPES.H"

struct ANIM_STRUCT
{
	short* frame_ptr;
	short interpolation;
	short current_anim_state;
	long velocity;
	long acceleration;
	long Xvelocity;
	long Xacceleration;
	short frame_base;
	short frame_end;
	short jump_anim_num;
	short jump_frame_num;
	short number_changes;
	short change_index;
	short number_commands;
	short command_index;
};

struct room_info
{
	short* data;
	short* door;
	struct FLOOR_INFO* floor;
	struct LIGHTINFO* light;
	struct MESH_INFO* mesh;
	long x;
	long y;
	long z;
	long minfloor;
	long maxceiling;
	short x_size;
	short y_size;
	struct CVECTOR ambient;
	short num_lights;
	short num_meshes;
	unsigned char ReverbType;
	unsigned char FlipNumber;
	char MeshEffect;
	char bound_active;
	short left;
	short right;
	short top;
	short bottom;
	short test_left;
	short test_right;
	short test_top;
	short test_bottom;
	short item_number;
	short fx_number;
	short flipped_room;
	unsigned short flags;
};

extern short LightningSFXDelay;
extern struct room_info* room;
extern short number_rooms;
extern long* bones;
extern struct ANIM_STRUCT* anims;
extern struct RANGE_STRUCT* ranges;
extern struct CHANGE_STRUCT* changes;
extern short* *meshes;
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

#endif