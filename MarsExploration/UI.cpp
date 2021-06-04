#include "UI.h"
#include "MarsStation.h"
#include "Formulation.h"
#include "Cancellation.h"
#include "Promotion.h"



UI::UI(MarsStation* Mars)
{
	pMars = Mars;
}

void UI::Read(ifstream& file, Queue<Event>& eventList)  //file.close() //file.eof()
{
	/*The type of each rover*/
	int NumOfPolarRover;
	int NumOfMountRover;
	int NumOfEmergRover;

	/*The speed of each rover*/
	int SpeedOfPolarRover;
	int SpeedOfMountRover;
	int SpeedOfEmergRover;

	/*The number of missions needed before check up*/
	int BeforeCheckup; 

	/*The Check up duration of each rover*/
	int CheckUpDurationPolar;
	int CheckUpDurationMount;
	int CheckUpDurationEmerg;

	/* TODO: For bonus the different speeds add char "B" and check on in to read differently */
	file >> NumOfMountRover >> NumOfPolarRover >> NumOfEmergRover;
	file >> SpeedOfMountRover >> SpeedOfPolarRover >> SpeedOfEmergRover;
	file >> BeforeCheckup;
	file >> CheckUpDurationMount >> CheckUpDurationPolar >> CheckUpDurationEmerg;
	pMars->SetAvailableRovers(NumOfMountRover, NumOfPolarRover, NumOfEmergRover, SpeedOfMountRover, SpeedOfPolarRover, SpeedOfEmergRover, CheckUpDurationMount, CheckUpDurationPolar, CheckUpDurationEmerg, BeforeCheckup);
	
	///////////////////       /////////////////////////
	
	int AutoPromotion;

	int NumOfEvents;

	file >> AutoPromotion;
	pMars->SetAutoPro(AutoPromotion);
	file >> NumOfEvents;
	
	char EventType;


	for (int i = 0; i < NumOfEvents; i++)
	{
		file >> EventType;

		if (EventType == 'F')
		{
			char MissionType;
			int ED, ID, Location, MDUR, Signif;

			file >> MissionType;
			file >> ED >> ID >> Location >> MDUR >> Signif;

			Formulation* F = new Formulation(MissionType,Location,MDUR,Signif,ID,ED);
			eventList.enqueue(F);

		}
		else if (EventType == 'X')
		{
			int ED,ID;
			file >> ED >> ID;
			Cancellation* X =new Cancellation(ID,ED);
			eventList.enqueue(X);
		}
		else if (EventType == 'P')
		{
			int ED, ID;
			file >> ED >> ID;
			Promotion* P = new Promotion(ID, ED);
			eventList.enqueue(P);
		}
	}
}

void UI::Write(ofstream& file, Queue<Mission> CompletedMissions, int* StatsArr)
{
	file << "CD\tID\tFD\tWD\tED" << endl;
	Queue<int> Temp;
	Node<Mission>* TempMission;

	while (!CompletedMissions.isEmpty())
	{
		CompletedMissions.dequeue(TempMission);

		file << TempMission->getData()->getCD() << "\t" << TempMission->getData()->getID() << "\t" << TempMission->getData()->getFormulationDate() << "\t" << TempMission->getData()->getTotalMissionDur() << "\t" << TempMission->getData()->getED() << endl;
	}
	file << "Missions: " << StatsArr[3] + StatsArr[4] + StatsArr[5] << " [M: " << StatsArr[5] << ", P: " << StatsArr[4] << ", E: " << StatsArr[3] << "]\n";
	file << "Rovers: " << StatsArr[0] + StatsArr[1] + StatsArr[2] << " [M: " << StatsArr[2] << ", P: " << StatsArr[1] << ", E: " << StatsArr[0] << "]\n";
	file << "Avg Wait = " << pMars->GetAvgWaitDays() << ", " << "Avg Exec = " << pMars->GetAvgExecDays() << endl;
	file << "Auto-promoted: " << pMars->GetAutoPromotedPercent();
}

