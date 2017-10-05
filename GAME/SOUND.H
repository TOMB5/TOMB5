#ifndef SOUND_H
#define SOUND_H

#include "SPECTYPES.H"

#define MAX_SOUND_SLOTS 24

enum audio_tracks
{
	CDA_xa1_TL_10B, // To climb out, swim to the edge and press 'action'.
	CDA_xa1_Z10,
	CDA_xa1_TL_05, // To perform a sideways somersault, press 'left' and jump.
	CDA_xa1_TL_08, // For me to crawl, hold down 'crouch' and now push 'forward'.
	CDA_xa1_TL_11, // To use the lever switch, stand next to the switch, and press 'action'.
	CDA_xa1_ANDYPEW,
	CDA_xa1_SECRET,
	CDA_xa1_TL_02, // To leap the short distance, walk to the edge, now press 'forward' and 'jump' together.
	CDA_xa2_HMMM05,
	CDA_xa2_TL_01, // To climb onto this crate, stand next to the crate, push 'forward', and then 'action'.
	CDA_xa2_ATTACK04,
	CDA_xa2_UWATER2B,
	CDA_xa2_SPOOKY2A,
	CDA_xa2_TL_10A, // To swim, jump into the water. Use 'action' to swim forward, and the directions to steer.
	CDA_xa2_HMMM02,
	CDA_xa2_TOMS01,
	CDA_xa3_Attack03,
	CDA_xa3_Attack02,
	CDA_xa3_Hmmm01,
	CDA_xa3_Stealth1,
	CDA_xa3_Stealth2,
	CDA_xa3_Attack01,
	CDA_xa3_TL_06, // To monkeyswing, jump straight up at the bars, and press and hold 'action', then push 'forward'.
	CDA_xa3_TL_03, // Now let's try a longer leap. Walk to the edge, and tap 'back' once. Now press 'forward' and 'jump' together.
	CDA_xa4_hmmm06,
	CDA_xa4_mil01,
	CDA_xa4_Z_03,
	CDA_xa4_hit01,
	CDA_xa4_spooky05,
	CDA_xa4_drama01,
	CDA_xa4_stealth4,
	CDA_xa4_mil05,
	CDA_xa5_HMMM04,
	CDA_xa5_MIL06,
	CDA_xa5_SPOOKY02,
	CDA_xa5_TL_12, // To walk the tightrope, walk up to the rope and press 'action'. Push 'forward'. If you unbalance, push in the opposite direction to correct.
	CDA_xa5_MIL02A,
	CDA_xa5_HMMM03,
	CDA_xa5_MIL02,
	CDA_xa5_TL_04, // And now for the big jump. Walk to the edge, then tap 'back' once. Now press 'forward' and 'jump' together. When in mid-air, hold 'action' to grab onto the ledge.
	CDA_xa6_Mil04,
	CDA_xa6_Solo01,
	CDA_xa6_Z12,
	CDA_xa6_Stealth3,
	CDA_xa6_AuthSolo,
	CDA_xa6_Spooky03,
	CDA_xa6_Z13,
	CDA_xa6_Z_04anim,
	CDA_xa7_z_06a,
	CDA_xa7_andyoooh,
	CDA_xa7_andyooer,
	CDA_xa7_tl_07, // For me to climb this wall, stand next to it, and press 'forward' and 'action' together. Keep hold of 'action' and push up to climb the wall.
	CDA_xa7_z_02,
	CDA_xa7_evibes01,
	CDA_xa7_z_06,
	CDA_xa7_authtr,
	CDA_xa8_mil03,
	CDA_xa8_fightsc,
	CDA_xa8_richcut3,
	CDA_xa8_z_13,
	CDA_xa8_z_08,
	CDA_xa8_uwater2a,
	CDA_xa8_jobyalrm,
	CDA_xa8_mil02b,
	CDA_xa9_swampy,
	CDA_xa9_evibes02,
	CDA_xa9_gods01,
	CDA_xa9_z_03,
	CDA_xa9_richcut4,
	CDA_xa9_title4,
	CDA_xa9_spooky01,
	CDA_xa9_chopin01,
	CDA_xa10_echoir01,
	CDA_xa10_title3,
	CDA_xa10_perc01,
	CDA_xa10_vc01,
	CDA_xa10_title2,
	CDA_xa10_z_09,
	CDA_xa10_spooky04,
	CDA_xa10_z_10,
	CDA_xa11_vc01atv,
	CDA_xa11_andy3,
	CDA_xa11_title1,
	CDA_xa11_flyby1,
	CDA_xa11_monk_2,
	CDA_xa11_andy4,
	CDA_xa11_flyby3,
	CDA_xa11_flyby2,
	CDA_xa12_moses01,
	CDA_xa12_andy4b,
	CDA_xa12_z_10,
	CDA_xa12_flyby4,
	CDA_xa12_richcut1,
	CDA_xa12_andy5,
	CDA_xa12_z_05,
	CDA_xa12_z_01,
	CDA_xa13_Joby3,
	CDA_xa13_Andy7,
	CDA_xa13_Andrea3B,
	CDA_xa13_cossack,
	CDA_xa13_Z_07,
	CDA_xa13_Andy6,
	CDA_xa13_Andrea3,
	CDA_xa13_Joby7,
	CDA_xa14_uwater1,
	CDA_xa14_joby1,
	CDA_xa14_andy10,
	CDA_xa14_richcut2,
	CDA_xa14_andrea1,
	CDA_xa14_andy8,
	CDA_xa14_joby6,
	CDA_xa14_ecredits,
	CDA_xa15_boss_01,
	CDA_xa15_joby2,
	CDA_xa15_joby4,
	CDA_xa15_joby5,
	CDA_xa15_joby9,
	CDA_xa15_a_andy,
	CDA_xa15_a_rome,
	CDA_xa15_andy2,
	CDA_xa16_Joby8,
	CDA_xa16_A_Sub_Amb,
	CDA_xa16_Joby10,
	CDA_xa16_A_Harbour_out,
	CDA_xa16_A_Andy_Out_Norm,
	CDA_xa16_A_Andy_Out_Spooky,
	CDA_xa16_A_Rome_Day,
	CDA_xa16_A_Underwater,
	CDA_xa17_A_Rome_Night,
	CDA_xa17_A_VC_Saga,
	CDA_xa17_A_Industry,
	CDA_xa17_Andrea2,
	CDA_xa17_Andy1,
	CDA_xa17_Andrea4,
	CDA_xa17_Andy9,
	CDA_xa17_Andy11,
};

void SayNo();
void SOUND_Init();
void SOUND_Stop();

extern int sound_active;
extern short* sample_lut;
extern struct SAMPLE_INFO* sample_infos;
extern struct SoundSlot LaSlot[MAX_SOUND_SLOTS];

#endif