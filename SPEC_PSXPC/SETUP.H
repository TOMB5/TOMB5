#ifndef SETUP_H
#define SETUP_H

#include "OBJECTS.H"
#include "SPECTYPES.H"

#if DEBUG_VERSION || !DISC_VERSION
	#include <stdio.h>
#endif

#ifndef PSX_FILE_VERSION
	#define PSX_FILE_VERSION OBJECT_VERSION * -1
#endif

#if DISC_VERSION
extern void RelocateLevel();
#else
extern void RelocateLevel(FILE* nHandle);
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
	int objectVersion;
	int offsetSoundPointers;
	int offsetSoundData;
	int offsetTextiles;

	//0x10
	int offsetAnimFrames;
	int offsetRoomInfo;
	int offsetObjects;
	int unk06;

	//0x20
	int unk07;
	int numSoundEffects;
	int soundWadLength;
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

	int roomInfoLength;
	int floorDataLength;

	//0x40
	int outsideRoomTableLength;
	int roomBoundingBoxesLength;
	unsigned short numBones;
	unsigned short numAnims;
	int meshBaseLength;

	//0x50
	int meshesLength;
	int animsLength;
	int changesLength;
	int rangesLength;

	//0x60
	int commandsLength;
	int bonesLength;
	int frameDataLength;
	int textureInfoLength;

	//0x70
	int spriteInfoLength;
	int mmTextureInfoLength;
	int animTextureRangesLength;
	int soundEffectInfoLength;

	//0x80
	int sampleInfoLength;
	int unk33;
	int unk34;
	int numBoxes;

	//0x90
	int boxesLength;
	int overlapsLength;
	int groundZoneLength;
	int groundZone2Length;

	//0xA0
	int groundZone3Length;
	int groundZone4Length;
	int groundZone5Length;
	int numFixedCameras;

	//0xB0
	unsigned short numSpotCameras;
	unsigned short unk45;
	int unk455;
	int unk46;
	unsigned short numAIObjects;
	unsigned short unk0003;

	//0xC0
	int numAiModuleRelocations;
	char aiModuleIndices[4];
	int unk50;
	int unk51;

	//0xD0
	int unk53;
	int unk54;
	int unk55;
	int unk56;

	//0xE0
	int unk57;
};

extern struct object_info* objects;
extern struct static_info* static_objects;
extern char* SkinVertNums;
extern char* ScratchVertNums;

#endif