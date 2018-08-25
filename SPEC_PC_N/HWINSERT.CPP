#include "HWINSERT.H"

TEXTUREBUCKET Bucket[MAXBUCKETS];

void InitBuckets()
{
	for (int n = 0; n < MAXBUCKETS; n++)
	{
		Bucket[n].tpage = 0xffffffff;
		Bucket[n].cnt = 0;
	}
}