#ifndef MALLOC_H
#define MALLOC_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;
#endif

#ifndef NULL
#define NULL 0
#endif

extern void InitHeap(unsigned long* unk00, unsigned long unk01);
/*extern void free(void* unk00);
extern void* malloc(size_t unk00);
extern void* calloc(size_t unk00, size_t unk01);
extern void* realloc(void* unk00, size_t unk01);*/
extern void InitHeap2(unsigned long* unk00, unsigned long unk01);
extern void free2(void* unk00);
extern void* malloc2(size_t unk00);
extern void* calloc2(size_t unk00, size_t unk01);
extern void* realloc2(void* unk00, size_t unk01);
extern void InitHeap3(unsigned long* unk00, unsigned long unk01);
extern void free3(void* unk00);
extern void* malloc3(size_t unk00);
extern void* calloc3(size_t unk00, size_t unk01);
extern void* realloc3(void* unk00, size_t unk01);

#endif