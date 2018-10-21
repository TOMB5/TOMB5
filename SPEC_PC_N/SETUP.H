#ifndef SETUP_H
#define SETUP_H

#include "GLOBAL.H"

typedef struct
{
	int GraphicsAdapter;
	bool OpenSetup;
	bool NoFMV;
	bool LowQualityTextures;
	bool LowQualityBumpMap;
	bool VolumetricFog;
} Settings;

enum ControlMethod
{
	CM_KEYBOARD = 0,
	CM_JOYSTICK = 1
};

extern Settings appsettings;;
extern int16_t opt_JDck;
extern int16_t opt_JDsh;
extern int16_t opt_JWlk;
extern int16_t opt_JJmp;
extern int16_t opt_JAct;
extern int16_t opt_JDrw;
extern int16_t opt_JFlr;
extern int16_t opt_JLok;
extern int16_t opt_JRol;
extern int16_t opt_JInv;
extern uint8_t opt_MusicVolume;
extern uint8_t opt_SFXVolume;
extern uint8_t opt_ControlMethod;
extern uint8_t opt_SoundQuality;

bool InitSetupDialog();
void SaveSettings();
bool LoadSettings();

#endif