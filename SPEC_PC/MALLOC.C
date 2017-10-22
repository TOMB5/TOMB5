#include "MALLOC.H"
#include <stdlib.h>
#include <string.h>
#include "SPECIFIC.H"
#include "WINMAIN.H"

#define GAME_MALLOC_BUFFER_SIZE 5000000

char* malloc_ptr;
int malloc_used;
int malloc_free;
int script_malloc_size;
char* malloc_buffer;
int malloc_size;

void init_game_malloc()
{
	char* buf = malloc(GAME_MALLOC_BUFFER_SIZE);
	malloc_buffer = buf;
	malloc_size = GAME_MALLOC_BUFFER_SIZE;
	malloc_ptr = buf;
	malloc_free = GAME_MALLOC_BUFFER_SIZE;
	malloc_used = 0;
}

char* game_malloc(int size)
{
	char *result; // eax@2

	size = (size + 3) & -4;
	if (size > malloc_free)
	{
		Log(0, "OUT OF MEMORY");
		result = NULL;
	}
	else
	{
		char *v2 = malloc_ptr;
		malloc_free -= size;
		malloc_used += size;
		malloc_ptr += size;
		memset(v2, 0, 4 * ((unsigned int)size >> 2));
		result = v2;
	}
	return result;
}

void game_free(int size)
{
	size = (size + 3) & -4;

	malloc_free += size;
	malloc_ptr -= size;
	malloc_used -= size;
}

void show_game_malloc_totals()
{
	S_Warn("[show_game_malloc_totals] - Unimplemented!\n");
}

void dump_game_malloc()
{
	S_Warn("[dump_game_malloc] - Unimplemented!\n");
}
