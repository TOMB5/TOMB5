#ifndef SPECIFIC_H
#define SPECIFIC_H
#include <windows.h>
#include <stdio.h>
#include "SPECTYPES.H"
#include <stdint.h>

#define UNIMPLEMENTED() printf("[%s] - Unimplemented!\n", __func__);

struct _RTL_CRITICAL_SECTION CriticalSection;

extern void S_Warn(const char* warning_message);

extern HWND Log(char a1, char* format, ...);
extern void S_SetReverbType(int reverb);
extern signed int __cdecl sub_4D30E0(_WORD *a1);
extern char TIME_Init();
extern inline void memset32(void* buf, uint32_t n, int32_t c);
extern int S_SoundStopAllSamples();
extern int sub_4D1A40();
extern char __cdecl Decompress(void* buf, void* compressed, int compSize, int uncompSize);
extern void DisplayStatsUCunt();
extern BYTE* bufSource;
extern void* ptr;
extern HANDLE Handles;
extern HANDLE dword_579FA4;
extern int XATrack;
extern void* dword_579FD4;
extern BYTE byte_579FE4;
extern DWORD dword_579FD8;
extern DWORD dword_579E4C;
extern BYTE byte_57A01C;
extern FILE* stream;
extern DWORD dword_579E30;
extern DWORD dword_57A018;
extern DWORD dword_510B18;
extern __int64 qword_D9AAB0;
extern unsigned short *AnimTextureRanges; // offset 0xA4670
extern unsigned short nAnimUVRanges; // offset 0xA4660
#endif