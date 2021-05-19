#pragma once
#include <iostream>
#include "PriQ.h"
#include "LinkedQueue.h"
#include "Event.h"
#include "HashTable.h"
#include "Mission.h"
#include "Rover.h"
#include "UI.h"

class MarsStation
{
private:

	PriQ<Rover*> AvaiableRovers[3];
	PriQ<Rover*> RoversInCheckUp;
	PriQ<Mission*> InExecution;
	PriQ<Mission*> EmeregncyMissions;
	LinkedQueue<Rover*> PolarRovers;
	LinkedQueue<Mission*> PolarMissions;
	LinkedQueue<Mission*> CompletedMissions;
	LinkedQueue<Event*> EventList;
	
	LinkedQueue<int> MountainousOrder;
	HashTable<Mission*,100> MountainousMissions;
};