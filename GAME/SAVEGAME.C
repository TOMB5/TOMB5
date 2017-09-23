#include "SAVEGAME.H"

#include "CONTROL.H"
#include "GAMEFLOW.H"
#include "ITEMS.H"
#include "MALLOC.H"
#include "ROOMLOAD.H"
#include "SPECIFIC.H"
#include "TRAPS.H"
#include "TYPES.H"


#include <string.h>
#ifdef PC_VERSION
#include "GAME.H"
#else
#include "SETUP.H"
#endif

char FromTitle;
char JustLoaded;
char* MGSaveGamePtr;
static int SGcount;
static char* SGpoint;
struct savegame_info savegame;

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

	savegame.CurrentLevel = gfCurrentLevel;
	SaveLevelData(1);

	savegame.Game.Timer = GameTimer;
	SaveLaraData();

	MGSaveGamePtr[7678] = GetRandomControl();
	
	memcpy(&MGSaveGamePtr, &savegame, sizeof(struct savegame_info));
	savegame.Checksum = GameTimer;

	return;
}

void RestoreLevelData(int FullSave)//54B08, 54F6C
{
	S_Warn("[RestoreLevelData] - Unimplemented!\n");
}

void SaveLevelData(int FullSave)//53AAC, 53F10
{
	S_Warn("[SaveLevelData] - Unimplemented!\n");
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
			savegame.Lara.gun_status = 0;
		}
	}
	memcpy(&lara, &savegame.Lara, sizeof(lara));
	lara.target = NULL;
	lara.spaz_effect = NULL;
	lara.right_arm.frame_base = (short*)((char*)lara.right_arm.frame_base + (unsigned int)objects[PISTOLS_ANIM].frame_base);
	lara.left_arm.frame_base = (short*)((char *)lara.left_arm.frame_base + (unsigned int)objects[PISTOLS_ANIM].frame_base);
	lara.GeneralPtr = (char *)lara.GeneralPtr + (unsigned int)malloc_buffer;
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
		item->status = 1;
		item->room_number = 255;
	}
	
	for (i = 0; i < 15; i++)
	{
		lara.mesh_ptrs[i] = (short*)((char*)mesh_base + (int)lara.mesh_ptrs[i]);
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
		lara.mesh_ptrs[i] = (short*)((char*)lara.mesh_ptrs[i] - (int)mesh_base);
	}

	lara.left_arm.frame_base = (short*)((char *)lara.left_arm.frame_base - (unsigned int)objects[PISTOLS_ANIM].frame_base);
	lara.right_arm.frame_base = (short*)((char *)lara.right_arm.frame_base - (unsigned int)objects[PISTOLS_ANIM].frame_base);
	lara.GeneralPtr = (char *)lara.GeneralPtr - (unsigned int)malloc_buffer;
	memcpy(&savegame.Lara, &lara, sizeof(savegame.Lara));
	
	for (i = 0; i < 15; i++)
	{
		lara.mesh_ptrs[i] = (short*)((char*)mesh_base + (int)lara.mesh_ptrs[i]);
	}

	lara.left_arm.frame_base = (short*)((char *)lara.left_arm.frame_base + (unsigned int)objects[PISTOLS_ANIM].frame_base);
	lara.right_arm.frame_base = (short*)((char *)lara.right_arm.frame_base + (unsigned int)objects[PISTOLS_ANIM].frame_base);
	lara.GeneralPtr = (char *)lara.GeneralPtr + (unsigned int)malloc_buffer;

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

void WriteSG(char* pointer, int size)//536A0, 53B04
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