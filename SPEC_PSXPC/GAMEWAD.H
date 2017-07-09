#ifndef GAMEWAD_H
#define GAMEWAD_H

#define NUM_BITS_IN_BYTE 8

//Image properties for the loading screen seen when the game is loading.
#define LOADING_SCREEN_IMG_BPP 16
#define LOADING_SCREEN_IMG_WIDTH 512
#define LOADING_SCREEN_IMG_HEIGHT 256
#define LOADING_SCREEN_IMG_SIZE LOADING_SCREEN_IMG_WIDTH * LOADING_SCREEN_IMG_HEIGHT * (LOADING_SCREEN_IMG_BPP / NUM_BITS_IN_BYTE)

//Image properties for the loading "disc" seen when the game is loading.
#define LOADING_DISC_IMG_BPP 16
#define LOADING_DISC_IMG_WIDTH 64
#define LOADING_DISC_IMG_HEIGHT 64
#define LOADING_DISC_IMG_SIZE LOADING_DISC_IMG_WIDTH * LOADING_DISC_IMG_HEIGHT * (LOADING_DISC_IMG_BPP / NUM_BITS_IN_BYTE)

//Cleanly named gamewad file indices
enum gw_files
{
	UNKNOWN_00,
	CUTSEQ,
	TITLE,
	ANDREA1,
	ANDREA2,
	ANDREA3,
	JOBY2,
	JOBY3,
	JOBY4,
	JOBY5,
	ANDY1,
	ANDY2,
	RICH1,
	RICH2,
	RICHCUT2,
	RICH3,
	GIBBY,
	DEL,
	TOM,
	UNKNOWN_19,
	UNKNOWN_20,
	UNKNOWN_21,
	UNKNOWN_22,
	UNKNOWN_23,
	UNKNOWN_24,
	UNKNOWN_25,
	UNKNOWN_26,
	UNKNOWN_27,
	UNKNOWN_28,
	UNKNOWN_29,
	UNKNOWN_30,
	UNKNOWN_31,
	UNKNOWN_32,
	UNKNOWN_33,
	UNKNOWN_34,
	UNKNOWN_35,
	UNKNOWN_36,
	UNKNOWN_37,
	UNKNOWN_38,
	UNKNOWN_39,
	UNKNOWN_40,
	UNKNOWN_41,
	UNKNOWN_42,
	UNKNOWN_43,
	UNKNOWN_44,
	UNKNOWN_45,
	UNKNOWN_46,
	UNKNOWN_47,
	UNKNOWN_48,
	UNKNOWN_49,
	UNKNOWN_50,
	UNKNOWN_51
};


#ifdef PSX
	#define GAMEWAD_FILENAME "\\GAMEWAD.OBJ;1"
#else
	#define GAMEWAD_FILENAME "GAMEWAD.OBJ"
#endif

int GAMEWAD_InitialiseFileEntry(int fileID);
void GAMEWAD_Load(int fileSize, char* ptr);

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