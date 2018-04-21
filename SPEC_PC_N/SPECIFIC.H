#ifndef SPECIFIC_H
#define SPECIFIC_H

#include "SPECTYPES.H"

extern char			cd_drive;

#ifdef __cplusplus
extern "C" {
#endif

extern void S_Warn(const char* warning_message, ...);

extern void S_CDPlay(sint16 track, int mode);
extern void S_SetReverbType(sint16 reverb);

#ifdef __cplusplus
}
#endif

#endif