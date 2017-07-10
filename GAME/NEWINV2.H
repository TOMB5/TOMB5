#ifndef NEWINV2_H
#define NEWINV2_H

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
//static unsigned short AmountShotGunAmmo1; // offset 0xA36B8
//static unsigned short AmountShotGunAmmo2; // offset 0xA36BA
//static unsigned short AmountHKAmmo1; // offset 0xA36BC
//static unsigned short AmountCrossBowAmmo1; // offset 0xA36BE
//static unsigned short AmountCrossBowAmmo2; // offset 0xA36C0
//static unsigned short AmountUziAmmo; // offset 0xA36C2
//static unsigned short AmountRevolverAmmo; // offset 0xA36C4
//static unsigned short AmountPistolsAmmo; // offset 0xA36C6
//static char CurrentPistolsAmmoType; // offset 0xA36C8
//static char CurrentUziAmmoType; // offset 0xA36C9
//static char CurrentRevolverAmmoType; // offset 0xA36CA
//static char CurrentShotGunAmmoType; // offset 0xA36CB
//static char CurrentGrenadeGunAmmoType; // offset 0xA36CC
//static char CurrentCrossBowAmmoType; // offset 0xA36CD
//static char StashedCurrentPistolsAmmoType; // offset 0xA36CE
//static char StashedCurrentUziAmmoType; // offset 0xA36CF
//static char StashedCurrentRevolverAmmoType; // offset 0xA36D0
//static char StashedCurrentShotGunAmmoType; // offset 0xA36D1
//static char StashedCurrentGrenadeGunAmmoType; // offset 0xA36D2
//static char StashedCurrentCrossBowAmmoType; // offset 0xA36D3
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

#endif