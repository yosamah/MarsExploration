#include "Action.h"


void Action::checkWaiting(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar, int d, PriQ<Rover>* roverArray)
{
	checkWaiting_E(Emergency, roverArray, d);
	
}

void Action::checkWaiting_E(PriQ<Mission>& Emergency, PriQ<Rover>* roverArray, int d)
{
	Node<Mission>* tempNode;
	Mission* tempMission;
	int cDay;
	PriQ<Mission> tempPriQ;
	if (!Emergency.isEmpty())
	{
		Emergency.dequeue(tempNode);
		tempMission = tempNode->getData();
		//tempPriQ.enqueue(tempMission, tempNode->getKey());
		cDay = tempMission->getFormulationDate();
		if (cDay > d)
		{
			tempPriQ.enqueue(tempMission, tempNode->getKey());
		}
		else
		{
			while (cDay <= d)
			{
				bool test = assignRover_E(roverArray, tempMission);
				if (test)
				{
					tempPriQ.enqueue(tempMission, tempNode->getKey());
					Emergency.dequeue(tempNode);
					tempMission = tempNode->getData();
					cDay = tempMission->getFormulationDate();
				}
				else
				{
					tempMission->increamentWaitingDays();
					tempPriQ.enqueue(tempMission, tempNode->getKey());
					break;

				}
				
			}
		}
		while (Emergency.dequeue(tempNode))
		{
			tempMission = tempNode->getData();
			cDay = tempMission->getFormulationDate();
			if (cDay <= d)
				tempMission->increamentWaitingDays();
			tempPriQ.enqueue(tempMission, tempNode->getKey());
		}
		while (tempPriQ.dequeue(tempNode))
		{
			tempMission = tempNode->getData();
			Emergency.enqueue(tempMission, tempNode->getKey());
		}
	}
}
void Action::checkWaiting_P(Queue<Mission>& Polar, PriQ<Rover>* roverArray, int d)
{

}
void Action::checkWaiting_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Rover>* roverArray, int d)
{

}
bool Action::assignRover_E(PriQ<Rover>* roverArray, Mission*& tempMission, char type)
{
	Node<Rover>* tempNode;
	bool test = roverArray[0].dequeue(tempNode);
	if (test)
	{
		// nen2el eel rover
		tempMission->setRover(tempNode->getData());
		return test;
	}
	if (type == 'M')
		return false;
	test = assignRover_P(roverArray, tempMission);
	if(!test)
		test = assignRover_M(roverArray, tempMission);
	return test;
}
bool Action::assignRover_P(PriQ<Rover>* roverArray, Mission*& tempMission)
{
	Node<Rover>* tempNode;
	bool test = roverArray[1].dequeue(tempNode);
	if (test)
	{
		// nen2el eel rover
		tempMission->setRover(tempNode->getData());
		
	}
	return test;

}
bool Action::assignRover_M(PriQ<Rover>* roverArray, Mission*& tempMission)
{
	Node<Rover>* tempNode;
	bool test = roverArray[2].dequeue(tempNode);
	if (test)
	{
		// nen2el eel rover
		tempMission->setRover(tempNode->getData());
		return test;
	}
	test = assignRover_E(roverArray, tempMission, 'M');
	return test;

}
