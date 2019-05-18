#include <cstddef>
#include "CAMERA.H"
#include "INCLUDE.H"
#include "GLOBAL.H"
#include "WINMAIN.H"

#define GAME_MALLOC_BUFFER_SIZE 5000000

char*	malloc_buffer = nullptr;
int		malloc_size;
char*	malloc_ptr;
int		malloc_used, malloc_free;

WATERTAB	WaterTable[22][64];


#ifdef __cplusplus
extern "C" {
#endif

	void init_game_malloc(void)// (F)
	{
		malloc_size = GAME_MALLOC_BUFFER_SIZE;
		malloc_buffer = (char*)malloc(malloc_size);
		malloc_ptr = malloc_buffer;
		malloc_free = malloc_size;
		malloc_used = 0;
#ifdef GAMEDEBUG
		ZeroArray(LanGameMallocTotals);
		Log(LT_Info, "init_game_malloc: size=%dK", malloc_size >> 10);
#endif
	}

	void* game_malloc(int size)// (F)
	{
		char* ptr;

		size = (size + 3) & 0xfffffffc;		// LongWord Align....
		if (size <= malloc_free)
		{
#ifdef GAMEDEBUG
			LanGameMallocTotals[type] += size;
#endif
			ptr = malloc_ptr;
			malloc_free -= size;
			malloc_used += size;
			malloc_ptr += size;
			return ptr;
		}

		Log(LT_Default, "OUT OF MEMORY");
		exit(0);
		return nullptr;	// S_ExitSystem doesn't return...
	}

	void show_game_malloc_totals(void)// (F)
	{
#ifdef GAMEDEBUG
		for (int i = 0; i<NUM_MALLOC_TYPES; ++i)
			Log("%s: %d", game_malloc_strings[i], LanGameMallocTotals[i]);
		Log("malloc_used=%dK; malloc_free=%dK; malloc_size=%dK", malloc_used >> 10, malloc_free >> 10, malloc_size >> 10);
#endif
	}

	void game_free(int size, int type)// (F)
	{
		size = (size + 3)&(~3);		// fuck Fuck FUck FUCk FUCK !FUCK!
#ifdef GAMEDEBUG
		LanGameMallocTotals[type] -= size;
#endif
		malloc_ptr -= size;
		malloc_free += size;
		malloc_used -= size;
	}

#ifdef __cplusplus
}
#endif