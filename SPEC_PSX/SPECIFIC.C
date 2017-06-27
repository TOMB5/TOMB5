#include "SPECIFIC.H"

#include <stdio.h>
#include <stdlib.h>

void S_ExitSystem(char* exit_message)
{
	printf(exit_message);
	exit(EXIT_FAILURE);
}