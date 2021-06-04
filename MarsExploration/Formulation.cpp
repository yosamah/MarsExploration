#include "Formulation.h"
Formulation::Formulation(char MT,int TL, int MD, int Signif, int MID, int ED):Event(ED,MID)
{
    MissionType=MT;
    TargetLocation = TL;
    MissionDuration = MD;
    Significance = Signif;
}

void Formulation::Execute(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar,int * Arr)
{
    if (MissionType == 'M')
    {
        Arr[5]++;
        Mission* Mount = new Mission(MissionType, MissionID,TargetLocation,MissionDuration, EventDay, Significance);
        Mountainous.insert(Mount, MissionID);
        MountainousSort.enqueue(& MissionID);
    }
    else if (MissionType == 'P')
    {
        Arr[4]++;
        Mission* Pola = new Mission(MissionType, MissionID, TargetLocation, MissionDuration, EventDay,Significance);
        Polar.enqueue(Pola);
    }
    else if (MissionType == 'E')
    {
        Arr[3]++;
        Mission* Emerg = new Mission(MissionType, MissionID, TargetLocation, MissionDuration, EventDay, Significance);
        /*Priority Equation*/
        int priority = (TargetLocation*MissionDuration*Significance)/(TargetLocation + MissionDuration + Significance); 
        Emergency.enqueue(Emerg,-priority);
    }

}

