#include "MALLOC.H"

#include "GAMEFLOW.H"
#include "SPECIFIC.H"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GAME_MALLOC_BUFFER_SIZE (1024*1024) + (1024*36)

char* malloc_ptr = NULL;
int malloc_used = 0;
int malloc_free = GAME_MALLOC_BUFFER_SIZE;
int script_malloc_size = 0;
char malloc_buffer[GAME_MALLOC_BUFFER_SIZE];

/*
 * [FUNCTIONALITY] - init_game_malloc.
 * Resets malloc_buffer and all allocation stats back to their default values.
 * Note: The entire malloc_buffer is zero initialised.
 * Note: Once the gameflow script is loaded it's always in malloc_buffer regardless.
 */

void init_game_malloc()//5E79C(<), 5F4F8(<) (F) (*)
{
	malloc_used = gfScriptLen;
	malloc_free = GAME_MALLOC_BUFFER_SIZE - gfScriptLen;
	malloc_ptr = &malloc_buffer[gfScriptLen];
	memset(&malloc_ptr[0], 0, GAME_MALLOC_BUFFER_SIZE - gfScriptLen);
}

/*
 * [FUNCTIONALITY] - game_malloc.
 * "Allocates" memory from our malloc_buffer declared on the stack.
 * Note: Memory that is "allocated" is not zero initialised.
 * Note: If you run out of memory the application will exit.
 * Note: Usage should be seen as stack functionality, always free the last block of memory you allocated (LIFO).
 * [USAGE]
 * @PARAM - [size] The amount of memory you wish to "allocate".
 * @RETURN - [ptr] Pointer to the memory block you just "allocated".
 */

char* game_malloc(int size)//5E7E8(<), 5F544(<) (F) (*) (?)
{
#if DEBUG_VERSION
	char buf[80];
#endif

	char* ptr;

	size = (size + 3) & -4;

	if (size <= malloc_free)
	{
		ptr = malloc_ptr;

		malloc_free -= size;
		malloc_ptr += size;
		malloc_used += size;
		
	}
#if DEBUG_VERSION
	else
	{
		sprintf(buf, "game_malloc() out of space (needs %d only got %d)\n", size, malloc_free);
		S_ExitSystem(buf);
		return NULL;
	}
#endif
	return ptr;
}

/*
 * [FUNCTIONALITY] - game_free.
 * "Frees" memory from malloc_buffer.
 * Note: Memory that is freed is not zero initialised.
 * Note: There is no error checking so ensure you do not free more memory than the buffer can hold.
 * Note: Usage should be seen as stack functionality, always free the last block of memory you allocated (LIFO).
 * [USAGE]
 * @PARAM - [size] The amount of memory you wish to "free".
 */

void game_free(int size)//5E85C(<), 5F590(<) (F) (*)
{
	size = (size + 3) & -4;

	malloc_ptr -= size;
	malloc_free += size;
	malloc_used -= size;
}

/*
 * [FUNCTIONALITY] - show_game_malloc_totals.
 * Prints the amount of free/used malloc_buffer memory to stdio in Kilobytes.
 */

void show_game_malloc_totals()//5E894(<), * (F) (*)
{
	printf("---->Total Memory Used %dK of %dK<----\n", ((malloc_used + 1023) / 1024) - 10, ((malloc_used + malloc_free) / 1024) - 10);
}

/*
 * [FUNCTIONALITY] - dump_game_malloc.
 * Dumps the entire malloc_buffer to a file named "DUMP.BIN"
 * This is typically used to inspect malloc_buffer memory and compare to PS1.
 */

void dump_game_malloc()//*, *
{
	return;
}