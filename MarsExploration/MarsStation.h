#pragma once
#include <iostream>
#include "PriQ.h"
#include "Queue.h"
#include "Event.h"
#include "HashTable.h"
#include "Mission.h"
#include "Rover.h"
#include "UI.h"
#include "Action.h"

class MarsStation
{
private:
	// AvailRov[0] -> EmergRov 
	// AvailRov[1] -> PolarRov 
	// AvailRov[2] -> MountRov
	// AvailRov[3] -> EmergRovMaint 
	// AvailRov[4] -> PolarRovMaint 
	// AvailRov[5] -> MountRovMaint 

	//StatsArr[0] -> EmergRov 
	//StatsArr[1] -> PolarRov 
	//StatsArr[2] -> MountRov
	//StatsArr[3] -> EmergMission 
	//StatsArr[4] -> PolarMission 
	//StatsArr[5] -> MountMission 
	//StatsArr[6] -> AutoPromotedMission 

	//RoversInCheckUp[0] -> EmergRov
	//RoversInCheckUp[1] -> PolarRov
	//RoversInCheckUp[2] -> MountRov


	PriQ<Rover> AvaiableRovers[6];
	Queue<Rover> RoversInCheckUp[3];
	PriQ<Mission> InExecution;
	PriQ<Mission> EmeregncyMissions;
	Queue<Rover> PolarRovers;
	Queue<Mission> PolarMissions;
	Queue<Mission> CompletedMissions;
	Queue<Event> EventList;
	Queue<int> MountainousOrder;
	HashTable<Mission,101> MountainousMissions;
	

	float NumberOfExec;
	float NumberOfWait;
	int StatsArr[7];
	int AutoPro;
	int day;

public:
	MarsStation();
	/*Function the sets the available rovers according the input file from the UI*/
	void SetAvailableRovers(int , int , int , int*, int*, int*, int,int , int, int);

	/*The main function that runs the code*/
	void Execute();

	/*A function that checks all the waiting missions and assign them if their formulation day is the current day*/
	void checkAndAssign();

	/*A function that checks the missions that have an assigned rover and move them to the execution list*/
	void MoveToExec();

	/*A function that checks if the current day equals the completion day of a certain mission to be moved to completed mission list*/
	void MoveToCompMissions();

	/*Functions that move the rovers between lists*/
	void MoveRover(Mission* mission);
	void MoveToAvailRover();

	/*Getter for the current day*/
	int GetDay();

	/*Getters for the average execution and waiting days*/
	float GetAvgExecDays();
	float GetAvgWaitDays();

	/*getter for the auto promotion precentage*/
	float GetAutoPromotedPercent();
	void SetAutoPro(int);

	/*Function that auto promotes mountainuous missions after a certain period of time*/
	void AutoPromote();

	/*Function that checkes if the rover is in maintenance*/
	void checkInMain();
};