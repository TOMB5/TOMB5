#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "LARA.H"

struct savegame_info
{
	short Checksum;
	unsigned short VolumeCD;
	unsigned short VolumeFX;
	short ScreenX;
	short ScreenY;
	unsigned char ControlOption;
	unsigned char VibrateOn;
	unsigned char AutoTarget;
	struct lara_info Lara;
	struct STATS Level;
	struct STATS Game;
	short WeaponObject;
	short WeaponAnim;
	short WeaponFrame;
	short WeaponCurrent;
	short WeaponGoal;
	unsigned long CutSceneTriggered1;
	unsigned long CutSceneTriggered2;
	char GameComplete;
	unsigned char CurrentLevel;
	unsigned char CampaignSecrets[4];
	unsigned char TLCount;
};

extern char FromTitle;
extern char JustLoaded;
extern char* MGSaveGamePtr;
extern struct savegame_info savegame;

#endif