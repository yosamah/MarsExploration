#include "MarsStation.h"



MarsStation::MarsStation()
{
	day = 1;
}
void MarsStation::SetAvailableRovers(int NOMR, int NOPR, int NOER, int SOMR, int SOPR, int SOER,int CDM, int CDP , int CDE)
{

	for (int i = 0; i < NOMR; i++)
	{
		Rover* Mount = new Rover('M', CDM , SOMR);		
		AvaiableRovers[2].enqueue(Mount , SOMR);
	}

	for (int i = 0; i < NOPR; i++)
	{
		Rover* Polar = new Rover('P', CDP, SOPR);
		AvaiableRovers[1].enqueue(Polar, SOPR);
	}

	for (int i = 0; i < NOER; i++)
	{
		Rover* Emerg = new Rover('E', CDE, SOER);
		AvaiableRovers[0].enqueue(Emerg, SOER);
	}
}

void MarsStation::Execute()
{
	UI* input;
	ifstream file;
	file.open("TEST.txt");
	input->Read(file);
	while (!EventList.isEmpty())
	{
		Node<Event>* tempNode;
		EventList.dequeue(tempNode);
		Event* temp;
	}
}