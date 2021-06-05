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
float MarsStation::GetAvgExecDays() //Should be used after all loops (calculations occur after end of while loop)
{
	return NumberOfExec;
}

float MarsStation::GetAvgWaitDays() //Should be used after all loops (calculations occur after end of while loop)
{
	return NumberOfWait;
}
float MarsStation::GetAutoPromotedPercent()
{
	return (((float)StatsArr[6] / ((float)StatsArr[6] + (float)StatsArr[5]))) * 100;
}

void MarsStation::SetAvailableRovers(int NOMR, int NOPR, int NOER, int* SOMR, int* SOPR, int* SOER, int CDM, int CDP, int CDE, int NBC)
{
	StatsArr[0] = NOER;
	StatsArr[1] = NOPR;
	StatsArr[2] = NOMR;
	int id = 1;

	for (int i = 0; i < NOMR; i++)
	{

		Rover* Mount = new Rover('M', CDM, SOMR[i], NBC);
		Mount->setID(id);
		id++;
		AvaiableRovers[2].enqueue(Mount, -SOMR[i]);
	}

	for (int i = 0; i < NOPR; i++)
	{
		Rover* Polar = new Rover('P', CDP, SOPR[i], NBC);
		Polar->setID(id);
		id++;
		AvaiableRovers[1].enqueue(Polar, -SOPR[i]);
	}

	for (int i = 0; i < NOER; i++)
	{

		Rover* Emerg = new Rover('E', CDE, SOER[i], NBC);
		Emerg->setID(id);
		id++;
		AvaiableRovers[0].enqueue(Emerg, -SOER[i]);
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

void MarsStation::checkInMain()
{
	int i = rand() % 101;
	// nezbat el range.
	if (i >= 15 && i <= 35)
	{
		int j = rand() % 3;
		Node<Rover>* tempNode = NULL;
		Rover* tempRover;
		AvaiableRovers[j].dequeue(tempNode);
		if (tempNode)
		{
			tempRover = tempNode->getData();
			if (tempRover->getMissionCountMain())
			{
				tempRover->setMaintain();
				tempRover->setCheckUpEnter(day);
				AvaiableRovers[j + 3].enqueue(tempRover, (day + tempRover->getCheckUpDuration()));
			}
			else
				AvaiableRovers[j].enqueue(tempRover, -tempRover->getSpeed());

		}

	}
	
}

void MarsStation::MoveToAvailRover()
{
	Node<Rover>* tempNode;
	Rover* tempR;
	for (int i = 0; i < 5; i++)
	{
		while (!RoversInCheckUp[i].isEmpty())
		{
			tempNode = NULL;
			RoversInCheckUp[i].peek(tempNode);
			if (tempNode)
				tempR = tempNode->getData();
			else
				break;
			if (tempNode && tempR->moveToAvail(day))
			{
				if (i > 2)
					tempR->resetMaintain();
				AvaiableRovers[i].enqueue(tempR, tempR->getSpeed());
				RoversInCheckUp[i].dequeue(tempNode);
			}
			else
				break;

		}
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
	ifstream InFile;
	InFile.open("TEST.txt");
	input.Read(InFile, EventList);
	char Choice;

	cout << "Select Mode:" << endl;
	cout << "i for interactive, s for Step-By-Step, x for Silent " << endl;
	cin >> Choice;
	if (Choice == 'i')
		cout << "Press enter to proceed" << endl;

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


		checkInMain();
		checkAndAssign();
		MoveToExec();
		MoveToCompMissions();
		MoveToAvailRover();
	//checkInMain();
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
			//} // AMIN AL M3AFEN
			Sleep(1000); // included <windows.h> // AMIN AL NDYF
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

	ofstream OutFile;
	OutFile.open("OutputFile.txt");
	output.Write(OutFile,CompletedMissions,StatsArr);

}