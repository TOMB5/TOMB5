#include "DRAWPHAS.H"

#include "LARA.H"
#include "SPECIFIC.H"

long DrawPhaseGame()//63F04, 
{
	//mQuickW2VMatrix();

	struct lara_info* a1 = &lara;
	
	if (lara.poisoned != lara.dpoisoned)
	{
		if (lara.dpoisoned > 4096)
		{
			lara.dpoisoned = 4096;
		}
		
		//loc_63F44

	}//loc_63F88

	//a2 = 0x000A000
	/*
	


	*/
	S_Warn("[DrawPhaseGame] - Unimplemented!\n");
	return 2;//hack
}

void UpdateSky()
{
	S_Warn("[UpdateSky] - Unimplemented!\n");
}