void UI::PrintWait(PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar)
{
	int CountM = 0;
	int CountP = 0;
	int CountE = 0;
	int CountW = 0;
	int CountInEx = 0;

	Queue<int> Temp;
	Node<int>* TempID;
	Node<Mission>* TempMission;
	int TempInt;
	while (!Emergency.isEmpty())
	{
		Emergency.dequeue(TempMission);
		int ID = TempMission->getData()->getID();
		CountE++;
		CountW++;
		Temp.enqueue(&ID);
	}
	while (!Polar.isEmpty())
	{
		Polar.dequeue(TempMission);
		int ID = TempMission->getData()->getID();
		CountP++;
		CountW++;
		Temp.enqueue(&ID);
	}
	while (!MountainousSort.isEmpty())
	{
		MountainousSort.dequeue(TempID);
		CountM++;
		CountW++;
		Temp.enqueue(TempID->getData());
	}

	cout << "Current Day: " << pMars->GetDay() << endl;
	cout << CountW << " Waiting Missions: ";
	if (Temp.isEmpty())
	{
		cout << "[ ] ( ) { } ";
	}
	while (!Temp.isEmpty())
	{
		cout << "[ ";
		for (int i = 0; i < CountE; i++)
		{
			Temp.dequeue(TempID);
			int* ids = TempID->getData();
			cout << (*ids) << ",";

		}
		cout << "\b ]" << "  ";
		cout << "( ";
		for (int i = 0; i < CountP; i++)
		{
			Temp.dequeue(TempID);
			int* ids = TempID->getData();
			cout << (*ids) << ",";
		}
		cout << "\b )" << "  ";
		cout << "{ ";
		for (int i = 0; i < CountM; i++)
		{
			Temp.dequeue(TempID);
			int* ids = TempID->getData();
			cout << (*ids) << ",";
		}
		cout << "\b }";
	}
	cout << endl;
	cout << "--------------------------------------" << endl;
}

void UI::PrintInExecution(PriQ<Mission> InExecution)
{
	int CountM = 0;
	int CountP = 0;
	int CountE = 0;
	int CountInEx = 0;


	Queue<Mission> Emerge;
	Queue<Mission> Mount;
	Queue<Mission> Polar;
	Node<Mission>* MissionNode;
	while (!InExecution.isEmpty())
	{
		InExecution.dequeue(MissionNode);
		if (MissionNode->getData()->getMissionType() == 'E')
		{
			CountE++;
			CountInEx++;
			Emerge.enqueue(MissionNode->getData());
		}
		else if (MissionNode->getData()->getMissionType() == 'P')
		{
			CountP++;
			CountInEx++;
			Polar.enqueue(MissionNode->getData());
		}
		else if (MissionNode->getData()->getMissionType() == 'M')
		{
			CountM++;
			CountInEx++;
			Mount.enqueue(MissionNode->getData());
		}
	
		

	}
	cout << CountInEx << " In-Execution Missions/Rovers: ";

	cout << "[  ";
	while (!Emerge.isEmpty())
	{
		Emerge.dequeue(MissionNode);
		cout << MissionNode->getData()->getID() << "/" << MissionNode->getData()->getRover()->getID() << ", ";

	}
	cout << "\b\b  ] ";

	cout << "(  ";
	while (!Polar.isEmpty())
	{
		Polar.dequeue(MissionNode);
		cout << MissionNode->getData()->getID() << "/" << MissionNode->getData()->getRover()->getID() << ", ";

	}
	cout << "\b\b  ) ";


	cout << "{  ";
	while (!Mount.isEmpty())
	{
		Mount.dequeue(MissionNode);
		cout << MissionNode->getData()->getID() << "/" << MissionNode->getData()->getRover()->getID() << ", ";
	}
	cout << "\b\b  } ";

	cout << endl;

	cout << "--------------------------------------" << endl;
}

void UI::PrintAvRovers(PriQ<Rover> AvaiableRoversE, PriQ<Rover> AvaiableRoversP, PriQ<Rover> AvaiableRoversM )
{
	int CountR = 0;
	int CountM = 0;
	int CountP = 0;
	int CountE = 0;


	Queue<Rover> Rovers;
	Node<Rover>* Temp;


	while (!AvaiableRoversE.isEmpty())
	{
		AvaiableRoversE.dequeue(Temp);
		Rovers.enqueue(Temp->getData());
		CountE++;
		CountR++;
	}
	while (!AvaiableRoversP.isEmpty())
	{
		AvaiableRoversP.dequeue(Temp);
		Rovers.enqueue(Temp->getData());
		CountP++;
		CountR++;
	}
	while (!AvaiableRoversM.isEmpty())
	{
		AvaiableRoversM.dequeue(Temp);
		Rovers.enqueue(Temp->getData());
		CountM++;
		CountR++;
	}
	cout << CountR << " Available Rovers: ";
	if (Rovers.isEmpty())
	{
		cout << "[ ] ( ) { } ";
	}
	while (!Rovers.isEmpty())
	{
		cout << "[  ";
		for (int i = 0; i < CountE; i++)
		{
			Rovers.dequeue(Temp);
			cout << Temp->getData()->getID() << ",";
		}

		cout << "\b  ]" << "  ";
		cout << "(  ";
		for (int i = 0; i < CountP; i++)
		{
			Rovers.dequeue(Temp);
			cout << Temp->getData()->getID() << ",";
		}
		cout << "\b  )" << "  ";
		cout << "{  ";
		for (int i = 0; i < CountM; i++)
		{
			Rovers.dequeue(Temp);
			cout << Temp->getData()->getID() << ",";
		}
		cout << "\b  }";

	}
	cout << endl;
	cout << "--------------------------------------" << endl;


}

