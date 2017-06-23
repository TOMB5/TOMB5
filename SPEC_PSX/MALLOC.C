#include "MALLOC.H"

#include "../GAME/GAMEFLOW.H"
#include "SPECIFIC.H"

#include <stdlib.h>
#include <stdio.h>

char* malloc_ptr = NULL;
int malloc_used = 0;
int malloc_free = GAME_MALLOC_BUFFER_SIZE;
int script_malloc_size = 0;//?
char malloc_buffer[GAME_MALLOC_BUFFER_SIZE];//Memory Address 0xE3DC0

void init_game_malloc()
{
	memset(malloc_buffer, GAME_MALLOC_BUFFER_SIZE-gfScriptLen, 0);
	malloc_ptr = &malloc_buffer;
}

char* game_malloc(int size)
{
	int alignedSize = size + 3 & -4;

	if (alignedSize > GAME_MALLOC_BUFFER_SIZE)
	{
		char buf[80];
		sprintf(buf, "game_malloc() out of space (needs %d only got %d)", size, GAME_MALLOC_BUFFER_SIZE - (malloc_ptr - malloc_buffer));
		S_ExitSystem(buf);
	}
	else
	{
		char* ptr = malloc_ptr;
		malloc_ptr += size;
		malloc_used += size;
		malloc_free -= size;
		return ptr;
	}

	return NULL;
}

void game_free(int size)
{
	size += 3;
	size &= -4;
	//TODO
}

void show_game_malloc_totals()
{
	if (malloc_used >= 0)
	{
		if (malloc_used + malloc_free >= 0)
		{
			printf("---->Total Memory Used %dK of %dK<----", malloc_used / 1024, malloc_used + malloc_free / 1024);
		}
	}
}