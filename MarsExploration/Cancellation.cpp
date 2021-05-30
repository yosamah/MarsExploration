#include "Cancellation.h"

Cancellation::Cancellation(int MID, int ED):Event(ED,MID)
{
}

void Cancellation::Execute(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar)
{
	bool removed = false;
	Mission* MissionToRemove = new Mission('M', MissionID, -1, -1, -1, -1);
	Node<Mission>* NodeToRemove=new Node<Mission>(MissionToRemove,MissionID);
	removed=Mountainous.remove(NodeToRemove,MissionID);
	if (!removed)
	{
		delete NodeToRemove;
		delete MissionToRemove;
		return;
	}
	/*if (removed)
	{
		Node<int> *T;
		Queue<int> tempQ;
		while (!MountainousSort.isEmpty())
		{
			MountainousSort.dequeue(T);
			if (T->getKey()!= MissionID)
			{
				int Key = T->getKey();
				tempQ.enqueue(&Key);
			}
		}
		while (!tempQ.isEmpty())
		{
			tempQ.dequeue(T);
			int Key = T->getKey();
			MountainousSort.enqueue(&Key);
		}
	}*/
	delete NodeToRemove;
	delete MissionToRemove;
}
