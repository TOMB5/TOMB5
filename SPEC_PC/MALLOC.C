#include "MALLOC.H"
#include <cstdlib>
#include <cstring>
#include "SPECIFIC.H"
#include "WINMAIN.H"

char* game_malloc(int size)
{
	char *result; // eax@2

	size = (size + 3) & -4;
	if (size > malloc_free)
	{
		sub_4DEB10(0, "OUT OF MEMORY");
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