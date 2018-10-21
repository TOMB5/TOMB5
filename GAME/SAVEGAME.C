#include "SAVEGAME.H"

#include "CONTROL.H"
#include "GAMEFLOW.H"
#include "ITEMS.H"
#include "MALLOC.H"

#include "SPECIFIC.H"
#include "SWITCH.H"
#include "TRAPS.H"
#include "TYPES.H"

#ifdef PC_VERSION
#include "GLOBAL.H"
#include "FILE.H"
#include "GAME.H"
#else
#include "SETUP.H"
#include "ROOMLOAD.H"
#endif

#include <stdio.h>
#include <string.h>
#include "NEWINV2.H"
#include "DRAW.H"
#include "CAMERA.H"
#include "SPOTCAM.H"
#include "LARA.H"

char FromTitle = 0; // offset 0xA14AC
char JustLoaded = 0; // offset 0xA14AD
char *MGSaveGamePtr; // offset 0xA3924
static int SGcount; // offset 0xA391C
static char *SGpoint; // offset 0xA3920
struct savegame_info savegame;

#define Write(a, b) WriteSG((char*)a, b)

#if PSX_VERSION//@HACK not really needed, can just take int.
	typedef int ptrdiff_t;
#endif

void sgRestoreGame()//55B88, 55FEC (F)
{
	SGcount = 0;
	SGpoint = &MGSaveGamePtr[sizeof(struct savegame_info)];
	GameTimer = savegame.Game.Timer;
	gfCurrentLevel = savegame.CurrentLevel;

	RestoreLevelData(1);
	RestoreLaraData(1);
}

void sgSaveGame()//55AF8(<), 55F5C(<)
{
	SGpoint = &MGSaveGamePtr[sizeof(struct savegame_info)];
	SGcount = 0;

	savegame.Game.Timer = GameTimer;
	savegame.CurrentLevel = gfCurrentLevel;

	SaveLevelData(1);
	SaveLaraData();

	MGSaveGamePtr[7678] = GetRandomControl();
	
	memcpy(&MGSaveGamePtr, &savegame, sizeof(struct savegame_info));
	savegame.Checksum = GameTimer;

	return;
}

void RestoreLevelData(int FullSave)//54B08, 54F6C
{
	UNIMPLEMENTED();
}

void WriteSG(char* pointer, int size)//536A0, 53B04 (F)
{
	SGcount += size;

	if (size > 0)
	{
		while (size-- > 0)
		{
			*SGpoint++ = *pointer++;
		}
	}
}

