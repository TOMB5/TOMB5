#include "DELTAPAK.H"

#include "CD.H"
#include "CONTROL.H"
#include "DRAW.H"
#include "GAMEFLOW.H"
#include "ITEMS.H"
#include "LARA.H"
#include "OBJECTS.H"
#include "PROFILE.H"
#include "SETUP.H"
#include "SPECIFIC.H"
#include "SPOTCAM.H"
#include "TOMB4FX.H"

#include <assert.h>
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

enum title_spotcam_sequences
{
	NONE,
	OUTSIDE_CHURCH_SEQUENCE,
	INSIDE_CHURCH_SEQUENCE,
	HOUSE_SEQUENCE,
	PYRAMID_SEQUENCE
};

void trigger_title_spotcam(int num)//32904(<), 32D9C(<)
{
	struct ITEM_INFO* item;

	jobyfrigger = 0;

	if (num == OUTSIDE_CHURCH_SEQUENCE)
	{
		/*
		 * Resetting all outside church sequence animatings to their original positions/animations.
		 */
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

	}
	else if (num == PYRAMID_SEQUENCE)
	{
		/*
		 * Resetting all pyramid sequence animatings to their original positions/animations.
		 */
		jobyfrigger = 1;

		//Stone slab being pulled on slope outside pyramid entrance.
		ResetCutanimate(ANIMATING4);

		//Jeep
		item = ResetCutanimate(ANIMATING7);
		item->pos.x_pos = SECTOR_TO_WORLD(31);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(88);
		item->room_number = 104;

		//Jeep
		ResetCutanimate(ANIMATING8);

		//Tomb Raider 4 Guide
		item = ResetCutanimate(ANIMATING9);
		item->pos.x_pos = SECTOR_TO_WORLD(30);
		item->pos.y_pos = SECTOR_TO_WORLD(0);
		item->pos.z_pos = SECTOR_TO_WORLD(89);
		item->room_number = 61;

		//Voncroy
		ResetCutanimate(ANIMATING12);

		//Tomb Raider 4 guides pulling stone slab (ANIMATING4).
		ResetCutanimate(ANIMATING13);
		ResetCutanimate(ANIMATING14);
		ResetCutanimate(ANIMATING15);

	}//0x32A00

	/*
	 * Each flyby sequence should play it's own unique music.
	 * Here we alter the music for the current flyby sequence.
	 */
	if (num == OUTSIDE_CHURCH_SEQUENCE)
	{
#ifdef INTERNAL//second arg is prob a def.
		S_CDPlay(83, 1);
#else
		S_CDPlay(83, 0);
#endif
	}
	else if (num == INSIDE_CHURCH_SEQUENCE)
	{
#ifdef INTERNAL
		S_CDPlay(87, 1);
#else
		S_CDPlay(87, 0);
#endif
	}
	else if (num == HOUSE_SEQUENCE)
	{
#ifdef INTERNAL
		S_CDPlay(86, 1);
#else
		S_CDPlay(86, 0);
#endif
	}
	else if (num == PYRAMID_SEQUENCE)
	{
#ifdef INTERNAL
		S_CDPlay(91, 1);
#else
		S_CDPlay(91, 0);
#endif
	}

	InitialiseSpotCam(num);

}//32968

struct ITEM_INFO* ResetCutanimate(int objnum)//32A80, 32F18
{
#if 1
	struct ITEM_INFO* item; // $s1

	item = find_a_fucking_item(objnum);

	item->anim_number = *(short*) &objects[(objnum << 6) + 38];//0x237, basically objects[objnum]+38
	item->frame_number = anims[item->anim_number].frame_base;
	RemoveActiveItem((int) (item - &items[0]));//index into items passed?

	item->flags &= 0xC1FF;
#if 0
	int test = *(int*) item->active;
	test &= -7;
	*(int*) item->active = test;
#endif
#endif
	return item;
}

