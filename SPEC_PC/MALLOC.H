#ifndef MALLOC_H
#define MALLOC_H

extern void init_game_malloc();
extern char* game_malloc(int size);
extern void game_free(int size);
extern void show_game_malloc_totals();
extern void dump_game_malloc();

extern char* malloc_ptr;
extern int malloc_used;
extern int malloc_free;
extern int script_malloc_size;
extern char* malloc_buffer;

#endif