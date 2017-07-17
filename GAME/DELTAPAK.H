#ifndef DELTAPAK_H
#define DELTAPAK_H

#include "ITEMS.H"

struct RESIDENT_THING
{
	char* packed_data;
};

struct CUTSEQ_ROUTINES
{
	void(*init_func)();
	void(*control_func)();
	void(*end_func)();
};

struct ACTORME
{
	int offset;
	short objslot;
	short nodes;
};

struct NEW_CUTSCENE
{
	short numactors;
	short numframes;
	int orgx;
	int orgy;
	int orgz;
	int audio_track;
	int camera_offset;
	struct ACTORME actor_data[10];
};

struct RTDECODE
{
	unsigned long length;
	unsigned long off;
	unsigned short counter;
	unsigned short data;
	unsigned char decodetype;
	unsigned char packmethod;
	unsigned short padfuck;
};

struct PACKNODE
{
	short xrot_run;
	short yrot_run;
	short zrot_run;
	short xkey;
	short ykey;
	short zkey;
	struct RTDECODE decode_x;
	struct RTDECODE decode_y;
	struct RTDECODE decode_z;
	unsigned long xlength;
	unsigned long ylength;
	unsigned long zlength;
	char* xpacked;
	char* ypacked;
	char* zpacked;
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
extern int GLOBAL_oldcamtype;
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

void trigger_title_spotcam(int num);
void handle_cutseq_triggering(int name);

#endif