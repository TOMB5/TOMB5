#include "NEWINV2.H"

#include "SPECIFIC.H"
#include "LARA.H"
#include "LOADSAVE.H"

struct INVOBJ inventry_objects_list[100] = // offset 0x92BE8
{
	{ 0x150, -4, 0x3E8, 0x4000, 0x6000, 0x4000, 2, 0x51, -1 },
	{ 0x14E, 6, 0x3E8, 0x4000, -0x52B4, -0x42C0, 2, 0x52, -1 },
	{ 0x152, -6, 0x280, -0x8000, -0x4000, 0x2000, 2, 0x53, 1 },
	{ 0x15B, 0, 0x320, 0x4000, 0x2AAA, 0x3BC2, 2, 0x54, 1 },
	{ 0x15B, 0, 0x320, 0x4000, 0x2AAA, 0x3BC2, 2, 0x55, 7 },
	{ 0x157, 0, 0x44C, 0x4000, -0x1000, 0, 2, 0x4D, -1 },
	{ 0x157, 0, 0x44C, 0x4000, -0x1000, 0, 2, 0x4D, -1 },
	{ 0x159, 0, 0x320, 0, -0x4000, 0, 2, 0x59, 1 },
	{ 0x159, 0, 0x320, 0, -0x4000, 0, 2, 0x5A, -1 },
	{ 0x153, 0, 0x1F4, 0x4000, 0, 0, 2, 0x5B, -1 },
	{ 0x154, 0, 0x1F4, 0x4000, 0, 0, 2, 0x5C, -1 },
	{ 0x15A, 3, 0x320, 0x4000, 0, 0, 2, 0x5D, 2 },
	{ 0x15A, 3, 0x320, 0x4000, 0, 0, 2, 0x5E, 4 },
	{ 0x15A, 3, 0x320, 0x4000, 0, 0, 2, 0x5F, 8 },
	{ 0x15A, 3, 0x320, 0x4000, 0, 0, 2, 0x60, 1 },
	{ 0x157, 0, 0x44C, 0x4000, -0x1000, 0, 2, 0x4D, -1 },
	{ 0x157, 0, 0x44C, 0x4000, -0x1000, 0, 2, 0x4D, -1 },
	{ 0x15C, 0, 0x2BC, 0x4000, -0xBB8, 0, 2, 0x61, -1 },
	{ 0x151, 5, 0x2BC, 0, 0x1508, 0, 2, 0x62, -1 },
	{ 0x14F, 4, 0x2BC, 0, 0x4000, 0, 2, 0x63, -1 },
	{ 0x15F, 2, 0x2BC, 0x4000, 0x7D0, 0, 2, 0x64, -1 },
	{ 0x161, 1, 0x384, 0, 0x7D0, 0, 2, 0x65, -1 },
	{ 0x15D, 2, 0x320, 0, 0, 0, 2, 0x66, -1 },
	{ 0x15E, 0, 0x200, 0, 0x5000, 0, 2, 0x67, -1 },
	{ 0x160, -1, 0x2BC, 0x1000, 0x7D0, 0, 2, 0x68, -1 },
	{ 0x163, 2, 0x44C, 0x4000, 0, 0, 2, 0x6A, -1 },
	{ 0x164, 2, 0x44C, -0x8000, 0, 0, 2, 0x6B, -1 },
	{ 0x165, 2, 0xFA0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0x166, 2, 0xFA0, 0, 0, 0, 2, 0x6D, -1 },
	{ 0xAC, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xAD, 0xE, 0x258, 0, -0x4000, 0, 2, 0x6C, -1 },
	{ 0xAE, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xAF, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB0, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB1, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB2, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB3, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB4, 0x12, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB5, 0x12, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB6, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB7, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB8, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xB9, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xBA, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xBB, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xBC, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xBD, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xBE, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xBF, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC0, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC1, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC2, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC3, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC4, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC5, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC6, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC7, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC8, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xC9, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xCA, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xCB, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xCC, 0x12, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xCD, 0x12, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xCE, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xCF, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD0, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD1, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD2, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD3, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD4, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD5, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD6, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD7, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD8, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xD9, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xDA, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xDB, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xDC, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xDD, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xDE, 8, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xDF, 2, 0x320, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE0, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE1, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE2, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE3, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE4, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE5, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE6, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xE7, 0xE, 0x4B0, 0, 0, 0, 2, 0x6C, -1 },
	{ 0xF1, 0xE, 0x4B0, 0, 0x4000, 0, 2, 0x6C, -1 },
	{ 0xF0, 4, 0x76C, 0, 0x4000, 0, 2, 0x6E, -1 },
	{ 0xE8, 4, 0x514, 0, 0x4000, 0, 2, 0x6C, -1 },
	{ 0xE9, 0xE, 0x4B0, 0, 0x4000, 0, 2, 0x6C, -1 },
	{ 0xEA, 0xE, 0x4B0, 0, 0x4000, 0, 2, 0x6C, -1 },
	{ 0xED, -0xC, 0x200, 0x4000, 0x3000, 0x5000, 2, 0x4E, -1 },
	{ 0x155, 0, 0x384, 0x2000, 0x1800, 0, 2, 0x4C, 1 },
	{ 0x156, 0, 0x44C, 0x4000, -0x1000, 0, 2, 0x4D, -1 },
	{ 0xEC, -0xC, 0x200, 0x4000, 0x3000, 0x5000, 2, 0x4F, -1 },
	{ 0xEB, 0x12, 0x320, -0x4000, 0, 0, 2, 0x50, -1 },
	{ 0xF9, -0xA, 0x180, -0x4000, 0x6800, -0x4000, 0xA, 0x50, -1 }
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
struct RINGME *rings[2]; // offset 0xA372C
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
char *current_ammo_type; // offset 0xA3700
int OBJLIST_SPACING; // offset 0xA3798
char friggrimmer; // offset 0xA36D4
char friggrimmer2; // offset 0xA36E4
char oldLaraBusy; // offset 0xA3774
struct MENUTHANG current_options[3]; // offset 0xA3740

void do_playstation_button_prompts_v1()//416E0, 41B34
{
	S_Warn("[do_playstation_button_prompts_v1] - Unimplemented!\n");
}

void S_DrawPickup(short object_number)//41608, 41A5C
{
	S_Warn("[S_DrawPickup] - Unimplemented!\n");
}

void dels_give_lara_guns_cheat()//41470, 418C4
{
	S_Warn("[dels_give_lara_guns_cheat] - Unimplemented!\n");
}

void dels_give_lara_items_cheat()//41324, 41778
{
	S_Warn("[dels_give_lara_items_cheat] - Unimplemented!\n");
}

void do_stats_mode()//412BC, 41710
{
	S_Warn("[do_stats_mode] - Unimplemented!\n");
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

int convert_obj_to_invobj(short obj)//40AC4, 40F18
{
	S_Warn("[convert_obj_to_invobj] - Unimplemented!\n");
	return 0;
}

void remove_inventory_item(short object_number)//4097C, 40DD0
{
	S_Warn("[remove_inventory_item] - Unimplemented!\n");
}

int have_i_got_object(short object_number)//4086C, 40CC0
{
	S_Warn("[have_i_got_object] - Unimplemented!\n");
	return 0;
}

void NailInvItem(short objnum)//40584, 409D8
{
	S_Warn("[NailInvItem] - Unimplemented!\n");
}

void DEL_picked_up_object(short objnum)//3FEB0, 40304
{
	S_Warn("[DEL_picked_up_object] - Unimplemented!\n");
}

void use_current_item()//3F9A0, 3FDF4
{
	S_Warn("[use_current_item] - Unimplemented!\n");
}

void setup_objectlist_startposition2(short newobj)//3F938, 3FD8C
{
	S_Warn("[setup_objectlist_startposition2] - Unimplemented!\n");
}

void setup_objectlist_startposition(short newobj)//3F8F0, 3FD44
{
	S_Warn("[setup_objectlist_startposition] - Unimplemented!\n");
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

void combine_crossbow_lasersight(int flag)//3F590, 3F9E4
{
	S_Warn("[combine_crossbow_lasersight] - Unimplemented!\n");
}

void combine_revolver_lasersight(int flag)//3F500, 3F954
{
	S_Warn("[combine_revolver_lasersight] - Unimplemented!\n");
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
		lara.hk_type_carried &= 0xFD;
	}
}

void seperate_object(short obj)//3F424, 3F878
{
	S_Warn("[seperate_object] - Unimplemented!\n");
}

void combine_these_two_objects(short obj1, short obj2)//3F348, 3F79C
{
	S_Warn("[combine_these_two_objects] - Unimplemented!\n");
}

int do_these_objects_combine(int obj1, int obj2)//3F2DC, 3F730
{
	S_Warn("[do_these_objects_combine] - Unimplemented!\n");
	return 0;
}

int have_i_got_item(short obj)//3F29C, 3F6F0
{
	S_Warn("[have_i_got_item] - Unimplemented!\n");
	return 0;
}

int is_item_currently_combinable(short obj)//3F200, 3F654
{
	S_Warn("[is_item_currently_combinable] - Unimplemented!\n");
	return 0;
}

void update_laras_weapons_status()//3F13C, 3F590
{
	S_Warn("[update_laras_weapons_status] - Unimplemented!\n");
}

void spinback(unsigned short *cock)//3F094, 3F4E8
{
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

void setup_ammo_selector()//3E9F8, 3EE4C
{
	S_Warn("[setup_ammo_selector] - Unimplemented!\n");
}

void handle_inventry_menu()//3DF44, 3E398
{
	S_Warn("[handle_inventry_menu] - Unimplemented!\n");
}

void handle_object_changeover(int ringnum)//3DF18, 3E36C
{
	S_Warn("[handle_object_changeover] - Unimplemented!\n");
}

void draw_current_object_list(int ringnum)//3D350, 3D7A4
{
	S_Warn("[draw_current_object_list] - Unimplemented!\n");
}

void insert_object_into_list(int num)//3D2C4, 3D718
{
	S_Warn("[insert_object_into_list] - Unimplemented!\n");
}

void construct_object_list()//3CC80, 3D0D4
{
	S_Warn("[construct_object_list] - Unimplemented!\n");
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

void DrawInventoryItemMe(struct ITEM_INFO *item, long shade, int overlay, int shagflag)//3C6A0, 3CAF4
{
	S_Warn("[DrawInventoryItemMe] - Unimplemented!\n");
}

void DrawThreeDeeObject2D(int x, int y, int num, int shade, int xrot, int yrot, int zrot, int bright, int overlay)//3C43C, 3C890
{
	S_Warn("[DrawThreeDeeObject2D] - Unimplemented!\n");
}

void do_debounced_joystick_poo()//3C224, 3C678
{
	S_Warn("[do_debounced_joystick_poo] - Unimplemented!\n");
}

void init_new_inventry()//3C024, 3C478
{
	S_Warn("[init_new_inventry] - Unimplemented!\n");
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
		struct ITEM_INFO *item; // $s0
		int val; // $a1
	} // line 415, offset 0x3c000
#endif

	return -1;
}