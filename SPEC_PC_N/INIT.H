#ifndef INIT_H
#define INIT_H

#ifdef __cplusplus
extern "C" {
#endif

	void *game_malloc(int size);
	void game_free(int size);
	void init_game_malloc();
	void show_game_malloc_totals(void);


#ifdef __cplusplus
}
#endif

#endif