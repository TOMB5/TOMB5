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
	LNG_ENGLISH,
	LNG_FRENCH,
	LNG_GERMAN,
	LNG_ITALIAN,
	LNG_SPANISH,
	LNG_US,
	LNG_JAPAN,
	LNG_DUTCH,
	NUM_GF_LANGUAGES
};

enum gf_commands
{
	GF_FMV = 0x80,
	GF_LEVEL = 0x81,
	GF_TITLE_LEVEL = 0x82,
	GF_LEVEL_DATA_END = 0x83,
	GF_CUT = 0x84,

	GF_RESIDENTCUT1 = 0x85,
	GF_RESIDENTCUT2 = 0x86,
	GF_RESIDENTCUT3 = 0x87,
	GF_RESIDENTCUT4 = 0x88,

	GF_LAYER1 = 0x89,
	GF_LAYER2 = 0x8A,

	GF_UV_ROTATE = 0x8B,
	GF_LEGEND = 0x8C,
	GF_LENS_FLARE = 0x8D,
	GF_MIRROR = 0x8E,
	GF_FOG = 0x8F,
	GF_ANIMATING_MIP = 0x90,
	GF_RESET_HUB = 0x91,

	GF_KEY_ITEM1 = 0x92,
	GF_KEY_ITEM2 = 0x93,
	GF_KEY_ITEM3 = 0x94,
	GF_KEY_ITEM4 = 0x95,
	GF_KEY_ITEM5 = 0x96,
	GF_KEY_ITEM6 = 0x97,
	GF_KEY_ITEM7 = 0x98,
	GF_KEY_ITEM8 = 0x99,
	GF_KEY_ITEM9 = 0x9A,
	GF_KEY_ITEM10 = 0x9B,
	GF_KEY_ITEM11 = 0x9C,
	GF_KEY_ITEM12 = 0x9D,

	GF_PUZZLE_ITEM1 = 0x9E,
	GF_PUZZLE_ITEM2 = 0x9F,
	GF_PUZZLE_ITEM3 = 0xA0,
	GF_PUZZLE_ITEM4 = 0xA1,
	GF_PUZZLE_ITEM5 = 0xA2,
	GF_PUZZLE_ITEM6 = 0xA3,
	GF_PUZZLE_ITEM7 = 0xA4,
	GF_PUZZLE_ITEM8 = 0xA5,
	GF_PUZZLE_ITEM9 = 0xA6,
	GF_PUZZLE_ITEM10 = 0xA7,
	GF_PUZZLE_ITEM11 = 0xA8,
	GF_PUZZLE_ITEM12 = 0xA9,

	GF_PICKUP_ITEM1 = 0xAA,
	GF_PICKUP_ITEM2 = 0xAB,
	GF_PICKUP_ITEM3 = 0xAC,
	GF_PICKUP_ITEM4 = 0xAD,

	GF_EXAMINE1 = 0xAE,
	GF_EXAMINE2 = 0xAF,
	GF_EXAMINE3 = 0xB0,

	GF_KEY_ITEM1_COMBO1 = 0xB1,
	GF_KEY_ITEM1_COMBO2 = 0xB2,
	GF_KEY_ITEM2_COMBO1 = 0xB3,
	GF_KEY_ITEM2_COMBO2 = 0xB4,
	GF_KEY_ITEM3_COMBO1 = 0xB5,
	GF_KEY_ITEM3_COMBO2 = 0xB6,
	GF_KEY_ITEM4_COMBO1 = 0xB7,
	GF_KEY_ITEM4_COMBO2 = 0xB8,
	GF_KEY_ITEM5_COMBO1 = 0xB9,
	GF_KEY_ITEM5_COMBO2 = 0xBA,
	GF_KEY_ITEM6_COMBO1 = 0xBB,
	GF_KEY_ITEM6_COMBO2 = 0xBC,
	GF_KEY_ITEM7_COMBO1 = 0xBD,
	GF_KEY_ITEM7_COMBO2 = 0xBE,
	GF_KEY_ITEM8_COMBO1 = 0xBF,
	GF_KEY_ITEM8_COMBO2 = 0xC0,

	GF_PUZZLE_ITEM1_COMBO1 = 0xC1,
	GF_PUZZLE_ITEM1_COMBO2 = 0xC2,
	GF_PUZZLE_ITEM2_COMBO1 = 0xC3,
	GF_PUZZLE_ITEM2_COMBO2 = 0xC4,
	GF_PUZZLE_ITEM3_COMBO1 = 0xC5,
	GF_PUZZLE_ITEM3_COMBO2 = 0xC6,
	GF_PUZZLE_ITEM4_COMBO1 = 0xC7,
	GF_PUZZLE_ITEM4_COMBO2 = 0xC8,
	GF_PUZZLE_ITEM5_COMBO1 = 0xC9,
	GF_PUZZLE_ITEM5_COMBO2 = 0xCA,
	GF_PUZZLE_ITEM6_COMBO1 = 0xCB,
	GF_PUZZLE_ITEM6_COMBO2 = 0xCC,
	GF_PUZZLE_ITEM7_COMBO1 = 0xCD,
	GF_PUZZLE_ITEM7_COMBO2 = 0xCE,
	GF_PUZZLE_ITEM8_COMBO1 = 0xCF,
	GF_PUZZLE_ITEM8_COMBO2 = 0xD0,

	GF_PICKUP_ITEM1_COMBO1 = 0xD1,
	GF_PICKUP_ITEM1_COMBO2 = 0xD2,
	GF_PICKUP_ITEM2_COMBO1 = 0xD3,
	GF_PICKUP_ITEM2_COMBO2 = 0xD4,
	GF_PICKUP_ITEM3_COMBO1 = 0xD5,
	GF_PICKUP_ITEM3_COMBO2 = 0xD6,
	GF_PICKUP_ITEM4_COMBO1 = 0xD7,
	GF_PICKUP_ITEM4_COMBO2 = 0xD8,

	GF_GIVE_ITEM_AT_STARTUP = 0xD9,
	GF_LOSE_ITEM_AT_STARTUP = 0xDA
};

// used in `levelOptions` and `titleOptions` parameters of GF_LEVEL and GF_TITLE_LEVEL, respectively
enum gf_level_options
{
	GF_LVOP_YOUNG_LARA = (1 << 0),				// 0x0001
	GF_LVOP_WEATHER = (1 << 1),					// 0x0002
	GF_LVOP_HORIZON = (1 << 2),					// 0x0004
	GF_LVOP_LAYER1_USED = (1 << 3),				// 0x0008
	GF_LVOP_LAYER2_USED = (1 << 4),				// 0x0010
	GF_LVOP_STARFIELD = (1 << 5),				// 0x0020
	GF_LVOP_LIGHTNING = (1 << 6),				// 0x0040
	GF_LVOP_TRAIN = (1 << 7),					// 0x0080
	GF_LVOP_PULSE = (1 << 8),					// 0x0100
	GF_LVOP_COL_ADD_HORIZON = (1 << 9),			// 0x0200
	GF_LVOP_RESETHUB_USED = (1 << 10),			// 0x0400
	GF_LVOP_LENSFLARE_USED = (1 << 11),			// 0x0800
	GF_LVOP_TIMER = (1 << 12),					// 0x1000
	GF_LVOP_MIRROR_USED = (1 << 13),			// 0x2000
	GF_LVOP_REMOVE_AMULET = (1 << 14),			// 0x4000
	GF_LVOP_NO_LEVEL = (1 << 15)				// 0x8000
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
extern unsigned short* gfFilenameOffset;
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
