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

	/*These functions assign the rovers in the availble rover list to their appropriate missions*/
	bool assignRover_E(PriQ<Rover>* roverArray ,Mission*&, char type = 'E');
	bool assignRover_P(PriQ<Rover>* roverArray ,Mission*&);
	bool assignRover_M(PriQ<Rover>* roverArray ,Mission*&);
	
	/*These functions are checking the waiting lists and the number of missions yhat need to be done in each list*/
	void checkWaiting_E(PriQ<Mission>& Emergency, PriQ<Rover>* roverArray, int d);
	void checkWaiting_P(Queue<Mission>& Polar, PriQ<Rover>* roverArray, int d);
	void checkWaiting_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Rover>* roverArray, int d);

	/*These functions move the waiting mission with assigned rovers to the execution list*/
	void MoveToExec_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Mission>& InExecution, float&Exec, float& Wait);
	void MoveToExec_P(Queue<Mission>& Polar, PriQ<Mission>& InExecution, float& Exec, float& Wait);
	void MoveToExec_E(PriQ<Mission>& Emergency, PriQ<Mission>& InExecution, float& Exec, float& Wait);

	/*This function auto promote */
	void AutoPromote(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Mission>& Emergency,int,int*);

};

