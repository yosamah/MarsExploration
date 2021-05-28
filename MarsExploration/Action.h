#pragma once
#include <iostream>
#include "PriQ.h"
#include "Queue.h"
#include "Event.h"
#include "HashTable.h"
#include "Mission.h"
#include "Rover.h"
#include "UI.h"


class Action
{
	/*This function is checking the waiting lists and the number of missions yhat need to be done in each list*/
	void checkWaiting(HashTable<Mission*> Mountainous, PriQ<Mission*> Emergency, Queue<int> MountainousSort, Queue<Mission*> Polar, int d, int* arr);
};

