#include "TWOGUN.H"

struct TWOGUN_INFO twogun[4];

void UpdateTwogunLasers()
{
	struct TWOGUN_INFO* info = twogun;

	for (int i = 0; i < 4; i++, info++)
	{
		if (info->life != 0)
		{
			info->life--;

			if (info->life > 16)
			{
				info->coil += (8192 - info->coil) >> 3;

				short dl = info->dlength - info->length;

				if (dl > info->dlength >> 2)
				{
					info->length += dl >> 2;
				}
				else
				{
					info->spinadd += (8192 - info->spinadd) >> 3;
					info->length = info->dlength;
				}

				if (info->size < 4)
					info->size++;
			}
			else if (info->life == 16)
			{
				info->spinadd = 8192;
				info->coil = 8192;
				info->length = info->dlength;
				info->size = 4;
			}
			else
			{
				info->size++;
				info->spinadd -= info->spinadd >> 3;
			}

			if (info->fadein < 8)
				info->fadein++;

			info->spin -= info->spinadd;
		}
	}
}