#ifndef SETUP_H
#define SETUP_H

#include "OBJECTS.H"
#include "SPECTYPES.H"

#if INTERNAL
#include <stdio.h>
#endif

#ifndef PSX_FILE_VERSION
	#define PSX_FILE_VERSION OBJECT_VERSION * -1
#endif

#if INTERNAL
extern void RelocateLevel(FILE* nHandle);
#else
extern void RelocateLevel();
#endif

extern long LoadSoundEffects(int numSounds, long* pSoundWadLengths, char* pSoundData, long soundWadSize);
extern void InitialiseObjects();
extern void sub_B5328();
extern void sub_B84F0();
extern void sub_B7E04();
extern void InitialiseClosedDoors();
extern void sub_B9DA8();
extern void sub_B4A40();
extern void InitialiseSqrtTable();
extern void InitialiseAnimatedTextures();
extern void InitialiseFootPrints();
extern void InitialiseBinocularGraphics();
extern void InitialiseTargetGraphics();
extern void InitialiseFlipMaps();
extern void sub_B4EE4(long keep_carried_items);
extern void sub_B9974();
extern void InitialiseCutseq();
extern void InitialiseResidentCut(unsigned char a0, unsigned char a1, unsigned char a2, unsigned char a3);
extern long sub_BA0DC(unsigned char a0);
extern long sub_BA148(unsigned char a0);

struct object_container
{
	struct object_info m_objects[NUMBER_OBJECTS];
	struct static_info m_static_objects[NUMBER_STATIC_OBJECTS];
	char m_SkinVertNums[480];
	char m_ScratchVertNums[480];
};

struct Level
{
	//0x0
	long objectVersion;
	long offsetSoundPointers;
	long offsetSoundData;
	long offsetTextiles;

	//0x10
	long offsetAnimFrames;
	long offsetRoomInfo;
	long offsetObjects;
	long unk06;

	//0x20
	long unk07;
	long numSoundEffects;
	long soundWadLength;
	unsigned short clutStartY;
	unsigned short numRooms;

	//0x30
	unsigned short laraDrawType : 3;
	unsigned short weatherType : 2;
	unsigned short roomDrawType : 2;
	unsigned short reserved : 9;

	unsigned short numLevelItems;
	unsigned short numAnimTextureRanges;//0x34
	unsigned short numAnimUVRanges;

	long roomInfoLength;
	long floorDataLength;

	//0x40
	long outsideRoomTableLength;
	long roomBoundingBoxesLength;
	unsigned short numBones;
	unsigned short numAnims;
	long meshBaseLength;

	//0x50
	long meshesLength;
	long animsLength;
	long changesLength;
	long rangesLength;

	//0x60
	long commandsLength;
	long bonesLength;
	long frameDataLength;
	long textureInfoLength;

	//0x70
	long spriteInfoLength;
	long mmTextureInfoLength;
	long animTextureRangesLength;
	long soundEffectInfoLength;

	//0x80
	long sampleInfoLength;
	long unk33;
	long unk34;
	long numBoxes;

	//0x90
	long boxesLength;
	long overlapsLength;
	long groundZoneLength;
	long groundZone2Length;

	//0xA0
	long groundZone3Length;
	long groundZone4Length;
	long groundZone5Length;
	long numFixedCameras;

	//0xB0
	unsigned short numSpotCameras;
	unsigned short unk45;
	long unk455;
	long unk46;
	unsigned short numAIObjects;
	unsigned short unk0003;

	//0xC0
	long numAiModuleRelocations;
	char aiModuleIndices[4];
	long unk50;
	long unk51;

	//0xD0
	long unk53;
	long unk54;
	long unk55;
	long unk56;

	//0xE0
	long unk57;
};

extern struct object_info* objects;
extern struct static_info* static_objects;
extern char* SkinVertNums;
extern char* ScratchVertNums;

#endif