void UI::PrintInCheckUp(Queue<Rover> RoversInCheckUpE, Queue<Rover> RoversInCheckUpP, Queue<Rover> RoversInCheckUpM)
{
	int CountC = 0;
	int CountM = 0;
	int CountP = 0;
	int CountE = 0;


	Queue<Rover> CheckRovers;
	Node<Rover>* Temp;


	while (!RoversInCheckUpE.isEmpty())
	{
		RoversInCheckUpE.dequeue(Temp);
		CheckRovers.enqueue(Temp->getData());
		CountE++;
		CountC++;
	}
	while (!RoversInCheckUpP.isEmpty())
	{
		RoversInCheckUpP.dequeue(Temp);
		CheckRovers.enqueue(Temp->getData());
		CountP++;
		CountC++;
	}
	while (!RoversInCheckUpM.isEmpty())
	{
		RoversInCheckUpM.dequeue(Temp);
		CheckRovers.enqueue(Temp->getData());
		CountM++;
		CountC++;
	}
	cout << CountC << " In-Checkup Rovers: ";
	if (CheckRovers.isEmpty())
	{
		cout << "[ ] ( ) { } ";
	}
	while (!CheckRovers.isEmpty())
	{
		cout << "[  ";
		for (int i = 0; i < CountE; i++)
		{
			CheckRovers.dequeue(Temp);
			cout << Temp->getData()->getID() << ",";
		}

		cout << "\b  ]" << "  ";
		cout << "(  ";
		for (int i = 0; i < CountP; i++)
		{
			CheckRovers.dequeue(Temp);
			cout << Temp->getData()->getID() << ",";
		}
		cout << "\b  )" << "  ";
		cout << "{  ";
		for (int i = 0; i < CountM; i++)
		{
			CheckRovers.dequeue(Temp);
			cout << Temp->getData()->getID() << ",";
		}
		cout << "\b  }";

	}
	cout << endl;
	cout << "--------------------------------------" << endl;



}

void UI::PrintComplete(Queue<Mission> CompletedMissions)
{
	int CountM = 0;
	int CountP = 0;
	int CountE = 0;
	int CountComp = 0;


	Queue<Mission> Emerge;
	Queue<Mission> Mount;
	Queue<Mission> Polar;
	Node<Mission>* MissionNode;
	while (!CompletedMissions.isEmpty())
	{
		CompletedMissions.dequeue(MissionNode);
		if (MissionNode->getData()->getMissionType() == 'E')
		{
			CountE++;
			CountComp++;
			Emerge.enqueue(MissionNode->getData());
		}
		else if (MissionNode->getData()->getMissionType() == 'P')
		{
			CountP++;
			CountComp++;
			Polar.enqueue(MissionNode->getData());
		}
		else if (MissionNode->getData()->getMissionType() == 'M')
		{
			CountM++;
			CountComp++;
			Mount.enqueue(MissionNode->getData());
		}

	}
	cout << CountComp << " Completed Missions: ";

	cout << "[  ";
	while (!Emerge.isEmpty())
	{
		Emerge.dequeue(MissionNode);
		cout << MissionNode->getData()->getID()  << ", ";

	}
	cout << "\b\b  ] ";

	cout << "(  ";
	while (!Polar.isEmpty())
	{
		Polar.dequeue(MissionNode);
		cout << MissionNode->getData()->getID() <<", ";

	}
	cout << "\b\b  ) ";


	cout << "{  ";
	while (!Mount.isEmpty())
	{
		Mount.dequeue(MissionNode);
		cout << MissionNode->getData()->getID()  << ", ";
	}
	cout << "\b\b  } ";

	cout << endl;

	cout << "--------------------------------------" << endl;
}

void UI::Mode(PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar, PriQ<Mission> InExecution,PriQ<Rover> AvaiableRoversE, PriQ<Rover> AvaiableRoversP, PriQ<Rover> AvaiableRoversM, Queue<Rover> RoversInCheckUpE, Queue<Rover> RoversInCheckUpP, Queue<Rover> RoversInCheckUpM, Queue<Mission> CompletedMissions)
{
	PrintWait(Emergency, MountainousSort, Polar);
	PrintInExecution(InExecution);
	PrintAvRovers(AvaiableRoversE, AvaiableRoversP, AvaiableRoversM);
	PrintInCheckUp(RoversInCheckUpE, RoversInCheckUpP, RoversInCheckUpM);
	PrintComplete(CompletedMissions);
	cout << "======================= New Day ======================" << endl;
	//we might need 5 functions for each line in the interactive mode
	// we did in deeddd


}
void UI::SilentMode()
{
	cout << "Silent Mode \nSimulation Starts... \nSimulation ends, Output file created" << endl;
		
}