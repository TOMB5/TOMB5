#include "GTE.H"

int gte_ldlzc(int input)
{
	int leadingZeroCount = 0;

	if (input > 0)
	{
		for (int i = (sizeof(int) * 8)-1; i >= 0 ; i--)
		{
			if (input & (1 << i))
			{
				break;
			}

			leadingZeroCount++;
		}
	}
	
	return leadingZeroCount;
}