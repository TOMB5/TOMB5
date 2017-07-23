#ifndef CD_H
#define CD_H

void cbvsync();
void InitNewCDSystem();
void S_CDPlay(short track, int mode);

extern unsigned short XATrackClip[136];
extern short XAFadeRate;
extern int current_cd_mode;
extern int XACurPos;
extern int XAEndPos;
extern short XAVolume;
extern short XAReqVolume;
extern short XAMasterVolume;
extern short XATrack;
extern short XAReqTrack;
extern char XAFlag;
extern char XAWait;
extern int XAStartPos;

#define CD_SECTOR_SIZE (2048)

#endif