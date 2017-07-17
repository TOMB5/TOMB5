#include "DELTAPAK.H"

#include "SPECIFIC.H"

struct CUTSEQ_ROUTINES cutseq_control_routines[45];
unsigned short crane_pistols_info[11];
unsigned short craneguard_pistols_info[7];
short admiral_chat_ranges_joby2[12];
short sergie_chat_ranges_joby2[8];
short lara_chat_ranges_joby3[6];
short lara_chat_ranges_joby4[10];
short admiral_chat_ranges_joby4[20];
unsigned short larson_pistols_info1[2];
short lara_chat_ranges_andrea1[4];
short larson_chat_ranges1[12];
short pierre_chat_ranges1[30];
short lara_chat_ranges_andrea2[32];
short larson_chat_ranges2[8];
short pierre_chat_ranges2[34];
short admiral_chat_ranges_joby5[18];
short sergie_chat_ranges_joby5[20];
short lara_chat_ranges_joby9[12];
short admiral_chat_ranges_joby9[36];
short lara_chat_ranges_joby10[12];
short admiral_chat_ranges_joby10[42];
unsigned short andrea3_pistols_info[5];
short lara_chat_ranges_andrea3[14];
short larson_chat_ranges3[14];
short lara_chat_ranges_andrea3b[12];
short larson_chat_ranges3b[4];
short priest_chat_ranges_andy7[32];
short lara_chat_ranges_andy7[14];
short lara_chat_ranges_joby7[10];
short lara_chat_ranges_andrea4[22];
short pierre_chat_ranges4[48];
int cuntercunter;
char jobyfrigger;
int cutrot;
int GLOBAL_playing_cutseq;
int cutseq_trig;
int cutseq_num;
unsigned char disable_horizon;
char cutseq_busy_timeout;
short frig_shadow_bbox[6];
int cut_seethrough;
char lara_chat_cnt;
char actor_chat_cnt;
struct NEW_CUTSCENE* GLOBAL_cutme;
int lastcamnum;
int GLOBAL_cutseq_frame;
int GLOBAL_numcutseq_frames;
int GLOBAL_oldcamtype;
struct PACKNODE* camera_pnodes;
struct PACKNODE* actor_pnodes[10];
struct ITEM_INFO duff_item;
int numnailed;
char old_status_flags[32];
unsigned short old_status_flags2[32];
unsigned long cutseq_meshbits[10];
unsigned long cutseq_meshswapbits[10];
struct RESIDENT_THING cutseq_resident_addresses[47];
char* GLOBAL_resident_depack_buffers;
int cutseq_malloc_used;
char* cutseq_malloc_ptr;
int cutseq_malloc_free;
unsigned short old_lara_holster;
short temp_rotation_buffer[160];

void trigger_title_spotcam(int num)
{
	S_Warn("[trigger_title_spotcam] - Unimplemented!\n");
}

void handle_cutseq_triggering(int name)
{
	S_Warn("[trigger_title_spotcam] - Unimplemented!\n");
}