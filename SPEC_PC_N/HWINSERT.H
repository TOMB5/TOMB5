#ifndef _HWINSERT_H_
#define _HWINSERT_H_

#include "INCLUDE.H"

#ifdef __cplusplus
extern "C" {
#endif

	void InitBuckets();
	void DrawBuckets(void *);

#define VERTSPERBUCKET	(1024+32)
#define MAXBUCKETS		73
	struct TEXTUREBUCKET
	{
		DWORD tpage;
		int cnt;
		D3DTLVERTEX Vertex[VERTSPERBUCKET];
	};

	extern TEXTUREBUCKET Bucket[];

#ifdef __cplusplus
}
#endif


#endif