#include "NEWINV2.H"

#include "SPECIFIC.H"
#include "LARA.H"
#include "LOADSAVE.H"
#include "OBJECTS.H"
#include "GAMEFLOW.H"
#include "CONTROL.H"
#include "SAVEGAME.H"
#include "CD.H"
#include "LARA2GUN.H"
#include "LARA1GUN.H"
#include INPUT_H
#include "EFFECTS.H"
#include "CAMERA.H"
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

enum invobj_types // update this whenever inventry_objects_list is modified
{
	INV_UZI_ITEM = 0,
	INV_PISTOLS_ITEM = 1,
	INV_SHOTGUN_ITEM = 2,
	INV_REVOLVER_ITEM1 = 3,
	INV_REVOLVER_ITEM2 = 4,
	INV_CROSSBOW_AMMO2_ITEM1 = 5,
	INV_CROSSBOW_AMMO2_ITEM2 = 6,
	INV_HK_ITEM1 = 7,
	INV_HK_ITEM2 = 8,
	INV_SHOTGUN_AMMO1_ITEM = 9,
	INV_SHOTGUN_AMMO2_ITEM = 10,
	INV_HK_AMMO_ITEM1 = 11,
	INV_HK_AMMO_ITEM2 = 12,
	INV_HK_AMMO_ITEM3 = 13,
	INV_HK_AMMO_ITEM4 = 14,
	INV_CROSSBOW_AMMO2_ITEM3 = 15,
	INV_CROSSBOW_AMMO2_ITEM4 = 16,
	INV_REVOLVER_AMMO_ITEM = 17,
	INV_UZI_AMMO_ITEM = 18,
	INV_PISTOLS_AMMO_ITEM = 19,
	INV_LASERSIGHT_ITEM = 20,
	INV_SILENCER_ITEM = 21,
	INV_BIGMEDI_ITEM = 22,
	INV_SMALLMEDI_ITEM = 23,
	INV_BINOCULARS_ITEM = 24,
	INV_FLARE_INV_ITEM = 25,
	INV_COMPASS_ITEM = 26,
	INV_MEMCARD_LOAD_INV_ITEM = 27,
	INV_MEMCARD_SAVE_INV_ITEM = 28,
	INV_PUZZLE_ITEM1 = 29,
	INV_PUZZLE_ITEM2 = 30,
	INV_PUZZLE_ITEM3 = 31,
	INV_PUZZLE_ITEM4 = 32,
	INV_PUZZLE_ITEM5 = 33,
	INV_PUZZLE_ITEM6 = 34,
	INV_PUZZLE_ITEM7 = 35,
	INV_PUZZLE_ITEM8 = 36,
	INV_PUZZLE_ITEM1_COMBO1 = 37,
	INV_PUZZLE_ITEM1_COMBO2 = 38,
	INV_PUZZLE_ITEM2_COMBO1 = 39,
	INV_PUZZLE_ITEM2_COMBO2 = 40,
	INV_PUZZLE_ITEM3_COMBO1 = 41,
	INV_PUZZLE_ITEM3_COMBO2 = 42,
	INV_PUZZLE_ITEM4_COMBO1 = 43,
	INV_PUZZLE_ITEM4_COMBO2 = 44,
	INV_PUZZLE_ITEM5_COMBO1 = 45,
	INV_PUZZLE_ITEM5_COMBO2 = 46,
	INV_PUZZLE_ITEM6_COMBO1 = 47,
	INV_PUZZLE_ITEM6_COMBO2 = 48,
	INV_PUZZLE_ITEM7_COMBO1 = 49,
	INV_PUZZLE_ITEM7_COMBO2 = 50,
	INV_PUZZLE_ITEM8_COMBO1 = 51,
	INV_PUZZLE_ITEM8_COMBO2 = 52,
	INV_KEY_ITEM1 = 53,
	INV_KEY_ITEM2 = 54,
	INV_KEY_ITEM3 = 55,
	INV_KEY_ITEM4 = 56,
	INV_KEY_ITEM5 = 57,
	INV_KEY_ITEM6 = 58,
	INV_KEY_ITEM7 = 59,
	INV_KEY_ITEM8 = 60,
	INV_KEY_ITEM1_COMBO1 = 61,
	INV_KEY_ITEM1_COMBO2 = 62,
	INV_KEY_ITEM2_COMBO1 = 63,
	INV_KEY_ITEM2_COMBO2 = 64,
	INV_KEY_ITEM3_COMBO1 = 65,
	INV_KEY_ITEM3_COMBO2 = 66,
	INV_KEY_ITEM4_COMBO1 = 67,
	INV_KEY_ITEM4_COMBO2 = 68,
	INV_KEY_ITEM5_COMBO1 = 69,
	INV_KEY_ITEM5_COMBO2 = 70,
	INV_KEY_ITEM6_COMBO1 = 71,
	INV_KEY_ITEM6_COMBO2 = 72,
	INV_KEY_ITEM7_COMBO1 = 73,
	INV_KEY_ITEM7_COMBO2 = 74,
	INV_KEY_ITEM8_COMBO1 = 75,
	INV_KEY_ITEM8_COMBO2 = 76,
	INV_PICKUP_ITEM1 = 77,
	INV_PICKUP_ITEM2 = 78,
	INV_PICKUP_ITEM3 = 79,
	INV_PICKUP_ITEM4 = 80,
	INV_PICKUP_ITEM1_COMBO1 = 81,
	INV_PICKUP_ITEM1_COMBO2 = 82,
	INV_PICKUP_ITEM2_COMBO1 = 83,
	INV_PICKUP_ITEM2_COMBO2 = 84,
	INV_PICKUP_ITEM3_COMBO1 = 85,
	INV_PICKUP_ITEM3_COMBO2 = 86,
	INV_PICKUP_ITEM4_COMBO1 = 87,
	INV_PICKUP_ITEM4_COMBO2 = 88,
	INV_BURNING_TORCH_ITEM = 89,
	INV_CROWBAR_ITEM = 90,
	INV_EXAMINE1 = 91,
	INV_EXAMINE2 = 92,
	INV_EXAMINE3 = 93,
	INV_WET_CLOTH = 94,
	INV_CROSSBOW_ITEM = 95,
	INV_CROSSBOW_AMMO1_ITEM = 96,
	INV_CLOTH = 97,
	INV_BOTTLE = 98,
	INV_PUZZLE_HOLE8 = 99,

	NUM_INV_OBJECTS
};

