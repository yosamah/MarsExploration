#pragma once
#include <fstream>
#include <iostream>
#include "PriQ.h"
#include "Queue.h"
#include "HashTable.h"
#include "Mission.h"

using namespace std;
class MarsStation;
class Event;


class UI
{
	MarsStation *pMars;
	

public:
	UI(MarsStation* Mars);

	void Read(ifstream& file, Queue<Event>&);  //file.close() //file.eof()
	void Write(ofstream& file , Queue<Mission> CompletedMissions, int* StatsArr);
	void Mode(PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar, PriQ<Mission> InExecution, PriQ<Rover> AvaiableRoversE, PriQ<Rover> AvaiableRoversP, PriQ<Rover> AvaiableRoversM, Queue<Rover> RoversInCheckUpE, Queue<Rover> RoversInCheckUpP, Queue<Rover> RoversInCheckUpM, Queue<Mission> CompletedMissions);
	void PrintWait(PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar);
	void PrintInExecution(PriQ<Mission> InExecution);
	void PrintAvRovers(PriQ<Rover> AvaiableRoversE, PriQ<Rover> AvaiableRoversP, PriQ<Rover> AvaiableRoversM);
	void PrintInCheckUp(Queue<Rover> RoversInCheckUpE, Queue<Rover> RoversInCheckUpP, Queue<Rover> RoversInCheckUpM);
	void PrintComplete(Queue<Mission> CompletedMissions);
	void SilentMode();
};

