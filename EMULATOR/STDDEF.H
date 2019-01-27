#ifndef STDDEF_H
#define STDDEF_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
//typedef unsigned long wchar_t;
#endif

#ifndef _UCHAR_T
#define _UCHAR_T
typedef unsigned char u_char;
#endif

#ifndef _USHORT_T
#define _USHORT_T
typedef unsigned short u_short;
#endif

#ifndef _UINT_T
#define _UINT_T
typedef	unsigned int u_int;
#endif

#ifndef _ULONG_T
#define _ULONG_T
typedef unsigned long u_long;
#endif

#ifndef _PTRDT_T
#define _PTRDT_T
typedef int ptrdiff_t;
#endif

#ifndef WEOF
#define WEOF    0xffffffff
#endif

#ifndef NULL
#define NULL 0
#endif

#endif