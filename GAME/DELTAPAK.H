#ifndef DELTAPAK_H
#define DELTAPAK_H

#include "SPECTYPES.H"
#include "OBJECTS.H"

enum cutseq_pistols_info
{
	CPI_FRAME_MASK = 0x3FFF,
	CPI_SHOOT_LEFT = 0x8000,
	CPI_SHOOT_RIGHT = 0x4000
};

enum cutscenes
{
	CUT_NULL,
	CUT_STEALTH3_1,
	CUT_STEALTH3_2,
	CUT_STEALTH3_3,
	CUT_STEALTH3_4,
	CUT_JOBY6,
	CUT_ANDY5,
	CUT_ANDREA3B,
	CUT_ANDREA3,
	CUT_ANDY4B,
	CUT_ANDY4,
	CUT_RICHCUT4,
	CUT_JOBY10,
	CUT_JOBY9,
	CUT_ANDY3,
	CUT_JOBY5,
	CUT_ANDREA2,
	CUT_ANDREA1,
	CUT_JOBY4,
	CUT_ANDY2,
	CUT_RICH1,
	CUT_ANDY1,
	CUT_JOBY_CUT_3,
	CUT_RICH_CUT_3,
	CUT_RICH_CUT_1,
	CUT_JOBY_CUT_2,
	CUT_RICH_CUT_2,
	CUT_JOBY_CRANE_CUT,
	CUT_SPECIAL1,
	CUT_SPECIAL2,
	CUT_SPECIAL3,
	CUT_SPECIAL4,
	CUT_JOBY8,
	CUT_ANDY6,
	CUT_ANDYPEW,
	CUT_ANDY7,
	CUT_COSSACK,
	CUT_ANDY9,
	CUT_ANDY8,
	CUT_ANDY10,
	CUT_JOBY7,
	CUT_ANDREA4,
	CUT_MONK2,
	CUT_SWAMPY,
	CUT_ANDY11,
};

extern struct CUTSEQ_ROUTINES cutseq_control_routines[45];
extern unsigned short crane_pistols_info[11];
extern unsigned short craneguard_pistols_info[7];
extern short admiral_chat_ranges_joby2[12];
extern short sergie_chat_ranges_joby2[8];
extern short lara_chat_ranges_joby3[6];
extern short lara_chat_ranges_joby4[10];
extern short admiral_chat_ranges_joby4[20];
extern unsigned short larson_pistols_info1[2];
extern short lara_chat_ranges_andrea1[4];
extern short larson_chat_ranges1[12];
extern short pierre_chat_ranges1[30];
extern short lara_chat_ranges_andrea2[32];
extern short larson_chat_ranges2[8];
extern short pierre_chat_ranges2[34];
extern short admiral_chat_ranges_joby5[18];
extern short sergie_chat_ranges_joby5[20];
extern short lara_chat_ranges_joby9[12];
extern short admiral_chat_ranges_joby9[36];
extern short lara_chat_ranges_joby10[12];
extern short admiral_chat_ranges_joby10[42];
extern unsigned short andrea3_pistols_info[5];
extern short lara_chat_ranges_andrea3[14];
extern short larson_chat_ranges3[14];
extern short lara_chat_ranges_andrea3b[12];
extern short larson_chat_ranges3b[4];
extern short priest_chat_ranges_andy7[32];
extern short lara_chat_ranges_andy7[14];
extern short lara_chat_ranges_joby7[10];
extern short lara_chat_ranges_andrea4[22];
extern short pierre_chat_ranges4[48];
extern short lara_chat_ranges_andy9[6];
extern short lara_chat_ranges_andy1[14];
extern short lara_chat_ranges_andy2[8];
extern short lara_chat_ranges_joby8[20];
extern short lara_chat_ranges_andy6[8];
extern short lara_chat_ranges_andy11[28];
extern short priest_chat_ranges_andy6[18];
extern short priest_chat_ranges_andy2[24];
extern short voncroy_chat_ranges_richcut2[20];
extern short associate_chat_ranges_richcut2[12];
extern short guard_chat_ranges_richcut2[10];
extern short hanged_man_chat_ranges_andy1[18];
extern short priest_chat_ranges_andy9[20];
extern short knight_chat_ranges_andy9[14];
extern short priest_chat_ranges_andy11[30];
extern short knight_chat_ranges_andy11[14];
extern int cuntercunter;
extern char jobyfrigger;
extern int cutrot;
extern int GLOBAL_playing_cutseq;
extern int cutseq_trig;
extern int cutseq_num;
extern unsigned char disable_horizon;
extern char cutseq_busy_timeout;
extern short frig_shadow_bbox[6];
extern int cut_seethrough;
extern char lara_chat_cnt;
extern char actor_chat_cnt;
extern struct NEW_CUTSCENE* GLOBAL_cutme;
extern int lastcamnum;
extern int GLOBAL_cutseq_frame;
extern int GLOBAL_numcutseq_frames;
extern enum camera_type GLOBAL_oldcamtype;
extern struct PACKNODE* camera_pnodes;
extern struct PACKNODE* actor_pnodes[10];
extern struct ITEM_INFO duff_item;
extern int numnailed;
extern char old_status_flags[32];
extern unsigned short old_status_flags2[32];
extern unsigned long cutseq_meshbits[10];
extern unsigned long cutseq_meshswapbits[10];
extern struct RESIDENT_THING cutseq_resident_addresses[47];
extern char* GLOBAL_resident_depack_buffers;
extern int cutseq_malloc_used;
extern char* cutseq_malloc_ptr;
extern int cutseq_malloc_free;
extern unsigned short old_lara_holster;
extern short temp_rotation_buffer[160];

