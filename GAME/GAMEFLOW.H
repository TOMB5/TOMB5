#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include "PSXTYPES.H"

void DoGameflow();
void LoadGameflow();
void QuickControlPhase();
void DoTitle(unsigned char Name, unsigned char Audio);
void DoLevel(unsigned char Name, unsigned char Audio);

#pragma pack(push, 1)

struct GAMEFLOW
{
	unsigned long CheatEnabled : 1;
	unsigned long LoadSaveEnabled : 1;
	unsigned long TitleEnabled : 1;
	unsigned long PlayAnyLevel : 1;
	unsigned long Language : 3;
	unsigned long DemoDisc : 1;
	unsigned long Unused : 24;

	unsigned long InputTimeout;
	unsigned char SecurityTag;
	unsigned char nLevels;
	unsigned char nFileNames;
	unsigned char Pad;
	unsigned short FileNameLen;
	unsigned short ScriptLen;
};

struct STRINGHEADER
{
	unsigned short nStrings;
	unsigned short nPSXStrings;
	unsigned short nPCStrings;
	unsigned short StringWadLen;
	unsigned short PSXStringWadLen;
	unsigned short PCStringWadLen;
};

#pragma pack(pop)

enum gf_languages
{
	ENGLISH,
	FRENCH,
	GERMAN,
	ITALIAN,
	SPANISH,
	US,
	JAPAN,
	DUTCH,
	MAX_GF_LANGUAGES
};

extern unsigned char gfGameMode;
extern unsigned char gfNumMips;
extern int scroll_pos;
extern char DEL_playingamefmv;
extern char num_fmvs;
extern char fmv_to_play[2];
extern unsigned short dels_cutseq_selector_flag;
extern unsigned short dels_cutseq_player;
extern char Chris_Menu;
extern unsigned char gfLegendTime;
extern unsigned char bDoCredits;
extern unsigned char gfInitialiseGame;
extern long nframes;
extern unsigned char gfNumPickups;
extern unsigned char gfNumTakeaways;
extern char CanLoad;
extern struct GAMEFLOW* Gameflow;
extern unsigned short* gfStringOffset;
extern char* gfStringWad;
extern unsigned short *gfFilenameOffset;
extern char* gfFilenameWad;
extern unsigned char gfCurrentLevel;
extern unsigned char gfLevelComplete;
extern unsigned char gfRequiredStartPos;
extern unsigned short gfLevelFlags;
extern unsigned char gfLevelNames[40];
extern unsigned char gfResidentCut[4];
extern unsigned char gfResetHubDest;
extern char gfUVRotate;
extern char gfLayer1Vel;
extern char gfLayer2Vel;
extern struct CVECTOR gfLayer1Col;
extern struct CVECTOR gfLayer2Col;
extern unsigned long GameTimer;
extern struct PHD_VECTOR gfLensFlare;
extern struct CVECTOR gfLensFlareColour;
extern unsigned char gfMirrorRoom;
extern unsigned char gfMips[8];
extern char title_controls_locked_out;
extern long gfScriptLen;
extern unsigned char gfLegend;
extern unsigned char gfWadNames[40];
extern unsigned char gfPickups[16];
extern unsigned char gfTakeaways[16];

#endif
