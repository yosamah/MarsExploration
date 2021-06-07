#include "Cancellation.h"

Cancellation::Cancellation(int MID, int ED):Event(ED,MID)
{
}

void Cancellation::Execute(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar,int * Arr)
{
	bool removed = false;
	Mission* MissionToRemove = new Mission('M', MissionID, -1, -1, -1, -1);
	Node<Mission>* NodeToRemove=new Node<Mission>(MissionToRemove,MissionID);
	removed=Mountainous.remove(NodeToRemove,MissionID);
	if (removed)
	{
		Arr[5]--;
	}
	delete NodeToRemove;
	delete MissionToRemove;
}
