#include "GAMEWAD.H"

int main(int argc, char* argv[])
{
	if(argc == 2)
		TombRaiderChronicles::UnpackGamewad(argv[1]);
	return 0;
}