#ifndef LOT_H
#define LOT_H

#include "CAMERA.H"
#include "ITEMS.H"

enum zone_type
{
	SKELLY_ZONE = 0,
	BASIC_ZONE  = 1,
	CROC_ZONE   = 2,
	HUMAN_ZONE  = 3,
	FLYER_ZONE  = 4
};

enum mood_type
{
	BORED_MOOD  = 0,
	ATTACK_MOOD = 1,
	ESCAPE_MOOD = 2,
	STALK_MOOD  = 3
};

struct AIOBJECT
{
	short object_number;
	short room_number;
	long x;
	long y;
	long z;
	short trigger_flags;
	short flags;
	short y_rot;
	short box_number;
};

struct lot_info
{
	struct box_node* node;
	short head;
	short tail;
	unsigned short search_number;
	unsigned short block_mask;
	short step;
	short drop;
	short zone_count;
	short target_box;
	short required_box;
	short fly;
	unsigned short can_jump : 1;
	unsigned short can_monkey : 1;
	unsigned short is_amphibious : 1;
	unsigned short is_jumping : 1;
	unsigned short is_monkeying : 1;
	struct PHD_VECTOR target;
	enum zone_type zone;
};

struct creature_info
{
	short joint_rotation[4];
	short maximum_turn;
	short flags;
	unsigned short alerted : 1;
	unsigned short head_left : 1;
	unsigned short head_right : 1;
	unsigned short reached_goal : 1;
	unsigned short hurt_by_lara : 1;
	unsigned short patrol2 : 1;
	unsigned short jump_ahead : 1;
	unsigned short monkey_ahead : 1;
	enum mood_type mood;
	struct ITEM_INFO* enemy;
	struct ITEM_INFO ai_target;
	short pad;
	short item_num;
	struct PHD_VECTOR target;
	struct lot_info LOT;
};

extern int slots_used;
extern short nAIObjects;
extern struct AIOBJECT* AIObjects;
extern struct creature_info* baddie_slots;

void InitialiseSlot(short item_number, int slot);

#endif