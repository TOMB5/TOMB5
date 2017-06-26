#include "MALLOC.H"

#include "../GAME/GAMEFLOW.H"
#include "SPECIFIC.H"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* malloc_ptr = NULL;
int malloc_used = 0;
int malloc_free = GAME_MALLOC_BUFFER_SIZE;
int script_malloc_size = 0;//?
char malloc_buffer[GAME_MALLOC_BUFFER_SIZE];//Memory Address 0xE3DC0

#pragma warning (disable : 4996)//sprintf

void init_game_malloc()//5E79C, 5F4F8
{
	memset(malloc_buffer + gfScriptLen, GAME_MALLOC_BUFFER_SIZE - gfScriptLen, 0);
	malloc_ptr = &malloc_buffer[0];
}

char* game_malloc(int size)//5E7E8, 5F544
{
	size = (size + 3) & -4;

	if (malloc_free > size)
	{
		char* ptr = malloc_ptr;

		malloc_free -= size;
		malloc_ptr += size;
		malloc_used += size;

		return ptr;
	}
	else
	{
		char buf[80];
		sprintf(buf, "game_malloc() out of space(needs %d only got %d", size, malloc_free);
		S_ExitSystem(buf);
	}

	return NULL;
}

void game_free(int size)//5E85C, 5F590
{
	size = (size + 3) & -4;

	malloc_free += size;
	malloc_ptr -= size;
	malloc_used -= size;
}

void show_game_malloc_totals()//5E894, * 
{
	if (malloc_used >= 0)
	{
		if (malloc_used + malloc_free >= 0)
		{
			printf("---->Total Memory Used %dK of %dK<----", malloc_used / 1024, malloc_used + malloc_free / 1024);
		}
	}
}

void dump_game_malloc()
{
	FILE* fileHandle = fopen("DUMP.BIN", "w");

	if (fileHandle != NULL)
	{
		fwrite(&malloc_buffer[0], 1, GAME_MALLOC_BUFFER_SIZE, fileHandle);
	}
	else
	{
		printf("Failed to dump memory!\n");
	}
}