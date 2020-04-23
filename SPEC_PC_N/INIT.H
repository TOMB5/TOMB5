#ifndef INIT_H
#define INIT_H

#include "TYPES.H"

void init_water_table();

extern WATERTAB WaterTable[22][64];
#ifdef __cplusplus
//extern "C" {
#endif

extern char* malloc_buffer;
extern int malloc_size;
extern char* malloc_ptr;
extern int malloc_used, malloc_free;

extern void* game_malloc(int size);

extern void game_free(int size);

extern void init_game_malloc();

extern void show_game_malloc_totals(void);


#ifdef __cplusplus
//}
#endif

#endif