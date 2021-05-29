#include "Action.h"


void Action::checkWaiting(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar, int d, PriQ<Rover>* roverArray)
{
	checkWaiting_E(Emergency, roverArray, d);
	checkWaiting_P(Polar, roverArray, d);
	checkWaiting_M(Mountainous, MountainousSort, roverArray, d);
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
				if (test && tempNode)
				{
					tempPriQ.enqueue(tempMission, tempNode->getKey());
					bool can = Emergency.dequeue(tempNode);
					tempMission = tempNode->getData();
					cDay = tempMission->getFormulationDate();
					if (!can)
					{
						tempNode = NULL;
						break;
					}
						
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
	Node<Mission>* tempNode;
	Mission* tempMission;
	int cDay;
	Queue<Mission> tempQ;
	while (!Polar.isEmpty())
	{
		Polar.dequeue(tempNode);
		tempMission = tempNode->getData();
		cDay = tempMission->getFormulationDate();
		if (cDay > d)
		{
			tempQ.enqueue(tempMission);
		}
		else
		{
			while (cDay <= d)
			{
				bool test = assignRover_P(roverArray, tempMission);
				if (test && tempNode)
				{
					tempQ.enqueue(tempMission);
					bool can = Polar.dequeue(tempNode);
					tempMission = tempNode->getData();
					cDay = tempMission->getFormulationDate();
					if (!can)
					{
						tempNode = NULL;
						break;
					}

				}
				else
				{
					tempMission->increamentWaitingDays();
					tempQ.enqueue(tempMission);
					break;

				}

			}
		}
	}
	while (Polar.dequeue(tempNode))
	{
		tempMission = tempNode->getData();
		cDay = tempMission->getFormulationDate();
		if (cDay <= d)
			tempMission->increamentWaitingDays();
		tempQ.enqueue(tempMission);
	}
	while (tempQ.dequeue(tempNode))
	{
		tempMission = tempNode->getData();
		Polar.enqueue(tempMission);
	}

}
void Action::checkWaiting_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Rover>* roverArray, int d)
{
	Node<Mission>* tempNode;
	Mission* tempMission;
	int cDay;
	Queue<int> tempQ;
	Node<int>* key;
	while (!MountainousSort.isEmpty())
	{
		MountainousSort.dequeue(key);
		Mountainous.remove(tempNode, *(key->getData()));
		tempMission = tempNode->getData();
		cDay = tempMission->getFormulationDate();
		if (cDay > d)
		{
			tempQ.enqueue((key->getData()));
			Mountainous.insert(tempMission, *(key->getData()));
		}
		else
		{
			while (cDay <= d)
			{
				bool test = assignRover_M(roverArray, tempMission);
				if (test && tempNode)
				{
					tempQ.enqueue((key->getData()));
					Mountainous.insert(tempMission, *(key->getData()));
					bool can = MountainousSort.dequeue(key);
					if (!can)
					{
						tempNode = NULL;
						break;
					}
					Mountainous.remove(tempNode, *(key->getData()));
					tempMission = tempNode->getData();
					cDay = tempMission->getFormulationDate();
					

				}
				else
				{
					tempMission->increamentWaitingDays();
					tempQ.enqueue((key->getData()));
					Mountainous.insert(tempMission, *(key->getData()));
					break;

				}

			}
		}
	}
	while (MountainousSort.dequeue(key))
	{
		Mountainous.remove(tempNode, *(key->getData()));
		tempMission = tempNode->getData();
		cDay = tempMission->getFormulationDate();
		if (cDay <= d)
			tempMission->increamentWaitingDays();
		tempQ.enqueue((key->getData()));
		Mountainous.insert(tempMission, *(key->getData()));
	}
	while (tempQ.dequeue(key))
	{
		MountainousSort.enqueue((key->getData()));
	}
}
	

// without maintainance
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
