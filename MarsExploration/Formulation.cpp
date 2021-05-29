#include "Formulation.h"
Formulation::Formulation(char MT,int TL, int MD, int Signif, int MID, int ED):Event(ED,MID)
{
    MissionType=MT;
    TargetLocation = TL;
    MissionDuration = MD;
    Significance = Signif;
}

void Formulation::Execute(HashTable<Mission>* Mountainous, PriQ<Mission>* Emergency, Queue<int>* MountainousSort, Queue<Mission>* Polar)
{
    if (MissionType == 'M')
    {
        Mission* Mount = new Mission(MissionType, MissionID,TargetLocation,MissionDuration, EventDay, Significance);
        Mountainous->insert(Mount,Significance);
        MountainousSort->enqueue(& MissionID);
    }
    else if (MissionType == 'P')
    {
        Mission* Pola = new Mission(MissionType, MissionID, TargetLocation, MissionDuration, EventDay,Significance);
        Polar->enqueue(Pola);
    }
    else if (MissionType == 'E')
    {
        Mission* Emerg = new Mission(MissionType, MissionID, TargetLocation, MissionDuration, EventDay, Significance);
        Emergency->enqueue(Emerg,Significance);
    }

}