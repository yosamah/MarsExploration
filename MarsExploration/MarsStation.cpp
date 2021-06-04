#include "MarsStation.h"
#include<windows.h>


MarsStation::MarsStation()
{

	day = 1;
	NumberOfExec = 0;
	NumberOfWait = 0;
	AutoPro = 0;
	for (int i = 0; i < 7; i++)
	{
		StatsArr[i] = 0;
	}



}

int MarsStation::GetDay()
{
	return day;
}


void MarsStation::SetAutoPro(int A)
{
	AutoPro = A;
}
int MarsStation::GetAvgExecDays() //Should be used after all loops (calculations occur after end of while loop)
{
	return NumberOfExec;
}

int MarsStation::GetAvgWaitDays() //Should be used after all loops (calculations occur after end of while loop)
{
	return NumberOfWait;
}
int MarsStation::GetAutoPromotedPercent()
{
	return ((StatsArr[6] / StatsArr[5]) * 100);
}

void MarsStation::SetAvailableRovers(int NOMR, int NOPR, int NOER, int SOMR, int SOPR, int SOER, int CDM, int CDP, int CDE, int NBC)
{
	StatsArr[0] = NOER;
	StatsArr[1] = NOPR;
	StatsArr[2] = NOMR;
	int id = 1;

	for (int i = 0; i < NOMR; i++)
	{

		Rover* Mount = new Rover('M', CDM, SOMR, NBC);
		Mount->setID(id);
		id++;
		AvaiableRovers[2].enqueue(Mount, SOMR);
	}

	for (int i = 0; i < NOPR; i++)
	{
		Rover* Polar = new Rover('P', CDP, SOPR, NBC);
		Polar->setID(id);
		id++;
		AvaiableRovers[1].enqueue(Polar, SOPR);
	}

	for (int i = 0; i < NOER; i++)
	{

		Rover* Emerg = new Rover('E', CDE, SOER, NBC);
		Emerg->setID(id);
		id++;
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
	act.MoveToExec_E(EmeregncyMissions, InExecution, NumberOfExec, NumberOfWait);
	act.MoveToExec_P(PolarMissions, InExecution, NumberOfExec, NumberOfWait);
	act.MoveToExec_M(MountainousMissions, MountainousOrder, InExecution, NumberOfExec, NumberOfWait);

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
			int ED = tempNode->getKey() - tempMission->getFormulationDate() - tempMission->getWaitingDay();
			tempMission->setED(ED);
			tempMission->setCD(tempNode->getKey());
			tempPri.enqueue(tempMission, ED);
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
void MarsStation::AutoPromote()
{
	Action act;
	act.AutoPromote(MountainousMissions, MountainousOrder, EmeregncyMissions, AutoPro, StatsArr);
}

void MarsStation::Execute()
{
	UI input(this);
	UI output(this);
	ifstream file;
	file.open("TEST.txt");
	input.Read(file, EventList);
	char Choice;

	cout << "Select Mode:" << endl;
	cout << "i for interactive, s for Step-By-Step, x for Silent " << endl;
	cin >> Choice;


	while (!EventList.isEmpty() || !InExecution.isEmpty() || !MountainousOrder.isEmpty() || !PolarMissions.isEmpty() || !EmeregncyMissions.isEmpty())
	{
		Node<Event>* tempNode;
		EventList.peek(tempNode);
		Event* temp;
		temp = tempNode->getData();
		while (temp->getED() == day)
		{
			temp->Execute(MountainousMissions, EmeregncyMissions, MountainousOrder, PolarMissions, StatsArr);
			EventList.dequeue(tempNode);


			bool check = EventList.peek(tempNode);
			if (!check)
				break;
			temp = tempNode->getData();
		}

		checkAndAssign();
		MoveToExec();
		MoveToCompMissions();
		MoveToAvailRover();

		AutoPromote();

		if (Choice == 'i')
		{
			cin.ignore();

			output.Mode(EmeregncyMissions, MountainousOrder, PolarMissions, InExecution, AvaiableRovers[0], AvaiableRovers[1], AvaiableRovers[2], RoversInCheckUp[0], RoversInCheckUp[1], RoversInCheckUp[2], CompletedMissions);
		}
		else if (Choice == 's')
		{
			//for (int i = 0; i < 1000000000; i++)
			//{
				//i++;
			//}
			Sleep(1000); // included <windows.h>
			output.Mode(EmeregncyMissions, MountainousOrder, PolarMissions, InExecution, AvaiableRovers[0], AvaiableRovers[1], AvaiableRovers[2], RoversInCheckUp[0], RoversInCheckUp[1], RoversInCheckUp[2], CompletedMissions);
		}

		day++;

	}
	if (Choice == 'x')
	{
		output.SilentMode();
	}
	
	NumberOfExec /= (StatsArr[3] + StatsArr[4] + StatsArr[5]);
	NumberOfWait /= (StatsArr[3] + StatsArr[4] + StatsArr[5]);

	//output.Write("Output.txt");

}