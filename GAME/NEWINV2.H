#ifndef NEWINV2_H
#define NEWINV2_H

#include "SPECTYPES.H"

extern struct INVOBJ inventry_objects_list[100]; // offset 0x92BE8
extern unsigned char wanky_secrets_table[18]; // offset 0x92BD4
extern short options_table[99]; // offset 0x933B8
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
extern struct RINGME *rings[2]; // offset 0xA372C
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
extern char *current_ammo_type; // offset 0xA3700
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
extern void spinback(unsigned short *cock);
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
extern void DrawInventoryItemMe(struct ITEM_INFO *item, long shade, int overlay, int shagflag);
extern void DrawThreeDeeObject2D(int x, int y, int num, int shade, int xrot, int yrot, int zrot, int bright, int overlay);
extern void do_debounced_joystick_poo();
extern void init_new_inventry();
extern int S_CallInventory2();

#endif