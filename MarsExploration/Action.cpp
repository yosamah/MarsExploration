#include "Action.h"



void Action::checkWaiting_E(PriQ<Mission>& Emergency, PriQ<Rover>* roverArray, int d)
{
	Node<Mission>* tempNode;
	Mission* tempMission;
	int cDay;
	PriQ<Mission> tempPriQ;
	/*Checking if the waiting emergency missions list is not empty*/
	if (!Emergency.isEmpty())
	{
		Emergency.dequeue(tempNode);
		tempMission = tempNode->getData();
		cDay = tempMission->getFormulationDate();
		/*Checking if the day of the formulation is smaller than or equal the current day*/
		/*Condition was not met, enqueue the dequeued Node to a temporary Priqueue*/
		if (cDay > d)
		{
			tempPriQ.enqueue(tempMission, tempNode->getKey());

		}
		else
		{
			/* While the Condition is met, Assign a rover to the dequeued Mission*/

			while (cDay <= d)
			{
				bool test = assignRover_E(roverArray, tempMission);
				/*Checking if there is available rover to be assigned to the waiting missions*/
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
				/*If there is no suitable rover to assign then increment the waiting days*/
				else
				{
					tempMission->increamentWaitingDays();
					tempPriQ.enqueue(tempMission, tempNode->getKey());
					break;

				}

			}
		}
		/*Incrementing the rest of the missions in the waiting*/
		while (Emergency.dequeue(tempNode))
		{
			tempMission = tempNode->getData();
			cDay = tempMission->getFormulationDate();
			if (cDay <= d)
				tempMission->increamentWaitingDays();
			tempPriQ.enqueue(tempMission, tempNode->getKey());
		}
		/*Adding the rest of the list back in its original list*/
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
	/*Checking if the waiting polar missions list is not empty*/
	if (!Polar.isEmpty())
	{
		Polar.dequeue(tempNode);
		tempMission = tempNode->getData();
		cDay = tempMission->getFormulationDate();
		/*Checking if the day of the formulation is smaller than or equal the current day*/
		/*Condition was not met, enqueue the dequeued Node to a temporary queue*/
		if (cDay > d)
		{
			tempQ.enqueue(tempMission);
		}
		else
		{
			/* While Condition is met, Assign a rover to the dequeued mission*/
			while (cDay <= d)
			{
				bool test = assignRover_P(roverArray, tempMission);
				/*Checking if there is available rover to be assigned to the waiting missions*/
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
				/*If there is no suitable rover to assign then increment the waiting days*/
				else
				{
					tempMission->increamentWaitingDays();
					tempQ.enqueue(tempMission);
					break;

				}

			}
		}
	}
	/*Incrementing the rest of the missions in the waiting*/
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
	Node<Mission>* tempNode = NULL;
	Mission* tempMission;
	int cDay;
	Queue<int> tempQ;
	Node<int>* key;
	/*Checking that the mountanious queue (Keeps the order in which the missions were entered) is not empty*/
	while (!MountainousSort.isEmpty())
	{
		tempNode = NULL;
		MountainousSort.dequeue(key);
		Mountainous.remove(tempNode, *(key->getData()));
		if (tempNode)
		{
			tempMission = tempNode->getData();
			cDay = tempMission->getFormulationDate();
			/*Checking if the day of the formulation is smaller than or equal the current day*/
			/*Condition was not met, enqueue the dequeued node to a temporary queue and re-insert it in the hashtable*/
			if (cDay > d)
			{
				tempQ.enqueue((key->getData()));
				Mountainous.insert(tempMission, *(key->getData()));
				break;
			}
			else
			{
				/*Condition was met, assign a suitable rover to the dequeued mission*/
				while (cDay <= d)
				{
					bool test = assignRover_M(roverArray, tempMission);
					/*Checking if there is available rover to be assigned to the waiting missions*/
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
						/*If there is no suitable rover to assign then increment the waiting days*/
					{
						tempMission->increamentWaitingDays();
						tempQ.enqueue((key->getData()));
						Mountainous.insert(tempMission, *(key->getData()));
						break;

					}

				}
			}
		}
	}
	/*Incrementing the rest of the missions in the waiting, and adding them in order in the queue and the hashtable*/
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


bool Action::assignRover_E(PriQ<Rover>* roverArray, Mission*& tempMission, char type)
{
	Node<Rover>* tempNode;
	/*Checking if the available emergency rover priqueue is not empty*/
	bool test = roverArray[0].dequeue(tempNode);
	/*Condition was met*/
	if (test)
	{
		tempMission->setRover(tempNode->getData());
		tempNode->getData()->increamentMissionCount();
		return test;
	}
	/*This condition was added to prevent mountanious missions to continue the function
	as a mountanious mission would have already searched for a mountanious rover and not found one if it enters this function*/
	if (type == 'M')
		return false;
	/*If no emergency rovers were available for this emergency mission, check available polar rovers*/
	test = assignRover_P(roverArray, tempMission);
	if (!test)
		/*If no polar rovers were available, check available mountanious rovers*/
		test = assignRover_M(roverArray, tempMission);
	/*If all available rovers were not present, check emergency rovers in maintenance*/
	if (!test)
	{
		test = roverArray[3].dequeue(tempNode);
		/*If a rover was found in the "Emergency rovers in maintenance" priqueue, assign it to the mission*/
		if (test)
		{
			tempMission->setRover(tempNode->getData());
			tempNode->getData()->increamentMissionCount();
		}
	}
	return test;
}

bool Action::assignRover_P(PriQ<Rover>* roverArray, Mission*& tempMission)
{
	Node<Rover>* tempNode;
	/*Checking the available polar rovers priqueue is not empty*/
	bool test = roverArray[1].dequeue(tempNode);

	if (test)
	{
		/*If the available polar rovers priqueue was not empty, dequeue the rover in a temporary node, and add this rover to the mission*/
		tempMission->setRover(tempNode->getData());
		tempNode->getData()->increamentMissionCount();
	}
	if (!test)
	{
		/*If the available polar rovers priqueue is empty, check the polar rovers in maintenance */
		test = roverArray[4].dequeue(tempNode);
		/*If the polar rovers in maintenance was not empty, assign the in-maintenance rover to the mission*/
		if (test)
		{
			tempMission->setRover(tempNode->getData());
			tempNode->getData()->increamentMissionCount();
		}
	}
	return test;

}

bool Action::assignRover_M(PriQ<Rover>* roverArray, Mission*& tempMission)
{
	Node<Rover>* tempNode;
	bool test = roverArray[2].dequeue(tempNode);
	/*Checking if the available mountainious rover priqueue is not empty*/
	if (test)
	{
		/*If the available mountainious rovers priqueue was not empty, dequeue the rover in a temporary node, and add this rover to the mission*/
		tempMission->setRover(tempNode->getData());
		tempNode->getData()->increamentMissionCount();
		return test;
	}
	/*If the available mountainious rovers priqueue was empty, check available emergency rovers*/
	test = assignRover_E(roverArray, tempMission, 'M');
	if (!test)
	{
		/*If no rovers were found in the available emergency rovers priqueue, check mountainious in maintenance rovers */
		test = roverArray[5].dequeue(tempNode);
		if (test)
		{
			tempMission->setRover(tempNode->getData());
			tempNode->getData()->increamentMissionCount();
		}
	}
	return test;

}

void Action::MoveToExec_M(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Mission>& InExecution, float& Exec, float& Wait)
{
	Node<Mission>* tempNode = NULL;
	Mission* tempMission;
	int CD;
	Queue<int> tempQ;
	Node<int>* key;
	/*Checking that the waiting mountainious missions queue is not empty*/
	while (!MountainousSort.isEmpty())
	{
		/*If the condition was met, check if missions are available in the Hashtable*/
		MountainousSort.peek(key);
		bool check = Mountainous.remove(tempNode, *(key->getData()));
		if (check)
		{
			/*If the missions are found in the hashtable, check each one for a rover
			if a mission has a rover, move it to the "InExecution" priqueue, and remove it from the queue and the hashtable
			if a mission does not have a rover, then re-insert the mission into the hashtable, and break from the loop, exiting the function*/
			tempMission = tempNode->getData();
			if (tempMission->getRover())
			{
				CD = tempMission->getTotalMissionDur() + tempMission->getWaitingDay() + tempMission->getFormulationDate();//Completion day equation for the mission
				Exec += tempMission->getTotalMissionDur();
				Wait += tempMission->getWaitingDay();
				InExecution.enqueue(tempMission, CD);
				MountainousSort.dequeue(key);
			}
			else
			{
				Mountainous.insert(tempMission, *(key->getData()));
				break;
			}

		}
		else
			MountainousSort.dequeue(key);
	}

}

void Action::MoveToExec_P(Queue<Mission>& Polar, PriQ<Mission>& InExecution, float& Exec, float& Wait)
{
	Node<Mission>* tempNode;
	Mission* tempMission;
	int CD;
	Queue<Mission> tempQ;
	/*Checking that the waiting polar missions queue is not empty*/
	while (!Polar.isEmpty())
	{
		/*if condition was met, peek the first element of the queue*/
		Polar.peek(tempNode);
		tempMission = tempNode->getData();
		/*If a rover was assigned for the mission peeked, move it from the waiting polar missions queue to the "InExecution" priqueue*/
		if (tempMission->getRover())
		{
			CD = tempMission->getTotalMissionDur() + tempMission->getWaitingDay() + tempMission->getFormulationDate();//Completion day equation for the mission
			Exec += tempMission->getTotalMissionDur();
			Wait += tempMission->getWaitingDay();
			InExecution.enqueue(tempMission, CD);
			Polar.dequeue(tempNode);
		}
		else
		{
			break;
		}

	}

}

void Action::MoveToExec_E(PriQ<Mission>& Emergency, PriQ<Mission>& InExecution, float& Exec, float& Wait)
{
	Node<Mission>* tempNode;
	Mission* tempMission;
	int CD;
	PriQ<Mission> tempPriQ;
	/*Checking that the waiting polar missions priqueue is not empty*/
	while (!Emergency.isEmpty())
	{
		/*if condition was met, peek the first element of the priqueue*/
		Emergency.peek(tempNode);
		tempMission = tempNode->getData();
		/*If a rover was assigned for the mission peeked, move it from the waiting emergency missions priqueue to the "InExecution" priqueue*/
		if (tempMission->getRover())
		{
			CD = tempMission->getTotalMissionDur() + tempMission->getWaitingDay() + tempMission->getFormulationDate(); //Completion day equation for the mission
			Exec += tempMission->getTotalMissionDur();
			Wait += tempMission->getWaitingDay();
			InExecution.enqueue(tempMission, CD);
			Emergency.dequeue(tempNode);
		}
		else
		{
			break;
		}

	}
}

void Action::AutoPromote(HashTable<Mission>& Mountainous, Queue<int>& MountainousSort, PriQ<Mission>& Emergency, int AutoPro, int* StatsArr)
{
	Node<Mission>* tempNode = NULL;
	Mission* tempMission;
	int WD = -1;
	Queue<int> tempQ;
	Node<int>* key = NULL;
	/*Checking if the waiting mountainious missions queue is not empty*/
	MountainousSort.peek(key);
	if (key)
	{
		/*If condition is met, check if the waiting mission can be found in the hashtable*/
		bool check = Mountainous.search(tempNode, *(key->getData()));
		while (true)
		{
			/*If the mission was found, search the hashtable for the mission with the key returned from Peek function*/
			while (!check)
			{ /*If mission with the key returned from peek does not exist in the hashtable, remove it from the queue, and peek again to check for missions after it*/
				tempNode = NULL;
				MountainousSort.dequeue(key);
				check = MountainousSort.peek(key);
				if (check)
					check = Mountainous.search(tempNode, *(key->getData()));
				else
					break;
			}
			/*If the mission exists in the hashtable, get its waiting day(s) value on this current day*/
			if (tempNode)
			{
				tempMission = tempNode->getData();
				WD = tempMission->getWaitingDay();
			}
			else
				break;
			/*Checking if the waiting days value on the current day equals the value of the autopromotion duration*/
			if (WD == AutoPro)
			{
				/*If the condition is met, remove the function from the  queue and hashtable, and add them to the emergency waiting missions priqueue, resetting their mission type to "E"(Emergency) from "M"(Mountainious)*/
				Mountainous.remove(tempNode, *(key->getData()));
				int priority = (tempMission->getTargetLocation() * tempMission->getMissionDuration() * tempMission->getSignificance()) / (tempMission->getTargetLocation() + tempMission->getMissionDuration() + tempMission->getSignificance());//priority (Key) equation of the priqueue
				tempMission->setMissionType('E');
				Emergency.enqueue(tempMission, -priority);
				/*Incrementing the number of both emergency missions and autopromoted missions and decrementing the number of mountainious missions*/
				StatsArr[6]++;
				StatsArr[3]++;
				StatsArr[5]--;
				check = MountainousSort.peek(key);
				/*If no more missions are found, exit the function*/
				tempNode = NULL;
				if (check)
					check = Mountainous.search(tempNode, *(key->getData()));
				else
					break;

			}
			else
				break;

		}
	}

}