extern void andy11_end();
extern void andy11_control();
extern void andy11_init();
extern void Cutanimate(int objnum);
extern struct ITEM_INFO* ResetCutanimate(int objnum);
extern void trigger_title_spotcam(int num);
extern void CutLaraBubbles();
extern void swampy_end();
extern void swampy_control();
extern void swampy_init();
extern void monk2_end();
extern void monk2_control();
extern void monk2_init();
extern void do_pierre_gun_meshswap();
extern void andrea4_end();
extern void andrea4_control();
extern void andrea4_init();
extern void joby7_end();
extern void joby7_control();
extern void joby7_init();
extern void andy10_end();
extern void andy10_control();
extern void andy10_init();
extern void do_chalk_meshswap();
extern void andy8_end();
extern void andy8_control();
extern void andy8_init();
extern void andy9_end();
extern void andy9_control();
extern void andy9_init();
extern void TriggerDelBrownSmoke(long x, long y, long z);
extern void cossack_end();
extern void cossack_control();
extern void cossack_init();
extern void andy7_end();
extern void andy7_control();
extern void andy7_init();
extern void andypew_end();
extern void andypew_control();
extern void andypew_init();
extern void andy6_end();
extern void andy6_control();
extern void andy6_init();
extern void joby8_end();
extern void joby8_control();
extern void joby8_init();
extern void joby6_end();
extern void joby6_control();
extern void joby6_init();
extern void andy5_end();
extern void andy5_control();
extern void andy5_init();
extern void andrea3b_end();
extern void andrea3b_control();
extern void andrea3b_init();
extern void andrea3_end();
extern void andrea3_control();
extern void andrea3_init();
extern void do_clanger_meshswap();
extern void andy4b_end();
extern void andy4b_control();
extern void andy4b_init();
extern void andy4_end();
extern void andy4_control();
extern void andy4_init();
extern void richcut4_end();
extern void richcut4_control();
extern void richcut4_init();
extern void joby10_end();
extern void joby10_control();
extern void joby10_init();
extern void joby9_end();
extern void joby9_control();
extern void joby9_init();
extern void do_catapult_meshswap();
extern void andy3_end();
extern void andy3_control();
extern void andy3_init();
extern void joby5_end();
extern void joby5_control();
extern void joby5_init();
extern void andrea2_end();
extern void andrea2_control();
extern void andrea2_init();
extern void andrea1_end();
extern void andrea1_control();
extern void andrea1_init();
extern void joby4_end();
extern void joby4_control();
extern void joby4_init();
extern void DelTorchFlames(struct PHD_VECTOR* pos);
extern void setup_preist_meshswap();
extern void andy2_end();
extern void andy2_control();
extern void andy2_init();
extern void do_hammer_meshswap();
extern void hamgate_end();
extern void hamgate_control();
extern void hamgate_init();
extern void andy1_end();
extern void andy1_control();
extern void andy1_init();
extern void joby3_end();
extern void joby3_control();
extern void joby3_init();
extern void joby2_end();
extern void joby2_control();
extern void joby2_init();
extern void TriggerDelSmoke(long x, long y, long z, int sizeme);
extern void TriggerActorBlood(int actornum, unsigned long nodenum, struct PHD_VECTOR* pos, int direction, int speed);
extern void GetActorJointAbsPosition(int actornum, unsigned long nodenum, struct PHD_VECTOR* vec);
extern void deal_with_actor_shooting(unsigned short* shootdata, int actornum, int nodenum, struct PHD_VECTOR* pos);
extern void stealth3_end();
extern void stealth3_start();
extern void special4_end();
extern void special4_control();
extern void special4_init();
extern void special3_end();
extern void special3_control();
extern void special3_init();
extern void special2_end();
extern void special2_control();
extern void special2_init();
extern void special1_end();
extern void special1_control();
extern void special1_init();
extern void richcut3_control();
extern void richcut3_end();
extern void richcut3_init();
extern void richcut2_control();
extern void richcut2_end();
extern void richcut2_init();
extern void richcut1_control();
extern void richcut1_end();
extern void richcut1_init();
extern void cranecut_control();
extern void cranecut_end();
extern void cranecut_init();
extern struct ITEM_INFO* find_a_fucking_item(int object_number); 
extern void handle_actor_chatting(int speechslot, int node, int slot, int objslot, short* ranges);
extern void handle_lara_chatting(short* ranges);
extern void DelsHandyTeleportLara(int x, int y, int z, int yrot);
extern void init_resident_cutseq(int num);
extern void init_cutseq_actors(char* data, int resident);
extern int Load_and_Init_Cutseq(int num);
extern struct ITEM_INFO* cutseq_restore_item(int num);
extern void cutseq_kill_item(int num);
extern void deal_with_pistols(unsigned short* shootdata);
extern void trigger_weapon_dynamics(int left_or_right);
extern void cutseq_shoot_pistols(int left_or_right);
extern void cutseq_removelara_hk();
extern void cutseq_givelara_hk();
extern void cutseq_removelara_pistols();
extern void cutseq_givelara_pistols();
extern void CalculateObjectLightingLaraCutSeq();
extern void finish_cutseq(int name);
extern void* cutseq_malloc(int size);
extern void init_cutseq_malloc();
extern void frigup_lara();
extern void InitPackNodes(struct NODELOADHEADER* lnode, struct PACKNODE* pnode, char* packed, int numnodes);
extern void do_new_cutscene_camera();
extern void handle_cutseq_triggering(int name);
extern void GrabActorMatrix(int actornum, int nodenum, struct MATRIX3D* matrix);
extern void TriggerUnderwaterBlood(int x, int y, int z, int sizeme);
extern void triggerwindowsmash(int item_num);
extern void resetwindowsmash(int item_num);
extern void ResetCutItem(int item_num);

#endif