#include "MarsStation.h"

void MarsStation::SetAvailableRovers(int NOMR, int NOPR, int NOER, int SOMR, int SOPR, int SOER,int CDM, int CDP , int CDE)
{

	for (int i = 0; i < NOMR; i++)
	{
		Rover* Mount = new Rover('M', CDM , SOMR);		
		AvaiableRovers[0].enqueue(&Mount , SOMR);
	}

	for (int i = 0; i < NOPR; i++)
	{
		Rover* Polar = new Rover('P', CDP, SOPR);
		AvaiableRovers[1].enqueue(&Polar, SOPR);
	}

	for (int i = 0; i < NOER; i++)
	{
		Rover* Emerg = new Rover('E', CDE, SOER);
		AvaiableRovers[2].enqueue(&Emerg, SOER);
	}
}
