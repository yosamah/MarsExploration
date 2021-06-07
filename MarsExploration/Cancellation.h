#pragma once
#include "Event.h"
class Cancellation :
    public Event
{
private:


public:
    /* Constructor */
    Cancellation(int MissionID, int EventDay);

    virtual void Execute(HashTable<Mission>& Mountainous, PriQ<Mission>& Emergency, Queue<int>& MountainousSort, Queue<Mission>& Polar, int* Arr);
};

