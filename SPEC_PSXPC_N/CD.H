#ifndef CD_H
#define CD_H

#include "SPECTYPES.H"

#include <sys/types.h>
#include <libcd.h>

#define CD_SECTOR_SIZE (2048)
#define CD_SECTOR_SHIFT (11)

#define NUM_BITS_IN_BYTE 8

//Image properties for the loading screens seen when the game is loading.
//Do not change these unless the image dimensions or pixel format of the bitmap in GAMEWAD.OBJ has been changed.
#define LOADING_SCREEN_IMG_BPP 16
#define LOADING_SCREEN_IMG_WIDTH 512
#define LOADING_SCREEN_IMG_HEIGHT 256
#define LOADING_SCREEN_IMG_SIZE LOADING_SCREEN_IMG_WIDTH * LOADING_SCREEN_IMG_HEIGHT * (LOADING_SCREEN_IMG_BPP / NUM_BITS_IN_BYTE)

#define LOADING_CD_VRAM_OFFSET_X 1024
#define LOADING_CD_VRAM_OFFSET_Y 256
#define VRAM_OFFSET 1024 * 256
//#define VRAM_OFFSET LOADING_CD_VRAM_OFFSET_X * LOADING_CD_VRAM_OFFSET_Y * (LOADING_CD_IMG_BPP / NUM_BITS_IN_BYTE)

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
#define GAMEWAD_HEADER_MAX_LENGTH CD_SECTOR_SIZE

//Filename for PSX "GAMEWAD" that is a container storing all levelfiles and load screens.
#define GAMEWAD_FILENAME "\\GAMEWAD.OBJ;1"

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

//If changed update GAMEWAD_ENTRYSIZE to the size of this struct.
struct GAMEWAD_entry
{
	int fileOffset;
	int fileSize;
};

struct GAMEWAD_header
{
	struct GAMEWAD_entry entries[NUM_GAMEWAD_FILE_ENTRIES];
	char reserved[GAMEWAD_HEADER_MAX_LENGTH - (NUM_GAMEWAD_FILE_ENTRIES * sizeof(struct GAMEWAD_entry))];
};

enum
{
	CD_MODE_NONE,
	CD_MODE_DATA,
	CD_MODE_AUDIO
};

enum
{
	CD_SYNC_STATUS,
	CD_SYNC_WAIT_START,
	CD_SYNC_WAIT_END
};

enum
{
	CD_STATUS_NOT_STARTED,
	CD_STATUS_PLAYING,
	CD_STATUS_FINISHED
};


extern struct GAMEWAD_header gwHeader;
extern int gwLba;
extern int cdCurrentSector;
extern unsigned short XATrackClip[136];
extern int current_cd_mode;
extern volatile int XACurPos;
extern volatile int XAEndPos;
extern volatile short XAVolume;
extern volatile short XAReqVolume;
extern short XAMasterVolume;
extern short XAFadeRate;
extern short XATrack;
extern short XAReqTrack;
extern volatile char XAFlag;
extern char XAWait;
extern int XAStartPos;

extern void CDDA_SetVolume(int nVolume);
extern void XAReplay();
extern void cbvsync();
extern void S_CDPlay(short track, int mode);
extern void S_CDStop();
extern void S_CDPause();
extern void S_CDRestart();
extern void S_StartSyncedAudio(int nTrack);
extern void CDDA_SetMasterVolume(int nVolume);
extern void InitNewCDSystem();
extern void DEL_ChangeCDMode(int mode);
extern int DEL_CDFS_OpenFile(int filenum);
extern int DEL_CDFS_Read(char* addr, int size);
extern int DEL_CDFS_Seek(int offset);
extern void FRIG_CD_POS_TO_CUR();

#endif