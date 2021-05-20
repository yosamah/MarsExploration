#pragma once
#include <iostream>
#include "PriQ.h"
#include "Queue.h"
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
	Queue<Rover*> PolarRovers;
	Queue<Mission*> PolarMissions;
	Queue<Mission*> CompletedMissions;
	Queue<Event*> EventList;
	Queue<int> MountainousOrder;
	HashTable<Mission*,100> MountainousMissions;
};