void handle_cutseq_triggering(int name)//2C3C4, 2C6EC
{
	int s1 = name;//guessed, moved but not used
	
	if (cutseq_num == 0)
	{
		int a1 = 0;//Must confirm initial value.
		if (cutseq_trig == 0)
		{
			if (lara.gun_status == 0)
			{
				if (lara.gun_type == 7)
				{
					a1 = -1;
				}//loc_2C448
			}
			else
			{
				//loc_2C41C
				if (lara.gun_type != 1)
				{
					lara.gun_status = 3;
				}

				//loc_2C430
				if (lara.gun_status != 1)
				{
					lara.gun_status = 3;
				}

				//loc_2C444
				a1 = -1;
			}

			//loc_2C448
			//loc_2C454
			for (int i = 0; i < 9; i++)//TODO const
			{
				cutseq_meshswapbits[i] = 0;
				cutseq_meshbits[i] = a1;
			}

			cutseq_trig = 1;
			cutseq_busy_timeout = 50;

			//Not title
			if (gfCurrentLevel != 0)
			{
				SetFadeClip(28, 1);
			}

			//loc_2C494
			if (ScreenFadedOut == 0)
			{
				//Not title
				if (gfCurrentLevel != 0)
				{
					XAReqVolume = 0;
				}

				//loc_2C4C8
				SetScreenFadeOut(16, 0);
			}

			//loc_2C4D0
#ifdef INTERNAL
			ProfileDraw = 0;
#endif
		}
		else
		{
			if (cutseq_num == 1)
			{
				struct ITEM_INFO* v00 = lara_item;
				int v1 = ScreenFadedOut;
				int a0 = v00->current_anim_state;
				int a1 = 0;

				if (ScreenFadedOut != 0)
				{
					cutseq_busy_timeout--;

					if ((cutseq_busy_timeout & 0xFF) == 0)
					{
						cutseq_busy_timeout = 0;
						a1 = 1;

					}//j loc_2C588
					else
					{
						//loc_2C52C
						if (lara.gun_status != 1 && lara.gun_status == 0 && lara.flare_control_left != 0)
						{
							//loc_2C55C

							if ((lara_item->current_anim_state - 80) > 2 ||
								(lara_item->current_anim_state - 80) != 84 ||
								(lara_item->current_anim_state - 80) != 85 ||
								(lara_item->current_anim_state - 80) == 86)
							{
								//2C584
								a1 = 1;
							}

						}
						//loc_2C584 - may merge
						a1 = 1;
					}
				}

				//loc_2C588
				if (a1 == 0)
				{
					//loc_2CA50 cpy
					return;
				}

				lara.IsClimbing = 0;
				lara.flare_age = 0;

				if ((gfLevelFlags & 1))
				{

					lara.gun_type = 0;
					lara.request_gun_type = 0;
					lara.last_gun_type = 0;

					if (((*(int*) &objects[0x53B0]) & 1) != 0 && lara.pistols_type_carried != 0)
					{
						//loc_2C5FC
						lara.last_gun_type = 1;
					}
					else
					{
						//loc_2C5F4
						lara.last_gun_type = 0;
					}

					//loc_2C600
					if ((gfLevelFlags & 0x80) != 0)
					{
						if (((*(int*) &objects[0x5670]) & 0x10000) != 0)
						{
							if ((objects[0x5670 + 0x121] & 1) != 0)
							{
								int v0000 = 5;
								///TODO:
								assert(0);
							}//loc_2C644
						}//loc_2C648

					}//loc_2C644

					//assert(0);//intentional, not finished!
					S_Warn("[handle_cutseq_triggering] - Unimplemented condition! loc_2C644\n");

				}//loc_2C6E4

			}//loc_2C79C
			
			if (gfCurrentLevel != 3)
			{
				//2C7DC
				if (gfCurrentLevel == 4 && ScreenFadedOut != 0)
				{
					if (gfCurrentLevel != 0)
					{
						S_CDStop();

					}//loc_2C818

					//loc_2C818
					assert(0);//Data is malformed in IDA output, also jalr	$v0 must be debugged on emu.

				}//loc_2CA50

			}///@CHECK does jump to loc_2CA50 at end?
			else
			{
				SetScreenFadeOut(16, 1);

				if (gfCurrentLevel != 0)
				{
					XAReqVolume = 0;
				}//loc_2C7D0

				//loc_2C7D0
				cutseq_trig = 4;
			}//loc_2CA50
		}
	}
	return;
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