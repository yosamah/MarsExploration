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

void MarsStation::checkAndAssign()
{
	Action act;
	act.checkWaiting_E(EmeregncyMissions, AvaiableRovers, day);
	act.checkWaiting_P(PolarMissions, AvaiableRovers, day);
	act.checkWaiting_M(MountainousMissions, MountainousOrder, AvaiableRovers, day);
}

void MarsStation::MoveToExec()
{
	Action act;
	act.MoveToExec_E(EmeregncyMissions, InExecution);
	act.MoveToExec_P(PolarMissions, InExecution);
	act.MoveToExec_M(MountainousMissions, MountainousOrder, InExecution);

}
void MarsStation::MoveToCompMissions()
{
	Node<Mission>* tempNode;
	Mission* tempMission;
	PriQ<Mission> tempPri;
	while (!InExecution.isEmpty())
	{
		InExecution.peek(tempNode);
		tempMission = tempNode->getData();
		if (tempNode->getKey() == day)
		{
			InExecution.dequeue(tempNode);
			MoveRover(tempMission);
			tempPri.enqueue(tempMission, tempMission->getFormulationDate());
		}
		else
			break;
	}
	while (!tempPri.isEmpty())
	{
		tempPri.dequeue(tempNode);
		tempMission = tempNode->getData();
		CompletedMissions.enqueue(tempMission);
	}
	
	MoveToAvailRover();

}

void MarsStation::MoveToAvailRover()
{
	Node<Rover>* tempNode;
	Rover* tempR;
	while (!RoversInCheckUp[0].isEmpty())
	{
		RoversInCheckUp[0].peek(tempNode);
		tempR = tempNode->getData();
		if (tempR->moveToAvail(day))
		{
			AvaiableRovers[0].enqueue(tempR, tempR->getSpeed());
			RoversInCheckUp[0].dequeue(tempNode);
		}
		else
			break;

	}
	while (!RoversInCheckUp[1].isEmpty())
	{
		RoversInCheckUp[1].peek(tempNode);
		tempR = tempNode->getData();
		if (tempR->moveToAvail(day))
		{
			AvaiableRovers[1].enqueue(tempR, tempR->getSpeed());
			RoversInCheckUp[1].dequeue(tempNode);
		}
		else
			break;

	}
	while (!RoversInCheckUp[2].isEmpty())
	{
		RoversInCheckUp[2].peek(tempNode);
		tempR = tempNode->getData();
		if (tempR->moveToAvail(day))
		{
			AvaiableRovers[2].enqueue(tempR, tempR->getSpeed());
			RoversInCheckUp[2].dequeue(tempNode);
		}
		else
			break;

	}
}
void MarsStation::MoveRover(Mission* tempM)
{
	Rover* tempRover = tempM->getRover();
	if (tempRover->getMissionCount(day) == -1)
	{
		if (tempRover->getRoverType() == 'E')
			RoversInCheckUp[0].enqueue(tempRover);
		else if (tempRover->getRoverType() == 'P')
			RoversInCheckUp[1].enqueue(tempRover);
		else
			RoversInCheckUp[2].enqueue(tempRover);
	}
	else 
	{
		if (tempRover->getRoverType() == 'E')
			AvaiableRovers[0].enqueue(tempRover, tempRover->getSpeed());
		else if (tempRover->getRoverType() == 'P')
			AvaiableRovers[1].enqueue(tempRover, tempRover->getSpeed());
		else
			AvaiableRovers[2].enqueue(tempRover, tempRover->getSpeed());
	}

	tempM->setRover(NULL);

}
void MarsStation::Execute()
{
	
	UI input(this);
	ifstream file;
	file.open("TEST3.txt");
	input.Read(file, EventList);
	while (!EventList.isEmpty())//lazem el inexc teb2a fadya.
	{
		Node<Event>* tempNode;
		EventList.peek(tempNode);
		Event* temp;
		temp = tempNode->getData();
		while (temp->getED() == day)
		{
			temp->Execute(MountainousMissions, EmeregncyMissions, MountainousOrder, PolarMissions);
			EventList.dequeue(tempNode);

			
			bool check=EventList.peek(tempNode);
			if (!check)
				break;
			temp = tempNode->getData();
		}

		checkAndAssign();
		MoveToExec();
		MoveToCompMissions();

		day++;
	}
}