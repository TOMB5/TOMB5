#include "ROOMLOAD.H"

#include "CD.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "MALLOC.H"
#include "SETUP.H"

#include <assert.h>

#include <stdio.h>
#include <string.h>
#include "SPECIFIC.H"

long AnimFilePos;
long AnimFileLen;
short* floor_data;
unsigned long* SetupPtr;
unsigned short ClutStartY;
struct SVECTOR* RoomBBoxes;
short* mesh_base;
struct PSXSPRITESTRUCT* GLOBAL_default_sprites_ptr;
struct PSXTEXTI* AnimatingWaterfalls[6];
int AnimatingWaterfallsV[6];
unsigned long envmap_data[6];
unsigned long* RelocPtr[128];

//FIXME (Retail)
int dword_800A5F04 = 0;
int dword_800AD724 = 0;
int dword_800A60D8 = 0;

void S_LoadLevelFile(int Name)//60188(<), 60D54(<) (F)
{
	char buf[80];
	unsigned long* mod;
	int len;
	int file;

#if! INTERNAL
	//TITLE is the base file entry index for levels, simply as a result, we must add gameflow level id to this.
	CD_InitialiseReaderPosition(Name + TITLE);
#endif

	DrawSync(0);

	init_game_malloc();

	LOAD_Start(Name + TITLE);

	SetupPtr = db.poly_buffer[0]+1026;

#if INTERNAL
	len = FILE_Length("DATA\\SETUP.MOD");
	file = PCopen("DATA\\SETUP.MOD", 0, 0);

	FILE_Read(&db.poly_buffer[1024], 1, len, file);

	PCclose(file);

#else
	CD_Read((char*)db.poly_buffer[0]+1024, gwHeader.entries[0].fileSize);//jal 5E414
#endif

	RelocateModule(SetupPtr, &SetupPtr[1024]);

#if INTERNAL
	strcpy(buff, gfFilenameWad[gfFilenameOffset[Name]]);
	strcat(buff, ".PSX");
		
	len = FILE_Length(buff);

	PCopen(buff, 0, 0);
#endif

	RelocateLevel(); //jalr SetupPtr[5](len);, retail a0 = s1? len?

	LOAD_Stop();
}

void ReloadAnims(int name, long len)//600E4, 60D20
{
	S_Warn("[ReloadAnims] - Unimplemented!\n");
}