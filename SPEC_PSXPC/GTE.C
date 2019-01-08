#include "GTE.H"

int gte_ldlzc(int input)
{
	int leadingZeroCount = 0;

	if (input > 0)
	{
		for (int i = 0; i < sizeof(int) * 8; i++)
		{
			if (input & (1 << i))
			{
				leadingZeroCount = 0;
			}
			else
			{
				leadingZeroCount++;
			}
		}
	}
	
	return leadingZeroCount;
}