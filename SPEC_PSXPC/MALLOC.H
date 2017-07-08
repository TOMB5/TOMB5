#ifndef MALLOC_H
#define MALLOC_H

#define GAME_MALLOC_BUFFER_SIZE 1085440

void init_game_malloc();
char* game_malloc(int size);
void game_free(int size);
void show_game_malloc_totals();

extern char* malloc_ptr;
extern int malloc_used;
extern int malloc_free;
extern int script_malloc_size;
extern char malloc_buffer[GAME_MALLOC_BUFFER_SIZE];

void dump_game_malloc();

#endif