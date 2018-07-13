#ifndef INIT_H
#define INIT_H

void	init_water_table();

#ifdef __cplusplus
extern "C" {
#endif

	extern char*	malloc_buffer;
	extern int		malloc_size;
	extern char*	malloc_ptr;
	extern int		malloc_used, malloc_free;

	void *game_malloc(int size);
	void game_free(int size);
	void init_game_malloc();
	void show_game_malloc_totals(void);


#ifdef __cplusplus
}
#endif

#endif