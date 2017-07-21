#include "DELTAPAK.H"

#include "CONTROL.H"
#include "ITEMS.H"
#include "OBJECTS.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"

#include <stddef.h>

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

#define WORLD_UNITS_PER_SECTOR 1024
#define SECTOR_TO_WORLD(S) ((S) > (0) ? ((S * WORLD_UNITS_PER_SECTOR) + (WORLD_UNITS_PER_SECTOR / 2)) : (0))

void trigger_title_spotcam(int num)//32904, 32D9C
{
	struct ITEM_INFO* item;//v0
	int s2 = num;

	jobyfrigger = 0;
	int v0 = 4;

	if (num == 1)//Church seq
	{
		//Man holding umbrella at church area (TITLE.TRC)
		item = ResetCutanimate(ANIMATING10);

		item->pos.x_pos = SECTOR_TO_WORLD(58);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(41);
		item->room_number = 0;

		//Female walking with man holding umbrella, church area (TITLE.TRC)
		item = ResetCutanimate(ANIMATING11);
		item->pos.x_pos = SECTOR_TO_WORLD(58);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(41);
		item->room_number = 0;

		v0 = 2;
		if (num == 1)
		{
			int a0 = 83;
			int a1 = 0;
			//S_CDPlay(short track /*$s0*/, int mode /*$s1*/);

			if (s2 == 2)//0x32EB0(r)
			{
				S_Warn("[trigger_title_spotcam] - Unimplemented condition!\n");
			}//0x32EC8(r)

			if (s2 == 3)//0x32EC8
			{
				S_Warn("[trigger_title_spotcam] - Unimplemented condition!\n");
			}//032EE0

			if (s2 == 4)
			{
				S_Warn("[trigger_title_spotcam] - Unimplemented condition!\n");
			}

			a0 = s2 << 0x10;
			a0 >>= 0x10;
			InitialiseSpotCam(a0);


		}//0x32A18

	}//32968

		
	
}

struct ITEM_INFO* ResetCutanimate(int objnum)//32A80, 32F18
{
#if 1
	struct ITEM_INFO* item; // $s1

	int a0 = objnum;//guessed
	int s0 = a0;

	item = find_a_fucking_item(objnum);

	//actually probably a table storing all initial item anims/frames?
	//char* a00 = &objects[0]; //FIXME needs init
	s0 <<= 6;
	//char* s00 = &objects[s0];

	//s1 = v0;//?
	//v1 = s0[0x26];
	//v0 = &anims[0];
	//a2 = &items[0];
	//s1[0x14] = v1;//short store
	//v1 <<= 16;
	//v1 >>=16;
	//a1 = v1 << 2;
	//a1 += v1;
	//a1 <<= 3;
	//a1 += v0;
	//a2 = s1 - a2;
	//v0 = a2 << 3;
	//v0 -= a2;
	//v1 = v0 << 6;
	//v0 += v1;
	//v0 <<= 3;
	//v0 += a2;
	//a0 = v0 << 15;
	//a0 -= v0;
	//a0 <<= 3;
	//a0 += a2;
	//a0 <<= 12;
	//v0 = a1[0x18]//short
	//a0 >>= 16;
	//s1[0x16] = v0; //store half
	RemoveActiveItem(0);
	//v0 = s1;
	//v1 = s1[0x28]//half
	//a0 = s1[0x84]//word
	//v1 &= 0xC1FF;
	//s1[0x28] = v1;//half
	//v1 = -7;
	//a0 &= v1;
	//s1[0x84] = a0//word
#endif
	return item;
}

void handle_cutseq_triggering(int name)//2C3C4, 2C6EC
{
	S_Warn("[handle_cutseq_triggering] - Unimplemented!\n");
}


struct ITEM_INFO* find_a_fucking_item(int object_number)//2DF50(<), 2E1E0(<)
{
	int i;

	if (level_items > 0)
	{
		for (i = 0; i < level_items; i++)
		{
			if (items[i].object_number == object_number)
			{
				return &items[i];
			}
		}
	}

	return NULL;
}