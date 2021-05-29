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
	// KOL el typenames ba2et object badal pointers.
	// AvailRov[0] -> EmergRov 
	// AvailRov[1] -> PolarRov 
	// AvailRov[2] -> MountRov
	// AvailRov[3] -> EmergRovMaint 
	// AvailRov[4] -> PolarRovMaint 
	// AvailRov[5] -> MountRovMaint 

	PriQ<Rover> AvaiableRovers[6];
	PriQ<Rover> RoversInCheckUp;
	PriQ<Mission> InExecution;
	PriQ<Mission> EmeregncyMissions;
	Queue<Rover> PolarRovers;
	Queue<Mission> PolarMissions;
	Queue<Mission> CompletedMissions;
	Queue<Event> EventList;
	Queue<int> MountainousOrder;
	HashTable<Mission,100> MountainousMissions;

	int day;
public:
	MarsStation();
	void SetAvailableRovers(int , int , int , int, int, int, int,int , int);

	void Execute();

};