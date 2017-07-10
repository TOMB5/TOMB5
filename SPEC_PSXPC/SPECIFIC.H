#ifndef SPECIFIC_H
#define SPECIFIC_H

struct REQUESTER
{
	unsigned short TitleTxt;
	unsigned short TitleCol : 5;
	unsigned short nOptions : 3;
	unsigned short CursorPos : 3;
	unsigned short OptionCol : 5;
	unsigned long JustifyL : 5;
	unsigned long JustifyR : 5;
	unsigned long Arrows : 5;
	unsigned long Ignore : 5;
	unsigned short OptionTxt[5];
};

extern unsigned short AnimComp;
extern short AnimatingTexturesVOffset;
extern struct REQUESTER SettingsReq;
extern struct REQUESTER ConfigReq;
extern unsigned char SoundFXVolume;
extern unsigned short nAnimTextureRanges;
extern unsigned short *AnimTextureRanges;
extern unsigned short nAnimUVRanges;
extern int GtSFXEnabled;
extern short AnimatingTexturesV[16][8][3];

void S_SoundStopAllSamples();
void S_ExitSystem(char* exit_message);

#endif