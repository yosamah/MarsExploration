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

public:
	/*This function is checking the waiting lists and the number of missions yhat need to be done in each list*/
	
	bool assignRover_E(PriQ<Rover>* roverArray ,Mission*&, char type = 'E');
	bool assignRover_P(PriQ<Rover>* roverArray ,Mission*&);
	bool assignRover_M(PriQ<Rover>* roverArray ,Mission*&);

	void checkWaiting_E(PriQ<Mission>& Emergency, PriQ<Rover>* roverArray, int d);
	void checkWaiting_P(Queue<Mission>& Polar, PriQ<Rover>* roverArray, int d);
	void checkWaiting_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Rover>* roverArray, int d);

	void MoveToExec_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Mission>& InExecution);
	void MoveToExec_P(Queue<Mission>& Polar, PriQ<Mission>& InExecution);
	void MoveToExec_E(PriQ<Mission>& Emergency, PriQ<Mission>& InExecution);
	

};