struct INVOBJ inventry_objects_list[NUM_INV_OBJECTS] = // offset 0x92BE8
{
	{ UZI_ITEM, -4, 1000, ANGLE(90), ANGLE(135), ANGLE(90), 2, 81, -1 },
	{ PISTOLS_ITEM, 6, 1000, ANGLE(90), -21172, -17088, 2, 82, -1 },
	{ SHOTGUN_ITEM, -6, 640, ANGLE(-180), ANGLE(-90), ANGLE(45), 2, 83, 1 },
	{ REVOLVER_ITEM, 0, 800, ANGLE(90), ANGLE(60), 15298, 2, 84, 1 },
	{ REVOLVER_ITEM, 0, 800, ANGLE(90), ANGLE(60), 15298, 2, 85, 7 },
	{ CROSSBOW_AMMO2_ITEM, 0, 1100, ANGLE(90), ANGLE(-22.5), ANGLE(0), 2, 77, -1 },
	{ CROSSBOW_AMMO2_ITEM, 0, 1100, ANGLE(90), ANGLE(-22.5), ANGLE(0), 2, 77, -1 },
	{ HK_ITEM, 0, 800, ANGLE(0), ANGLE(-90), ANGLE(0), 2, 89, 1 },
	{ HK_ITEM, 0, 800, ANGLE(0), ANGLE(-90), ANGLE(0), 2, 90, -1 },
	{ SHOTGUN_AMMO1_ITEM, 0, 500, ANGLE(90), ANGLE(0), ANGLE(0), 2, 91, -1 },
	{ SHOTGUN_AMMO2_ITEM, 0, 500, ANGLE(90), ANGLE(0), ANGLE(0), 2, 92, -1 },
	{ HK_AMMO_ITEM, 3, 800, ANGLE(90), ANGLE(0), ANGLE(0), 2, 93, 2 },
	{ HK_AMMO_ITEM, 3, 800, ANGLE(90), ANGLE(0), ANGLE(0), 2, 94, 4 },
	{ HK_AMMO_ITEM, 3, 800, ANGLE(90), ANGLE(0), ANGLE(0), 2, 95, 8 },
	{ HK_AMMO_ITEM, 3, 800, ANGLE(90), ANGLE(0), ANGLE(0), 2, 96, 1 },
	{ CROSSBOW_AMMO2_ITEM, 0, 1100, ANGLE(90), ANGLE(-22.5), ANGLE(0), 2, 77, -1 },
	{ CROSSBOW_AMMO2_ITEM, 0, 1100, ANGLE(90), ANGLE(-22.5), ANGLE(0), 2, 77, -1 },
	{ REVOLVER_AMMO_ITEM, 0, 700, ANGLE(90), -3000, ANGLE(0), 2, 97, -1 },
	{ UZI_AMMO_ITEM, 5, 700, ANGLE(0), 5384, ANGLE(0), 2, 98, -1 },
	{ PISTOLS_AMMO_ITEM, 4, 700, ANGLE(0), ANGLE(90), ANGLE(0), 2, 99, -1 },
	{ LASERSIGHT_ITEM, 2, 700, ANGLE(90), 2000, ANGLE(0), 2, 100, -1 },
	{ SILENCER_ITEM, 1, 900, ANGLE(0), 2000, ANGLE(0), 2, 101, -1 },
	{ BIGMEDI_ITEM, 2, 800, ANGLE(0), ANGLE(0), ANGLE(0), 2, 102, -1 },
	{ SMALLMEDI_ITEM, 0, 512, ANGLE(0), ANGLE(112.5), ANGLE(0), 2, 103, -1 },
	{ BINOCULARS_ITEM, -1, 700, ANGLE(22.5), 2000, ANGLE(0), 2, 104, -1 },
	{ FLARE_INV_ITEM, 2, 1100, ANGLE(90), ANGLE(0), ANGLE(0), 2, 106, -1 },
	{ COMPASS_ITEM, 2, 1100, ANGLE(-180), ANGLE(0), ANGLE(0), 2, 107, -1 },
	{ MEMCARD_LOAD_INV_ITEM, 2, 4000, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ MEMCARD_SAVE_INV_ITEM, 2, 4000, ANGLE(0), ANGLE(0), ANGLE(0), 2, 109, -1 },
	{ PUZZLE_ITEM1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM2, 14, 600, ANGLE(0), ANGLE(-90), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM3, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM4, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM5, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM6, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM7, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM8, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM1_COMBO1, 18, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM1_COMBO2, 18, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM2_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM2_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM3_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM3_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM4_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM4_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM5_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM5_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM6_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM6_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM7_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM7_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM8_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PUZZLE_ITEM8_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM3, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM4, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM5, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM6, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM7, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM8, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM1_COMBO1, 18, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM1_COMBO2, 18, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM2_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM2_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM3_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM3_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM4_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM4_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM5_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM5_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM6_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM6_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM7_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM7_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM8_COMBO1, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ KEY_ITEM8_COMBO2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM2, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM3, 8, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM4, 2, 800, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM1_COMBO1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM1_COMBO2, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM2_COMBO1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM2_COMBO2, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM3_COMBO1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM3_COMBO2, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM4_COMBO1, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ PICKUP_ITEM4_COMBO2, 14, 1200, ANGLE(0), ANGLE(0), ANGLE(0), 2, 108, -1 },
	{ BURNING_TORCH_ITEM, 14, 1200, ANGLE(0), ANGLE(90), ANGLE(0), 2, 108, -1 },
	{ CROWBAR_ITEM, 4, 1900, ANGLE(0), ANGLE(90), ANGLE(0), 2, 110, -1 },
	{ EXAMINE1, 4, 1300, ANGLE(0), ANGLE(90), ANGLE(0), 2, 108, -1 },
	{ EXAMINE2, 14, 1200, ANGLE(0), ANGLE(90), ANGLE(0), 2, 108, -1 },
	{ EXAMINE3, 14, 1200, ANGLE(0), ANGLE(90), ANGLE(0), 2, 108, -1 },
	{ WET_CLOTH, -12, 512, ANGLE(90), ANGLE(67.5), ANGLE(112.5), 2, 78, -1 },
	{ CROSSBOW_ITEM, 0, 900, ANGLE(45), 6144, ANGLE(0), 2, 76, 1 },
	{ CROSSBOW_AMMO1_ITEM, 0, 1100, ANGLE(90), ANGLE(-22.5), ANGLE(0), 2, 77, -1 },
	{ CLOTH, -12, 512, ANGLE(90), ANGLE(67.5), ANGLE(112.5), 2, 79, -1 },
	{ BOTTLE, 18, 800, ANGLE(-90), ANGLE(0), ANGLE(0), 2, 80, -1 },
	{ PUZZLE_HOLE8, -10, 384, ANGLE(-90), 26624, ANGLE(-90), 10, 80, -1 },
};
unsigned char wanky_secrets_table[18] = // offset 0x92BD4
{
	0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03
};
short options_table[99] = // offset 0x933B8
{
	0x020A, 0x040A, 0x004A, 0x080A, 0x0812, 0x008A, 0x0092, 0x010A, 0x0112, 0x0004, 
	0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 
	0x000C, 0x000C, 0x0004, 0x0004, 0x0004, 0x0004, 0x8000, 0x1000, 0x2000, 0x0004, 
	0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x000C, 0x000C, 0x000C, 
	0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 
	0x000C, 0x000C, 0x000C, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 
	0x0004, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 
	0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x0004, 0x0004, 0x0004, 
	0x0004, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x000C, 0x0004,
	0x0004, 0x0020, 0x0020, 0x0020, 0x0004, 0x4002, 0x0004, 0x000C, 0x000C
};

short optmessages[11] = // offset 0x93480
{
	0x003B, 0x003C, 0x003E, 0x003F, 0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x00B2, 0x003D
};

struct COMBINELIST dels_handy_combine_table[24] = // offset 0x93498
{
	{ combine_revolver_lasersight, 3, 0x14, 4 },
	{ combine_crossbow_lasersight, 5, 0x14, 6 },
	{ combine_HK_SILENCER, 7, 0x15, 8 },
	{ combine_PuzzleItem1, 0x25, 0x26, 0x1D },
	{ combine_PuzzleItem2, 0x27, 0x28, 0x1E },
	{ combine_PuzzleItem3, 0x29, 0x2A, 0x1F },
	{ combine_PuzzleItem4, 0x2B, 0x2C, 0x20 },
	{ combine_PuzzleItem5, 0x2D, 0x2E, 0x21 },
	{ combine_PuzzleItem6, 0x2F, 0x30, 0x22 },
	{ combine_PuzzleItem7, 0x31, 0x32, 0x23 },
	{ combine_PuzzleItem8, 0x33, 0x34, 0x24 },
	{ combine_KeyItem1, 0x3D, 0x3E, 0x35 },
	{ combine_KeyItem2, 0x3F, 0x40, 0x36 },
	{ combine_KeyItem3, 0x41, 0x42, 0x37 },
	{ combine_KeyItem4, 0x43, 0x44, 0x38 },
	{ combine_KeyItem5, 0x45, 0x46, 0x39 },
	{ combine_KeyItem6, 0x47, 0x48, 0x3A },
	{ combine_KeyItem7, 0x49, 0x4A, 0x3B },
	{ combine_KeyItem8, 0x4B, 0x4C, 0x3C },
	{ combine_PickupItem1, 0x51, 0x52, 0x4D },
	{ combine_PickupItem2, 0x53, 0x54, 0x4E },
	{ combine_PickupItem3, 0x55, 0x56, 0x4F },
	{ combine_PickupItem4, 0x57, 0x58, 0x50 },
	{ combine_clothbottle, 0x61, 0x62, 0x5E }
};