void SaveLevelData(int FullSave)//53AAC, 53F10
{
#if PC_VERSION
	int i;
	short word = 0;
	unsigned char byte = 0;

	Write(&FmvSceneTriggered, 4);
	Write(&GLOBAL_lastinvitem, 4);

	for(i = 0; i < 10; i++)
	{
		if (flip_stats[i])
			word |= 1 << i;
	}
	Write(&word, 2);

	for(i = 0; i < 10; i++)
	{
		word = flipmap[i] >> 8;
		Write(&word, 2);
	}

	Write(&flipeffect, 4);
	Write(&fliptimer, 4);
	Write(&flip_status, 4);
	Write(cd_flags, 136);
	Write(&CurrentAtmosphere, 1);

	word = 0;
	if (number_rooms > 0)
	{
		int k = 0;
		for(i = 0; i < number_rooms; i++)
		{
			int j;		
			for (j = 0; j < room[i].num_meshes; j++)
			{
				if (room[i].mesh[j].static_number >= 50 && room[i].mesh[j].static_number <= 59)
				{
					word |= (room[i].mesh[j].Flags & 1) << k++;

					if (k == 16)
					{
						Write(&word, 2);
						k = 0;
						word = 0;
					}
				}
			}
		}

		if (k != 0)
			Write(&word, 2);
	}

	Write(&CurrentSequence, 1);

	byte = 0;
	for (i = 0; i < 6; i++)
	{
		byte |= SequenceUsed[i] << i;
	}
	Write(&byte, 1);

	for (i = 0; i < number_cameras; i++)
	{
		Write(&camera.fixed[i].flags, 2);
	}

	for(i = 0; i < number_spotcams; i++)
	{
		Write(&SpotCam[i].flags, 2);
	}
	
	struct ITEM_INFO* item = &items[0];
	for(i = 0; i < level_items; i++, item++)
	{
		struct object_info* obj = &objects[item->object_number];

		if (item->flags & IFLAG_KILLED)
		{
			word = 0x2000;
			Write(&word, 2);
		}
		else if (item->flags & (IFLAG_ACTIVATION_MASK | IFLAG_INVISIBLE | 0x20) || item->object_number == LARA && FullSave)
		{
			word = 0x8000;

			if (item->pos.x_rot != 0)
				word |= 1;

			if (item->pos.z_rot != 0)
				word |= 2;

			if (item->pos.x_pos & 1)
				word |= 4;

			if (item->pos.y_pos & 1)
				word |= 8;

			if (item->pos.z_pos & 1)
				word |= 0x10;

			if (item->speed != 0)
				word |= 0x20;

			if (item->fallspeed != 0)
				word |= 0x40;

			if (item->item_flags[0])
				word |= 0x80;

			if (item->item_flags[1])
				word |= 0x100;

			if (item->item_flags[2])
				word |= 0x200;

			if (item->item_flags[3])
				word |= 0x400;

			if (item->timer)
				word |= 0x800;

			if (item->trigger_flags)
				word |= 0x1000;

			if (obj->save_hitpoints)
				word |= 0x4000;

			if (obj->save_position)
			{
				short packed = item->pos.x_pos >> 1;
				Write(&packed, 2);
				packed = item->pos.y_pos >> 1;
				Write(&packed, 2);
				packed = item->pos.z_pos >> 1;
				Write(&packed, 2);

				Write(&item->room_number, 1);

				Write(&item->pos.y_rot, 2);

				if (word & 1)
					Write(&item->pos.x_rot, 2);
				if (word & 2)
					Write(&item->pos.z_rot, 2);
				if (word & 0x20)
					Write(&item->speed, 2);
				if (word & 0x40)
					Write(&item->fallspeed, 2);
			}

			if (obj->save_anim)
			{
				Write(&item->current_anim_state, 2);
				Write(&item->goal_anim_state, 2);
				Write(&item->required_anim_state, 2);

				if (item->object_number == LARA)
				{
					Write(&item->anim_number, 2);
				}
				else
				{
					byte = item->anim_number - obj->anim_index;
					Write(&byte, 1);
				}

				Write(&item->frame_number, 2);
			}

			if (word & 0x4000)
				Write(&item->hit_points, 2);

			if (obj->save_flags)
			{
				//int x = item->flags | ((*(unsigned long*)&item->active & 0x7FFF) << 16);
			}
		}

	}

#else
	// todo check for psx
	UNIMPLEMENTED();
#endif
}

