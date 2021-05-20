#pragma once
#include "Event.h"
class Formulation :
    public Event
{
    int TargetLocation;
    int MissionDuration;
    int Significance;
public:
    /* Constructor */                                                    //Initialiser list 3shan al event
    Formulation(int TargetLocation,int MissionDuration,int Significance, int MissionID, int EventDay);

    void Execute(HashTable<Mission*>* Mountainous, PriQ<Mission*>* Emergency, Queue<int>* MountainousSort, Queue<Mission*>* Polar);
};