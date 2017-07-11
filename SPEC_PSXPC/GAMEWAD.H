#ifndef GAMEWAD_H
#define GAMEWAD_H

#define NUM_BITS_IN_BYTE 8

//Image properties for the loading screen seen when the game is loading.
//Do not change these unless the image dimensions or pixel format of the bitmap in GAMEWAD.OBJ has been changed.
#define LOADING_SCREEN_IMG_BPP 16
#define LOADING_SCREEN_IMG_WIDTH 512
#define LOADING_SCREEN_IMG_HEIGHT 256
#define LOADING_SCREEN_IMG_SIZE LOADING_SCREEN_IMG_WIDTH * LOADING_SCREEN_IMG_HEIGHT * (LOADING_SCREEN_IMG_BPP / NUM_BITS_IN_BYTE)

//Image properties for the loading "disc" seen when the game is loading.
//Do not change these unless the image dimensions or pixel format of the bitmap in GAMEWAD.OBJ has been changed.
#define LOADING_DISC_IMG_BPP 16
#define LOADING_DISC_IMG_WIDTH 64
#define LOADING_DISC_IMG_HEIGHT 64
#define LOADING_DISC_IMG_SIZE LOADING_DISC_IMG_WIDTH * LOADING_DISC_IMG_HEIGHT * (LOADING_DISC_IMG_BPP / NUM_BITS_IN_BYTE)

//Cleanly named gamewad file indices
//RESERVED_* are file entry indices that are null/unused.
//UNKNOWN_* are file entry indices which are not null but the data itself has not been discovered
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


#ifdef PSX
	#define GAMEWAD_FILENAME "\\GAMEWAD.OBJ;1"
#else
	#define GAMEWAD_FILENAME "GAMEWAD.OBJ"
#endif

int GAMEWAD_InitialiseFileEntry(int fileID);
void GAMEWAD_Load(int fileSize, char* ptr);
void GAMEWAD_SeekCurrent(int size);

#pragma pack(push, 1)

struct GAMEWAD_entry
{
	int fileOffset;
	int fileSize;
};

struct GAMEWAD_header
{
	struct GAMEWAD_entry entries[64];
};

#pragma pack(pop)

extern struct GAMEWAD_header gwHeader;

extern int gwLba;
extern int dword_A563C;
extern int dword_A5620;

#endif