void RestoreLaraData(int FullSave)//538D0(<), 53D34(<) (F)
{
	struct ITEM_INFO* item;
	char flag;
	int i;

	if (!FullSave)
	{
		savegame.Lara.item_number = lara.item_number;
		if (savegame.Lara.IsMoving)
		{
			savegame.Lara.IsMoving = 0;
			savegame.Lara.gun_status = LG_NO_ARMS;
		}
	}
	memcpy(&lara, &savegame.Lara, sizeof(struct lara_info));
	lara.target = NULL;
	lara.spaz_effect = NULL;
	lara.right_arm.frame_base = (short*)((char*)lara.right_arm.frame_base + (ptrdiff_t)objects[PISTOLS_ANIM].frame_base);
	lara.left_arm.frame_base = (short*)((char *)lara.left_arm.frame_base + (ptrdiff_t)objects[PISTOLS_ANIM].frame_base);
	lara.GeneralPtr = (char *)lara.GeneralPtr + (ptrdiff_t)malloc_buffer;
	if (lara.burn)
	{
		lara.burn = 0;
		flag = 0;
		if (lara.BurnSmoke)
		{
			lara.BurnSmoke = 0;
			flag = 1;
		}
		LaraBurn();
		if (flag)
		{
			lara.BurnSmoke = 1;
		}
	}
	if (lara.weapon_item != -1)
	{
		lara.weapon_item = CreateItem();
		item = &items[lara.weapon_item];
		item->object_number = savegame.WeaponObject;
		item->anim_number = savegame.WeaponAnim;
		item->frame_number = savegame.WeaponFrame;
		item->current_anim_state = savegame.WeaponCurrent;
		item->goal_anim_state = savegame.WeaponGoal;
		item->status = ITEM_ACTIVE;
		item->room_number = 255;
	}
	
	for (i = 0; i < 15; i++)
	{
		lara.mesh_ptrs[i] = (short*)((char*)mesh_base + (ptrdiff_t)lara.mesh_ptrs[i]);
	}

	_CutSceneTriggered1 = savegame.CutSceneTriggered1;
	_CutSceneTriggered2 = savegame.CutSceneTriggered2;
}

void SaveLaraData()//53738(<), 53B9C(<) (F)
{
	struct ITEM_INFO* item;
	int i;

	for (i = 0; i < 15; i++)
	{
		lara.mesh_ptrs[i] = (short*)((char*)lara.mesh_ptrs[i] - (ptrdiff_t)mesh_base);
	}

	lara.left_arm.frame_base = (short*)((char *)lara.left_arm.frame_base - (ptrdiff_t)objects[PISTOLS_ANIM].frame_base);
	lara.right_arm.frame_base = (short*)((char *)lara.right_arm.frame_base - (ptrdiff_t)objects[PISTOLS_ANIM].frame_base);
	lara.GeneralPtr = (char *)lara.GeneralPtr - (ptrdiff_t)malloc_buffer;
	memcpy(&savegame.Lara, &lara, sizeof(savegame.Lara));
	
	for (i = 0; i < 15; i++)
	{
		lara.mesh_ptrs[i] = (short*)((char*)mesh_base + (ptrdiff_t)lara.mesh_ptrs[i]);
	}

	lara.left_arm.frame_base = (short*)((char *)lara.left_arm.frame_base + (ptrdiff_t)objects[PISTOLS_ANIM].frame_base);
	lara.right_arm.frame_base = (short*)((char *)lara.right_arm.frame_base + (ptrdiff_t)objects[PISTOLS_ANIM].frame_base);
	lara.GeneralPtr = (char *)lara.GeneralPtr + (ptrdiff_t)malloc_buffer;

	if (lara.weapon_item == -1)
	{
		savegame.CutSceneTriggered1 = _CutSceneTriggered1;
		savegame.CutSceneTriggered2 = _CutSceneTriggered2;
	}
	else
	{
		item = &items[lara.weapon_item];
		savegame.WeaponObject = item->object_number;
		savegame.WeaponAnim = item->anim_number;
		savegame.WeaponFrame = item->frame_number;
		savegame.WeaponCurrent = item->current_anim_state;
		savegame.WeaponGoal = item->goal_anim_state;
		savegame.CutSceneTriggered1 = _CutSceneTriggered1;
		savegame.CutSceneTriggered2 = _CutSceneTriggered2;
	}
}

int CheckSumValid(char* buffer)//53720(<), 53B84(<) (F)
{
	return *(short*)buffer ^ *(short*)(buffer + 0x1DFE) < 1;
}

void ReadSG(char* pointer, int size)//536E0, 53B44 (F)
{
	SGcount += size;
	
	if (size > 0)
	{
		while (size-- > 0)
		{
			*pointer++ = *SGpoint++;
		}
	}

	return;
}

