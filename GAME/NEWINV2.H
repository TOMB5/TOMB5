#ifndef NEWINV2_H
#define NEWINV2_H

#include "STYPES.H"
#include "GAMEFLOW.H"

enum rings
{
	RING_INVENTORY,
	RING_AMMO
};

enum inv_options
{
	OPT_SHOTGUN = 0x40,
	OPT_CROSSBOW_TYPE2 = 0x80,
	OPT_HK = 0x100,
	OPT_UZI = 0x200,
	OPT_PISTOLS = 0x400,
	OPT_REVOLVER = 0x800,
	OPT_CROSSBOW_TYPE1 = 0x4000
};

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


extern struct INVOBJ inventry_objects_list[NUM_INV_OBJECTS]; // offset 0x92BE8
extern unsigned char wanky_secrets_table[NUM_TR5_LEVELS]; // offset 0x92BD4
extern unsigned short options_table[99]; // offset 0x933B8
extern short optmessages[11]; // offset 0x93480
extern struct COMBINELIST dels_handy_combine_table[24]; // offset 0x93498
extern int GLOBAL_enterinventory; // offset 0xA0B30
extern int GLOBAL_inventoryitemchosen; // offset 0xA0B34
extern int GLOBAL_lastinvitem; // offset 0xA0B2C
extern short examine_mode; // offset 0xA0B28
extern short stats_mode; // offset 0xA0B2A
extern int GLOBAL_invkeypadmode; // offset 0xA0B38
extern int GLOBAL_invkeypadcombination; // offset 0xA0B3C
extern unsigned char keypadx; // offset 0xA0B40
extern unsigned char keypady; // offset 0xA0B41
extern unsigned char keypadnuminputs; // offset 0xA0B42
extern unsigned char keypadpause; // offset 0xA0B43
extern short inventry_xpos; // offset 0xA0B44
extern short inventry_ypos; // offset 0xA0B46
extern unsigned char keypadinputs[4]; // offset 0xA3780
extern short ammo_selector_fade_val; // offset 0xA3710
extern short ammo_selector_fade_dir; // offset 0xA371C
extern short combine_ring_fade_val; // offset 0xA370C
extern short combine_ring_fade_dir; // offset 0xA3718
extern short normal_ring_fade_val; // offset 0xA3708
extern short normal_ring_fade_dir; // offset 0xA3714
extern char seperate_type_flag; // offset 0xA3738
extern char combine_type_flag; // offset 0xA373C
extern short combine_obj1; // offset 0xA3720
extern short combine_obj2; // offset 0xA3724
extern char menu_active; // offset 0xA36F0
extern struct RINGME* rings[2]; // offset 0xA372C
extern char loading_or_saving; // offset 0xA3778
extern char use_the_bitch; // offset 0xA36FC
extern unsigned char left_debounce; // offset 0xA3760
extern unsigned char right_debounce; // offset 0xA376C
extern unsigned char up_debounce; // offset 0xA3768
extern unsigned char down_debounce; // offset 0xA3764
extern unsigned char select_debounce; // offset 0xA375C
extern unsigned char deselect_debounce; // offset 0xA3770
extern unsigned char go_left; // offset 0xA36F8
extern unsigned char go_right; // offset 0xA36D8
extern unsigned char go_up; // offset 0xA3704
extern unsigned char go_down; // offset 0xA36F4
extern unsigned char left_repeat; // offset 0xA36E8
extern unsigned char right_repeat; // offset 0xA36EC
extern unsigned char go_select; // offset 0xA3734
extern unsigned char go_deselect; // offset 0xA379C
extern unsigned char ammo_active; // offset 0xA377C
extern char bullshitbollox; // offset 0xA37A4
extern char _bullshitbollox; // offset 0xA37A0
extern char current_selected_option; // offset 0xA36E0
extern char Stashedcurrent_selected_option; // offset 0xA36DC
extern struct AMMOLIST ammo_object_list[3]; // offset 0xA3784
extern char ammo_selector_flag; // offset 0xA3728
extern char num_ammo_slots; // offset 0xA3758
extern char* current_ammo_type; // offset 0xA3700
extern int OBJLIST_SPACING; // offset 0xA3798
extern char friggrimmer; // offset 0xA36D4
extern char friggrimmer2; // offset 0xA36E4
extern char oldLaraBusy; // offset 0xA3774
extern struct MENUTHANG current_options[3]; // offset 0xA3740

extern void do_playstation_button_prompts_v1();
extern void S_DrawPickup(short object_number);
extern void dels_give_lara_guns_cheat();
extern void dels_give_lara_items_cheat();
extern void do_stats_mode();
extern void do_examine_mode();
extern void do_keypad_mode();
extern void init_keypad_mode();
extern int convert_invobj_to_obj(int obj);
extern int convert_obj_to_invobj(short obj);
extern void remove_inventory_item(short object_number);
extern int have_i_got_object(short object_number);
extern void NailInvItem(short objnum);
extern void DEL_picked_up_object(short objnum);
extern void use_current_item();
extern void setup_objectlist_startposition2(short newobj);
extern void setup_objectlist_startposition(short newobj);
extern void combine_clothbottle(int flag);
extern void combine_PickupItem4(int flag);
extern void combine_PickupItem3(int flag);
extern void combine_PickupItem2(int flag);
extern void combine_PickupItem1(int flag);
extern void combine_KeyItem8(int flag);
extern void combine_KeyItem7(int flag);
extern void combine_KeyItem6(int flag);
extern void combine_KeyItem5(int flag);
extern void combine_KeyItem4(int flag);
extern void combine_KeyItem3(int flag);
extern void combine_KeyItem2(int flag);
extern void combine_KeyItem1(int flag);
extern void combine_PuzzleItem8(int flag);
extern void combine_PuzzleItem7(int flag);
extern void combine_PuzzleItem6(int flag);
extern void combine_PuzzleItem5(int flag);
extern void combine_PuzzleItem4(int flag);
extern void combine_PuzzleItem3(int flag);
extern void combine_PuzzleItem2(int flag);
extern void combine_PuzzleItem1(int flag);
extern void combine_crossbow_lasersight(int flag);
extern void combine_revolver_lasersight(int flag);
extern void combine_HK_SILENCER(int flag);
extern void seperate_object(short obj);
extern void combine_these_two_objects(short obj1, short obj2);
extern int do_these_objects_combine(int obj1, int obj2);
extern int have_i_got_item(short obj);
extern int is_item_currently_combinable(short obj);
extern void update_laras_weapons_status();
extern void spinback(unsigned short* cock);
extern void draw_ammo_selector();
extern void fade_ammo_selector();
extern void setup_ammo_selector();
extern void handle_inventry_menu();
extern void handle_object_changeover(int ringnum);
extern void draw_current_object_list(int ringnum);
extern void insert_object_into_list(int num);
extern void construct_object_list();
extern void insert_object_into_list_v2(int num);
extern void construct_combine_object_list();
extern int go_and_save_game();
extern int go_and_load_game();
extern void DrawInventoryItemMe(struct ITEM_INFO* item, long shade, int overlay, int shagflag);
extern void DrawThreeDeeObject2D(int x, int y, int num, int shade, int xrot, int yrot, int zrot, int bright, int overlay);
extern void do_debounced_joystick_poo();
extern void init_new_inventry();
extern int S_CallInventory2();

#endif