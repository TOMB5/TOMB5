#ifndef CD_H
#define CD_H

#include "PSXTYPES.H"

#ifdef PSX_VERSION
	#include <sys/types.h>
	#include <libcd.h>
#endif

#define CD_SECTOR_SIZE (2048)

#define NUM_BITS_IN_BYTE 8

//Image properties for the loading screens seen when the game is loading.
//Do not change these unless the image dimensions or pixel format of the bitmap in GAMEWAD.OBJ has been changed.
#define LOADING_SCREEN_IMG_BPP 16
#define LOADING_SCREEN_IMG_WIDTH 512
#define LOADING_SCREEN_IMG_HEIGHT 256
#define LOADING_SCREEN_IMG_SIZE LOADING_SCREEN_IMG_WIDTH * LOADING_SCREEN_IMG_HEIGHT * (LOADING_SCREEN_IMG_BPP / NUM_BITS_IN_BYTE)

//Image properties for the loading "cd" seen when the game is loading.
//Do not change these unless the image dimensions or pixel format of the bitmap in GAMEWAD.OBJ has been changed.
#define LOADING_CD_IMG_BPP 16
#define LOADING_CD_IMG_WIDTH 64
#define LOADING_CD_IMG_HEIGHT 64
#define LOADING_CD_IMG_SIZE LOADING_CD_IMG_WIDTH * LOADING_CD_IMG_HEIGHT * (LOADING_CD_IMG_BPP / NUM_BITS_IN_BYTE)

//The number of file entries stored in GAMEWAD.OBJ.
//If this is changed, ensure that GAMEWAD.OBJ is recompiled ensuring the size  of GAMEWAD_header does not surpass 512 bytes.
#define NUM_GAMEWAD_FILE_ENTRIES 51

//Maximum size of the GAMEWAD header struct.
#define GAMEWAD_HEADER_MAX_LENGTH 512

//Filename for PSX "GAMEWAD" that is a container storing all levelfiles and load screens.
#ifdef PSX_VERSION
#define GAMEWAD_FILENAME "\\GAMEWAD.OBJ;1"
#else
#define GAMEWAD_FILENAME "GAMEWAD.OBJ"
#endif

//Cleanly named gamewad file indices
//RESERVED_* are file entry indices that are null/unused.
//UNKNOWN_* are file entry indices which are not null but the data itself has not been discovered.
enum gw_files
{
	NONE,//Used to initialise Gamewad offset to 0.
	CUTSEQ,
	TITLE,
	ANDREA1,//Guessed
	ANDREA2,
	ANDREA3,
	JOBY2,
	JOBY3,
	JOBY4,
	JOBY5,
	ANDY1,
	ANDY2,
	ANDY3,
	RICH1,
	RICH2,
	RICHCUT2,
	RICH3,//End Guessed
	RESERVED_17,
	RESERVED_18,
	RESERVED_19,
	RESERVED_20,
	RESERVED_21,
	RESERVED_22,
	RESERVED_23,
	RESERVED_24,
	RESERVED_25,
	RESERVED_26,
	RESERVED_27,
	RESERVED_28,
	RESERVED_29,
	UNKNOWN_30, //16bpp TR5 Extras Storyboards (ENG) 512x
	UNKNOWN_31, //16bpp TRN Extras Storyboards 512x
	UNKNOWN_32, //16bpp TR5 Extras Storyboards (ENG) 512x
	RESERVED_33,
	RESERVED_34,
	RESERVED_35,
	RESERVED_36,
	RESERVED_37,
	RESERVED_38,
	RESERVED_39,
	RESERVED_40,
	UNKNOWN_41, //16bpp TR5 Legal Screen (ENG)  512x256 & 16bpp Loading CD (64x64)
	UNKNOWN_42, //16bpp TR4 Legal Screen (FR)   512x256 & 16bpp Placeholder loading CD (64x64)
	UNKNOWN_43, //16bpp TR4 Legal Screen (US)   512x256 & 16bpp Placeholder loading CD (64x64)
	UNKNOWN_44, //16bpp TR4 Legal Screen (ENG)  512x256 & 16bpp Placeholder loading CD (64x64)
	UNKNOWN_45, //16bpp TR4 Legal Screen (ENG)  512x256 & 16bpp Placeholder loading CD (64x64)
	UNKNOWN_46, //16bpp TR5 Legal Screen (ENG)  512x256 & 16bpp Loading CD (64x64)
	UNKNOWN_47, //16bpp TR4 Legal Screen (US)   512x256 & 16bpp Placeholder loading CD (64x64)
	UNKNOWN_48, //16bpp TR4 Legal Screen (ENG)  512x256 & 16bpp Placeholder loading CD (64x64)
	UNKNOWN_49, //4bpp  TR4 Logo         (FR)   256x58
	UNKNOWN_50  //4bpp  TR4 Logo         (ENG)  256x58
};

#ifdef PSXPC_VERSION
#pragma pack(push, 1)
#endif

//If changed update GAMEWAD_ENTRYSIZE to the size of this struct.
struct GAMEWAD_entry
{
	int fileOffset;
	int fileSize;
};

#define GAMEWAD_ENTRYSIZE 8

struct GAMEWAD_header
{
	struct GAMEWAD_entry entries[NUM_GAMEWAD_FILE_ENTRIES];
#ifdef PSX_VERSION
	char reserved[GAMEWAD_HEADER_MAX_LENGTH - (NUM_GAMEWAD_FILE_ENTRIES * GAMEWAD_ENTRYSIZE)];
#else
	char reserved[GAMEWAD_HEADER_MAX_LENGTH - (NUM_GAMEWAD_FILE_ENTRIES * sizeof(GAMEWAD_entry))];
#endif
};

#ifdef PSXPC_VERSION
#pragma pack(pop)
#endif


//If you recieve this warning, make sure you have recompiled GAMEWAD.OBJ since the header size is greater than retail files.
#if (NUM_GAMEWAD_FILE_ENTRIES * GAMEWAD_ENTRYSIZE) - GAMEWAD_HEADER_MAX_LENGTH > GAMEWAD_HEADER_MAX_LENGTH
	#ifdef PSXPC_VERSION
		#pragma message("Warning: Gamewad header size exceeds limit!")
	#endif
#endif

int CD_InitialiseReaderPosition(int fileID);
void CD_Read(int fileSize, char* ptr);
void CD_Seek(int offset);
void CD_ReaderPositionToCurrent();

extern struct GAMEWAD_header gwHeader;
extern int gwLba;
extern int cdCurrentSector;


extern void cbvsync();
extern void InitNewCDSystem();
extern void S_CDPlay(short track, int mode);
extern void S_CDStop();
extern void CDDA_SetMasterVolume(int nVolume);
extern void CDDA_SetVolume(int nVolume);
extern void DEL_ChangeCDMode(int mode);
extern void XAReplay();

extern unsigned short XATrackClip[136];
extern short XAFadeRate;
extern int current_cd_mode;
extern int XACurPos;
extern int XAEndPos;
extern short XAVolume;
extern short XAReqVolume;
extern short XAMasterVolume;
extern short XATrack;
extern short XAReqTrack;
extern char XAFlag;
extern char XAWait;
extern int XAStartPos;

#ifdef PSX_VERSION
	extern CdlFILE fp;
#endif

#endif