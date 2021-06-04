#pragma once
#include "Event.h"
class Promotion :
    public Event
{

public:
    /* Constructor */  //Initialiser list 3shan al event
    Promotion(int MissionID, int EventDay);

    virtual void Execute(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar, int* Arr);

};

