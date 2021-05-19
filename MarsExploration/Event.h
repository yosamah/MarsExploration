#pragma once
#include <iostream>
#include "PriQ.h"
#include "LinkedQueue.h"
#include "Event.h"
#include "HashTable.h"
#include "Mission.h"
#include "Rover.h"
#include "UI.h"

class Event
{
	int EventDay;
	int MissionID;
public:
	/* Constructor */
	Event(int, int);

	/* Check and execute to create mission and add it to the appropriate list */
	virtual void Execute(HashTable<Mission*>* Mountainous = NULL, PriQ<Mission*>* Emergency = NULL, LinkedQueue<int>* MountainousSort = NULL, LinkedQueue<Mission*>* Polar = NULL) = 0;  //Mtnsosh fi al call t7oto "&"
};