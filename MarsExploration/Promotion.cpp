#include "Promotion.h"
Promotion::Promotion(int MID, int ED):Event(ED,MID)
{
}

void Promotion::Execute(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar,int* Arr)
{
	Mission* MissionToPro = new Mission('M', MissionID, -1, -1, -1, -1);
	Node<Mission>* NodeToPro = new Node<Mission>(MissionToPro, MissionID);
	bool found=Mountainous.search(NodeToPro,MissionID);
	if (found)
	{
		Mission* Temp = NodeToPro->getData();
		Mission* Promote=new Mission('E',Temp->getID(),Temp->getTargetLocation(), Temp->getMissionDuration(), Temp->getFormulationDate(), Temp->getSignificance());
		/*Priority Equation*/
		int priority = (Temp->getTargetLocation() * Temp->getMissionDuration() * Temp->getSignificance()) / (Temp->getTargetLocation() + Temp->getMissionDuration() + Temp->getSignificance());
		Emergency.enqueue(Promote,-priority); 
		Mountainous.remove(NodeToPro, MissionID);
		delete MissionToPro;
		delete NodeToPro;
	}
}