int GLOBAL_enterinventory = -1; // offset 0xA0B30
int GLOBAL_inventoryitemchosen; // offset 0xA0B34
int GLOBAL_lastinvitem; // offset 0xA0B2C
short examine_mode; // offset 0xA0B28
short stats_mode; // offset 0xA0B2A
int GLOBAL_invkeypadmode; // offset 0xA0B38
int GLOBAL_invkeypadcombination; // offset 0xA0B3C
unsigned char keypadx; // offset 0xA0B40
unsigned char keypady; // offset 0xA0B41
unsigned char keypadnuminputs; // offset 0xA0B42
unsigned char keypadpause; // offset 0xA0B43
short inventry_xpos; // offset 0xA0B44
short inventry_ypos; // offset 0xA0B46
unsigned char keypadinputs[4]; // offset 0xA3780
short ammo_selector_fade_val; // offset 0xA3710
short ammo_selector_fade_dir; // offset 0xA371C
short combine_ring_fade_val; // offset 0xA370C
short combine_ring_fade_dir; // offset 0xA3718
short normal_ring_fade_val; // offset 0xA3708
short normal_ring_fade_dir; // offset 0xA3714
char seperate_type_flag; // offset 0xA3738
char combine_type_flag; // offset 0xA373C
short combine_obj1; // offset 0xA3720
short combine_obj2; // offset 0xA3724
char menu_active; // offset 0xA36F0
struct RINGME* rings[2]; // offset 0xA372C
char loading_or_saving; // offset 0xA3778
char use_the_bitch; // offset 0xA36FC
unsigned char left_debounce; // offset 0xA3760
unsigned char right_debounce; // offset 0xA376C
unsigned char up_debounce; // offset 0xA3768
unsigned char down_debounce; // offset 0xA3764
unsigned char select_debounce; // offset 0xA375C
unsigned char deselect_debounce; // offset 0xA3770
unsigned char go_left; // offset 0xA36F8
unsigned char go_right; // offset 0xA36D8
unsigned char go_up; // offset 0xA3704
unsigned char go_down; // offset 0xA36F4
unsigned char left_repeat; // offset 0xA36E8
unsigned char right_repeat; // offset 0xA36EC
unsigned char go_select; // offset 0xA3734
unsigned char go_deselect; // offset 0xA379C
unsigned char ammo_active; // offset 0xA377C
char bullshitbollox; // offset 0xA37A4
char _bullshitbollox; // offset 0xA37A0
static unsigned short AmountShotGunAmmo1; // offset 0xA36B8
static unsigned short AmountShotGunAmmo2; // offset 0xA36BA
static unsigned short AmountHKAmmo1; // offset 0xA36BC
static unsigned short AmountCrossBowAmmo1; // offset 0xA36BE
static unsigned short AmountCrossBowAmmo2; // offset 0xA36C0
static unsigned short AmountUziAmmo; // offset 0xA36C2
static unsigned short AmountRevolverAmmo; // offset 0xA36C4
static unsigned short AmountPistolsAmmo; // offset 0xA36C6
static char CurrentPistolsAmmoType; // offset 0xA36C8
static char CurrentUziAmmoType; // offset 0xA36C9
static char CurrentRevolverAmmoType; // offset 0xA36CA
static char CurrentShotGunAmmoType; // offset 0xA36CB
static char CurrentGrenadeGunAmmoType; // offset 0xA36CC
static char CurrentCrossBowAmmoType; // offset 0xA36CD
static char StashedCurrentPistolsAmmoType; // offset 0xA36CE
static char StashedCurrentUziAmmoType; // offset 0xA36CF
static char StashedCurrentRevolverAmmoType; // offset 0xA36D0
static char StashedCurrentShotGunAmmoType; // offset 0xA36D1
static char StashedCurrentGrenadeGunAmmoType; // offset 0xA36D2
static char StashedCurrentCrossBowAmmoType; // offset 0xA36D3
char current_selected_option; // offset 0xA36E0
char Stashedcurrent_selected_option; // offset 0xA36DC
struct AMMOLIST ammo_object_list[3]; // offset 0xA3784
char ammo_selector_flag; // offset 0xA3728
char num_ammo_slots; // offset 0xA3758
char* current_ammo_type; // offset 0xA3700
int OBJLIST_SPACING; // offset 0xA3798
char friggrimmer; // offset 0xA36D4
char friggrimmer2; // offset 0xA36E4
char oldLaraBusy; // offset 0xA3774
struct MENUTHANG current_options[3]; // offset 0xA3740

void do_playstation_button_prompts_v1()//416E0, 41B34
{
	if (examine_mode)
	{
		auto i = rings[0]->current_object_list[rings[0]->curobjinlist].invitem;
		// to be continued
	}
	else
	{
		if (stats_mode)
		{
			
		}
		else
		{
			if (ammo_active)
			{
				
			}
			else
			{
				if (GLOBAL_invkeypadmode)
				{
					
				}
				else
				{
					if(rings[1]->ringactive)
					{
						
					}
				}
			}
		}
	}
	S_Warn("[do_playstation_button_prompts_v1] - Unimplemented!\n");
}

void S_DrawPickup(short object_number)//41608, 41A5C
{
	S_Warn("[S_DrawPickup] - Unimplemented!\n");
}

void dels_give_lara_guns_cheat()//41470, 418C4 (F)
{
#if PC_VERSION
	; // null sub
#else
	if(objects[FLARE_INV_ITEM].loaded)
	{
		lara.num_flares = -1;
	}

	lara.num_small_medipack = -1;
	lara.num_large_medipack = -1;

	if (!(gfLevelFlags & GF_LVOP_YOUNG_LARA))
	{
		if (objects[PISTOLS_ITEM].loaded)
		{
			lara.num_shotgun_ammo1 = -1;
			lara.num_shotgun_ammo2 = -1;
			lara.shotgun_type_carried |= 1;
		}

		if (objects[REVOLVER_ITEM].loaded)
		{
			lara.num_revolver_ammo = -1;
			lara.sixshooter_type_carried |= 1;
		}

		if (objects[CROSSBOW_ITEM].loaded)
		{
			lara.num_crossbow_ammo1 = -1;
			lara.num_crossbow_ammo2 = -1;
			lara.crossbow_type_carried |= 1;
		}

		if (gfCurrentLevel < LVL5_GIBBY_LEVEL)
		{
			lara.crossbow_type_carried = 0xD;
			lara.num_crossbow_ammo2 = 0;
		}

		if (objects[HK_ITEM].loaded)
		{
			lara.num_hk_ammo1 = -1;
			lara.hk_type_carried |= 1;
		}

		if(objects[UZI_ITEM].loaded)
		{
			lara.num_uzi_ammo = -1;
			lara.uzis_type_carried |= 1;
		}

		if(objects[LASERSIGHT_ITEM].loaded)
		{
			lara.lasersight = 1;
		}

		if(objects[SILENCER_ITEM].loaded)
		{
			lara.silencer = 1;
		}
	}
#endif
}

