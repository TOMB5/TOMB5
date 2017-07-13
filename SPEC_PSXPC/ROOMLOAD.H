#ifndef ROOMLOAD_H
#define ROOMLOAD_H

#include "PSXTYPES.H"

struct FLOOR_INFO {
	unsigned short index; // size=0, offset=0
	unsigned short fx : 4; // offset=2.0
	unsigned short box : 11; // offset=2.4
	unsigned short stopper : 1; // offset=3.7
	unsigned char pit_room; // size=0, offset=4
	char floor; // size=0, offset=5
	unsigned char sky_room; // size=0, offset=6
	char ceiling; // size=0, offset=7
};

struct LIGHTINFO {
	long x; // size=0, offset=0
	long y; // size=0, offset=4
	long z; // size=0, offset=8
	unsigned char Type; // size=0, offset=12
	unsigned char r; // size=0, offset=13
	unsigned char g; // size=0, offset=14
	unsigned char b; // size=0, offset=15
	short nx; // size=0, offset=16
	short ny; // size=0, offset=18
	short nz; // size=0, offset=20
	short Intensity; // size=0, offset=22
	unsigned char Inner; // size=0, offset=24
	unsigned char Outer; // size=0, offset=25
	short FalloffScale; // size=0, offset=26
	short Length; // size=0, offset=28
	short Cutoff; // size=0, offset=30
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

void S_LoadLevelFile(int Name);

extern long AnimFilePos;
extern long AnimFileLen;
extern short* floor_data;
extern unsigned long* SetupPtr;
extern unsigned short ClutStartY;
extern struct SVECTOR* RoomBBoxes;
extern short* mesh_base;
extern struct PSXSPRITESTRUCT* GLOBAL_default_sprites_ptr;
extern struct PSXTEXTI* AnimatingWaterfalls[6];
extern int AnimatingWaterfallsV[6];
extern unsigned long envmap_data[6];
extern unsigned long RelocPtr[128];

#endif