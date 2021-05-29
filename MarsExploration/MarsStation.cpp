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
	Action act;
	UI input(this);
	ifstream file;
	file.open("TEST.txt");
	input.Read(file, EventList);
	while (!EventList.isEmpty())
	{
		Node<Event>* tempNode;
		EventList.peek(tempNode);
		Event* temp;
		temp = tempNode->getData();
		while (temp->getED() == day)
		{
			temp->Execute(MountainousMissions, EmeregncyMissions, MountainousOrder, PolarMissions);
			bool check = EventList.dequeue(tempNode);
			if (!check)
				return;
			EventList.peek(tempNode);
			temp = tempNode->getData();

		}
		act.checkWaiting(MountainousMissions, EmeregncyMissions, MountainousOrder, PolarMissions, day, AvaiableRovers);
		
		day++;
	}
}