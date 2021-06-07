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
	char mode;

public:
	UI(MarsStation* Mars);

	/*Read and write functions which deal with the files whether getting infro from the info file or printing in the output one*/
	void Read(ifstream& file, Queue<Event>&);
	void Write(ofstream& file , Queue<Mission> CompletedMissions, int* StatsArr);

	/*Function for calling the print functions*/
	void Mode(PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar, PriQ<Mission> InExecution, PriQ<Rover> AvaiableRoversE, PriQ<Rover> AvaiableRoversP, PriQ<Rover> AvaiableRoversM, PriQ<Rover> AvaiableRoversEM, PriQ<Rover> AvaiableRoversPM, PriQ<Rover> AvaiableRoversMM, Queue<Rover> RoversInCheckUpE, Queue<Rover> RoversInCheckUpP, Queue<Rover> RoversInCheckUpM, Queue<Mission> CompletedMissions);
	/*Printing function for each line*/
	void PrintWait(PriQ<Mission> Emergency, Queue<int> MountainousSort, Queue<Mission> Polar);
	void PrintInExecution(PriQ<Mission> InExecution);
	void PrintAvRovers(PriQ<Rover> AvaiableRoversE, PriQ<Rover> AvaiableRoversP, PriQ<Rover> AvaiableRoversM,char c);
	void PrintInCheckUp(Queue<Rover> RoversInCheckUpE, Queue<Rover> RoversInCheckUpP, Queue<Rover> RoversInCheckUpM);
	void PrintComplete(Queue<Mission> CompletedMissions);

	/*Function to print the silent mode messages*/
	void SilentMode();

	/*Setter and getter for the mode*/
	char getMode();
	void setMode(char);
};

