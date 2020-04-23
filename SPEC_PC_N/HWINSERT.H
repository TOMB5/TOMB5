#ifndef _HWINSERT_H_
#define _HWINSERT_H_

#include "INCLUDE.H"

#ifdef __cplusplus
extern "C" {
#endif


#define VERTSPERBUCKET    2080
#define MAXBUCKETS        30
struct TEXTUREBUCKET
{
	int tpage;
	int cnt;
	D3DTLBUMPVERTEX Vertex[VERTSPERBUCKET];
};

extern TEXTUREBUCKET Bucket[];


void InitBuckets();
void DrawBuckets();
void FindBucket(uint16_t tile, D3DTLBUMPVERTEX** vptr, int** cntptr);
void DrawBucket(TEXTUREBUCKET* buk);

#ifdef __cplusplus
}
#endif


#endif