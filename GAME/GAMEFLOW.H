#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include "SPECTYPES.H"

extern void DoGameflow();
extern void LoadGameflow();
extern void QuickControlPhase();
extern void DoTitle(unsigned char Name, unsigned char Audio);
extern void DoLevel(unsigned char Name, unsigned char Audio);

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
	NUM_GF_LANGUAGES
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
