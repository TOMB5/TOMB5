#ifndef STYPES_H
#define STYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*** log types for game/specific stuff ***/
#define LT_Default			(char*)0
#define LT_Enter			(char*)2
//#define LT_Exit				(char*)1
#define LT_Release			(char*)3
#define LT_Info				(char*)5
//#define LT_WindowMessage	(char*)5
#define LT_DXTry			(char*)6
#define LT_Error			(char*)1
#define LT_Warning			(char*)8
#define LT_Version			(char*)9
#define LT_Texture			(char*)10	// crappy temporary texture loading messages
#define LT_Sound			(char*)11	// sample info

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
