#ifndef STYPES_H
#define STYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*** log types for game/specific stuff ***/
#define LT_Default			0
#define LT_Enter			2
//#define LT_Exit				(char*)1
#define LT_DXShit			3
#define LT_Release			4
#define LT_Info				5
#define LT_WindowMessage	6
#define LT_Status			7
#define LT_Error			1
#define LT_Warning			????
#define LT_Version			9
#define LT_Texture			10	// crappy temporary texture loading messages
#define LT_Sound			8	// sample info

#define S_MemSet(A,B,C) 		memset(A,B,C)
#define S_MemCpy(A,B,C) 		memcpy(A,B,C)
#define S_LongMemCpy(A,B,C)		memcpy(A,B,C*4)

typedef unsigned short ushort;
typedef unsigned char uchar;

#define mSqrt phd_sqrt

#ifdef __cplusplus
}
#endif

#endif