void dels_give_lara_items_cheat()//41324, 41778 (F)
{
#if PC_VERSION
	; // null sub
#else
	if(objects[CROWBAR_ITEM].loaded)
	{
		lara.crowbar = 1;
	}

	for(int i = 0; i < 8; i++)
	{
		if(objects[PUZZLE_ITEM1 + i].loaded)
		{
			lara.puzzleitems[i] = 1;
		}
	}

	for(int i = 0; i < 8; i++)
	{
		if(objects[KEY_ITEM1 + i].loaded)
		{
			lara.keyitems |= 1 << i;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		if(objects[PICKUP_ITEM1 + i].loaded)
		{
			lara.pickupitems |= 1 << i;
		}
	}

	lara.puzzleitemscombo = 0;
	lara.keyitemscombo = 0;
	lara.pickupitemscombo = 0;

	if(gfCurrentLevel == LVL5_SUBMARINE)
	{
		lara.puzzleitems[0] = 0;
	}

	if(gfCurrentLevel == LVL5_OLD_MILL)
	{
		lara.puzzleitems[2] = 0;
	}
#endif
}

void do_stats_mode()//412BC, 41710
{
	stats_mode += 8;
	if (stats_mode > 0x80)
		stats_mode = 0x80;

	DisplayStatusUCunt();

	if (go_deselect)
	{
		SoundEffect(0x6D, 0, 2);
		go_deselect = 0;
		stats_mode = 0;
	}
}

void do_examine_mode()//411C4, 41618
{
	S_Warn("[do_examine_mode] - Unimplemented!\n");
}

void do_keypad_mode()//40B54, 40FA8
{
	S_Warn("[do_keypad_mode] - Unimplemented!\n");
}

void init_keypad_mode()//40B2C(<), 40F80(<) (F)
{
	keypadx = 0;
	keypady = 0;
	keypadnuminputs = 0;
	keypadinputs[0] = 0;
	keypadinputs[1] = 0;
	keypadinputs[2] = 0;
	keypadinputs[3] = 0;
	keypadpause = 0;
}

int convert_invobj_to_obj(int obj)//40B08(<), 40F5C(<) (F)
{
	return inventry_objects_list[obj].object_number;
}

int convert_obj_to_invobj(short obj)//40AC4(<), 40F18() (F)
{
	int i;

	for(i = 0; i < 100; i++)
	{
		if (inventry_objects_list[i].object_number == obj)
			return i;
	}

	return 27;
}

void remove_inventory_item(short object_number)//4097C, 40DD0 (F)
{
	if (object_number >= PICKUP_ITEM1 && object_number <= PICKUP_ITEM3)
	{
		lara.pickupitems &= ~(1 << (object_number - PICKUP_ITEM1));
	}
	else if (object_number >= PICKUP_ITEM1_COMBO1 && object_number <= PICKUP_ITEM4_COMBO2)
	{
		lara.pickupitemscombo &= ~(1 << (object_number - PICKUP_ITEM1_COMBO1));
	}
	else if (object_number >= KEY_ITEM1 && object_number <= KEY_ITEM8)
	{
		lara.keyitems &= ~(1 << (object_number - KEY_ITEM1));
	}
	else if (object_number >= KEY_ITEM1_COMBO1 && object_number <= KEY_ITEM8_COMBO2)
	{
		lara.keyitemscombo &= ~(1 << (object_number - KEY_ITEM1_COMBO1));
	}
	else if (object_number >= PUZZLE_ITEM1 && object_number <= PUZZLE_ITEM8)
	{
		lara.puzzleitems[object_number - PUZZLE_ITEM1]--;
	}
	else if (object_number >= PUZZLE_ITEM1_COMBO1 && object_number <= PUZZLE_ITEM8_COMBO2)
	{
		lara.puzzleitemscombo &= ~(1 << (object_number - PUZZLE_ITEM1_COMBO1));
	}
}

int have_i_got_object(short object_number)//4086C, 40CC0 (F)
{
	if (object_number >= PICKUP_ITEM1 && object_number <= PICKUP_ITEM3)
	{
		return lara.pickupitems & 1 << (object_number - PICKUP_ITEM1);
	}
	if (object_number >= PICKUP_ITEM1_COMBO1 && object_number <= PICKUP_ITEM4_COMBO2)
	{
		return lara.pickupitemscombo & 1 << (object_number - PICKUP_ITEM1_COMBO1);
	}
	if (object_number >= KEY_ITEM1 && object_number <= KEY_ITEM8)
	{
		return lara.keyitems & 1 << (object_number - KEY_ITEM1);
	}
	if (object_number >= KEY_ITEM1_COMBO1 && object_number <= KEY_ITEM8_COMBO2)
	{
		return lara.keyitemscombo & 1 << (object_number - KEY_ITEM1_COMBO1);
	}
	if (object_number >= PUZZLE_ITEM1 && object_number <= PUZZLE_ITEM8)
	{
		return lara.puzzleitems[object_number - PUZZLE_ITEM1];
	}
	if (object_number >= PUZZLE_ITEM1_COMBO1 && object_number <= PUZZLE_ITEM8_COMBO2)
	{
		return lara.puzzleitemscombo & 1 << (object_number - PUZZLE_ITEM1_COMBO1);
	}
	if (object_number == CROWBAR_ITEM)
	{
		return lara.crowbar;
	}
	if (object_number == WET_CLOTH)
	{
		return lara.wetcloth & 2;
	}

	return 0;
}

void NailInvItem(short objnum)//40584, 409D8
{
	switch (objnum)
	{
	case UZI_ITEM:
		lara.uzis_type_carried = 0;
		lara.num_uzi_ammo = 0;
		break;
	case PISTOLS_ITEM:
		lara.holster = 13;
		lara.pistols_type_carried = 0;
		lara.gun_status = 0;
		lara.last_gun_type = 0;
		lara.gun_type = 0;
		lara.request_gun_type = 0;
		break;
	case SHOTGUN_ITEM:
		lara.shotgun_type_carried = 0;
		lara.num_shotgun_ammo1 = 0;
		break;
	case REVOLVER_ITEM:
		lara.sixshooter_type_carried = 0;
		lara.num_revolver_ammo = 0;
		break;
	case CROSSBOW_ITEM:
		lara.crossbow_type_carried = 0;
		lara.num_crossbow_ammo1 = 0;
		break;
	case HK_ITEM:
		lara.hk_type_carried = 0;
		lara.num_hk_ammo1 = 0;
		break;
	case FLARE_INV_ITEM:
		lara.num_flares = 0;
		break;
	case SILENCER_ITEM:
		lara.silencer = 0;
		break;
	case LASERSIGHT_ITEM:
		lara.lasersight = 0;
		break;
	case BIGMEDI_ITEM:
		lara.num_large_medipack = 0;
		break;
	case SMALLMEDI_ITEM:
		lara.num_small_medipack = 0;
		break;
	case BINOCULARS_ITEM:
		lara.binoculars = 0;
		break;
	case CROWBAR_ITEM:
		lara.crowbar = 0;
		break;
	case EXAMINE1:
		lara.examine1 = 0;
		break;
	case EXAMINE2:
		lara.examine2 = 0;
		break;
	case EXAMINE3:
		lara.examine3 = 0;
		break;
	case WET_CLOTH:
		lara.wetcloth = 0;
		break;
	case CLOTH:
		lara.wetcloth = 0;
		break;
	case BOTTLE:
		lara.bottle = 0;
		break;
	default:
		if (objnum >= PICKUP_ITEM1 && objnum <= PICKUP_ITEM3)
		{
			lara.pickupitems &= ~(1 << (objnum - PICKUP_ITEM1));
		}
		else if (objnum >= PICKUP_ITEM1_COMBO1 && objnum <= PICKUP_ITEM4_COMBO2)
		{
			lara.pickupitemscombo &= ~(1 << (objnum - PICKUP_ITEM1_COMBO1));
		}
		else if (objnum >= KEY_ITEM1 && objnum <= KEY_ITEM8)
		{
			lara.keyitems &= ~(1 << (objnum - KEY_ITEM1));
		}
		else if (objnum >= KEY_ITEM1_COMBO1 && objnum <= KEY_ITEM8_COMBO2)
		{
			lara.keyitemscombo &= ~(1 << (objnum - KEY_ITEM1_COMBO1));
		}
		else if (objnum >= PUZZLE_ITEM1 && objnum <= PUZZLE_ITEM8)
		{
			lara.puzzleitems[objnum - PUZZLE_ITEM1] = 0;
		}
		else if (objnum >= PUZZLE_ITEM1_COMBO1 && objnum <= PUZZLE_ITEM8_COMBO2)
		{
			lara.puzzleitemscombo &= ~(1 << (objnum - PUZZLE_ITEM1_COMBO1));
		}
		break;
	}
}

void DEL_picked_up_object(short objnum)//3FEB0, 40304
{
	switch (objnum)
	{
	case UZI_ITEM:
		if (!(lara.uzis_type_carried & 1))
			lara.uzis_type_carried = 9;

		if (lara.num_uzi_ammo != -1)
			lara.num_uzi_ammo += 30;

		return;

	case PISTOLS_ITEM:
		if (!(lara.pistols_type_carried & 1))
			lara.pistols_type_carried = 9;

		lara.num_pistols_ammo = -1;

		return;

	case SHOTGUN_ITEM:
		if (!(lara.shotgun_type_carried & 1))
			lara.shotgun_type_carried = 9;

		if (lara.num_shotgun_ammo1 != -1)
			lara.num_shotgun_ammo1 += 36;

		return;

	case REVOLVER_ITEM:
		if (!(lara.sixshooter_type_carried & 1))
			lara.sixshooter_type_carried = 9;

		if (lara.num_revolver_ammo != -1)
			lara.num_revolver_ammo += 6;

		return;

	case CROSSBOW_ITEM:
		if (gfCurrentLevel >= LVL5_THIRTEENTH_FLOOR && gfCurrentLevel <= LVL5_RED_ALERT)
		{
			lara.crossbow_type_carried = 13;
			lara.num_crossbow_ammo2 = 0;
		}
		else
		{
			if (!(lara.crossbow_type_carried & 1))
				lara.crossbow_type_carried = 9;

			if (lara.num_crossbow_ammo1 != -1)
				lara.num_crossbow_ammo1 += 10;
		}

		return;

	case HK_ITEM:
		SetCutNotPlayed(23);

		if (!(lara.hk_type_carried & 1))
			lara.hk_type_carried = 9;

		if (gfCurrentLevel != LVL5_ESCAPE_WITH_THE_IRIS)
			if (lara.num_hk_ammo1 != -1)
				lara.num_hk_ammo1 += 30;

		return;

	case SHOTGUN_AMMO1_ITEM:
		if (lara.num_shotgun_ammo1 != -1)
			lara.num_shotgun_ammo1 += 36;

		return;

	case SHOTGUN_AMMO2_ITEM:
		if (lara.num_shotgun_ammo2 != -1)
			lara.num_shotgun_ammo2 += 36;

		return;

	case HK_AMMO_ITEM:
		if (lara.num_hk_ammo1 != -1)
			lara.num_hk_ammo1 += 30;

		return;

	case CROSSBOW_AMMO1_ITEM:
		if (lara.num_crossbow_ammo1 != -1)
			++lara.num_crossbow_ammo1;

		return;

	case CROSSBOW_AMMO2_ITEM:
		if (lara.num_crossbow_ammo2 != -1)
			lara.num_crossbow_ammo2 += 10;

		return;

	case REVOLVER_AMMO_ITEM:
		if (lara.num_revolver_ammo != -1)
			lara.num_revolver_ammo += 6;

		return;

	case UZI_AMMO_ITEM:
		if (lara.num_uzi_ammo != -1)
			lara.num_uzi_ammo += 30;

		return;

	case FLARE_INV_ITEM:
		if (lara.num_flares != -1)
			lara.num_flares += 12;

		return;

	case SILENCER_ITEM:
		if (!((lara.uzis_type_carried |
			(lara.pistols_type_carried |
				lara.shotgun_type_carried |
				lara.sixshooter_type_carried |
				lara.crossbow_type_carried |
				lara.hk_type_carried)) & 2))
			lara.silencer = 1;

		return;

	case LASERSIGHT_ITEM:
		if (!((lara.uzis_type_carried |
			(lara.pistols_type_carried |
				lara.shotgun_type_carried |
				lara.sixshooter_type_carried |
				lara.crossbow_type_carried |
				lara.hk_type_carried)) & 2))
			lara.lasersight = 1;

		return;

	case BIGMEDI_ITEM:
		if (lara.num_large_medipack != -1)
			++lara.num_large_medipack;

		return;

	case SMALLMEDI_ITEM:
		if (lara.num_small_medipack != -1)
			++lara.num_small_medipack;

		return;

	case BINOCULARS_ITEM:
		lara.binoculars = 1;
		return;

	case PICKUP_ITEM4:
		IsAtmospherePlaying = 0;

		S_CDPlay(6, 0);

		lara.pickupitems |= 8u;

		++savegame.Level.Secrets;
		++savegame.Game.Secrets;

		if (gfCurrentLevel >= LVL5_THIRTEENTH_FLOOR && gfCurrentLevel <= LVL5_RED_ALERT)
		{
			++savegame.CampaignSecrets[3];
		}
		else if (gfCurrentLevel >= LVL5_BASE && gfCurrentLevel <= LVL5_SINKING_SUBMARINE)
		{
			++savegame.CampaignSecrets[2];
		}
		else if (gfCurrentLevel >= LVL5_STREETS_OF_ROME && gfCurrentLevel <= LVL5_COLOSSEUM)
		{
			++savegame.CampaignSecrets[0];
		}
		else if (gfCurrentLevel >= LVL5_GALLOWS_TREE && gfCurrentLevel <= LVL5_OLD_MILL)
		{
			++savegame.CampaignSecrets[1];
		}

		return;

	case CROWBAR_ITEM:
		lara.crowbar = 1;
		return;

	case EXAMINE1:
		lara.examine1 = 1;
		return;

	case EXAMINE2:
		lara.examine2 = 1;
		return;

	case EXAMINE3:
		lara.examine3 = 1;
		return;

	case WET_CLOTH:
		lara.wetcloth = 2;
		return;

	case CLOTH:
		lara.wetcloth = 1;
		return;

	case BOTTLE:
		lara.bottle++;

		return;

	default:
		if (objnum >= PICKUP_ITEM1 && objnum <= PICKUP_ITEM3)
		{
			lara.pickupitems |= 1 << (objnum - PICKUP_ITEM1);
		}
		else if (objnum >= PICKUP_ITEM1_COMBO1 && objnum <= PICKUP_ITEM4_COMBO2)
		{
			lara.pickupitemscombo |= 1 << (objnum - PICKUP_ITEM1_COMBO1);
		}
		else if (objnum >= KEY_ITEM1 && objnum <= KEY_ITEM8)
		{
			lara.keyitems |= 1 << (objnum - KEY_ITEM1);
		}
		else if (objnum >= KEY_ITEM1_COMBO1 && objnum <= KEY_ITEM8_COMBO2)
		{
			lara.keyitemscombo |= 1 << (objnum - KEY_ITEM1_COMBO1);
		}
		else if (objnum >= PUZZLE_ITEM1 && objnum <= PUZZLE_ITEM8)
		{
			lara.puzzleitems[objnum - PUZZLE_ITEM1]++;
		}
		else if (objnum >= PUZZLE_ITEM1_COMBO1 && objnum <= PUZZLE_ITEM8_COMBO2)
		{
			lara.puzzleitemscombo |= 1 << (objnum - PUZZLE_ITEM1_COMBO1);
		}
	}
}

void use_current_item()//3F9A0, 3FDF4
{
	S_Warn("[use_current_item] - Unimplemented!\n");
}

void setup_objectlist_startposition2(short newobj)//3F938, 3FD8C (F)
{
	for (int i = 0; i < 100; i++)
	{
		if (inventry_objects_list[rings[0]->current_object_list[i].invitem].object_number == newobj)
		{
			rings[0]->curobjinlist = i;
		}
	}
}

void setup_objectlist_startposition(short newobj)//3F8F0, 3FD44 (F)
{
	for(int i = 0; i < 100; i++)
	{
		if (rings[0]->current_object_list[i].invitem == newobj)
		{
			rings[0]->curobjinlist = i;
		}
	}
}

void combine_clothbottle(int flag)//3F8D0(<), 3FD24(<) (F)
{
	lara.wetcloth = 2;
	lara.bottle--;
}

void combine_PickupItem4(int flag)//3F8AC(<), 3FD00(<) (F)
{
	lara.pickupitems |= 8;
	lara.pickupitemscombo &= 0xFF3F;
}

void combine_PickupItem3(int flag)//3F888(<), 3FCDC(<) (F)
{
	lara.pickupitems |= 4;
	lara.pickupitemscombo &= 0xFFCF;
}

void combine_PickupItem2(int flag)//3F864(<), 3FCB8(<) (F)
{
	lara.pickupitems |= 2;
	lara.pickupitemscombo &= 0xFFF3;
}

void combine_PickupItem1(int flag)//3F840(<), 3FC94(<) (F)
{
	lara.pickupitems |= 1;
	lara.pickupitemscombo &= 0xFFFC;
}

void combine_KeyItem8(int flag)//3F81C(<), 3FC70(<) (F)
{
	lara.keyitems |= 128;
	lara.keyitemscombo &= 0x3FFF;
}

void combine_KeyItem7(int flag)//3F7F8(<), 3FC4C(<) (F)
{
	lara.keyitems |= 64;
	lara.keyitemscombo &= 0xCFFF;
}

void combine_KeyItem6(int flag)//3F7D4(<), 3FC28(<) (F)
{
	lara.keyitems |= 32;
	lara.keyitemscombo &= 0xF3FF;
}

void combine_KeyItem5(int flag)//3F7B0(<), 3FC04(<) (F)
{
	lara.keyitems |= 16;
	lara.keyitemscombo &= 0xFCFF;
}

void combine_KeyItem4(int flag)//3F78C(<), 3FBE0(<) (F)
{
	lara.keyitems |= 8;
	lara.keyitemscombo &= 0xFF3F;
}

void combine_KeyItem3(int flag)//3F768(<), 3FBBC(<) (F)
{
	lara.keyitems |= 4;
	lara.keyitemscombo &= 0xFFCF;
}

void combine_KeyItem2(int flag)//3F744(<), 3FB98(<) (F)
{
	lara.keyitems |= 2;
	lara.keyitemscombo &= 0xFFF3;
}

void combine_KeyItem1(int flag)//3F720(<), 3FB74(<) (F)
{
	lara.keyitems |= 1;
	lara.keyitemscombo &= 0xFFFC;
}

void combine_PuzzleItem8(int flag)//3F700(<), 3FB54(<) (F)
{
	lara.puzzleitems[7] = 1;
	lara.puzzleitemscombo &= 0x3FFF;
}

void combine_PuzzleItem7(int flag)//3F6E0(<), 3FB34(<) (F)
{
	lara.puzzleitems[6] = 1;
	lara.puzzleitemscombo &= 0xCFFF;
}

void combine_PuzzleItem6(int flag)//3F6C0(<), 3FB14(<) (F)
{
	lara.puzzleitems[5] = 1;
	lara.puzzleitemscombo &= 0xF3FF;
}

void combine_PuzzleItem5(int flag)//3F6A0(<), 3FAF4(<) (F)
{
	lara.puzzleitems[4] = 1;
	lara.puzzleitemscombo &= 0xFCFF;
}

void combine_PuzzleItem4(int flag)//3F680(<), 3FAD4(<) (F)
{
	lara.puzzleitems[3] = 1;
	lara.puzzleitemscombo &= 0xFF3F;
}

void combine_PuzzleItem3(int flag)//3F660(<), 3FAB4(<) (F)
{
	lara.puzzleitems[2] = 1;
	lara.puzzleitemscombo &= 0xFFCF;
}

void combine_PuzzleItem2(int flag)//3F640(<), 3FA94(<) (F)
{
	lara.puzzleitems[1] = 1;
	lara.puzzleitemscombo &= 0xFFF3;
}

void combine_PuzzleItem1(int flag)//3F620(<), 3FA74(<) (F)
{
	lara.puzzleitems[0] = 1;
	lara.puzzleitemscombo &= 0xFFFC;
}

void combine_crossbow_lasersight(int flag)//3F590, 3F9E4 (F)
{
	if (flag)
	{
		lara.lasersight = 1;
		lara.crossbow_type_carried &= ~4;
	}
	else
	{
		lara.lasersight = 0;
		lara.crossbow_type_carried |= 4;
	}

	if (lara.gun_status && lara.gun_type == 6)
	{
		undraw_shotgun_meshes(6);
		draw_shotgun_meshes(6);
	}
}

void combine_revolver_lasersight(int flag)//3F500, 3F954 (F)
{
	if (flag)
	{
		lara.lasersight = 1;
		lara.sixshooter_type_carried &= ~4;
	}
	else
	{
		lara.lasersight = 0;
		lara.sixshooter_type_carried |= 4;
	}

	if (lara.gun_status && lara.gun_type == 2)
	{
		undraw_pistol_mesh_right(2);
		draw_pistol_meshes(2);
	}
}

void combine_HK_SILENCER(int flag)//3F4C0(<), 3F914(<) (F)
{
	if(flag == 0)
	{
		lara.silencer = 0;
		lara.hk_type_carried |= 2;
	}
	else
	{
		lara.silencer = 1;
		lara.hk_type_carried &= ~2;
	}
}

void seperate_object(short obj)//3F424, 3F878
{
	int n;

	for (n = 0; n < 24; n++)
	{
		if (dels_handy_combine_table[n].combined_item == obj)
			break;
	}

	dels_handy_combine_table[n].combine_routine(1);
	construct_object_list();
	setup_objectlist_startposition(dels_handy_combine_table[n].item1);
}

void combine_these_two_objects(short obj1, short obj2)//3F348, 3F79C
{
	int n;

	for(n = 0; n < 24; n++)
	{
		if (dels_handy_combine_table[n].item1 == obj1 &&
			dels_handy_combine_table[n].item2 == obj2)
			break;
	}

	dels_handy_combine_table[n].combine_routine(0);
	construct_object_list();
	setup_objectlist_startposition(dels_handy_combine_table[n].combined_item);
	handle_object_changeover(0);
}

int do_these_objects_combine(int obj1, int obj2)//3F2DC, 3F730
{
	S_Warn("[do_these_objects_combine] - Unimplemented!\n");
	return 0;
}

int have_i_got_item(short obj)//3F29C, 3F6F0 (F)
{
	for(int i = 0; i < 100; i++)
	{
		if (rings[0]->current_object_list[i].invitem == obj)
			return 1;
	}

	return 0;
}

int is_item_currently_combinable(short obj)//3F200, 3F654
{
	S_Warn("[is_item_currently_combinable] - Unimplemented!\n");
	return 0;
}

void update_laras_weapons_status()//3F13C, 3F590 (F)
{
	if(lara.shotgun_type_carried & 1)
	{
		lara.shotgun_type_carried &= 0xC7;
		if (CurrentShotGunAmmoType != 0)
			lara.shotgun_type_carried |= 0x10;
		else
			lara.shotgun_type_carried |= 8;
	}

	if (lara.hk_type_carried & 1)
	{
		lara.hk_type_carried &= 0xC7;
		if (CurrentGrenadeGunAmmoType == 0)
			lara.hk_type_carried |= 8;
		else if (CurrentGrenadeGunAmmoType == 1)
			lara.hk_type_carried |= 0x10;
		else
			lara.hk_type_carried |= 0x20;
	}

	if (lara.crossbow_type_carried & 1)
	{
		lara.crossbow_type_carried &= 0xC7;
		if (CurrentCrossBowAmmoType != 0)
			lara.crossbow_type_carried |= 0x10;
		else
			lara.crossbow_type_carried |= 8;
	}
	S_Warn("[update_laras_weapons_status] - Unimplemented!\n");
}

void spinback(unsigned short* cock)//3F094, 3F4E8 (F)
{
	unsigned short val = *cock;
	unsigned short val2;
	if (val)
	{
		if (val <= ANGLE(180))
		{
			if (val < ANGLE(5))
				val = ANGLE(5);

			if (val > ANGLE(90))
				val = ANGLE(90);

			val2 = val - (val >> 3);

			if (val2 > ANGLE(180))
				val2 = ANGLE(0);
		}
		else
		{
			if (-(short)val < ANGLE(5))
				val = ANGLE(5);

			if (-(short)val > ANGLE(90))
				val = ANGLE(90);

			val2 = ((unsigned short)-(short)val >> 3) + val;

			if (val2 < ANGLE(180))
				val2 = ANGLE(0);
		}

		*cock = val2;
	}

	S_Warn("[spinback] - Unimplemented!\n");
}

void draw_ammo_selector()//3EDDC, 3F230
{
	S_Warn("[draw_ammo_selector] - Unimplemented!\n");
}

void fade_ammo_selector()//3ED08, 3F15C
{
	S_Warn("[fade_ammo_selector] - Unimplemented!\n");
}

void setup_ammo_selector()//3E9F8, 3EE4C (F)
{
	int num = 0;
	int opts = options_table[rings[0]->current_object_list[rings[0]->curobjinlist].invitem];
	ammo_selector_flag = 0;
	num_ammo_slots = 0;
	if (!rings[1]->ringactive)
	{
		ammo_object_list[2].yrot = 0;
		ammo_object_list[1].yrot = 0;
		ammo_object_list[0].yrot = 0;
		if (opts & 0x4FC0)
		{
			ammo_selector_flag = 1;
			ammo_selector_fade_dir = 1;
			if (HIBYTE(opts) & 2)
			{
				ammo_object_list[0].invitem = 18;
				ammo_object_list[0].amount = AmountUziAmmo;
				num = 1;
				num_ammo_slots = 1;
				current_ammo_type = &CurrentUziAmmoType;
			}
			if (HIBYTE(opts) & 4)
			{
				num = 1;
				ammo_object_list[0].invitem = 19;
				ammo_object_list[0].amount = -1;
				num_ammo_slots = 1;
				current_ammo_type = &CurrentPistolsAmmoType;
			}
			if (HIBYTE(opts) & 8)
			{
				num = 1;
				ammo_object_list[0].invitem = 17;
				ammo_object_list[0].amount = AmountRevolverAmmo;
				num_ammo_slots = 1;
				current_ammo_type = &CurrentRevolverAmmoType;
			}
			if (opts & 0x80)
			{
				current_ammo_type = &CurrentCrossBowAmmoType;
				ammo_object_list[num].invitem = 15;
				ammo_object_list[num].amount = AmountCrossBowAmmo1;
				num++;
				ammo_object_list[num].invitem = 16;
				ammo_object_list[num].amount = AmountCrossBowAmmo2;
				num++;
				num_ammo_slots = num;
			}
			if (HIBYTE(opts) & 1)
			{
				current_ammo_type = &CurrentGrenadeGunAmmoType;
				ammo_object_list[num].invitem = 11;
				ammo_object_list[num].amount = AmountHKAmmo1;
				num++;
				ammo_object_list[num].invitem = 12;
				ammo_object_list[num].amount = AmountHKAmmo1;
				num++;
				ammo_object_list[num].invitem = 13;
				ammo_object_list[num].amount = AmountHKAmmo1;
				num++;
				num_ammo_slots = num;
			}
			if (opts & 0x40)
			{
				current_ammo_type = &CurrentShotGunAmmoType;
				ammo_object_list[num].invitem = 9;
				ammo_object_list[num].amount = AmountShotGunAmmo1;
				num++;
				ammo_object_list[num].invitem = 10;
				ammo_object_list[num].amount = AmountShotGunAmmo2;
				num++;
				num_ammo_slots = num;
			}
			if (HIBYTE(opts) & 0x40)
			{
				ammo_object_list[0].invitem = 96;
				ammo_object_list[0].amount = AmountCrossBowAmmo1;
				num_ammo_slots = 1;
				current_ammo_type = &CurrentCrossBowAmmoType;
			}
		}
	}
}

void handle_inventry_menu()//3DF44, 3E398
{
	S_Warn("[handle_inventry_menu] - Unimplemented!\n");
}

void handle_object_changeover(int ringnum)//3DF18, 3E36C (F)
{
	current_selected_option = 0;
	menu_active = 1;
	setup_ammo_selector();
}

void draw_current_object_list(int ringnum)//3D350, 3D7A4
{
	S_Warn("[draw_current_object_list] - Unimplemented!\n");
}

void insert_object_into_list(int num)//3D2C4(<), 3D718(<) (F)
{
	rings[0]->current_object_list[rings[0]->numobjectsinlist].invitem = num;
	rings[0]->current_object_list[rings[0]->numobjectsinlist].yrot = 0;
	rings[0]->current_object_list[rings[0]->numobjectsinlist].bright = 32;
	rings[0]->numobjectsinlist++;
}

void construct_object_list()//3CC80, 3D0D4
{
	rings[0]->numobjectsinlist = 0;
	for(int i = 0; i < 100; i++)
	{
		rings[0]->current_object_list[i].invitem = -1;
	}

	CurrentPistolsAmmoType = 0;
	CurrentUziAmmoType = 0;
	CurrentRevolverAmmoType = 0;
	CurrentShotGunAmmoType = 0;
	CurrentGrenadeGunAmmoType = 0;
	CurrentCrossBowAmmoType = 0;

	if (!(gfLevelFlags & GF_LVOP_YOUNG_LARA))
	{
		if (lara.pistols_type_carried & 1)
			insert_object_into_list(INV_PISTOLS_ITEM);

		if (lara.uzis_type_carried & 1)
		{
			insert_object_into_list(INV_UZI_ITEM);
		}
		else if (AmountUziAmmo)
		{
			insert_object_into_list(INV_UZI_AMMO_ITEM);
		}

		if (lara.sixshooter_type_carried & 1)
		{
			if (lara.sixshooter_type_carried & 4)
				insert_object_into_list(INV_REVOLVER_ITEM2);
			else
				insert_object_into_list(INV_REVOLVER_ITEM1);
		}
		else if (AmountRevolverAmmo)
		{
			insert_object_into_list(INV_REVOLVER_AMMO_ITEM);
		}

		if (lara.shotgun_type_carried & 1)
		{
			insert_object_into_list(INV_SHOTGUN_ITEM);
			if (lara.shotgun_type_carried & 0x10)
				CurrentShotGunAmmoType = 1;
		}
		else
		{
			if (AmountShotGunAmmo1)
				insert_object_into_list(INV_SHOTGUN_AMMO1_ITEM);
			if (AmountShotGunAmmo2)
				insert_object_into_list(INV_SHOTGUN_AMMO2_ITEM);
		}

		if (lara.hk_type_carried & 1)
		{
			if (lara.hk_type_carried & 2)
				insert_object_into_list(INV_HK_ITEM2);
			else
				insert_object_into_list(INV_HK_ITEM1);

			if (lara.hk_type_carried & 0x10)
			{
				CurrentGrenadeGunAmmoType = 1;
			}
			else if (lara.hk_type_carried & 0x20)
			{
				CurrentGrenadeGunAmmoType = 2;
			}
		}
		else if (AmountHKAmmo1)
		{
			insert_object_into_list(INV_HK_AMMO_ITEM4);
		}

		if (lara.crossbow_type_carried & 1)
		{
			if (gfCurrentLevel >= LVL5_THIRTEENTH_FLOOR && gfCurrentLevel <= LVL5_RED_ALERT)
			{
				insert_object_into_list(INV_CROSSBOW_ITEM);
				CurrentCrossBowAmmoType = 0;
			}
			else
			{
				if (lara.crossbow_type_carried & 4)
					insert_object_into_list(INV_CROSSBOW_AMMO2_ITEM2);
				else
					insert_object_into_list(INV_CROSSBOW_AMMO2_ITEM1);

				if (lara.crossbow_type_carried & 0x10)
					CurrentCrossBowAmmoType = 1;
			}
		}
		else if (gfCurrentLevel >= LVL5_THIRTEENTH_FLOOR && gfCurrentLevel <= LVL5_RED_ALERT)
		{
			if (AmountCrossBowAmmo1)
			{
				insert_object_into_list(INV_CROSSBOW_AMMO1_ITEM);
			}
		}
		else
		{
			if (AmountCrossBowAmmo1)
				insert_object_into_list(INV_CROSSBOW_AMMO2_ITEM3);

			if (AmountCrossBowAmmo2)
				insert_object_into_list(INV_CROSSBOW_AMMO2_ITEM4);
		}

		if (lara.lasersight)
			insert_object_into_list(INV_LASERSIGHT_ITEM);

		if (lara.silencer)
			insert_object_into_list(INV_SILENCER_ITEM);

		if (lara.binoculars)
			insert_object_into_list(INV_BINOCULARS_ITEM);

		if (lara.num_flares)
			insert_object_into_list(INV_FLARE_INV_ITEM);
	}
	insert_object_into_list(INV_COMPASS_ITEM);
	if (lara.num_small_medipack)
		insert_object_into_list(INV_SMALLMEDI_ITEM);
	if (lara.num_large_medipack)
		insert_object_into_list(INV_BIGMEDI_ITEM);
	if (lara.crowbar)
		insert_object_into_list(INV_CROWBAR_ITEM);

	for (int i = 0; i < 8; i++)
	{
		if (lara.puzzleitems[i])
			insert_object_into_list(INV_PUZZLE_ITEM1 + i);
	}

	for (int i = 0; i < 16; i++)
	{
		if (lara.puzzleitemscombo & (1 << i))
			insert_object_into_list(INV_PUZZLE_ITEM1_COMBO1 + i);
	}

	for (int i = 0; i < 8; i++)
	{
		if (lara.keyitems & (1 << i))
			insert_object_into_list(INV_KEY_ITEM1 + i);
	}

	for (int i = 0; i < 16; i++)
	{
		if (lara.keyitemscombo & (1 << i))
			insert_object_into_list(INV_KEY_ITEM1_COMBO1 + i);
	}

	for (int i = 0; i < 4; i++)
	{
		if (lara.pickupitems & (1 << i))
			insert_object_into_list(INV_PICKUP_ITEM1 + i);
	}

	for (int i = 0; i < 8; i++)
	{
		if (lara.pickupitemscombo & (1 << i))
			insert_object_into_list(INV_PICKUP_ITEM1_COMBO1 + i);
	}

	if (lara.examine1)
		insert_object_into_list(INV_EXAMINE1);
	if (lara.examine2)
		insert_object_into_list(INV_EXAMINE2);
	if (lara.examine3)
		insert_object_into_list(INV_EXAMINE3);
	if (lara.wetcloth == 2)
		insert_object_into_list(INV_WET_CLOTH);
	if (lara.wetcloth == 1)
		insert_object_into_list(INV_CLOTH);
	if (lara.bottle)
		insert_object_into_list(INV_BOTTLE);
	if (Gameflow->LoadSaveEnabled)
	{
		insert_object_into_list(INV_MEMCARD_LOAD_INV_ITEM);
		insert_object_into_list(INV_MEMCARD_SAVE_INV_ITEM);
	}
	rings[0]->objlistmovement = 0;
	rings[0]->curobjinlist = 0;
	rings[0]->ringactive = 1;

	rings[1]->objlistmovement = 0;
	rings[1]->curobjinlist = 0;
	rings[1]->ringactive = 0;

	handle_object_changeover(0);

	ammo_active = 0;
}

void insert_object_into_list_v2(int num)//3CB90, 3CFE4
{
	S_Warn("[insert_object_into_list_v2] - Unimplemented!\n");
}

void construct_combine_object_list()//3C940, 3CD94
{
	S_Warn("[construct_combine_object_list] - Unimplemented!\n");
}

int go_and_save_game()//3C920(<), 3CD74(<) (F)
{
	return SaveGame();
}

int go_and_load_game()//3C900(<), 3CD54(<) (F)
{
	return LoadGame();
}

void DrawInventoryItemMe(struct ITEM_INFO* item, long shade, int overlay, int shagflag)//3C6A0, 3CAF4
{
	S_Warn("[DrawInventoryItemMe] - Unimplemented!\n");
}

void DrawThreeDeeObject2D(int x, int y, int num, int shade, int xrot, int yrot, int zrot, int bright, int overlay)//3C43C, 3C890
{
	S_Warn("[DrawThreeDeeObject2D] - Unimplemented!\n");
}

void do_debounced_joystick_poo()//3C224(<), 3C678(<) (F)
{
	go_left = 0;
	go_right = 0;
	go_up = 0;
	go_down = 0;
	go_select = 0;
	go_deselect = 0;

	if (input & IN_LEFT)
	{
		if (left_repeat >= 8u)
			go_left = 1;
		else
			++left_repeat;
		if (!left_debounce)
			go_left = 1;
		left_debounce = 1;
	}
	else
	{
		left_debounce = 0;
		left_repeat = 0;
	}

	if (input & IN_RIGHT)
	{
		if (right_repeat >= 8u)
			go_right = 1;
		else
			++right_repeat;
		if (!right_debounce)
			go_right = 1;
		right_debounce = 1;
	}
	else
	{
		right_debounce = 0;
		right_repeat = 0;
	}

	if (input & IN_UP)
	{
		if (!up_debounce)
			go_up = 1;
		up_debounce = 1;
	}
	else
	{
		up_debounce = 0;
	}

	if (input & IN_DOWN)
	{
		if (!down_debounce)
			go_down = 1;
		down_debounce = 1;
	}
	else
	{
		down_debounce = 0;
	}

#if PC_VERSION
	if (input & IN_ACTION || input & IN_UNK20)
#else
	if (input & IN_JUMP)
#endif
	{
		select_debounce = 1;
	}
	else
	{
		if (select_debounce == 1 && !friggrimmer)
			go_select = 1;
		select_debounce = 0;
		friggrimmer = 0;
	}

#if PC_VERSION
	if (input & IN_UNK21)
#else
	if (input & IN_DRAW)
#endif
	{
		deselect_debounce = 1;
	}
	else
	{
		if (deselect_debounce == 1 && !friggrimmer2)
			go_deselect = 1;
		deselect_debounce = 0;
		friggrimmer2 = 0;
	}
}

void init_new_inventry()//3C024, 3C478 (F)
{
	examine_mode = 0;
	stats_mode = 0;

	AlterFOV(ANGLE(80));

	lara.Busy = 0;

	GLOBAL_inventoryitemchosen = -1;

	left_debounce = 0;
	right_debounce = 0;
	up_debounce = 0;
	down_debounce = 0;

	go_left = 0;
	go_right = 0;
	go_up = 0;
	go_down = 0;

	select_debounce = 0;
	deselect_debounce = 0;

	go_select = 0;
	go_deselect = 0;

	left_repeat = 0;
	right_repeat = 0;

	loading_or_saving = 0;
	use_the_bitch = 0;

	if (lara.num_shotgun_ammo1 == -1)
		AmountShotGunAmmo1 = -1;
	else
		AmountShotGunAmmo1 = lara.num_shotgun_ammo1 / 6;

	if (lara.num_shotgun_ammo2 == -1)
		AmountShotGunAmmo2 = -1;
	else
		AmountShotGunAmmo2 = lara.num_shotgun_ammo2 / 6;

	AmountHKAmmo1 = lara.num_hk_ammo1;
	AmountCrossBowAmmo1 = lara.num_crossbow_ammo1;
	AmountCrossBowAmmo2 = lara.num_crossbow_ammo2;
	AmountUziAmmo = lara.num_uzi_ammo;
	AmountRevolverAmmo = lara.num_revolver_ammo;
	AmountPistolsAmmo = lara.num_pistols_ammo;

	construct_object_list();

	if (GLOBAL_enterinventory == -1)
	{
		if (GLOBAL_lastinvitem != -1)
		{
			if (have_i_got_item(GLOBAL_lastinvitem))
				setup_objectlist_startposition(GLOBAL_lastinvitem);

			GLOBAL_lastinvitem = -1;
		}
	}
	else if (GLOBAL_enterinventory == 0xDEADBEEF)
	{
		GLOBAL_invkeypadmode = 1;
		init_keypad_mode();
		GLOBAL_enterinventory = -1;
	}
	else
	{
		if (have_i_got_object(GLOBAL_enterinventory))
			setup_objectlist_startposition2(GLOBAL_enterinventory);

		GLOBAL_enterinventory = -1;
	}

	ammo_selector_fade_val = 0;
	ammo_selector_fade_dir = 0;

	combine_ring_fade_val = 0;
	combine_ring_fade_dir = 0;

	combine_type_flag = 0;
	seperate_type_flag = 0;

	combine_obj1 = 0;
	combine_obj2 = 0;

	normal_ring_fade_val = 128;
	normal_ring_fade_dir = 0;

	handle_object_changeover(0);
}

int S_CallInventory2()//3B7A8, 3BC04
{
	S_Warn("[S_CallInventory2] - Unimplemented!\n");
#if 0
	short flag; // $s2
	int return_value; // $s3
	{ // line 291, offset 0x3bd3c
		int val; // $s0
	} // line 335, offset 0x3be20
	{ // line 387, offset 0x3bf3c
		short room_number; // stack offset -32
		struct ITEM_INFO* item; // $s0
		int val; // $a1
	} // line 415, offset 0x3c000
#endif

	return -1;
}