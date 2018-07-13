#include <cstddef>
#include "CAMERA.H"
#include "INCLUDE.H"
#include "GLOBAL.H"
#include "WINMAIN.H"

#define GAME_MALLOC_BUFFER_SIZE 5000000

char*	malloc_buffer = NULL;
int		malloc_size;
char*	malloc_ptr;
int		malloc_used, malloc_free;

WATERTAB	WaterTable[22][64];

static unsigned short GetRandom(WATERTAB *w, int n)
{
	int i;
	unsigned short random;

	do {
		random = rand() & 0xfc;

		for (i = 0; i<n; i++)
		{
			if (w[i].random == random)
				break;
		}

		if (i == n)
			return random;

	} while (1);

	return 0;		// to stop warning
}

void	init_water_table()
{
	long	lp;

	srand(121197);

	for (lp = 0; lp<64; lp++)
	{
		int i, j, k;
		short sin = rcossin_tbl[(lp << 7)];

		/* -------- underwater/swamp table */

		WaterTable[0][lp].shimmer = (sin * 63) >> (12 + 3);
		WaterTable[0][lp].choppy = (sin * 16) >> 12;
		WaterTable[0][lp].random = GetRandom(&WaterTable[0][0], lp);
		WaterTable[0][lp].abs = 0;

		/* -------- mist tables */

		WaterTable[1][lp].shimmer = (sin * 32) >> (12 + 3);
		WaterTable[1][lp].choppy = 0;
		WaterTable[1][lp].random = GetRandom(&WaterTable[1][0], lp);
		WaterTable[1][lp].abs = -3;

		WaterTable[2][lp].shimmer = (sin * 64) >> (12 + 3);
		WaterTable[2][lp].choppy = 0;
		WaterTable[2][lp].random = GetRandom(&WaterTable[2][0], lp);
		WaterTable[2][lp].abs = 0;

		WaterTable[3][lp].shimmer = (sin * 96) >> (12 + 3);
		WaterTable[3][lp].choppy = 0;
		WaterTable[3][lp].random = GetRandom(&WaterTable[3][0], lp);
		WaterTable[3][lp].abs = 4;

		WaterTable[4][lp].shimmer = (sin * 127) >> (12 + 3);
		WaterTable[4][lp].choppy = 0;
		WaterTable[4][lp].random = GetRandom(&WaterTable[4][0], lp);
		WaterTable[4][lp].abs = 8;

		/* -------- shimmer/ripple tables */

		for (i = 0, j = 5; i<4; i++, j += 4)
		{
			for (k = 0; k<4; k++)
			{
				static unsigned char off[4] = { 4, 8, 12, 16 };
				static short shim[4] = { 31, 63, 95, 127 };
				static short chop[4] = { 16, 53, 90, 127 };

				WaterTable[j + k][lp].shimmer = -((sin*shim[k]) >> 15);
				WaterTable[j + k][lp].choppy = (sin*chop[i]) >> 12;
				WaterTable[j + k][lp].random = GetRandom(&WaterTable[j + k][0], lp);
				WaterTable[j + k][lp].abs = off[k];
			}
		}
	}

}

#ifdef __cplusplus
extern "C" {
#endif

	void init_game_malloc(void)
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

	void* game_malloc(int size)
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

		Log(0, "OUT OF MEMORY");
		S_ExitSystem(exit_message);
		return 0;	// S_ExitSystem doesn't return...
	}

	void show_game_malloc_totals(void)
	{
#ifdef GAMEDEBUG
		for (int i = 0; i<NUM_MALLOC_TYPES; ++i)
			Log("%s: %d", game_malloc_strings[i], LanGameMallocTotals[i]);
		Log("malloc_used=%dK; malloc_free=%dK; malloc_size=%dK", malloc_used >> 10, malloc_free >> 10, malloc_size >> 10);
#endif
	}

	void game_free(int size, int type)
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