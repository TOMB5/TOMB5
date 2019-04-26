#include "ROOMLOAD.H"

#include "CD.H"
#include "DRAW.H"
#include "FILE.H"
#include "GAMEFLOW.H"
#include "GPU.H"
#include "LOAD_LEV.H"
#include "SETUP.H"
#include "TYPEDEFS.H"
#include "MALLOC.H"

#include <stdio.h>

#if !DISC_VERSION
	#include <LIBSN.H>
#endif

#include <STRINGS.H>

#ifdef __linux__
#define SETUP_MOD "DATA/SETUP.MOD"
#else
#define SETUP_MOD "DATA\\SETUP.MOD"
#endif

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

void ReloadAnims(int name, long len)//600E4(<), 60D20(<) (*) (*) (ND) (D)
{
#if DISC_VERSION
	cdCurrentSector = AnimFilePos;
	DEL_CDFS_Read((char*)frames, len);
#else
	int file;
	char buf[80];

	strcpy(buf, &gfFilenameWad[gfFilenameOffset[name]]);
	strcat(buf, ".PSX");
	file = PCopen(buf, 0, 0);

	PClseek(file, AnimFilePos, 0);
	FILE_Read((char*)frames, 1, len, file);

	PCclose(file);
#endif

	return;
}

void S_LoadLevelFile(int Name)//60188(<), 60D54(<) (F) (*) () (D) (D)
{
#if !DISC_VERSION
	char buf[80];
#endif
	unsigned long* mod;
	int len;
	int file;

#if DISC_VERSION
	//TITLE is the base file entry index for levels, simply as a result, we must add gameflow level id to this.
	DEL_CDFS_OpenFile(Name + TITLE);
#endif

	DrawSync(0);

	init_game_malloc();

	LOAD_Start(Name + TITLE);

	SetupPtr = &db.poly_buffer[0][1026];
	mod = &db.poly_buffer[0][1024];

#if DISC_VERSION
	DEL_CDFS_Read((char*)mod, gwHeader.entries[NONE].fileSize);//jal 5E414
#else
	len = FILE_Length(SETUP_MOD);
	file = PCopen(SETUP_MOD, 0, 0);
	FILE_Read((char*)mod, 1, len, file);

	PCclose(file);
#endif
	/*
	 *  SETUP.MOD
	 * Layout is:
	 * [SETUP.BIN]
	 * [SETUP.REL]
	 */
	RelocateModule((unsigned long)SetupPtr, (unsigned long*)(*mod + (unsigned long)SetupPtr));

#if DISC_VERSION
#if RELOC
	((VOIDFUNCVOID*)SetupPtr[LOAD_LEVEL])();
#else
	LoadLevel();
#endif
#else
	strcpy(&buf[0], &gfFilenameWad[gfFilenameOffset[Name]]);

#ifdef __linux__
	//Fix paths for Linux
	for (int i = 0; i < strlen(&buf[0]); i++)
	{
		if (buf[i] == '\\')
		{
			buf[i] = '/';
		}
	}
#endif

	strcat(&buf[0], ".PSX");

	FILE_Length(buf);

#if RELOC
	((VOIDFUNCINT*)SetupPtr[LOAD_LEVEL])(PCopen(&buf[0], 0, 0));
#else
	LoadLevel(PCopen(buf, 0, 0));
#endif
#endif

	LOAD_Stop();

	return;
}